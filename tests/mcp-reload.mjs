import assert from 'node:assert/strict';
import { spawn } from 'node:child_process';
import { copyFileSync, existsSync, mkdtempSync, renameSync, rmSync, writeFileSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { basename, dirname, join, resolve } from 'node:path';
import { createInterface } from 'node:readline';

const root = resolve(import.meta.dirname, '..');
const binary = resolve(root, 'target/release', process.platform === 'win32' ? 'tos.exe' : 'tos');
assert(existsSync(binary), `Build the native MCP backend first: ${binary}`);
const temporary = mkdtempSync(join(tmpdir(), 'tos-mcp-reload-'));
const clients = [];

// A real campaign keeps failures independent of the original adventure's
// opening route. The trade changes counters, flags, inventory and presentation
// while leaving an active conversation whose private pending tile is needed
// for the next choose action.
const campaign = {
  id: 'mcp-reload-fixture', title: 'Reload regression fixture', width: 4, height: 1,
  start: { floor: 1, x: 0, y: 0, hp: 100, attack: 10, defense: 10, gold: 10,
    inventory: ['hero_orb', 'wisdom_orb', 'sword_5', 'sacred_shield'] },
  floors: [{ id: 1, title: 'Regression room', tiles: [0, 1, 2, 5] }],
  tiles: {
    0: { name: 'Road', kind: 'floor' },
    1: { name: 'Yellow key', kind: 'key', key: 'yellow', amount: 1 },
    3: { name: 'Iron Sword', kind: 'equipment', item: 'sword_1', stat: 'attack', amount: 10 },
    4: { name: 'Iron Shield', kind: 'equipment', item: 'shield_1', stat: 'defense', amount: 10 },
    5: { name: 'Slime', kind: 'enemy', enemy: 'slime' },
    7: { name: 'Sacred Sword', kind: 'equipment', item: 'sword_5', stat: 'attack', amount: 100 },
    8: { name: 'Sacred Shield', kind: 'equipment', item: 'sacred_shield', stat: 'defense', amount: 100 },
    2: {
      name: 'Keeper', kind: 'npc', text: 'Keep this conversation open while rebuilding.',
      dialogue_ids: [62, 63],
      after_text: { flag: 'token_received', text: 'The token will restore 2 HP when used.' },
      offers: [{ id: 'trade', label: 'Take the token', cost: 3, once: true, effects: [
        { type: 'add_stat', stat: 'hp', amount: 7 },
        { type: 'give_item', item: 'reload_token' },
        { type: 'flag', flag: 'token_received' },
        { type: 'message', text: 'The token is yours.' },
      ] }, { id: 'ask_more', label: 'Ask another question', cost: 0, once: true,
        conditions: [{ type: 'flag', flag: 'token_received' }],
        effects: [{ type: 'message', text: 'Remember this second answer after returning.', dialogue_id: 64 }] }],
    },
  },
  enemies: { slime: { name: 'Slime', hp: 1, attack: 0, defense: 0, gold: 0 } },
  rules: { empty_tile: 0, wisdom_dialogue_range: [62, 85], forecast_requires_item: 'hero_orb' },
  items: { reload_token: { name: 'Reload token', description: 'Restore 2 HP.', consumable: true,
    effects: [{ type: 'add_stat', stat: 'hp', amount: 2 }] } },
  events: [{ id: 'first_key', trigger: { type: 'step', floor: 1, x: 1, y: 0 },
    effects: [{ type: 'flag', flag: 'key_visited' },
      { type: 'give_item', item: 'sword_1' }, { type: 'give_item', item: 'shield_1' },
      { type: 'battle_at', floor: 1, x: 3, y: 0 }] }],
};

function jsonFile(path, value) {
  writeFileSync(path, `${JSON.stringify(value)}\n`);
}

function publish(path, value) {
  // Deployment uses a fresh activation even when a previous binary failed.
  // Replace the complete manifest so the bridge never observes a partial write.
  const next = `${path}.next`;
  jsonFile(next, value);
  renameSync(next, path);
}

function client(program, args) {
  const process = spawn(program, args, { cwd: root, stdio: ['pipe', 'pipe', 'pipe'] });
  const requests = new Map();
  const notifications = [];
  const invalidOutput = [];
  let nextId = 1;
  let stderr = '';
  process.stderr.on('data', chunk => { stderr += chunk; });
  const lines = createInterface({ input: process.stdout });
  lines.on('line', line => {
    let message;
    try { message = JSON.parse(line); }
    catch { invalidOutput.push(line); return; }
    const request = requests.get(message.id);
    if (request) {
      requests.delete(message.id);
      clearTimeout(request.timeout);
      request.resolve(message);
    } else if (!Object.hasOwn(message, 'id') && message.method) {
      notifications.push(message);
    } else {
      invalidOutput.push(message);
    }
  });
  process.on('error', error => {
    for (const request of requests.values()) {
      clearTimeout(request.timeout);
      request.reject(error);
    }
    requests.clear();
  });
  const exited = new Promise(resolveExit => process.once('exit', (code, signal) => {
    for (const request of requests.values()) {
      clearTimeout(request.timeout);
      request.reject(new Error(`MCP exited (${code ?? signal}): ${stderr}`));
    }
    requests.clear();
    resolveExit({ code, signal });
  }));
  const connection = {
    process, notifications, invalidOutput,
    rpc(method, params = {}) {
      return new Promise((resolveRequest, reject) => {
        const id = nextId++;
        const timeout = setTimeout(() => {
          requests.delete(id);
          reject(new Error(`MCP ${method} timed out: ${stderr}`));
        }, 15_000);
        requests.set(id, { resolve: resolveRequest, reject, timeout });
        process.stdin.write(`${JSON.stringify({ jsonrpc: '2.0', id, method, params })}\n`);
      });
    },
    notify(method, params = {}) {
      process.stdin.write(`${JSON.stringify({ jsonrpc: '2.0', method, params })}\n`);
    },
    async initialize() {
      const response = await this.rpc('initialize', {
        protocolVersion: '2025-11-25', capabilities: {},
        clientInfo: { name: 'reload-integration-test', version: '1' },
      });
      assert(!response.error, JSON.stringify(response));
      assert.equal(response.result.protocolVersion, '2025-11-25');
      this.notify('notifications/initialized');
      return response.result;
    },
    async tool(name, arguments_ = {}) {
      const response = await this.rpc('tools/call', { name, arguments: arguments_ });
      assert(!response.error, JSON.stringify(response));
      assert.equal(response.result.isError, false, JSON.stringify(response));
      return response;
    },
    async close() {
      process.stdin.end();
      let timer;
      const stopped = await Promise.race([
        exited,
        new Promise(resolveStop => { timer = setTimeout(() => resolveStop(null), 3000); }),
      ]);
      clearTimeout(timer);
      if (!stopped) {
        process.kill();
        await exited;
      }
      lines.close();
      for (const request of requests.values()) clearTimeout(request.timeout);
    },
  };
  clients.push(connection);
  return connection;
}

const content = response => response.result.structuredContent;
const reload = response => response.result._meta?.runtime_reload;

function expectReload(response, status) {
  assert(reload(response), `Expected reload metadata: ${JSON.stringify(response)}`);
  assert.equal(reload(response).status, status, JSON.stringify(response));
  if (status === 'succeeded') assert.equal(reload(response).session_restored, true);
}

async function runtime(connection, previous, deployment) {
  const info = content(await connection.tool('mcp_runtime'));
  assert.equal(info.bridge_pid, connection.process.pid);
  assert.equal(typeof info.worker_pid, 'number');
  assert(info.worker_pid > 0);
  assert.equal(info.current.version, deployment.version);
  assert.equal(info.current.activation, deployment.activation);
  assert.equal(info.current.executable, resolve(temporary, deployment.executable));
  if (previous) assert.notEqual(info.worker_pid, previous.worker_pid);
  return info;
}

async function prepareConversation(connection, developer = true) {
  await connection.tool('game_action', { action: { type: 'move', direction: 'right' } });
  await connection.tool('game_action', { action: { type: 'move', direction: 'right' } });
  const response = await connection.tool('game_action', { action: { type: 'choose', choice: 'trade' } });
  const state = content(response);
  assert.equal(state.player.hp, 107);
  assert.equal(state.player.gold, 7);
  assert.equal(state.player.keys.yellow, 1);
  assert.deepEqual(state.player.inventory, developer
    ? ['hero_orb', 'wisdom_orb', 'sword_5', 'sacred_shield', 'sword_1', 'shield_1', 'reload_token']
    : ['hero_orb', 'wisdom_orb', 'reload_token']);
  assert.equal(state.equipment.weapon.id, 'sword_1');
  assert.equal(state.equipment.shield.id, 'shield_1');
  assert.equal(state.abilities.field_magic_protection, true);
  assert.deepEqual(state.last_encounter, { cycle: 1, floor: 1, x: 3, y: 0, tile: 5,
    enemy_name: 'Slime', hp: 1, attack: 0, defense: 0 });
  assert(state.pending_interaction);
  if (developer) {
    assert(state.flags.includes('token_received'));
    assert(state.flags.includes('key_visited'));
  }
  assert.equal(state.last_action.ok, true);
  assert(state.last_action.presentation.some(effect => effect.text === 'The token is yours.'));
  assert.deepEqual(state.journal.map(entry => entry.text), [
    'Keep this conversation open while rebuilding.',
    'The token will restore 2 HP when used.',
  ]);
  assert.equal(state.journal[0].title, 'Keeper');
  assert.deepEqual(state.journal.map(entry => entry.cycle), [1, 1]);
  const orbHelp = state.inventory_items.find(item => item.id === 'hero_orb').usage;
  assert.equal(orbHelp.activation, 'passive');
  assert.equal(orbHelp.consumable, false);
  assert(!Object.hasOwn(orbHelp, 'command'));
  assert.equal(typeof orbHelp.description, 'string');
  assert(orbHelp.description.length > 0);
  const tokenHelp = state.inventory_items.find(item => item.id === 'reload_token').usage;
  assert.equal(tokenHelp.activation, 'use_item');
  assert.equal(tokenHelp.consumable, true);
  assert.deepEqual(tokenHelp.command, { type: 'use_item', item: 'reload_token' });
  assert.equal(typeof tokenHelp.description, 'string');
  assert(tokenHelp.description.length > 0);
  assert(Array.isArray(tokenHelp.restrictions));
  return state;
}

async function checkCatalogParity(connection, native) {
  const bridgedTools = (await connection.rpc('tools/list')).result.tools;
  const nativeTools = (await native.rpc('tools/list')).result.tools;
  assert.equal(bridgedTools.filter(tool => tool.name === 'mcp_runtime').length, 1);
  assert.deepEqual(bridgedTools.filter(tool => tool.name !== 'mcp_runtime'), nativeTools);
  assert(!bridgedTools.some(tool => tool.name.startsWith('runtime/')));
  const bridgedResources = await connection.rpc('resources/list');
  const nativeResources = await native.rpc('resources/list');
  assert.deepEqual(bridgedResources.result, nativeResources.result);
}

try {
  const campaignPath = join(temporary, 'campaign.json');
  const manifestPath = join(temporary, 'active.json');
  jsonFile(campaignPath, campaign);
  const executableA = join(temporary, `tos-a${process.platform === 'win32' ? '.exe' : ''}`);
  const executableB = join(temporary, `tos-b${process.platform === 'win32' ? '.exe' : ''}`);
  copyFileSync(binary, executableA);
  copyFileSync(binary, executableB);
  const first = { version: 'test-a', activation: 'initial', executable: basename(executableA) };
  const second = { version: 'test-b', activation: 'rebuild-1', executable: basename(executableB) };
  publish(manifestPath, first);
  const bridge = client(process.execPath, [join(root, 'tools/mcp-server.mjs'),
    '--manifest', manifestPath, '--campaign', campaignPath, '--developer']);
  const native = client(binary, ['mcp', '--campaign', campaignPath, '--developer']);
  const [bridgeInit] = await Promise.all([bridge.initialize(), native.initialize()]);
  assert.equal(bridgeInit.capabilities.tools.listChanged, true);
  await checkCatalogParity(bridge, native);
  const beforeRuntime = await runtime(bridge, null, first);
  const before = await prepareConversation(bridge);
  const beforeSave = content(await bridge.tool('save_game')).save;
  assert.equal(typeof beforeSave, 'string');
  const decodedSave = JSON.parse(beforeSave);
  assert.equal(decodedSave.shop_visits['1:2:0'], 1);
  assert.equal(decodedSave.shop_visits['1:2:0:offer:trade'], 1);
  assert.equal(decodedSave.event_counts.first_key, 1);
  assert.deepEqual(decodedSave.pending_tile, [1, 2, 0]);
  assert.deepEqual(decodedSave.journal.map(({ dialogue_id, ...entry }) => entry), before.journal);

  publish(manifestPath, second);
  const restored = await bridge.tool('game_state');
  expectReload(restored, 'succeeded');
  assert.deepEqual(content(restored), before, 'Reload must preserve presentation and pending dialogue exactly');
  assert.equal(content(await bridge.tool('save_game')).save, beforeSave);
  const secondRuntime = await runtime(bridge, beforeRuntime, second);
  assert.equal(secondRuntime.last_reload.status, 'succeeded');
  await checkCatalogParity(bridge, native);
  assert.equal(bridge.notifications.filter(message => message.method === 'notifications/tools/list_changed').length, 0,
    'An unchanged native catalog must not produce a tools/list_changed notification');

  // An invalid publication is diagnosed without making the current playable
  // session unavailable or misreporting a previous successful activation.
  writeFileSync(manifestPath, '{this is not a deployment manifest');
  const invalidManifest = await bridge.tool('game_state');
  expectReload(invalidManifest, 'unchanged');
  assert.equal(reload(invalidManifest).session_lost, false);
  assert.deepEqual(content(invalidManifest), before);
  assert.deepEqual(content(await bridge.tool('game_state')), before);
  const afterInvalidManifest = await runtime(bridge, null, second);
  assert.equal(afterInvalidManifest.worker_pid, secondRuntime.worker_pid);
  assert.equal(afterInvalidManifest.last_reload.status, 'unchanged');

  // A candidate loads the new authored revision but cannot consume the old
  // checkpoint. Its rejected action must never reach the still-running worker.
  jsonFile(campaignPath, { ...campaign, title: 'Incompatible revision' });
  const incompatible = { ...first, activation: 'bad-campaign' };
  publish(manifestPath, incompatible);
  const rejected = await bridge.rpc('tools/call', {
    name: 'game_action', arguments: { action: { type: 'choose', choice: 'leave' } },
  });
  assert.equal(rejected.result.isError, true, JSON.stringify(rejected));
  expectReload(rejected, 'unchanged');
  assert.deepEqual(content(await bridge.tool('game_state')), before);
  const stillSecond = await runtime(bridge, null, second);
  assert.equal(stillSecond.worker_pid, secondRuntime.worker_pid);
  assert.equal(stillSecond.last_reload.status, 'unchanged');
  assert.equal(content(await bridge.tool('save_game')).save, beforeSave);

  // The same rejected activation is skipped even after its external campaign
  // is repaired; a fresh activation is the explicit retry signal.
  jsonFile(campaignPath, campaign);
  const skipped = await bridge.tool('game_state');
  assert(!reload(skipped), 'Do not keep retrying the same failed activation');
  assert.equal((await runtime(bridge, null, second)).worker_pid, secondRuntime.worker_pid);
  const retry = { ...first, activation: 'retry-campaign' };
  publish(manifestPath, retry);
  const retried = await bridge.tool('game_state');
  expectReload(retried, 'succeeded');
  assert.deepEqual(content(retried), before);
  const retryRuntime = await runtime(bridge, secondRuntime, retry);

  const missing = { version: 'missing', activation: 'bad-executable', executable: 'does-not-exist.exe' };
  publish(manifestPath, missing);
  const badExecutable = await bridge.rpc('tools/call', { name: 'game_state', arguments: {} });
  assert.equal(badExecutable.result.isError, true, JSON.stringify(badExecutable));
  expectReload(badExecutable, 'unchanged');
  assert.deepEqual(content(await bridge.tool('game_state')), before);
  assert.equal((await runtime(bridge, null, retry)).worker_pid, retryRuntime.worker_pid);

  const finalDeployment = { ...second, activation: 'rebuild-2' };
  publish(manifestPath, finalDeployment);
  const finalRestored = await bridge.tool('game_state');
  expectReload(finalRestored, 'succeeded');
  assert.deepEqual(content(finalRestored), before);
  await runtime(bridge, retryRuntime, finalDeployment);
  const continued = content(await bridge.tool('game_action', { action: { type: 'choose', choice: 'leave' } }));
  assert.equal(continued.pending_interaction, null, 'Pending dialogue must remain actionable after reload');
  assert.equal(continued.last_action.ok, true);
  assert.equal(continued.steps, before.steps, 'Dialogue choices must not add movement steps');
  assert.deepEqual(continued.player, before.player);

  // The default player profile's opaque checkpoint table belongs to the
  // session too, and must survive backend replacement along with its world.
  const playerManifestPath = join(temporary, 'player-active.json');
  publish(playerManifestPath, first);
  const player = client(process.execPath, [join(root, 'tools/mcp-server.mjs'),
    '--manifest', playerManifestPath, '--campaign', campaignPath]);
  const playerNative = client(binary, ['mcp', '--campaign', campaignPath]);
  await Promise.all([player.initialize(), playerNative.initialize()]);
  await checkCatalogParity(player, playerNative);
  const playerBefore = await prepareConversation(player, false);
  const checkpoint = content(await player.tool('save_game'));
  assert.equal(typeof checkpoint.checkpoint, 'string');
  assert(!Object.hasOwn(checkpoint, 'save'), 'Player checkpoints must not disclose serialized hidden state');
  const extraSpeech = content(await player.tool('game_action', { action: { type: 'choose', choice: 'ask_more' } }));
  assert.equal(extraSpeech.journal.length, playerBefore.journal.length + 1);
  await player.tool('game_action', { action: { type: 'choose', choice: 'leave' } });
  for (let index = 0; index < 125; index += 1) {
    await player.tool('game_action', { action: { type: 'use_item', item: 'hero_orb' } });
  }
  const playerBeforeReload = content(await player.tool('game_state'));
  assert.equal(playerBeforeReload.log.length, 100);
  assert(playerBeforeReload.log.every(line => line === 'The item is always active.'));
  assert.deepEqual(playerBeforeReload.journal, extraSpeech.journal,
    'Encountered dialogue must survive eviction from the activity log');
  publish(playerManifestPath, second);
  const playerRestored = await player.tool('game_state');
  expectReload(playerRestored, 'succeeded');
  assert.deepEqual(content(playerRestored), playerBeforeReload);
  const newCheckpoint = content(await player.tool('save_game'));
  assert.notEqual(newCheckpoint.checkpoint, checkpoint.checkpoint,
    'Restoring the checkpoint table must also preserve its next ID');
  const checkpointRestored = content(await player.tool('load_game', { checkpoint: checkpoint.checkpoint }));
  assert.deepEqual(checkpointRestored.player, playerBefore.player);
  assert.deepEqual(checkpointRestored.pending_interaction, playerBefore.pending_interaction);
  assert.equal(checkpointRestored.steps, playerBefore.steps);
  assert.deepEqual(checkpointRestored.journal, playerBefore.journal,
    'Loading an opaque checkpoint restores its encountered journal, including removal of later speech');
  const playerContinued = content(await player.tool('game_action', { action: { type: 'choose', choice: 'leave' } }));
  assert.equal(playerContinued.pending_interaction, null);
  assert.equal(playerContinued.last_action.ok, true);
  assert.deepEqual(playerContinued.journal, playerBefore.journal);
  const tokenUsed = content(await player.tool('game_action', {
    action: checkpointRestored.inventory_items.find(item => item.id === 'reload_token').usage.command,
  }));
  assert.equal(tokenUsed.last_action.ok, true, 'Owned-item help supplies an executable MCP action');
  assert.equal(tokenUsed.player.hp, playerBefore.player.hp + 2);
  assert(!tokenUsed.player.inventory.includes('reload_token'), 'Consumption help matches the committed action');

  // Original manual-save gating must not prevent the private checkpoint needed
  // to replace an early-game worker while keeping the connection alive.
  const lockedCampaignPath = join(temporary, 'locked-save-campaign.json');
  const lockedCampaign = structuredClone(campaign);
  lockedCampaign.start.inventory = [];
  lockedCampaign.rules.save_requires_hero_orb = true;
  jsonFile(lockedCampaignPath, lockedCampaign);
  const lockedManifest = join(temporary, 'locked-save-active.json');
  publish(lockedManifest, first);
  const lockedPlayer = client(process.execPath, [join(root, 'tools/mcp-server.mjs'),
    '--manifest', lockedManifest, '--campaign', lockedCampaignPath]);
  await lockedPlayer.initialize();
  await lockedPlayer.tool('game_action', { action: { type: 'move', direction: 'right' } });
  const lockedBefore = content(await lockedPlayer.tool('game_state'));
  assert.equal(lockedBefore.save_unlocked, false);
  assert.equal(lockedBefore.journal_unlocked, false);
  assert.equal(lockedBefore.forecasts_unlocked, false);
  assert.equal(lockedBefore.last_encounter.hp, 1, 'Contact stats are available before Hero');
  assert.equal(lockedBefore.equipment.weapon.id, 'sword_1');
  assert.equal((await lockedPlayer.rpc('tools/call', { name: 'save_game', arguments: {} })).result.isError, true);
  const lockedRuntime = await runtime(lockedPlayer, null, first);
  publish(lockedManifest, second);
  const lockedReload = await lockedPlayer.tool('game_state');
  expectReload(lockedReload, 'succeeded');
  assert.deepEqual(content(lockedReload), lockedBefore,
    'Private worker replacement is available before earning the Hero Orb');
  await runtime(lockedPlayer, lockedRuntime, second);
  assert.equal((await lockedPlayer.rpc('tools/call', { name: 'save_game', arguments: {} })).result.isError, true);

  // No private migration methods may be routed through the public connection.
  for (const method of ['runtime/checkpoint', 'runtime/restore']) {
    const denied = await player.rpc(method, { path: join(temporary, 'must-not-exist.json') });
    assert.equal(denied.error?.code, -32601, JSON.stringify(denied));
  }
  assert(!existsSync(join(temporary, 'must-not-exist.json')));

  const seedPath = join(temporary, 'startup-save.json');
  const legacySave = { ...decodedSave };
  delete legacySave.journal;
  jsonFile(seedPath, legacySave);
  const seeded = client(process.execPath, [join(root, 'tools/mcp-server.mjs'),
    '--manifest', manifestPath, '--campaign', campaignPath, '--save', seedPath]);
  await seeded.initialize();
  const seededState = content(await seeded.tool('game_state'));
  assert.deepEqual(seededState.player, playerBefore.player, '--save must reach the native worker at startup');
  assert.deepEqual(seededState.equipment, before.equipment);
  assert.deepEqual(seededState.last_encounter, before.last_encounter);
  assert.deepEqual(seededState.pending_interaction, playerBefore.pending_interaction);
  assert.deepEqual(seededState.journal, [], 'Legacy startup saves load without inventing lost encounter history');

  // A startup import is consumed once: later replacements use the live
  // checkpoint even if the original portable save has been removed.
  rmSync(seedPath);
  publish(manifestPath, { ...finalDeployment, activation: 'reload-without-startup-file' });
  const seededReloaded = await seeded.tool('game_state');
  expectReload(seededReloaded, 'succeeded');
  assert.deepEqual(content(seededReloaded), seededState);

  // A crash must be reported distinctly from a healthy old worker. The bridge
  // stays responsive for diagnostics and never guesses/retries a lost action.
  const alive = content(await bridge.tool('mcp_runtime'));
  assert.equal(alive.worker_running, true);
  assert.equal(alive.worker_error, null);
  process.kill(alive.worker_pid);
  const crashed = await bridge.rpc('tools/call', { name: 'game_state', arguments: {} });
  assert.equal(crashed.result.isError, true);
  const dead = content(await bridge.tool('mcp_runtime'));
  assert.equal(dead.worker_running, false);
  assert.equal(typeof dead.worker_error, 'string');

  for (const connection of clients) assert.deepEqual(connection.invalidOutput, [], 'MCP stdout must contain only JSON-RPC');
  console.log('MCP reload integration passed: stable connections, exact world/dialogue/presentation/journal restore, revision/executable rollback, invalid publication recovery, activation retry, catalog parity, legacy startup saves, owned-item usage help, and opaque player checkpoints.');
} finally {
  await Promise.all(clients.map(connection => connection.close()));
  assert.equal(dirname(temporary), resolve(tmpdir()));
  assert(basename(temporary).startsWith('tos-mcp-reload-'));
  rmSync(temporary, { recursive: true, force: true });
}
