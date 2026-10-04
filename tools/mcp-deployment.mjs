import { copyFileSync, mkdirSync, mkdtempSync, readFileSync, renameSync, rmSync, writeFileSync } from 'node:fs';
import { createHash, randomUUID } from 'node:crypto';
import { spawnSync } from 'node:child_process';
import { tmpdir } from 'node:os';
import { join, resolve } from 'node:path';

export const defaultManifest = resolve(import.meta.dirname, '../dist/mcp/current.json');

// Each worker runs an immutable copy, never Cargo's build output on Windows.
export function deployMcp(binary, manifest = defaultManifest) {
  const fingerprint = createHash('sha256').update(readFileSync(binary)).digest('hex');
  const activation = randomUUID();
  const version = `${new Date().toISOString().replace(/[:.]/g, '-')}-${fingerprint.slice(0, 12)}-${activation.slice(0, 8)}`;
  const directory = resolve(manifest, '..', 'versions', version);
  mkdirSync(directory, { recursive: true });
  const executable = join(directory, process.platform === 'win32' ? 'tos.exe' : 'tos');
  copyFileSync(binary, executable);
  const probeDirectory = mkdtempSync(join(tmpdir(), 'tos-mcp-probe-'));
  try {
    const checkpoint = join(probeDirectory, 'checkpoint.json');
    const requests = [
      { id: 1, method: 'initialize', params: { protocolVersion: '2025-11-25' } },
      { id: 2, method: 'tools/list' },
      { id: 3, method: 'runtime/checkpoint', params: { path: checkpoint } },
      { id: 4, method: 'runtime/restore', params: { path: checkpoint } },
    ].map(request => JSON.stringify({ jsonrpc: '2.0', ...request })).join('\n') + '\n';
    const probe = spawnSync(executable, ['mcp', '--runtime-bridge'], {
      input: requests, encoding: 'utf8', timeout: 15000, windowsHide: true,
    });
    if (probe.error) throw probe.error;
    const replies = probe.stdout.trim().split(/\r?\n/).map(line => JSON.parse(line));
    if (probe.status !== 0 || replies.length !== 4 || replies.some((reply, index) => reply.id !== index + 1 || reply.error) || !replies[1].result?.tools?.length) {
      throw new Error(`MCP deployment smoke test failed: ${probe.stderr || probe.stdout}`);
    }
    const deployment = { version, activation, executable };
    const temporary = `${manifest}.${activation}.tmp`;
    writeFileSync(temporary, JSON.stringify(deployment, null, 2) + '\n');
    // Readers see either the complete old manifest or the complete new one.
    renameSync(temporary, manifest);
    return deployment;
  } finally {
    rmSync(probeDirectory, { recursive: true, force: true });
  }
}
