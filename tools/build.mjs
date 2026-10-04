import { existsSync, readFileSync, mkdirSync, copyFileSync } from 'node:fs';
import { spawnSync } from 'node:child_process';
import { join, resolve } from 'node:path';
import { cargoBin, cargo, rustEnv } from './rust-env.mjs';
import { deployMcp } from './mcp-deployment.mjs';

const root = resolve(import.meta.dirname, '..');
const env = rustEnv;
function run(program, args) {
  const result = spawnSync(program, args, { cwd: root, env, stdio: 'inherit' });
  if (result.error) throw result.error;
  if (result.status !== 0) process.exit(result.status || 1);
}
run(cargo, ['rustc', '--release', '-p', 'tos-ui', '--lib', '--target', 'wasm32-unknown-unknown', '--crate-type', 'cdylib']);
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
run(bindgen, ['--target', 'web', '--out-dir', 'web/pkg', '--out-name', 'tos_ui', 'target/wasm32-unknown-unknown/release/tos_ui.wasm']);
copyFileSync(join(root, 'data', 'campaign.json'), join(root, 'web', 'campaign.json'));
run(cargo, ['build', '--release', '-p', 'tos-cli', '-p', 'tos-ui']);
deployMcp(join(root, 'target/release', process.platform === 'win32' ? 'tos.exe' : 'tos'));
console.log('Built shared Rust browser UI, native desktop GUI, CLI, and MCP. Run npm start or target/release/tos-ui.exe.');
