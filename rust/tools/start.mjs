import { spawn } from 'node:child_process';
import { resolve } from 'node:path';
import { existsSync } from 'node:fs';
const root=resolve(import.meta.dirname,'..');
const binary=resolve(root,'../build/rust/target/release',process.platform==='win32'?'tos.exe':'tos');
if(!existsSync(binary)){console.error('Run npm run build first.');process.exit(1);}
const child=spawn(binary,['serve',...process.argv.slice(2)],{cwd:root,stdio:'inherit'});
child.on('exit',code=>process.exit(code||0));
process.on('SIGINT',()=>child.kill());
