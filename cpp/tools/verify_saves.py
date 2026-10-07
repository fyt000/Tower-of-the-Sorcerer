"""Compare C++ save records and Zeno reconstruction with the original x86 routines.

Only file I/O, the overwrite dialog and VCL presentation are mocked. The original
checksum loops and reconstruction instructions execute in Unicorn. Fixtures and
outputs stay in the build tree; the installed executable is read only.
"""
from pathlib import Path
import argparse
import hashlib
import json
import os
import random
import struct
import subprocess

import capstone
import pefile
import unicorn
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX,
                              UC_X86_REG_EIP, UC_X86_REG_ESI, UC_X86_REG_ESP)

ROOT = Path(__file__).resolve().parents[2]
HASH = '41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779'
HERO, MAP, MONSTERS = 0x4b8688, 0x4b8934, 0x489910
MAP_BYTES, HERO_BYTES, SAVE_BYTES = 6273, 684, 6957
STOP = 0x6ffff0
CLUES = [272, 276, 220, 224, 228, 236, 280, 288, 292, 296, 300, 244,
         304, 308, 312, 248, 316, 252, 320, 324, 256, 328, 260, 332]
# Words not represented by named C++ gameplay state must survive rewriting.
OPAQUE = [48, 52, 336, 356, 604, 608, 612, 644, 648, 652, 668, 672, 676, 680]


def pack_words(values):
    return struct.pack('<' + 'I' * len(values), *(v & 0xffffffff for v in values))


class Original:
    def __init__(self, path):
        self.pe = pefile.PE(str(path))
        if hashlib.sha256(self.pe.__data__).hexdigest() != HASH:
            raise RuntimeError('Original executable hash mismatch')
        self.image = self.pe.get_memory_mapped_image()
        self.disassembler = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.skipped = set()
        self.read_sizes = set()
        self.write_sizes = set()

    def memory(self):
        machine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        machine.mem_map(0, 0x300000)
        machine.mem_map(0x400000, 0x300000)
        machine.mem_write(0x400000, self.image)
        machine.reg_write(UC_X86_REG_EAX, 0x200000)
        machine.reg_write(UC_X86_REG_ESP, 0x6ff000)
        machine.mem_write(0x6ff000, pack_words([STOP]))
        return machine

    def run(self, entry, maps=None, hero=None, file=None, stop_at=None):
        machine = self.memory()
        if maps is not None:
            machine.mem_write(MAP, maps)
        if hero is not None:
            machine.mem_write(HERO, hero)
        position, writes, accepted, stopped = 0, [], False, False

        def hook(uc, address, size, _):
            nonlocal position, accepted, stopped
            if address == STOP:
                stopped = True
                uc.emu_stop()
                return
            if address == stop_at:
                accepted = file is not None
                stopped = True
                uc.emu_stop()
                return
            if file is not None and address in (0x47e8f7, 0x47e99a):
                stopped = True
                uc.emu_stop()  # Invalid checksum/sentinel, before the save0 fallback.
                return
            ins = next(self.disassembler.disasm(bytes(uc.mem_read(address, size)), address))
            if ins.mnemonic != 'call':
                return
            target = int(ins.op_str, 16)
            if target == 0x454de8 and file is not None:
                accepted = stopped = True
                uc.emu_stop()
                return
            cleanup = 0
            if target == 0x404254:  # Delphi BlockWrite(file, EDX buffer, ECX count, result*)
                length = uc.reg_read(UC_X86_REG_ECX)
                writes.append(bytes(uc.mem_read(uc.reg_read(UC_X86_REG_EDX), length)))
                self.write_sizes.add(length)
                cleanup = 4
            elif target == 0x4041f0:
                length = uc.reg_read(UC_X86_REG_ECX)
                self.read_sizes.add(length)
                if file is None or len(file) - position < length:
                    stopped = True
                    uc.emu_stop()
                    return
                uc.mem_write(uc.reg_read(UC_X86_REG_EDX), file[position:position + length])
                position += length
                cleanup = 4
            elif target == 0x42cec8:
                cleanup = 4
                uc.reg_write(UC_X86_REG_EAX, 6)  # Yes in the overwrite dialog.
            elif target not in (0x40414d, 0x40458d, 0x4045a4, 0x4042b8,
                                0x402710, 0x44cb34, 0x4034dc):
                raise RuntimeError(f'Unexpected original call {target:#x} at {address:#x}')
            self.skipped.add(hex(target))
            uc.reg_write(UC_X86_REG_ESP, uc.reg_read(UC_X86_REG_ESP) + cleanup)
            uc.reg_write(UC_X86_REG_EIP, address + size)

        hook_id = machine.hook_add(unicorn.UC_HOOK_CODE, hook)
        machine.emu_start(entry, STOP, count=20000)
        machine.hook_del(hook_id)
        if not stopped and machine.reg_read(UC_X86_REG_EIP) != STOP:
            raise RuntimeError(f'Original save probe exhausted its instruction budget at {machine.reg_read(UC_X86_REG_EIP):#x}')
        if file is None:
            if [len(chunk) for chunk in writes] != [MAP_BYTES, HERO_BYTES]:
                raise RuntimeError('Original writer did not emit the two expected records')
            return b''.join(writes)
        if not accepted:
            return None
        # Run the actual load-time Zeno reconstruction, skipping preceding UI refresh.
        machine.reg_write(UC_X86_REG_ESI, HERO)
        machine.emu_start(0x455b49, 0x455b9f, count=100)
        return {'maps': bytes(machine.mem_read(MAP, MAP_BYTES)),
                'hero': bytes(machine.mem_read(HERO, HERO_BYTES)),
                'monsters': [list(struct.unpack('<4i', machine.mem_read(MONSTERS + 16*i, 16)))
                             for i in range(33)], 'consumed': position}

    def write(self, maps, hero):
        return self.run(0x47eadc, maps, hero)

    def load(self, file):
        return self.run(0x47e7d4, file=file)

    def write_checkpoint(self, maps, hero):
        # Fairy's two BlockWrites, after score/rank updates and before its UI message.
        return self.run(0x47ade1, maps, hero, stop_at=0x47ae26)

    def load_checkpoint(self, file):
        # The original raw save0 read used for recovery, without slot checksum validation.
        return self.run(0x47e948, file=file, stop_at=0x47e98b)


