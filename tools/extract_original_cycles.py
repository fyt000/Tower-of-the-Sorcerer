"""Record original v1.2 cycle reset and event-presentation evidence.

The installed executable is never launched. Requires pefile/capstone/unicorn;
TOS_ORIGINAL_EXE can override its location. Run after extract_original.py.
"""
import json
import struct
from original_event_probe import probe, pe, md, ROOT


def disassembly(address, size):
    image = pe.get_memory_mapped_image()
    return [f"0x{i.address:06x}: {i.mnemonic} {i.op_str}".rstrip()
            for i in md.disasm(image[address-0x400000:address-0x400000+size],address)]


def initializer(factor, later):
    values = [(0x4b8904,factor),(0x4b8908,later),(0x4b8688,12345),
              (0x4b868c,321),(0x4b8690,456),(0x4b8694,789),
              (0x4b86a8,3),(0x4b86ac,2),(0x4b86b0,1),(0x4b86b4,7),
              (0x4b86cc,1),(0x4b86d0,1),(0x4b86d4,1)]
    result = probe(0x455cb8,50,5,6,globals=values)
    slots = result['stat_slots']
    return {'hp':slots[0],'attack':slots[1],'defense':slots[2],'gold':slots[3],
            'floor':slots[4],'highest_floor':slots[5],'x':slots[6],'y':slots[7],
            'keys':slots[8:11],'altar_visits':slots[11],'sword_shield':slots[15:17],
            'hero_wisdom_flight_orbs':slots[17:20],
            'cycle_factor_minus_one':result['cycle_factor_minus_one'],
            'later_cycle_flag':result['later_cycle_flag']}


def main():
    f10 = probe(0x46cb1c,10,5,6,include_presentation=True)
    evidence = {
        'source':'Installed English TSW Windows v1.2, executable-emulated constants and recorded instructions',
        'initial_input':{'hp':12345,'attack':321,'defense':456,'gold':789,
                         'keys':[3,2,1],'altar_visits':7,'orbs':[1,1,1]},
        'initializers':{'first_cycle':initializer(0,0),'second_cycle':initializer(43,0),
                        'third_and_later_cycle':initializer(43,1)},
        'reset_dispatch':disassembly(0x453415,0x48),
        'capture_cycle_branch':disassembly(0x4655d7,0x131),
        'second_cycle_zeno':disassembly(0x4463a1,0x3d),
        'hero_orb_forecast_gate':disassembly(0x48108a,0x17),
        'zeno_seal_table_reset':disassembly(0x455b49,0x56),
        'audio_queue_names':{'1':'open.wav','2':'get.wav','3':'taisen.wav','4':'zeno.wav',
                            '5':'music-start','6':'music-stop','7':'3f.wav',
                            '8':'20f.wav','9':'kai.wav','10':'kai2.wav'},
        'floor_music_dispatch':disassembly(0x47c8f8,0x7e),
        'music_cue_files':music_files(),
        'floor_10_trap_queue':f10['queue'],
        'floor_10_trap_skipped_calls':f10['calls'],
        'presentation_timing':'Wait records and movement order are recovered. Remake durations are deliberately configurable modern presentation timings, not exact original timer emulation.',
        'bug_policy':'Later-cycle F50 Zeno keeps normalized base 1000/625/125 rather than repeating the original double-multiplier bug. Original F45 merchant keeps unscaled 2000HP gain.'}
    path = ROOT/'data/original-cycle-evidence.json'
    path.write_text(json.dumps(evidence,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    assert evidence['initializers']['second_cycle']['hp']==12345
    assert evidence['initializers']['second_cycle']['gold']==0
    assert evidence['initializers']['second_cycle']['keys']==[0,0,0]
    assert evidence['initializers']['third_and_later_cycle']['gold']==789
    assert sum(q[0]==12 for q in f10['queue'])==43
    print('Recorded first/backside reset evidence and 43 skeleton-trap motions')


def music_files():
    """Read soundplay's 17-case table and its Delphi filename constants."""
    image=pe.get_memory_mapped_image()
    files={}
    for cue in range(5,22):
        offset=0x7c304+(cue-5)*4
        address=struct.unpack('<I',image[offset:offset+4])[0]
        for instruction in md.disasm(image[address-0x400000:address-0x400000+55],address):
            if instruction.mnemonic=='mov' and instruction.op_str.startswith('ecx, 0x'):
                pointer=int(instruction.op_str.split(', ')[1],16)-0x400000
                size=struct.unpack('<I',image[pointer-4:pointer])[0]
                files[str(cue)]=image[pointer:pointer+size].decode('cp1252').split('\\')[-1].lower()
    assert len(files)==17
    return files


if __name__=='__main__':main()
