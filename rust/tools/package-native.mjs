// Local distribution helper: generated media/binaries never enter Git.
import { cpSync, existsSync, mkdirSync, copyFileSync, writeFileSync } from 'node:fs';
import { resolve } from 'node:path';
const root = resolve(import.meta.dirname, '..');
const output = resolve(root, '../build/rust/dist/native');
const executable = process.platform === 'win32' ? 'tos-ui.exe' : 'tos-ui';
const source = resolve(root, '../build/rust/target/release', executable);
if (!existsSync(source) || !existsSync(resolve(root, 'web/assets/original-atlas.png'))) {
  throw new Error('Run ../tools/setup_assets.py and npm run build first.');
}
mkdirSync(output, { recursive: true });
copyFileSync(source, resolve(output, executable));
cpSync(resolve(root, 'web/assets'), resolve(output, 'assets'), { recursive: true });
cpSync(resolve(root, 'web/fonts'), resolve(output, 'fonts'), { recursive: true });
writeFileSync(resolve(output, 'README.txt'), `Launch ${executable}. Use --editor for the campaign editor.\nOriginal assets belong to Oz & Kenichi; this local package is not a license to redistribute them.\nSaves use your application-data folder under tos-rust.\n`);
console.log(`Local native package: ${output}`);
