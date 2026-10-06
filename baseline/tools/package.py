"""Package the static Windows build and local original media for portable play."""
from pathlib import Path
import argparse
import hashlib
import json
import shutil

BASELINE = Path(__file__).resolve().parents[1]
ROOT = BASELINE.parent
NAME = 'tos-original-baseline-0.1-windows-x64'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir', type=Path, default=BASELINE / 'build-vs')
    parser.add_argument('--configuration', default='Release', choices=['Debug', 'Release'])
    parser.add_argument('--assets', type=Path, default=ROOT / 'web/assets')
    parser.add_argument('--output', type=Path, default=BASELINE / 'dist' / NAME)
    args = parser.parse_args()
    binaries = args.build_dir.resolve() / args.configuration
    output = args.output.resolve()
    assets = args.assets.resolve()
    required = ['tos_baseline.exe', 'tos_baseline_probe.exe', 'baseline_tests.exe', 'music.sf2',
                'GeneralUser-GS-LICENSE.txt', 'TinySoundFont-LICENSE.txt', 'raylib-LICENSE.txt']
    for name in required:
        if not (binaries / name).is_file():
            raise RuntimeError(f'Build output missing: {binaries / name}')
    required_assets = ['original-atlas.png', 'original-background-atlas.png',
                       'hero-down.png', 'hero-left.png', 'hero-right.png', 'hero-up.png']
    required_assets += [f'data3-{name}.png' for name in ('left', 'leftr', 'center', 'right', 'rightr',
                        'title05', 'title05r', 'open0', 'open1', 'open2')]
    required_assets += [f'data2-end{number:02}.png' for number in (*range(5, 21), 26)]
    required_assets += ['data-exe-ending-story.png', 'data-exe-ending-card.png']
    for name in required_assets:
        if not (assets / name).is_file():
            raise RuntimeError(f'Original asset missing: {assets / name}')
    if len(list((assets / 'midi').glob('*.mid'))) != 17 or len(list((assets / 'wav').glob('*.wav'))) != 8:
        raise RuntimeError('Expected the original 17 MIDI tracks and 8 WAV effects')
    output.mkdir(parents=True, exist_ok=True)
    for name in required:
        shutil.copy2(binaries / name, output / name)
    for file in assets.rglob('*'):
        if file.is_file() and file.suffix.lower() in ('.png', '.wav', '.mid'):
            target = output / 'assets' / file.relative_to(assets)
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(file, target)
    licenses = args.build_dir.resolve() / 'vcpkg_installed/x64-windows-static/share'
    for file in licenses.glob('*/copyright'):
        target = output / 'licenses' / (file.parent.name + '.txt')
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(file, target)
    for name in ('FIDELITY.md', 'THIRD_PARTY.md'):
        shutil.copy2(BASELINE / name, output / name)
    (output / 'validation').mkdir(exist_ok=True)
    for name in ('differential-report.json', 'interaction-report.json', 'callback-report.json', 'item-report.json'):
        report = json.loads((BASELINE / name).read_text(encoding='utf-8'))
        if report['passed'] != report['scenarios'] or report['failures']:
            raise RuntimeError(f'Unresolved fidelity comparisons in {name}')
        shutil.copy2(BASELINE / name, output / 'validation' / name)
    presentation_path = args.build_dir.resolve() / 'presentation-checks/presentation-report.json'
    presentation = json.loads(presentation_path.read_text(encoding='utf-8'))
    if presentation['passed'] != len(presentation['checks']) or presentation['passed'] < 131:
        raise RuntimeError('Unresolved presentation checks; run CTest before packaging')
    shutil.copy2(presentation_path, output / 'validation/presentation-report.json')
    (output / 'PLAY.txt').write_text(
        'Tower of the Sorcerer 1.2 - readable original baseline\n'
        'Start tos_baseline.exe. Keep assets/ and music.sf2 beside the executable.\n\n'
        'Arrow keys / WASD: move. Enter / Space: continue dialogue.\n'
        'Enter / Space or Continue: leave the ending card and start the backside tower.\n'
        'Left item sprites: inspect an item, then click Use or press Enter. I: inventory overlay.\n'
        'Up/Down + Enter: Orb of Flight. Esc: cancel or close an overlay.\n'
        'F6: eight save slots. F7: eight load slots. Also available from the Game menu.\n'
        'Save/load picker: 1-8 or arrows to select, Enter to save/replace/load, Esc to close.\n'
        'F5: quick save. F9: quick restore. F8: last Fairy checkpoint.\n'
        'F2: new game. M: mute. Options menu: 1x / 3x / 10x walking and animation speed.\n'
        'Hero Orb: View enemies for this floor\'s stats and damage forecasts. Scroll or use Up/Down.\n'
        'The bottom-right panel retains the last defeated enemy while you walk.\n'
        'Fairy checkpoints are saved automatically after her dialogue and animation finish.\n\n'
        'Eight independent manual files: slot-1.save through slot-8.save.\n'
        'Quick save and Fairy checkpoint are separate; replacing a file keeps its previous .bak.\n'
        'The load picker pauses pending commands. Empty/damaged slots cannot be loaded.\n'
        'Backside uses the original red panels and cycle-specific 50F Zeno branches.\n\n'
        'Default saves: %APPDATA%/TosOriginalBaseline on Windows.\n'
        'Optional command line: tos_baseline.exe --save-dir DIRECTORY\n'
        'Run baseline_tests.exe for the core regression checks.\n'
        'See FIDELITY.md for tested coverage and presentation/save differences.\n'
        'Original game/artwork: Oz & Kenichi / Shigemasa Ozawa.\n', encoding='utf-8')
    hashes = {str(file.relative_to(output)).replace('\\', '/'): hashlib.sha256(file.read_bytes()).hexdigest()
              for file in sorted(output.rglob('*')) if file.is_file() and file.name != 'package-manifest.json'}
    (output / 'package-manifest.json').write_text(json.dumps({'version': '0.1', 'files': hashes}, indent=2) + '\n', encoding='utf-8')
    archive = shutil.make_archive(str(output), 'zip', root_dir=output.parent, base_dir=output.name)
    print(f'Portable game: {output / "tos_baseline.exe"}')
    print(f'Archive: {archive}')
    print(f'{len(hashes)} files; ZIP SHA-256 {hashlib.sha256(Path(archive).read_bytes()).hexdigest()}')


if __name__ == '__main__':
    main()
