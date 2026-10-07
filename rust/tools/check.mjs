import { spawnSync } from 'node:child_process';
import { resolve } from 'node:path';
import { cargo, rustEnv } from './rust-env.mjs';
const cwd = resolve(import.meta.dirname, '..');
for (const args of [
  ['test', '--workspace'],
  ['clippy', '--workspace', '--all-targets', '--', '-D', 'warnings'],
  ['clippy', '-p', 'tos-ui', '--lib', '--target', 'wasm32-unknown-unknown', '--', '-D', 'warnings'],
]) {
  const result = spawnSync(cargo, args, { cwd, env: rustEnv, stdio: 'inherit' });
  if (result.error) throw result.error;
  if (result.status !== 0) process.exit(result.status || 1);
}
