"""Package a self-contained Windows replacement with the original media layout."""
from pathlib import Path
import argparse
import hashlib
import json
import os
import re
import shutil
import zipfile
from comparison_boundary import check_skipped_calls

CPP = Path(__file__).resolve().parents[1]
ROOT = CPP.parent
NAME = 'tower-of-the-sorcerer-0.9-windows-x64'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir', type=Path, default=ROOT / 'build/cpp/vs')
    parser.add_argument('--configuration', default='Release', choices=['Debug', 'Release'])
    parser.add_argument('--original-dir', type=Path, default=Path(os.environ.get(
        'TOS_ORIGINAL_EXE', r'D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe')).parent)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/packages' / NAME)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    binaries, original, output = build / args.configuration, args.original_dir.resolve(), args.output.resolve()
    suite = json.loads((ROOT / 'build/cpp/reports/original-suite.json').read_text(encoding='utf-8'))
    if suite['cpp_probe_sha256'] != hashlib.sha256((binaries / 'tsw_probe.exe').read_bytes()).hexdigest():
        raise RuntimeError('Original comparison suite belongs to another build; run verify_original.py')
    if suite['boundary_policy_sha256'] != hashlib.sha256(Path(__file__).with_name('comparison_boundary.py').read_bytes()).hexdigest():
        raise RuntimeError('Comparison exclusions changed after verification; run verify_original.py')
    inventory = ROOT / 'reference/original/presentation/effect-inventory.json'
    if suite.get('presentation_inventory_sha256') != hashlib.sha256(inventory.read_bytes()).hexdigest():
        raise RuntimeError('Presentation recovery/review inventory changed; run verify_original.py')
    if output == original or output.is_relative_to(original):
        raise RuntimeError('Package output must be separate from the original installation')
    required = ['tsw_game.exe', 'tsw_cli.exe', 'tsw_probe.exe', 'tsw_tests.exe', 'tsw_audio_tests.exe', 'tsw_verify.exe',
                'GeneralUser-GS-LICENSE.txt', 'TinySoundFont-LICENSE.txt', 'raylib-LICENSE.txt', 'miniaudio-LICENSE.txt']
    for name in required:
        if not (binaries / name).is_file():
            raise RuntimeError(f'Build output missing: {binaries / name}')
    for folder in ('Data3', 'Data2', 'Midi', 'Wav'):
        if not (original / folder).is_dir():
            raise RuntimeError(f'Original media directory missing: {original / folder}')
    output.mkdir(parents=True, exist_ok=True)
    for name in required:
        shutil.copy2(binaries / name, output / ('TSW.exe' if name == 'tsw_game.exe' else name))
    for folder in ('Data', 'Data3', 'Data2', 'Midi', 'Wav'):
        if not (original / folder).is_dir():
            continue
        for file in (original / folder).iterdir():
            if file.is_file() and file.suffix.lower() in ('.bmp', '.oz', '.wav', '.mid'):
                target = output / folder / file.name
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(file, target)
    licenses = ROOT / 'build/dependencies/vcpkg_installed/x64-windows-static/share'
    dependencies = {'raylib', 'glfw3', 'stb', 'miniaudio', 'catch2', 'glaze', 'cgltf',
                    'dirent', 'drlibs', 'mmx', 'nanosvg', 'qoi'}
    for notice in (output / 'licenses').glob('*.txt'):
        if notice.stem not in dependencies:
            notice.unlink()
    for file in licenses.glob('*/copyright'):
        if file.parent.name not in dependencies:
            continue
        target = output / 'licenses' / (file.parent.name + '.txt')
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(file, target)
    shutil.copy2(CPP / 'THIRD_PARTY.md', output / 'THIRD_PARTY.md')
    fidelity = (CPP / 'FIDELITY.md').read_text(encoding='utf-8')
    fidelity = re.sub(r'\[([^]]+)\]\(\.\./docs/[^)]+\)', r'\1', fidelity)
    (output / 'FIDELITY.md').write_text(fidelity, encoding='utf-8')
    validation = output / 'validation'
    validation.mkdir(exist_ok=True)
    for name in ('differential', 'interaction', 'callback', 'item', 'save', 'quirk', 'flight', 'ui-sequence'):
        source = ROOT / 'build/cpp/reports' / f'{name}-report.json'
        report = json.loads(source.read_text(encoding='utf-8'))
        if suite['reports'].get(source.name) != hashlib.sha256(source.read_bytes()).hexdigest():
            raise RuntimeError(f'Comparison report changed after verification: {source.name}')
        if report['passed'] != report['scenarios'] or report['failures']:
            raise RuntimeError(f'Unresolved fidelity comparisons in {source.name}')
        boundary = check_skipped_calls(report['skipped_original_calls'])
        if boundary['unreviewed_calls'] or boundary['effectful_skips']:
            raise RuntimeError(f'Unreviewed comparison boundary in {source.name}: {boundary}')
        if name == 'flight' and report['cpp_probe_sha256'] != hashlib.sha256((binaries / 'tsw_probe.exe').read_bytes()).hexdigest():
            raise RuntimeError('Flight evidence belongs to a different compiled probe; rerun verify_original.py')
        shutil.copy2(source, validation / source.name)
    for folder, name, minimum in [('presentation-checks', 'presentation-report.json', 131),
                                   ('asset-checks', 'asset-report.json', 71),
                                   ('window-checks', 'window-report.json', 6)]:
        source = build / folder / name
        report = json.loads(source.read_text(encoding='utf-8'))
        if report['passed'] < minimum or ('checks' in report and report['passed'] != len(report['checks'])):
            raise RuntimeError(f'Unresolved {name}; run CTest before packaging')
        shutil.copy2(source, validation / name)
    (output / 'PLAY.txt').write_text(
        'Tower of the Sorcerer 1.2 - faithful C++ implementation\n'
        'Start TSW.exe beside Data3/, Data2/, Midi/ and Wav/.\n'
        'The original BMP/OZ/MIDI/WAV files keep their names and formats.\n'
        'Ending pictures and the MIDI soundfont are embedded; no extra runtime is needed.\n\n'
        'Startup: New game, Load game, Play replay and Settings. Mouse or Up/Down + Enter selects.\n'
        'Esc returns to the main menu; Continue keeps your current game or paused replay.\n'
        'Settings persist in Savedat/settings.json: game/replay speeds, recording and audio mute.\n\n'
        'For an existing installation, keep the old EXE as TSW.original.exe, then copy the new TSW.exe.\n'
        'F6/F7 write and read the same Savedat/save1.dat through save8.dat files.\n'
        'New saves use the original 6957-byte records and original shared-Zeno load rules.\n'
        'Fairy snapshots use Savedat/save0.dat and retain the original raw checksum words.\n'
        'Original preferences and rankings are not imported.\n\n'
        'Arrows / WASD: walk. Enter / Space: continue dialogue and the ending card.\n'
        'Click owned items or press I for inventory. Flight: Up/Down, Enter to travel, Esc to cancel.\n'
        'F6 / F7: eight save / load slots. 1-8 or arrows: select. Enter: confirm. Esc: close.\n'
        'F5 / F9: quick save / restore. F8: completed Fairy checkpoint.\n'
        'F2: new game. M: mute. Settings: 1x / 3x / 10x walking and animation speed.\n'
        'Saves: Savedat/ beside the EXE. Replace keeps a .bak. No other folders are searched.\n'
        'Optional: --assets DIRECTORY (original or PNG layout), --save-dir DIRECTORY, --load FILE.\n'
        'Opt-in recording: Settings > Record new games, then New game; --record overrides the launch preference.\n'
        'Recorded saves have a .replay.jsonl companion; keep it together with its save.\n'
        'A load without a recording continues unrecorded.\n'
        'Normal numbered saves already use the original format, filenames and folder.\n\n'
        'Visual replay: Play replay selects a saved recording, accepts a pasted path or a dropped JSONL file.\n'
        'Direct launch: --replay FILE. Space: pause/resume. Left/Right: previous/next input.\n'
        'Home: restart paused. T: take over. -/+: replay and animation speed. O: settings. Esc: menu.\n'
        'Speeds: 0.25x / 0.5x / 1x / 2x / 3x / 5x / 10x. Next finishes one input, then pauses.\n'
        'Rewind reconstructs earlier commands; long recordings can take longer. Music restarts after rewind.\n'
        'Watching never writes gameplay saves. Takeover records the consumed prefix when recording is enabled.\n'
        'Full-package headless replay: tsw_cli replay FILE.\n\n'
        'See FIDELITY.md for evidence and limits, THIRD_PARTY.md and the license files for attribution.\n',
        encoding='utf-8')
    hashes = {file.relative_to(output).as_posix(): hashlib.sha256(file.read_bytes()).hexdigest()
              for file in sorted(output.rglob('*')) if file.is_file() and file.name != 'package-manifest.json'}
    (output / 'package-manifest.json').write_text(
        json.dumps({'version': '0.9', 'layout': 'original', 'files': hashes}, indent=2) + '\n', encoding='utf-8')
    archive = shutil.make_archive(str(output), 'zip', root_dir=output.parent, base_dir=output.name)
    drop_in = output.parent / 'tower-of-the-sorcerer-0.9-drop-in.zip'
    with zipfile.ZipFile(drop_in, 'w', compression=zipfile.ZIP_DEFLATED) as package:
        for file in sorted(output.rglob('*')):
            relative = file.relative_to(output)
            if file.is_file() and (len(relative.parts) == 1 and file.name not in
                                   ('tsw_tests.exe', 'tsw_cli.exe', 'tsw_probe.exe', 'tsw_audio_tests.exe', 'tsw_verify.exe', 'package-manifest.json')
                                   or relative.parts[0] == 'licenses'):
                package.write(file, relative.as_posix())
    print(f'Replacement EXE: {output / "TSW.exe"}')
    print(f'Original-layout package: {archive}')
    print(f'EXE and licenses only: {drop_in}')
    print(f'{len(hashes)} files; ZIP SHA-256 {hashlib.sha256(Path(archive).read_bytes()).hexdigest()}')


if __name__ == '__main__':
    main()
