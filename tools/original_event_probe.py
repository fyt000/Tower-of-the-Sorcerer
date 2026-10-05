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

def probe(addr,floor,x=0,y=0,changes=(),end=0x6ffff0,globals=(),include_presentation=False,registers=(),follow_calls=()):
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
    for f,tx,ty,tile in changes:u.mem_write(MAP+f*123+2+ty*11+tx,bytes([tile]))
    for address,value in globals:u.mem_write(address,struct.pack('<I',value))
    initial=bytes(u.mem_read(MAP,len(RAW)))
    initial_monsters=bytes(u.mem_read(0x489910,528))
    read=set(); skipped=set();followed=set();cache={}
    def mem(uc,access,a,size,value,data):
        if MAP<=a<MAP+6273:read.add(a-MAP)
    def hook(uc,a,size,data):
        if a==end or a==0x6ffff0:uc.emu_stop();return
        ins=cache.setdefault(a,next(md.disasm(bytes(uc.mem_read(a,size)),a),None))
        if ins and ins.mnemonic=='call':
            target=ins.op_str
            if target.startswith('0x') and int(target,16) in follow_calls:
                followed.add(target)
                return
            skipped.add(target)
            uc.reg_write(UC_X86_REG_EIP,a+size)
    u.hook_add(unicorn.UC_HOOK_CODE,hook)
    u.hook_add(unicorn.UC_HOOK_MEM_READ,mem)
    u.emu_start(addr,0x6ffff0,count=200000)
    count=struct.unpack('<I',u.mem_read(0x48c5ac,4))[0]
    if count>10000:raise RuntimeError(count)
    queue=[struct.unpack('<HHH',u.mem_read(0x48c74c+i*6,6)) for i in range(count,0,-1)]
    changed=[(f,(i-2)%11,(i-2)//11,new) for off,(old,new) in enumerate(zip(initial,bytes(u.mem_read(MAP,len(RAW))))) if old!=new for f,i in [divmod(off,123)]]
    return {'queue':[list(q) for q in queue if include_presentation or q[0] not in [0,1,2,8,9]],'changed':changed,
            'reads':[(f,(i-2)%11,(i-2)//11,int(u.mem_read(MAP+offset,1)[0])) for offset in sorted(read) for f,i in [divmod(offset,123)]],
            'monster_changes':[(i,list(struct.unpack('<4I',u.mem_read(0x489910+i*16,16)))) for i in range(33) if bytes(u.mem_read(0x489910+i*16,16))!=initial_monsters[i*16:i*16+16]],
            'stat_slots':list(struct.unpack('<32I',u.mem_read(0x4b8688,128))),
            'cycle_factor_minus_one':struct.unpack('<I',u.mem_read(0x4b8904,4))[0],
            'later_cycle_flag':struct.unpack('<I',u.mem_read(0x4b8908,4))[0],
            'calls':sorted(skipped),'followed_calls':sorted(followed)}

if __name__=='__main__':
    addr=int(sys.argv[1],0); f=int(sys.argv[2]);x=int(sys.argv[3]) if len(sys.argv)>3 else 0;y=int(sys.argv[4]) if len(sys.argv)>4 else 0
    changes=json.loads(sys.argv[5]) if len(sys.argv)>5 else []
    print(json.dumps(probe(addr,f,x,y,changes),indent=2))
