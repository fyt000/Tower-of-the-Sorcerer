import { spawn, spawnSync } from 'node:child_process';
import { readFileSync, writeFileSync, mkdirSync } from 'node:fs';
import { createInterface } from 'node:readline';
import { resolve } from 'node:path';
import assert from 'node:assert/strict';
const root=resolve(import.meta.dirname,'..');
const originalCampaign=JSON.parse(readFileSync(resolve(root,'../data/campaign.json'),'utf8'));
const binary=resolve(root,'../build/rust/target/release',process.platform==='win32'?'tos.exe':'tos');
const server=spawn(binary,['mcp','--developer'],{cwd:root,stdio:['pipe','pipe','pipe']});
const pending=new Map();let nextId=1;const unexpected=[];
const lines=createInterface({input:server.stdout});
lines.on('line',line=>{try{const msg=JSON.parse(line);const request=pending.get(msg.id);if(request){pending.delete(msg.id);clearTimeout(request.timeout);request.resolve(msg);}else unexpected.push(msg);}catch{unexpected.push(line);}});
function rpc(method,params={}){return new Promise((resolve,reject)=>{const id=nextId++;const timeout=setTimeout(()=>reject(new Error(`MCP ${method} timed out`)),10000);pending.set(id,{resolve,reject,timeout});server.stdin.write(JSON.stringify({jsonrpc:'2.0',id,method,params})+'\n');});}
async function tool(name,args={}){const response=await rpc('tools/call',{name,arguments:args});assert(!response.error,JSON.stringify(response));assert.equal(response.result.isError,false);return response.result.structuredContent;}
function route(state,target){
  const start=state.player.y*state.width+state.player.x,goal=target[1]*state.width+target[0];
  const queue=[start],previous=new Map([[start,null]]);
  for(let i=0;i<queue.length;i++){
    const cell=queue[i];if(cell===goal)break;
    const x=cell%state.width,y=Math.floor(cell/state.width);
    for(const [direction,dx,dy] of [['up',0,-1],['left',-1,0],['down',0,1],['right',1,0]]){
      const nx=x+dx,ny=y+dy;if(nx<0||ny<0||nx>=state.width||ny>=state.height)continue;
      const next=ny*state.width+nx;if(previous.has(next))continue;
      const def=state.tile_defs[state.tiles[next]];let passable=['floor','empty','key','potion','gem','equipment','item','trigger'].includes(def.kind);
      if(def.kind==='door')passable=state.player.keys[def.key]>0;
      // Regression-route oracle can read source data; the MCP session must
      // keep player-facing forecasts locked until the actual Hero Orb gift.
      if(def.kind==='enemy') { const enemy=originalCampaign.enemies[def.enemy],hit=state.player.attack-enemy.defense; passable=hit>0&&Math.floor((enemy.hp-1)/hit)*Math.max(enemy.attack-state.player.defense,0)<state.player.hp; }
      if(['stairs_up','stairs_down'].includes(def.kind))passable=next===goal;
      if(passable){previous.set(next,[cell,direction]);queue.push(next);}
    }
  }
  assert(previous.has(goal),`No observed route on floor ${state.floor} to ${target}`);
  const directions=[];for(let cell=goal;cell!==start;){const [parent,direction]=previous.get(cell);directions.push(direction);cell=parent;}
  return directions.reverse();
}
try{
  const init=await rpc('initialize',{protocolVersion:'2025-11-25',capabilities:{},clientInfo:{name:'integration-test',version:'1'}});
  assert.equal(init.result.protocolVersion,'2025-11-25');assert.equal(init.result.serverInfo.name,'tower-of-the-sorcerer');
  server.stdin.write(JSON.stringify({jsonrpc:'2.0',method:'notifications/initialized'})+'\n');
  const list=await rpc('tools/list');assert.equal(list.result.tools.length,8);assert(list.result.tools.every(t=>t.inputSchema.type==='object'));
  const initial=await tool('game_state');assert.equal(initial.width,11);assert.equal(initial.floors.length,51);
  const plan=await tool('plan_path',{x:5,y:9});assert.deepEqual(plan.directions,['up']);assert.equal((await tool('game_state')).steps,initial.steps);
  const tile=await tool('inspect_tile',{x:5,y:9});assert.equal(typeof tile.name,'string');
  const simulated=await tool('simulate_actions',{actions:[{type:'move',direction:'up'}]});const unchanged=await tool('game_state');assert.deepEqual(initial.player,unchanged.player);assert.equal(unchanged.steps,initial.steps);
  const moved=await tool('game_action',{action:{type:'move',direction:'up'}});assert.deepEqual(simulated.player,moved.player);assert.equal(simulated.steps,moved.steps);
  const save=await tool('save_game');assert.equal(typeof save.save,'string');await tool('new_game');await tool('load_game',{save:save.save});assert.deepEqual((await tool('game_state')).player,moved.player);
  const bad=await rpc('tools/call',{name:'load_game',arguments:{save:'broken'}});assert.equal(bad.result.isError,true);
  assert.deepEqual((await tool('game_state')).player,moved.player);
  const resources=await rpc('resources/list');assert.equal(resources.result.resources.length,2);
  const stateResource=await rpc('resources/read',{uri:'tos://state'});assert.equal(JSON.parse(stateResource.result.contents[0].text).floor,moved.floor);
  const unknown=await rpc('unknown');assert.equal(unknown.error.code,-32601);
  // Drive the real native engine through MCP, recording a reusable CLI replay.
  const actions=[];let state=await tool('new_game');
  async function act(action){actions.push(action);state=await tool('game_action',{action});assert.equal(state.last_action.ok,true,JSON.stringify(state.last_action));assert.equal(state.status,'playing');}
  async function walk(target){for(const direction of route(state,target))await act({type:'move',direction});}
  await walk([4,9]);assert.equal(state.player.keys.yellow,1);
  await walk([0,0]);assert.equal(state.floor,2);
  await walk([0,10]);assert.equal(state.floor,3);
  await walk([4,8]);assert.equal(state.floor,2);assert.deepEqual([state.player.hp,state.player.attack,state.player.defense],[400,10,10]);assert.equal(state.player.inventory.length,0);
  await act({type:'move',direction:'up'});assert(state.pending_interaction);
  await act({type:'choose',choice:'leave'});
  for(const direction of ['up','left','left'])await act({type:'move',direction});
  assert.deepEqual([state.player.x,state.player.y,state.player.hp],[0,6,400]);
  const jsonl=actions.map(action=>JSON.stringify(action)).join('\n')+'\n';
  const replayDirectory=resolve(root,'../build/rust/test-results/mcp');mkdirSync(replayDirectory,{recursive:true});const example=resolve(replayDirectory,'opening.jsonl');writeFileSync(example,jsonl);
  const replay=spawnSync(binary,['replay',example],{cwd:root,encoding:'utf8'});assert.equal(replay.status,0,replay.stderr);const replayed=JSON.parse(replay.stdout);
  assert.deepEqual(replayed.player,state.player);assert.deepEqual(replayed.flags,state.flags);assert.equal(replayed.steps,state.steps);
  const headless=spawnSync(binary,['headless'],{cwd:root,input:jsonl,encoding:'utf8',maxBuffer:10*1024*1024});assert.equal(headless.status,0,headless.stderr);
  const transitions=headless.stdout.trim().split(/\r?\n/).map(line=>JSON.parse(line));assert.equal(transitions.length,actions.length);assert.deepEqual(transitions.at(-1).player,state.player);
  assert.equal(unexpected.length,0,'stdout must contain only responses');
  console.log(`MCP integration passed: 8 tools, simulation isolation, save restore, resources/errors, and ${actions.length} natural opening actions with CLI replay/headless parity.`);
} finally {server.stdin.end();server.kill();lines.close();for(const request of pending.values())clearTimeout(request.timeout);}
