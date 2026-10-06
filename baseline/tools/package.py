"""Package a self-contained Windows replacement with the original media layout."""
from pathlib import Path
import argparse
import hashlib
import json
import os
import re
import shutil
import zipfile

BASELINE = Path(__file__).resolve().parents[1]
NAME = 'tos-original-baseline-0.4-windows-x64'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir', type=Path, default=BASELINE / 'build-vs')
    parser.add_argument('--configuration', default='Release', choices=['Debug', 'Release'])
    parser.add_argument('--original-dir', type=Path, default=Path(os.environ.get(
        'TOS_ORIGINAL_EXE', r'D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe')).parent)
    parser.add_argument('--output', type=Path, default=BASELINE / 'dist' / NAME)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    binaries, original, output = build / args.configuration, args.original_dir.resolve(), args.output.resolve()
    if output == original or output.is_relative_to(original):
        raise RuntimeError('Package output must be separate from the original installation')
    required = ['tos_baseline.exe', 'tos_baseline_probe.exe', 'baseline_tests.exe',
                'GeneralUser-GS-LICENSE.txt', 'TinySoundFont-LICENSE.txt', 'raylib-LICENSE.txt']
    for name in required:
        if not (binaries / name).is_file():
            raise RuntimeError(f'Build output missing: {binaries / name}')
    for folder in ('Data3', 'Data2', 'Midi', 'Wav'):
        if not (original / folder).is_dir():
            raise RuntimeError(f'Original media directory missing: {original / folder}')
    output.mkdir(parents=True, exist_ok=True)
    for name in required:
        shutil.copy2(binaries / name, output / ('TSW.exe' if name == 'tos_baseline.exe' else name))
    for folder in ('Data', 'Data3', 'Data2', 'Midi', 'Wav'):
        if not (original / folder).is_dir():
            continue
        for file in (original / folder).iterdir():
            if file.is_file() and file.suffix.lower() in ('.bmp', '.oz', '.wav', '.mid'):
                target = output / folder / file.name
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(file, target)
    licenses = build / 'vcpkg_installed/x64-windows-static/share'
    for file in licenses.glob('*/copyright'):
        target = output / 'licenses' / (file.parent.name + '.txt')
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(file, target)
    shutil.copy2(BASELINE / 'THIRD_PARTY.md', output / 'THIRD_PARTY.md')
    fidelity = (BASELINE / 'FIDELITY.md').read_text(encoding='utf-8')
    fidelity = re.sub(r'\[([^]]+)\]\(\.\./docs/[^)]+\)', r'\1', fidelity)
    (output / 'FIDELITY.md').write_text(fidelity, encoding='utf-8')
    validation = output / 'validation'
    validation.mkdir(exist_ok=True)
    for name in ('differential', 'interaction', 'callback', 'item', 'save'):
        source = BASELINE / f'{name}-report.json'
        report = json.loads(source.read_text(encoding='utf-8'))
        if report['passed'] != report['scenarios'] or report['failures']:
            raise RuntimeError(f'Unresolved fidelity comparisons in {source.name}')
        shutil.copy2(source, validation / source.name)
    for folder, name, minimum in [('presentation-checks', 'presentation-report.json', 131),
                                   ('asset-checks', 'asset-report.json', 71)]:
        source = build / folder / name
        report = json.loads(source.read_text(encoding='utf-8'))
        if report['passed'] < minimum or ('checks' in report and report['passed'] != len(report['checks'])):
            raise RuntimeError(f'Unresolved {name}; run CTest before packaging')
        shutil.copy2(source, validation / name)
    (output / 'PLAY.txt').write_text(
        'Tower of the Sorcerer 1.2 - faithful C++ baseline\n'
        'Start TSW.exe beside Data3/, Data2/, Midi/ and Wav/.\n'
        'The original BMP/OZ/MIDI/WAV files keep their names and formats.\n'
        'Ending pictures and the MIDI soundfont are embedded; no extra runtime is needed.\n\n'
        'For an existing installation, keep the old EXE as TSW.original.exe, then copy the new TSW.exe.\n'
        'F6/F7 write and read the same Savedat/save1.dat through save8.dat files.\n'
        'New saves use the original 6957-byte records and original shared-Zeno load rules.\n'
        'Original preferences and rankings are not imported.\n\n'
        'Arrows / WASD: walk. Enter / Space: continue dialogue and the ending card.\n'
        'Click owned items or press I for inventory. Flight: Up/Down, Enter to travel, Esc to cancel.\n'
        'F6 / F7: eight save / load slots. 1-8 or arrows: select. Enter: confirm. Esc: close.\n'
        'F5 / F9: quick save / restore. F8: completed Fairy checkpoint.\n'
        'F2: new game. M: mute. Options: 1x / 3x / 10x walking and animation speed.\n'
        'Saves: Savedat/ beside the EXE. Replace keeps a .bak. No other folders are searched.\n'
        'Optional: --assets DIRECTORY (original or PNG layout), --save-dir DIRECTORY, --load FILE.\n'
        'Export or convert: TSW.exe --load OLD_FILE --export-original save1.dat\n'
        'Normal numbered saves already use the original format, filenames and folder.\n\n'
        'See FIDELITY.md for evidence and limits, THIRD_PARTY.md and the license files for attribution.\n',
        encoding='utf-8')
    hashes = {file.relative_to(output).as_posix(): hashlib.sha256(file.read_bytes()).hexdigest()
              for file in sorted(output.rglob('*')) if file.is_file() and file.name != 'package-manifest.json'}
    (output / 'package-manifest.json').write_text(
        json.dumps({'version': '0.4', 'layout': 'original', 'files': hashes}, indent=2) + '\n', encoding='utf-8')
    archive = shutil.make_archive(str(output), 'zip', root_dir=output.parent, base_dir=output.name)
    drop_in = output.parent / 'tos-original-baseline-0.4-drop-in.zip'
    with zipfile.ZipFile(drop_in, 'w', compression=zipfile.ZIP_DEFLATED) as package:
        for file in sorted(output.rglob('*')):
            relative = file.relative_to(output)
            if file.is_file() and (len(relative.parts) == 1 and file.name not in
                                   ('baseline_tests.exe', 'tos_baseline_probe.exe', 'package-manifest.json')
                                   or relative.parts[0] == 'licenses'):
                package.write(file, relative.as_posix())
    print(f'Replacement EXE: {output / "TSW.exe"}')
    print(f'Original-layout package: {archive}')
    print(f'EXE and licenses only: {drop_in}')
    print(f'{len(hashes)} files; ZIP SHA-256 {hashlib.sha256(Path(archive).read_bytes()).hexdigest()}')


if __name__ == '__main__':
    main()
