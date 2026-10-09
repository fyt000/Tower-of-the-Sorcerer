"""Probe original v1.2 event builders without running the Windows UI.

Requires pefile, capstone, and unicorn. Set TOS_ORIGINAL_EXE to override
where the installed executable is read. Calls are skipped unless explicitly
whitelisted through follow_calls; followed and skipped targets are reported.
"""
import json, struct, pathlib, sys, os
import capstone, pefile, unicorn
from unicorn.x86_const import *

ROOT=pathlib.Path(__file__).resolve().parents[1]
pe=pefile.PE(os.environ.get('TOS_ORIGINAL_EXE',r'D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe'))
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
MAP=0x4b8934
RAW=(ROOT/'data/original-map-bytes.bin').read_bytes()

def probe(addr,floor,x=0,y=0,changes=(),end=0x6ffff0,globals=(),include_presentation=False,registers=(),follow_calls=(),watch_globals=(),state=None,return_state=False,observe_controls=False,observe_effects=False,call_returns=None,observe_arguments=()):
    u=unicorn.Uc(unicorn.UC_ARCH_X86,unicorn.UC_MODE_32)
    u.mem_map(0,0x300000); u.mem_map(0x400000,0x300000)
    u.mem_write(0x400000,pe.get_memory_mapped_image())
    u.mem_write(MAP,RAW)
    u.reg_write(UC_X86_REG_EAX,0x200000)
    u.reg_write(UC_X86_REG_ESP,0x6ff000)
    for register,value in registers:u.reg_write(register,value)
    u.mem_write(0x6ff000,struct.pack('<I',0x6ffff0))
    for a,v in [(0x200254,0x201000),(0x20102c,40),(0x201030,40),
                (0x4b8688,400),(0x4b868c,10),(0x4b8690,10),
                (0x4b8698,floor),(0x4b86a0,x),(0x4b86a4,y),(0x48c584,y*11+x)]:
        u.mem_write(a,struct.pack('<I',v))
    # Preserve the actual machine's output between entry/preview/confirm calls.
    # Callers can still override explicit inputs, but need not synthesize hidden flags.
    if state:
        for address, data in state.items():u.mem_write(address,data)
    for f,tx,ty,tile in changes:u.mem_write(MAP+f*123+2+ty*11+tx,bytes([tile]))
    for address,value in globals:u.mem_write(address,struct.pack('<I',value))
    initial=bytes(u.mem_read(MAP,len(RAW)))
    initial_monsters=bytes(u.mem_read(0x489910,528))
    read=set();written=set(); skipped=set();followed=set();cache={};stopped=False;controls={}
    call_sites=set();effect_writes=[];modeled=[];arguments=[]
    def mem(uc,access,a,size,value,data):
        if MAP<=a<MAP+6273:read.add(a-MAP)
    def write(uc,access,a,size,value,data):
        written.update(offset-MAP for offset in range(max(a,MAP),min(a+size,MAP+len(RAW))))
        if observe_effects and any(start<=a<stop for start,stop in
                                  [(0x4b8688,0x4ba1b5),(0x489910,0x489b20),
                                   (0x48c54c,0x48c5d4),(0x200000,0x220000)]):
            effect_writes.append(dict(site=hex(uc.reg_read(UC_X86_REG_EIP)),address=hex(a),
                                      size=size,before=bytes(uc.mem_read(a,size)).hex(),
                                      value=value & ((1 << (size*8))-1)))
    def hook(uc,a,size,data):
        nonlocal stopped
        if a==end or a==0x6ffff0:stopped=True;uc.emu_stop();return
        ins=cache.setdefault(a,next(md.disasm(bytes(uc.mem_read(a,size)),a),None))
        if ins and ins.mnemonic=='call':
            target=ins.op_str
            if target.startswith('0x') and int(target,16) in observe_arguments:
                arguments.append(dict(site=hex(a),target=target,
                                      eax=uc.reg_read(UC_X86_REG_EAX),
                                      edx=uc.reg_read(UC_X86_REG_EDX),
                                      ecx=uc.reg_read(UC_X86_REG_ECX)))
            if observe_controls and target in ('0x41353c','0x410378'):
                control=uc.reg_read(UC_X86_REG_EAX)
                enabled=uc.reg_read(UC_X86_REG_EDX)&0xff
                controls[hex(control)]=bool(enabled)
                if int(target,16) not in follow_calls:
                    uc.mem_write(control+(0x38 if target=='0x41353c' else 0x29),bytes([enabled]))
            if target.startswith('0x') and int(target,16) in follow_calls:
                followed.add(target)
                return
            skipped.add(target)
            call_sites.add((a,target))
            # Delphi's multi-string concatenation pops EDX arguments. Leaving
            # them on the stack corrupts a followed helper's return address.
            if target=='0x403710':
                uc.reg_write(UC_X86_REG_ESP,uc.reg_read(UC_X86_REG_ESP)+4*uc.reg_read(UC_X86_REG_EDX))
            elif target in ['0x40923c','0x417e44','0x41a5b8','0x413cb8','0x42cec8']:
                # Verified Delphi callee cleanup: Rect and Draw use RET 8;
                # CopyRect uses RET 4. Their pixels are still not emulated.
                cleanup=4 if target in ['0x41a5b8','0x413cb8','0x42cec8'] else 8
                uc.reg_write(UC_X86_REG_ESP,uc.reg_read(UC_X86_REG_ESP)+cleanup)
            if call_returns and target.startswith('0x') and int(target,16) in call_returns:
                result=call_returns[int(target,16)]
                uc.reg_write(UC_X86_REG_EAX,result)
                modeled.append(dict(site=hex(a),target=target,return_eax=result))
            uc.reg_write(UC_X86_REG_EIP,a+size)
    u.hook_add(unicorn.UC_HOOK_CODE,hook)
    u.hook_add(unicorn.UC_HOOK_MEM_READ,mem)
    u.hook_add(unicorn.UC_HOOK_MEM_WRITE,write)
    u.emu_start(addr,0x6ffff0,count=200000)
    if not stopped and u.reg_read(UC_X86_REG_EIP) not in [end,0x6ffff0]:
        raise RuntimeError(f'Probe {addr:#x} did not reach its stop address; instruction budget exhausted at {u.reg_read(UC_X86_REG_EIP):#x}')
    count=struct.unpack('<I',u.mem_read(0x48c5ac,4))[0]
    if count>10000:raise RuntimeError(count)
    queue=[struct.unpack('<HHH',u.mem_read(0x48c74c+i*6,6)) for i in range(count,0,-1)]
    changed=[(f,(i-2)%11,(i-2)//11,new) for off,(old,new) in enumerate(zip(initial,bytes(u.mem_read(MAP,len(RAW))))) if old!=new for f,i in [divmod(off,123)]]
    return {'queue':[list(q) for q in queue if include_presentation or q[0] not in [0,1,2,8,9]],'changed':changed,
            'direct_map_writes':[(f,(i-2)%11,(i-2)//11,int(u.mem_read(MAP+offset,1)[0])) for offset in sorted(written) for f,i in [divmod(offset,123)] if i>=2],
            'reads':[(f,(i-2)%11,(i-2)//11,int(u.mem_read(MAP+offset,1)[0])) for offset in sorted(read) for f,i in [divmod(offset,123)]],
            'monster_changes':[(i,list(struct.unpack('<4I',u.mem_read(0x489910+i*16,16)))) for i in range(33) if bytes(u.mem_read(0x489910+i*16,16))!=initial_monsters[i*16:i*16+16]],
            'stat_slots':list(struct.unpack('<32I',u.mem_read(0x4b8688,128))),
            'cycle_factor_minus_one':struct.unpack('<I',u.mem_read(0x4b8904,4))[0],
            'later_cycle_flag':struct.unpack('<I',u.mem_read(0x4b8908,4))[0],
            'calls':sorted(skipped),'followed_calls':sorted(followed),
            'skipped_call_sites':[dict(site=hex(a),target=target) for a,target in sorted(call_sites)],
            **({'effect_writes':effect_writes,'modeled_returns':modeled} if observe_effects else {}),
            **({'call_arguments':arguments} if observe_arguments else {}),
            **({'watched_globals':{hex(address):struct.unpack('<I',u.mem_read(address,4))[0]
                                  for address in watch_globals}} if watch_globals else {}),
            **({'control_enables':controls} if observe_controls else {}),
            **({'state':{address:bytes(u.mem_read(address,size)) for address,size in
                        [(0x4b8688,684),(MAP,len(RAW)),(0x489910,528),(0x48c550,0x88),
                         (0x200000,0x20000)]}} if return_state else {})}

if __name__=='__main__':
    addr=int(sys.argv[1],0); f=int(sys.argv[2]);x=int(sys.argv[3]) if len(sys.argv)>3 else 0;y=int(sys.argv[4]) if len(sys.argv)>4 else 0
    changes=json.loads(sys.argv[5]) if len(sys.argv)>5 else []
    print(json.dumps(probe(addr,f,x,y,changes),indent=2))
