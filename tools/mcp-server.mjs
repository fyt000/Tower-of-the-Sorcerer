import { spawn } from 'node:child_process';
import { mkdtempSync, readFileSync, rmSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { dirname, isAbsolute, join, resolve } from 'node:path';
import { createInterface } from 'node:readline';
import { defaultManifest } from './mcp-deployment.mjs';

const args = process.argv.slice(2);
function option(name) {
  const index = args.indexOf(name);
  if (index === -1) return undefined;
  if (!args[index + 1] || args[index + 1].startsWith('--')) throw new Error(`${name} requires a path`);
  return resolve(args[index + 1]);
}
const manifestPath = option('--manifest') || process.env.TOS_MCP_CURRENT || defaultManifest;
const workerArgs = ['mcp', '--runtime-bridge'];
for (const name of ['--campaign']) {
  const value = option(name);
  if (value) workerArgs.push(name, value);
}
const startingSave = option('--save');
if (args.includes('--developer')) workerArgs.push('--developer');
const timeoutMs = Number(process.env.TOS_MCP_TIMEOUT_MS || 15000);
if (!Number.isFinite(timeoutMs) || timeoutMs <= 0) throw new Error('TOS_MCP_TIMEOUT_MS must be positive');

function deployment() {
  const value = JSON.parse(readFileSync(manifestPath, 'utf8'));
  for (const name of ['version', 'activation', 'executable']) {
    if (typeof value[name] !== 'string' || !value[name]) throw new Error(`Manifest requires ${name}`);
  }
  return { version: value.version, activation: value.activation,
    executable: isAbsolute(value.executable) ? value.executable : resolve(dirname(manifestPath), value.executable) };
}
const key = value => JSON.stringify(value);
const runtimeTool = {
  name: 'mcp_runtime', description: 'Read bridge/worker process IDs, the active deployment and the last hot reload outcome.',
  inputSchema: { type: 'object', properties: {}, additionalProperties: false }, annotations: { readOnlyHint: true },
};
const write = message => process.stdout.write(JSON.stringify(message) + '\n');

class Worker {
  constructor(selected, starting = false) {
    this.deployment = selected;
    this.nextId = 1;
    this.pending = new Map();
    this.child = spawn(selected.executable, [...workerArgs, ...(starting && startingSave ? ['--save', startingSave] : [])], { stdio: ['pipe', 'pipe', 'pipe'], windowsHide: true });
    this.lines = createInterface({ input: this.child.stdout });
    this.child.stderr.on('data', data => process.stderr.write(data));
    this.child.stdin.on('error', error => this.fail(error));
    this.child.on('error', error => this.fail(error));
    this.child.on('exit', (code, signal) => this.fail(new Error(`MCP worker exited (${code ?? signal})`)));
    this.lines.on('line', line => {
      try {
        const reply = JSON.parse(line);
        const waiting = this.pending.get(reply.id);
        if (!waiting) {
          // The bridge handles public tool-change notifications after activation.
          if (!('id' in reply) && this === active && initialized && reply.method !== 'notifications/tools/list_changed') write(reply);
          return;
        }
        this.pending.delete(reply.id);
        clearTimeout(waiting.timer);
        waiting.resolve(reply);
      } catch (error) { this.fail(new Error(`Invalid worker JSON: ${error.message}`)); }
    });
  }
  fail(error) {
    this.failure = error;
    for (const waiting of this.pending.values()) {
      clearTimeout(waiting.timer);
      waiting.reject(error);
    }
    this.pending.clear();
  }
  request(method, params = {}) {
    if (this.failure) return Promise.reject(this.failure);
    const id = `bridge-${this.nextId++}`;
    return new Promise((resolveReply, reject) => {
      const timer = setTimeout(() => {
        // Never retry a timed-out action; its commit status is unknown.
        this.fail(new Error(`MCP worker timed out during ${method}; action was not retried`));
        this.child.kill();
      }, timeoutMs);
      this.pending.set(id, { resolve: resolveReply, reject, timer });
      this.child.stdin.write(JSON.stringify({ jsonrpc: '2.0', id, method, params }) + '\n');
    });
  }
  async required(method, params) {
    const reply = await this.request(method, params);
    if (reply.error) throw new Error(reply.error.message);
    return reply.result;
  }
  notify(method, params) {
    if (!this.failure) this.child.stdin.write(JSON.stringify({ jsonrpc: '2.0', method, params }) + '\n');
  }
  async prepare() {
    await this.required('initialize', initialization);
    this.notify('notifications/initialized', {});
    const catalog = await this.required('tools/list', {});
    if (!Array.isArray(catalog.tools)) throw new Error('Worker did not supply a tool catalog');
    this.catalog = catalog.tools;
  }
  stop() {
    this.stopping ??= this.stopProcess();
    return this.stopping;
  }
  async stopProcess() {
    if (!this.child.pid || this.child.exitCode !== null || this.child.signalCode !== null) { this.lines.close(); return; }
    await new Promise(done => {
      let finished = false;
      const finish = () => {
        if (finished) return;
        finished = true;
        clearTimeout(terminate);
        clearTimeout(kill);
        clearTimeout(deadline);
        this.child.removeListener('exit', finish);
        done();
      };
      const terminate = setTimeout(() => this.child.kill(), 1500);
      const kill = setTimeout(() => this.child.kill('SIGKILL'), 2500);
      const deadline = setTimeout(() => {
        console.error(`MCP worker ${this.child.pid} did not exit after termination`);
        this.child.stdin.destroy();
        this.child.stdout.destroy();
        this.child.stderr.destroy();
        this.child.unref();
        finish();
      }, 3500);
      this.child.once('exit', finish);
      this.child.stdin.end();
    });
    this.lines.close();
  }
}

let active;
let candidate;
let initialized = false;
let initialization = { protocolVersion: '2025-11-25', capabilities: {}, clientInfo: { name: 'tos-mcp-bridge', version: '1' } };
let blocked;
let lastReload = null;
const checkpointDirectory = mkdtempSync(join(tmpdir(), 'tos-mcp-session-'));
const checkpointPath = join(checkpointDirectory, 'worker.json');

async function reload() {
  let requested;
  try { requested = deployment(); }
  catch (error) {
    // An unreadable publication never becomes a deployment. Continue the
    // already-running session and make the failed publication observable.
    lastReload = { status: 'unchanged', previous: active.deployment, error: `Cannot read deployment manifest: ${error.message}`, session_lost: Boolean(active.failure) };
    return lastReload;
  }
  if (key(requested) === key(active.deployment) || key(requested) === blocked) return null;
  const previous = active.deployment;
  try {
    await active.required('runtime/checkpoint', { path: checkpointPath });
    candidate = new Worker(requested);
    await candidate.prepare();
    await candidate.required('runtime/restore', { path: checkpointPath });
    const old = active;
    const toolsChanged = key(old.catalog) !== key(candidate.catalog);
    active = candidate;
    candidate = undefined;
    blocked = undefined;
    await old.stop();
    lastReload = { status: 'succeeded', previous, current: requested, session_restored: true, tools_changed: toolsChanged };
    if (initialized && toolsChanged) write({ jsonrpc: '2.0', method: 'notifications/tools/list_changed' });
    return lastReload;
  } catch (error) {
    if (candidate) await candidate.stop();
    candidate = undefined;
    blocked = key(requested);
    lastReload = { status: 'unchanged', previous, requested, error: error.message, session_lost: Boolean(active.failure) };
    const recovery = active.failure ? 'previous worker is unavailable; reconnect with a saved game' : 'previous worker remains active';
    throw new Error(`Runtime reload failed; ${recovery}: ${error.message}`);
  }
}

async function dispatch(request) {
  if (!request || typeof request !== 'object' || Array.isArray(request) || request.jsonrpc !== '2.0' || typeof request.method !== 'string' || ('id' in request && !(typeof request.id === 'string' || typeof request.id === 'number' || request.id === null))) {
    return { jsonrpc: '2.0', id: null, error: { code: -32600, message: 'Invalid Request' } };
  }
  if (!('id' in request)) {
    if (request.method === 'notifications/initialized') initialized = true;
    if (!request.method.startsWith('runtime/')) active.notify(request.method, request.params);
    return null;
  }
  let reloaded;
  try {
    reloaded = await reload();
    let reply;
    if (request.method.startsWith('runtime/')) return { jsonrpc: '2.0', id: request.id, error: { code: -32601, message: 'Method not found' } };
    if (request.method === 'tools/call' && request.params?.name === runtimeTool.name) {
      const parameters = request.params.arguments ?? {};
      if (!parameters || typeof parameters !== 'object' || Array.isArray(parameters) || Object.keys(parameters).length) throw new Error('mcp_runtime accepts no arguments');
      const state = { bridge_pid: process.pid, worker_pid: active.child.pid, worker_running: !active.failure,
        worker_error: active.failure?.message ?? null, current: active.deployment, last_reload: lastReload };
      reply = { jsonrpc: '2.0', result: { content: [{ type: 'text', text: JSON.stringify(state) }], structuredContent: state, isError: false } };
    } else {
      reply = await active.request(request.method, request.params);
    }
    reply.id = request.id;
    if (request.method === 'initialize' && reply.result) {
      initialization = request.params ?? initialization;
      reply.result.capabilities.tools.listChanged = true;
    }
    if (request.method === 'tools/list' && reply.result) reply.result.tools.push(runtimeTool);
    if (reloaded && reply.result) reply.result._meta = { ...reply.result._meta, runtime_reload: reloaded };
    return reply;
  } catch (error) {
    const meta = { runtime_reload: lastReload };
    if (request.method === 'tools/call') return { jsonrpc: '2.0', id: request.id, result: { content: [{ type: 'text', text: error.message }], isError: true, _meta: meta } };
    return { jsonrpc: '2.0', id: request.id, error: { code: -32603, message: error.message, data: meta } };
  }
}

let closing;
function close() {
  closing ??= (async () => {
    if (candidate) await candidate.stop();
    if (active) await active.stop();
    rmSync(checkpointDirectory, { recursive: true, force: true });
  })();
  return closing;
}
for (const signal of ['SIGINT', 'SIGTERM']) process.once(signal, () => { close().finally(() => process.exit(0)); });
try {
  active = new Worker(deployment(), true);
  await active.prepare();
  const input = createInterface({ input: process.stdin, crlfDelay: Infinity });
  // Requests, reloads and state-changing actions share one ordered queue.
  for await (const line of input) {
    if (!line.trim()) continue;
    let request;
    try { request = JSON.parse(line); }
    catch { write({ jsonrpc: '2.0', id: null, error: { code: -32700, message: 'Parse error' } }); continue; }
    const response = await dispatch(request);
    if (response) write(response);
  }
} catch (error) {
  console.error(`tos MCP bridge: ${error.message}. Run npm run build:mcp before starting the bridge.`);
  process.exitCode = 1;
} finally { await close(); }
