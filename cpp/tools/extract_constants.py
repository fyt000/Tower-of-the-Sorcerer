"""Compile original constants, without consulting the Rust campaign or game rules."""
from pathlib import Path
import hashlib, json, sys
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from extract_original import extract_maps, extract_dialogue, MONSTER_OFFSET, MONSTERS
import struct

def main():
    source = Path(sys.argv[1] if len(sys.argv)>1 else r'D:\Program Files (x86)\Tower of the Sorcerer\TSW.exe')
    exe = source.read_bytes()
    digest = hashlib.sha256(exe).hexdigest()
    assert digest == '41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779'
    raw, _ = extract_maps(exe)
    lines = ['// Extracted from hash-pinned TSW 1.2; regenerate with tools/extract_constants.py.',
             '#pragma once', '#include "tsw/game.hpp"', 'namespace tsw::original {',
             f'inline constexpr std::string_view ImageHash = "{digest}";',
             '// Keep one source row per 11-cell board row.', '// clang-format off',
             'inline constexpr std::array<Floor, FloorCount> Maps{{']
    for floor in range(51):
        record = raw[floor*123:(floor+1)*123]
        lines.append(f'    // Floor {floor}; header bytes are stair landing cells.')
        lines.append(f'    Floor{{{record[0]}, {record[1]}, {{{{')
        for y in range(11):
            lines.append('        '+', '.join(f'{t:3}' for t in record[2+y*11:2+(y+1)*11])+',')
        lines.append('    }}},')
    lines += ['}};', '// clang-format on', 'inline constexpr std::array<Monster, 33> Monsters{{']
    for i,(_,name,_) in enumerate(MONSTERS):
        stats = struct.unpack_from('<4i',exe,MONSTER_OFFSET+i*16)
        lines.append('    Monster{'+', '.join(map(str,stats))+'}, // '+name)
    lines += ['}};', 'inline constexpr std::array<std::string_view,33> MonsterNames{{']
    lines.extend('    '+json.dumps(name)+',' for _,name,_ in MONSTERS)
    lines += ['}};', 'inline constexpr std::array<std::string_view,268> Dialogue{{']
    lines.extend('    '+json.dumps(d['text'], ensure_ascii=True)+', // '+str(d['id']) for d in extract_dialogue(exe))
    lines += ['}};', '} // namespace tsw::original', '']
    destination = ROOT/'cpp/src/original_constants.hpp'
    destination.write_text('\n'.join(lines),encoding='utf-8',newline='\n')
    print(f'Wrote {destination}: 51 maps, 33 monster rows, 268 strings; SHA-256 {digest}')

if __name__ == '__main__': main()
