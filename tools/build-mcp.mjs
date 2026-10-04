import { spawnSync } from 'node:child_process';
import { resolve } from 'node:path';
import { cargo, rustEnv } from './rust-env.mjs';
import { deployMcp } from './mcp-deployment.mjs';

const root = resolve(import.meta.dirname, '..');
const build = spawnSync(cargo, ['build', '--release', '-p', 'tos-cli'], {
  cwd: root, env: rustEnv, stdio: 'inherit', windowsHide: true,
});
if (build.error) throw build.error;
if (build.status !== 0) process.exit(build.status || 1);
const deployment = deployMcp(resolve(root, 'target/release', process.platform === 'win32' ? 'tos.exe' : 'tos'));
console.log(`Published MCP worker ${deployment.version}. Running bridges reload before their next request.`);
