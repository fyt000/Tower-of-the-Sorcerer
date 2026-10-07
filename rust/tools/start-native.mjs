import { spawn } from 'node:child_process';
import { resolve } from 'node:path';
const root = resolve(import.meta.dirname, '..');
const binary = resolve(root, '../build/rust/target/release', process.platform === 'win32' ? 'tos-ui.exe' : 'tos-ui');
const child = spawn(binary, ['--assets-root', resolve(root, 'web'), ...process.argv.slice(2)], { cwd: root, stdio: 'inherit' });
child.on('error', error => { console.error(`${error.message}. Run npm run build first.`); process.exit(1); });
child.on('exit', code => process.exit(code || 0));