class Cpp:
    def __init__(self, exe):
        self.process = subprocess.Popen([str(exe)], stdin=subprocess.PIPE,
                                        stdout=subprocess.PIPE, text=True)

    def run(self, *commands):
        self.process.stdin.write('\n'.join(commands) + '\nsnapshot\n')
        self.process.stdin.flush()
        result = json.loads(self.process.stdout.readline())
        if 'error' in result:
            raise RuntimeError(result['error'])
        return result

    def rejected(self, path):
        self.process.stdin.write(f'load "{path.as_posix()}"\nsnapshot\nforecast 61 0\n')
        self.process.stdin.flush()
        first = json.loads(self.process.stdout.readline())
        unchanged = json.loads(self.process.stdout.readline()) if 'error' in first else first
        boundary = json.loads(self.process.stdout.readline())
        if set(boundary) != {'penetrates', 'damage', 'hits'}:
            raise RuntimeError('C++ probe lost its command boundary')
        return 'error' in first, unchanged

    def close(self):
        self.process.stdin.close()
        if self.process.wait(timeout=10):
            raise RuntimeError('C++ probe failed')


def expected_snapshot(record, original):
    words = list(struct.unpack('<171i', record[MAP_BYTES:SAVE_BYTES]))
    value = lambda offset: words[offset // 4]
    return {
        'hero': words[:12] + [0, 0] + words[14:17],
        'items': words[17:32], 'equipment': words[32:42],
        'flags': [0] * 11 + words[91:148],
        'hints': [value(offset) for offset in CLUES],
        'merchant_used': words[42:54], 'old_man_heard': [value(i) for i in (264, 268, 284)],
        'flight': [value(632), value(664), value(352)], 'music': value(360),
        'fairy': [value(i) for i in (340, 344, 348)] + [False],
        'cycle': [value(636), value(640), value(624)],
        'reward_flags': [value(i) for i in (592, 596, 600, 616)],
        'maps': [list(record[123*i + 2:123*(i+1)]) for i in range(51)],
        'monsters': original['monsters'], 'queue': [], 'dialogue': -1,
    }


def main():
    (ROOT / 'build/cpp/reports').mkdir(parents=True, exist_ok=True)
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe', type=Path, default=ROOT/'build/cpp/vs/Release/tsw_probe.exe')
    parser.add_argument('--original-exe', type=Path, default=Path(os.environ.get(
        'TOS_ORIGINAL_EXE', r'D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe')))
    parser.add_argument('--fixtures', type=Path, default=ROOT/'build/cpp/vs/save-checks')
    parser.add_argument('--report', type=Path, default=ROOT/'build/cpp/reports/save-report.json')
    args = parser.parse_args()
    original, cpp = Original(args.original_exe), Cpp(args.probe)
    directory = args.fixtures.resolve()
    if directory == args.original_exe.parent.resolve() or directory.is_relative_to(args.original_exe.parent.resolve()):
        raise RuntimeError('Fixture output must be separate from the original installation')
    directory.mkdir(parents=True, exist_ok=True)
    cases, failures = [], []

    def check(name, condition):
        cases.append(name)
        if not condition:
            failures.append(name)

    raw_maps = (ROOT/'data/original-map-bytes.bin').read_bytes()
    rng = random.Random(0x47eadc)
    try:
        for cycle, later in ((0, 0), (43, 0), (43, 1)):
            for sealed in (0, 1):
                for facing in range(1, 5):
                    name = f'cycle-{cycle}-{later}/seal-{sealed}/facing-{facing}'
                    hero = [0] * 171
                    put = lambda offset, value: hero.__setitem__(offset // 4, value)
                    hero[:12] = [987654, 12345, 2345, 123456, 49, 50, 5, 4, 3, 5, 7, 19]
                    for offset, value in ((56, 3), (60, 4), (64, 5), (340, 54321), (344, 7), (348, 3),
                                          (352, facing), (360, facing), (620, 1), (624, sealed),
                                          (628, -4), (632, facing % 3), (636, cycle), (640, later), (664, 2)):
                        put(offset, value)
                    for index in range(15):
                        put(68 + 4 * index, (2 if index == 0 else 3 if index == 7 else index % 2))
                    for offset in list(range(128, 216, 4)) + list(range(364, 592, 4)) + [592, 596, 600, 616]:
                        put(offset, rng.randrange(2))
                    for offset in CLUES + [216, 264, 268, 284]:
                        put(offset, rng.randrange(3))
                    for offset in OPAQUE:
                        put(offset, rng.getrandbits(32))
                    maps = bytearray(raw_maps)
                    for floor in range(51):
                        maps[floor * 123] = (floor + facing) % 121
                        maps[floor * 123 + 1] = (floor + facing * 2) % 121
                        maps[floor * 123 + 2 + (floor + facing) % 121] = 6
                    file = original.write(bytes(maps), pack_words(hero))
                    old = original.load(file)
                    check(name + '/original-accepts', old is not None and old['consumed'] == SAVE_BYTES)
                    path = directory / 'original.dat'
                    path.write_bytes(file)
                    actual = cpp.run('reset', f'load "{path.as_posix()}"')
                    expected = expected_snapshot(file, old)
                    check(name + '/all-imported-fields', all(actual[key] == value for key, value in expected.items()))
                    output = directory / 'roundtrip.dat'
                    cpp.run(f'save "{output.as_posix()}"')
                    check(name + '/exact-roundtrip', output.read_bytes() == file)
                    check(name + '/original-reads-cpp', original.load(output.read_bytes())['monsters'] == actual['monsters'])
                    cpp.run('set hp 456789', 'set sealed 0', 'item 7 2', 'flag 51 1', 'hint 12 2', 'tile 49 27 6',
                            f'save "{output.as_posix()}"')
                    edited_hero = list(struct.unpack('<171I', file[MAP_BYTES:]))
                    edited_maps = bytearray(file[:MAP_BYTES])
                    for offset, value in ((0, 456789), (624, 0), (96, 2), (524, 1), (304, 2)):
                        edited_hero[offset // 4] = value
                    edited_maps[49 * 123 + 2 + 27] = 6
                    check(name + '/edited-writer-matches', output.read_bytes() ==
                          original.write(bytes(edited_maps), pack_words(edited_hero)))

        # Fairy keeps the same records and their existing checksum words in save0.dat.
        manual_file = directory / 'manual.dat'
        cpp.run('reset', f'save "{manual_file.as_posix()}"')
        manual = manual_file.read_bytes()
        edited = list(struct.unpack('<171I', manual[MAP_BYTES:]))
        edited[0] = 4567
        edited[636 // 4], edited[640 // 4], edited[624 // 4] = 43, 1, 1
        expected = original.write_checkpoint(manual[:MAP_BYTES], pack_words(edited))
        checkpoint = directory / 'save0.dat'
        cpp.run('set hp 4567', 'set cycle 43', 'set later 1', 'set sealed 1',
                f'save-checkpoint "{checkpoint.as_posix()}"')
        check('Fairy/writer-matches-original', checkpoint.read_bytes() == expected)
        check('Fairy/checksum-words-preserved', checkpoint.read_bytes()[MAP_BYTES + 656:MAP_BYTES + 664] ==
              manual[MAP_BYTES + 656:MAP_BYTES + 664])
        check('Fairy/raw-record-is-not-a-checksummed-slot', original.load(expected) is None)
        loaded = cpp.run('reset', f'load-checkpoint "{checkpoint.as_posix()}"')
        recovered = original.load_checkpoint(expected)
        expected_state = expected_snapshot(expected, recovered)
        check('Fairy/original-raw-reader', recovered is not None and recovered['consumed'] == SAVE_BYTES)
        check('Fairy/all-restored-fields', all(loaded[key] == value for key, value in expected_state.items()))
        rejected, unchanged = cpp.rejected(checkpoint)
        check('Fairy/slot-loader-stays-strict', rejected and unchanged == loaded)
        cpp.run(f'save "{manual_file.as_posix()}"')
        check('Fairy/manual-save-refreshes-checksums', manual_file.read_bytes() ==
              original.write(expected[:MAP_BYTES], expected[MAP_BYTES:]))

        file = manual_file.read_bytes()
        before = cpp.run(f'load "{manual_file.as_posix()}"')
        for name, offset, value in (('sentinel', MAP_BYTES + 628, 0), ('sum', MAP_BYTES + 656, 0),
                                    ('alternating-sum', MAP_BYTES + 660, 0), ('hero-tamper', MAP_BYTES, 1)):
            corrupt = bytearray(file)
            corrupt[offset] ^= value or 0x40
            path = directory / 'invalid.dat'
            path.write_bytes(corrupt)
            check(name + '/original-rejects', original.load(bytes(corrupt)) is None)
            rejected, after = cpp.rejected(path)
            check(name + '/cpp-rejects-without-mutation', rejected and before == after)
        for length in (0, 75, MAP_BYTES, SAVE_BYTES - 1):
            path = directory / 'truncated.dat'
            path.write_bytes(file[:length])
            rejected, after = cpp.rejected(path)
            check(f'truncated-{length}/cpp-rejects-without-mutation', rejected and before == after)
        # The old checksum covers hero words, not maps. Valid tile changes remain readable.
        map_change = bytearray(file)
        map_change[100] = 6 if map_change[100] != 6 else 7
        path = directory / 'map-change.dat'
        path.write_bytes(map_change)
        loaded = cpp.run(f'load "{path.as_posix()}"')
        check('legacy-map-checksum-coverage', original.load(bytes(map_change)) is not None and
              loaded['maps'][0][98] == map_change[100])
        extra = directory / 'trailing-data.dat'
        extra.write_bytes(file + b'ignored by original BlockRead')
        loaded = cpp.run(f'load "{extra.as_posix()}"')
        check('original-trailing-data-behavior', original.load(extra.read_bytes())['consumed'] == SAVE_BYTES and
              loaded == before)
        # C++ checks bounds before replacing live state; original UI memory safety is not copied.
        for name, offset, value in (('floor', 16, 51), ('facing', 352, 0), ('item', 68, 3), ('cycle', 636, 44),
                                    ('bool-flag', 624, 2)):
            hero = list(struct.unpack('<171I', file[MAP_BYTES:]))
            hero[offset // 4] = value
            invalid = original.write(file[:MAP_BYTES], pack_words(hero))
            path = directory / 'invalid-state.dat'
            path.write_bytes(invalid)
            rejected, after = cpp.rejected(path)
            check(name + '/validated-before-replacement', rejected and before == after)
        for name, offset, value in (('tile', 100, 255), ('stair-landing', 0, 121)):
            maps = bytearray(file[:MAP_BYTES])
            maps[offset] = value
            path = directory / 'invalid-map.dat'
            path.write_bytes(original.write(bytes(maps), file[MAP_BYTES:]))
            rejected, after = cpp.rejected(path)
            check(name + '/validated-before-replacement', rejected and before == after)
    finally:
        cpp.close()
    report = {'original_sha256': HASH, 'probe': str(args.probe), 'scenarios': len(cases),
              'passed': len(cases) - len(failures), 'failures': failures,
              'original_blockread_sizes': sorted(original.read_sizes),
              'original_blockwrite_sizes': sorted(original.write_sizes),
              'skipped_original_calls': sorted(original.skipped), 'checks': cases,
              'limits': 'Synthetic records from the actual original writer. Original checksum and Zeno load instructions run; VCL UI and file system calls are mocked. No historical player save was available.'}
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8', newline='\n')
    print(f'{report["passed"]}/{len(cases)} save comparisons passed; {args.report}', flush=True)
    if failures:
        print(json.dumps(failures, indent=2))
        return 1
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
