"""Compare the original folder-copy handler at explicit stream and Windows boundaries."""
import argparse
import hashlib
import itertools
import json
from pathlib import Path

import pefile
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ECX, UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_EFLAGS

from verify_delphi_startup import StartupRunner
from verify_delphi_graphics import ROOT, WORK, ORIGINAL_HASH, digest, symbols, first_difference, data_symbols
from compare_delphi_routines import memory_stream_vmt, REVIEWED
import delphi_routine_layout as layout


NAMES = ['option' + suffix + '.dat' for suffix in ('', '1', '11', '2', '21', '3', '31', '4', '41', '5', '51')]
CALLS = {0x402C0C: 'TObject.Create', 0x403570: '@LStrLAsg', 0x40B26C: 'TMemoryStream.LoadFromFile',
         0x40B19C: 'TCustomMemoryStream.SaveToFile', 0x4135A4: 'TControl.GetText', 0x4034FC: '@LStrArrayClr'}


class FolderRunner(StartupRunner):
    def __init__(self, pe, **kwargs):
        super().__init__(pe, **kwargs)
        mapping = {} if self.original else symbols(pe, kwargs['map_path'])
        self.stream_vmt = memory_stream_vmt(pe)
        self.boundaries.update(CALLS if self.original else {mapping[name]: name for name in CALLS.values()})
        start = 0x4402E8 if self.original else mapping['TForm4.Button1Click']
        stop = int(REVIEWED[start]['successor'], 16) if self.original else next(a for a in sorted(set(mapping.values())) if a > start)
        self.entries['folder'] = start
        layout.DONE_EXCEPT = 0x403268 if self.original else mapping['@DoneExcept']
        if not self.original:
            layout.DISPATCHERS |= {mapping[n] for n in ('@HandleFinally', '@HandleAnyException')}
        self.allowed.update(at for at, _ in layout.trace_layout(pe, start, stop)['records'])
        self.holder = 0x660000
        self.names[self.holder] = 'TForm4'
        self.names[self.holder + 0x1000] = 'TForm4.memo1'
        self.holder_global = 0x48C50C if self.original else data_symbols(pe, kwargs['map_path'])['DataHolderForm']
        self.modal_offset = 0x12C if self.original else 0x128

    def seed_folder(self, destination, name, missing=None):
        self.seed_case([b'X:\\source', b'X:\\assets', name])
        self.destination = destination
        self.self = self.holder
        self.write32(self.holder_global, self.holder)
        self.write32(self.holder + (0x1C8 if self.original else 0x1C4), self.holder + 0x1000)
        self.write32(self.holder + self.modal_offset, 0)
        self.files = {'X:\\source\\' + filename: bytes((i * 137 + j) % 256 for i in range(size))
                      for j, (filename, size) in enumerate(zip(NAMES, (10, 288, 37, 288, 1000, 288, 0, 288, 128, 288, 9)))}
        if missing:
            del self.files['X:\\source\\' + missing]
        self.stream = None
        self.trace.clear()

    def write(self, u, access, at, size, value, data):
        if hasattr(self, 'holder') and at == self.holder + self.modal_offset and size == 4:
            self.trace.append(['modal_result', value])
            return
        super().write(u, access, at, size, value, data)

    def observe(self, name):
        a, d = (self.u.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX))
        if name == 'TObject.Create':
            assert a == self.stream_vmt and d & 255 == 1
            self.stream = b''
            self.trace.append(['stream_create'])
            self.ret(value=0x690000)
        elif name == '@LStrLAsg':
            super().observe('@LStrAsg')
        elif name == 'TControl.GetText':
            assert a == self.holder + 0x1000
            self.put_string(d, self.destination)
            self.trace.append(['destination', self.destination.decode()])
            self.ret()
        elif name in ('TMemoryStream.LoadFromFile', 'TCustomMemoryStream.SaveToFile'):
            assert a == 0x690000 and self.stream is not None
            path = self.string(d).decode()
            if name.endswith('LoadFromFile'):
                self.trace.append(['stream_load', path])
                if path not in self.files:
                    self.stop('missing-source:' + path)
                    return
                self.stream = self.files[path]
            else:
                self.files[path] = self.stream
                self.trace.append(['stream_save', path, len(self.stream), hashlib.sha256(self.stream).hexdigest()])
            self.ret()
        elif name == 'TObject.Free' and a == 0x690000:
            self.stream = None
            self.trace.append(['stream_free'])
            self.ret()
        else:
            super().observe(name)

    def run_folder(self):
        stack, stop = 0x3FE000, 0x3FF000
        self.u.mem_write(0x3FB000, bytes(0x4000))
        self.write32(0, 0)
        self.write32(stack, stop)
        for reg, value in ((UC_X86_REG_ESP, stack), (UC_X86_REG_EAX, self.holder),
                           (UC_X86_REG_EDX, 0), (UC_X86_REG_ECX, 0), (UC_X86_REG_EFLAGS, 2)):
            self.u.reg_write(reg, value)
        self.u.emu_start(self.entries['folder'], stop, count=100000)
        if self.terminal is None:
            assert self.u.reg_read(UC_X86_REG_EIP) == stop
            assert self.u.reg_read(UC_X86_REG_ESP) == stack + 4 and self.read32(0) == 0
        return dict(trace=self.trace, memo=[x.hex() for x in self.memo],
                    saved=None if self.saved is None else [x.hex() for x in self.saved],
                    files={n: v.hex() for n, v in sorted(self.files.items())},
                    modal_result=self.read32(self.holder + self.modal_offset), terminal=self.terminal)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--candidate', type=Path, default=WORK / 'game/Tower.exe')
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    original = ROOT / 'build/research/TSW.exe'
    assert digest(original) == ORIGINAL_HASH
    cases, transcript = [], hashlib.sha256()
    for destination, name, missing in itertools.product((b'X:\\target', b'X:\\source'),
                                                       (b'', b'Player name'), (None, *NAMES)):
        # Fresh runners keep modeled memo/allocator state independent across cases.
        old = FolderRunner(pefile.PE(str(original)), original=True)
        new = FolderRunner(pefile.PE(str(args.candidate)), map_path=args.candidate.with_suffix('.map'))
        for runner in (old, new):
            runner.seed_folder(destination, name, missing)
        expected, actual = old.run_folder(), new.run_folder()
        assert expected == actual, first_difference(expected['trace'], actual['trace'])
        inputs = [destination.decode(), name.decode(), missing]
        cases.append(dict(inputs=inputs, passed=True, terminal=expected['terminal']))
        transcript.update(json.dumps([inputs, expected], sort_keys=True).encode())
        if missing is None:
            assert expected['modal_result'] == 1 and expected['saved'] == [destination.hex(), b'X:\\assets'.hex(), name.hex()]
            for filename in NAMES:
                assert expected['files'][destination.decode() + '\\' + filename] == expected['files']['X:\\source\\' + filename]
        old.pe.close()
        new.pe.close()
    report = dict(original_sha256=ORIGINAL_HASH, candidate_sha256=digest(args.candidate),
                  comparisons=len(cases), passed=True, transcript_sha256=transcript.hexdigest(), cases=cases,
                  limits='Real game handler and memo getter/clear bodies execute. Stream/file and Windows calls are observers; missing-source cases stop at the failing load, before exception unwinding.')
    output = WORK / 'reports/folder-report.json'
    content = json.dumps(report, indent=2) + '\n'
    if args.check:
        assert output.read_text() == content, 'Stale folder report'
    else:
        output.write_text(content)
    print(json.dumps({k: v for k, v in report.items() if k != 'cases'}))


if __name__ == '__main__':
    main()
