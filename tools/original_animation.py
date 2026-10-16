"""Translations of dooropen's opcode-13 modes, audited in TSW.exe v1.2.

These are visual operations, despite the original helper's name: modes 7/8
move brick vertically, and mode 5 assembles a sealed gate. All coordinates
remain zero-based. The actual simulation write follows the presentation.
"""
TILE_TRANSITIONS = {
    1: ('door_open', 6), 2: ('door_open', 6), 3: ('door_open', 6),
    4: ('gate_open', 6), 5: ('gate_close', 4), 6: ('prison_open', 6),
    7: ('wall_collapse', 6), 8: ('wall_rise', 8),
    9: ('lava_open_right', 6), 10: ('lava_open_left', 6),
    11: ('lava_open_up', 6), 12: ('lava_open_down', 6),
}


def tile_transition(floor, index, from_tile, mode):
    style, tile = TILE_TRANSITIONS[mode]
    return {
        'type': 'cinematic', 'kind': 'tile_reveal', 'style': style,
        'floor': floor, 'x': index % 11, 'y': index // 11,
        'from_tile': from_tile, 'tile': tile, 'duration_ms': 400,
        'original_mode': mode, 'original_steps': 16,
    }
