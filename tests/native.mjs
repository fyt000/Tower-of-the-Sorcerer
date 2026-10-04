// Exercise the actual native renderer without desktop/computer-use automation.
import { spawnSync } from 'node:child_process';
import { existsSync, mkdirSync, writeFileSync } from 'node:fs';
import { resolve } from 'node:path';
import assert from 'node:assert/strict';
const root = resolve(import.meta.dirname, '..');
const results = resolve(root, 'test-results');
mkdirSync(results, { recursive: true });
const executable = resolve(root, 'target/release', process.platform === 'win32' ? 'tos-ui.exe' : 'tos-ui');
const report = [];
const portable = resolve(root, 'dist/native', process.platform === 'win32' ? 'tos-ui.exe' : 'tos-ui');
const scenarios = [['native-en', ['--language', 'en']], ['native-zh', ['--language', 'zh-CN']], ['native-editor', ['--editor']]];
if (existsSync(portable)) scenarios.push(['native-portable', ['--language', 'zh-CN']]);
for (const [name, args] of scenarios) {
  const path = resolve(results, `${name}.png`);
  const packaged = name === 'native-portable';
  const run = spawnSync(packaged ? portable : executable, packaged ? args : ['--assets-root', resolve(root, 'web'), ...args], {
    cwd: packaged ? results : root, windowsHide: true, timeout: 30000, encoding: 'utf8',
    env: { ...process.env, EFRAME_SCREENSHOT_TO: path, TOS_STORAGE_DIR: resolve(results, `storage-${name}`) },
  });
  assert.equal(run.status, 0, `${name}: ${run.error || run.stderr}`);
  assert(existsSync(path), `${name} screenshot missing`);
  report.push({ name, path, exit: run.status });
  console.log(`Native renderer passed: ${name}`);
}
writeFileSync(resolve(results, 'native-report.json'), JSON.stringify(report, null, 2));
