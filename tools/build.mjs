import { existsSync, readFileSync, mkdirSync, copyFileSync } from 'node:fs';
import { spawnSync } from 'node:child_process';
import { join, resolve } from 'node:path';
import { homedir } from 'node:os';

const root = resolve(import.meta.dirname, '..');
const cargoBin = join(homedir(), '.cargo', 'bin');
const env = { ...process.env, PATH: `${cargoBin}${process.platform === 'win32' ? ';' : ':'}${process.env.PATH}` };
function run(program, args) {
  const result = spawnSync(program, args, { cwd: root, env, stdio: 'inherit' });
  if (result.error) throw result.error;
  if (result.status !== 0) process.exit(result.status || 1);
}
const cargo = join(cargoBin, process.platform === 'win32' ? 'cargo.exe' : 'cargo');
run(cargo, ['build', '--release', '-p', 'tos-wasm', '--target', 'wasm32-unknown-unknown']);
const lock = readFileSync(join(root, 'Cargo.lock'), 'utf8');
const version = lock.match(/name = "wasm-bindgen"\r?\nversion = "([^"]+)"/)[1];
let bindgen = join(cargoBin, process.platform === 'win32' ? 'wasm-bindgen.exe' : 'wasm-bindgen');
const local = join(root, 'tools', `wasm-bindgen-${version}-x86_64-pc-windows-msvc`, 'wasm-bindgen.exe');
if (existsSync(local)) bindgen = local;
const probe = spawnSync(bindgen, ['--version'], { env, encoding: 'utf8' });
if (!probe.stdout?.includes(version)) {
  console.log(`Installing wasm-bindgen-cli ${version} to match Cargo.lock…`);
  run(cargo, ['install', 'wasm-bindgen-cli', '--version', version, '--locked']);
  bindgen = join(cargoBin, process.platform === 'win32' ? 'wasm-bindgen.exe' : 'wasm-bindgen');
}
mkdirSync(join(root, 'web', 'pkg'), { recursive: true });
run(bindgen, ['--target', 'web', '--out-dir', 'web/pkg', '--out-name', 'tos_wasm', 'target/wasm32-unknown-unknown/release/tos_wasm.wasm']);
copyFileSync(join(root, 'data', 'campaign.json'), join(root, 'web', 'campaign.json'));
run(cargo, ['build', '--release', '-p', 'tos-cli']);
console.log('Built native CLI + browser WebAssembly. Run npm start.');
