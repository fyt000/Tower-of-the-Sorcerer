"""Exercise the actual native stdio MCP process and its CLI replay/save compatibility."""
import argparse
import json
from pathlib import Path
from queue import Queue, Empty
import subprocess
from tempfile import TemporaryDirectory
from threading import Thread


class Client:
    def __init__(self, cli, *options):
        self.process = subprocess.Popen(
            [str(cli), 'mcp', *options], stdin=subprocess.PIPE,
            stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, encoding='utf-8',
            creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0))
        self.messages = Queue()
        self.next_id = 0
        self.reader = Thread(target=self.read, daemon=True)
        self.reader.start()

    def read(self):
        for line in self.process.stdout:
            self.messages.put(line)

    def send(self, message):
        self.process.stdin.write(json.dumps(message, ensure_ascii=False) + '\n')
        self.process.stdin.flush()

    def rpc(self, method, params=None):
        self.next_id += 1
        self.send({'jsonrpc': '2.0', 'id': self.next_id, 'method': method,
                   'params': {} if params is None else params})
        try:
            line = self.messages.get(timeout=10)
        except Empty as error:
            raise AssertionError(f'No response to {method}') from error
        response = json.loads(line)
        assert response['jsonrpc'] == '2.0' and response['id'] == self.next_id, response
        return response

    def initialize(self, version='2025-11-25'):
        response = self.rpc('initialize', {
            'protocolVersion': version, 'capabilities': {},
            'clientInfo': {'name': 'cpp-stdio-check', 'version': '1'}})
        assert response['result']['protocolVersion'] == version, response
        assert response['result']['serverInfo']['name'] == 'tower-of-the-sorcerer-cpp'
        self.send({'jsonrpc': '2.0', 'method': 'notifications/initialized'})

    def tool(self, name, **arguments):
        if name in ('game_state', 'game_action', 'new_game', 'load_game', 'replay_game', 'simulate_actions'):
            arguments.setdefault('detail', 'full')
        if name == 'export_replay' and 'path' in arguments:
            arguments.setdefault('include_replay', True)
        response = self.rpc('tools/call', {'name': name, 'arguments': arguments})
        assert 'error' not in response, response
        result = response['result']
        assert result['isError'] is False, result
        assert json.loads(result['content'][0]['text']) == result['structuredContent']
        return result['structuredContent']

    def close(self):
        self.process.stdin.close()
        try:
            code = self.process.wait(timeout=5)
            assert code == 0, self.process.stderr.read()
            self.reader.join(timeout=1)
            assert self.messages.empty(), 'Unexpected messages on stdout'
        finally:
            if self.process.poll() is None:
                self.process.kill()
                self.process.wait(timeout=5)
            self.process.stdout.close()
            self.process.stderr.close()


def same_game(native, mcp):
    for name in ('inventory', 'map_floor', 'map', 'flight', 'dead'):
        assert native[name] == mcp[name], (name, native[name], mcp[name])
    for name, value in native['hero'].items():
        assert mcp['hero'][name] == value, (name, value, mcp['hero'][name])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cli', type=Path, required=True)
    args = parser.parse_args()
    cli = args.cli.resolve()
    clients = []
    with TemporaryDirectory(prefix='tsw-mcp-') as directory:
        temporary = Path(directory)
        try:
            ordinary = Client(cli)
            clients.append(ordinary)
            ordinary.initialize('2025-03-26')
            assert len(ordinary.rpc('tools/list')['result']['tools']) == 10
            initial = ordinary.tool('game_state')
            assert initial['width'] == 11 and not initial['save_unlocked']
            assert 'floors' not in initial
            refused = ordinary.rpc('tools/call', {'name': 'save_game', 'arguments': {}})
            assert refused['result']['isError'] is True
            assert ordinary.tool('game_state') == initial

            client = Client(cli, '--developer')
            clients.append(client)
            client.initialize()
            tools = client.rpc('tools/list')['result']['tools']
            assert len(tools) == 11 and all(t['inputSchema']['type'] == 'object' for t in tools)
            initial = client.tool('game_state')
            assert len(initial['floors']) == 51 and len(initial['monsters']) == 33
            assert client.tool('plan_path', x=5, y=9)['directions'] == ['up']
            predicted = client.tool('simulate_actions', actions=[{'type': 'move', 'direction': 'up'}])
            assert client.tool('game_state') == initial
            moved = client.tool('game_action', action={'type': 'move', 'direction': 'up'})
            assert moved == predicted and moved['hero']['y'] == 9
            checkpoint = client.tool('save_game')['checkpoint']
            client.tool('new_game')
            assert client.tool('load_game', checkpoint=checkpoint) == moved

            save_path = temporary / '测试存档.dat'
            client.tool('save_game', path=str(save_path))
            assert save_path.stat().st_size == 6957
            assert Path(str(save_path) + '.replay.jsonl').is_file()
            loaded = client.tool('load_game', path=str(save_path))
            assert loaded['hero']['y'] == 9 and loaded['recording']['active']
            restarted = Client(cli, '--developer', '--load', str(save_path))
            clients.append(restarted)
            restarted.initialize()
            assert restarted.tool('game_state')['hero'] == loaded['hero']

            replay_path = temporary / 'branch.jsonl'
            exported = client.tool('export_replay', path=str(replay_path))
            assert replay_path.read_text(encoding='utf-8') == exported['replay']
            native = subprocess.run([str(cli), 'replay', str(replay_path)], check=True,
                                    capture_output=True, text=True, encoding='utf-8')
            replayed = client.tool('replay_game', path=str(replay_path))
            same_game(json.loads(native.stdout), replayed)
            prefix = client.tool('replay_game', replay=exported['replay'], limit=2)
            assert prefix['replay']['executed'] == 2 and not prefix['replay']['complete']
            assert prefix['hero']['y'] == 9
            client.tool('game_action', action={'type': 'move', 'direction': 'left'})
            branch = client.tool('export_replay')['replay']
            assert len(branch.splitlines()) == 3
            assert json.loads(branch.splitlines()[-1]) == {'type': 'move', 'direction': 'left'}
            before = client.tool('game_state')
            invalid = client.rpc('tools/call', {'name': 'replay_game', 'arguments': {
                'replay': branch + '{"type":"flight_up"}\n'}})
            assert invalid['result']['isError'] is True
            assert client.tool('game_state') == before

            fixture = Path(__file__).resolve().parents[2] / 'tests/replays/first-floor-door.jsonl'
            for limit in (3, 8):
                native = subprocess.run([str(cli), 'replay', str(fixture), '--limit', str(limit)],
                                        check=True, capture_output=True, text=True, encoding='utf-8')
                observed = client.tool('replay_game', path=str(fixture), limit=limit)
                same_game(json.loads(native.stdout), observed)
            resources = client.rpc('resources/list')['result']['resources']
            assert len(resources) == 3
            state = client.rpc('resources/read', {'uri': 'tos://state'})['result']['contents'][0]
            assert json.loads(state['text']) == client.tool('game_state', detail='compact')
            assert client.rpc('missing')['error']['code'] == -32601
        finally:
            for client in reversed(clients):
                client.close()
    print('MCP stdio passed: lifecycle, 10/11 tools, state/inspection, simulation isolation, checkpoints, '
          'Unicode native save/load/restart, replay prefixes/takeover, CLI parity and resources/errors.')


if __name__ == '__main__':
    main()
