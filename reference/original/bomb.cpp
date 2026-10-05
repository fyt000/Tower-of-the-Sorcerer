#include "mechanics.hpp"

namespace tsw12 {
// 0x451C20..0x451D39: shared mattock/Bomb/Crystal classifier. The two
// large-monster index branches at 0x451CEA/CF6 are unreachable from the
// eligible ranges. This expresses the same branches without dead code.
Classification classify_tile(std::uint8_t tile, int previous_monster_index) {
    if (tile == 8) return {1, previous_monster_index};
    if (tile == 13) return {3, previous_monster_index};
    if ((tile >= 61 && tile <= 90) || (tile >= 93 && tile <= 96)) {
        return {2, (tile - 61) / 2}; // 0x451CD4..0x451CE3
    }
    if ((tile >= 133 && tile <= 144) || (tile >= 147 && tile <= 158)) {
        return {2, 20 + (tile - 133) / 2}; // 0x451D15..0x451D29
    }
    return {0, previous_monster_index};
}

// toroad2 0x44BC34..0x44BED6. The old monster tile is captured in the
// operand records; removal occurs only at the final opcode-17 record.
static void push_dissolve(State& s, int index) {
    s.push(17, index, 6);
    for (int mask : {182, 178, 174, 170, 166}) {
        s.push(0, s.tiles[index], 6);
        s.push(9, index, mask);
        s.push(0);
        s.push(1, 1);
    }
}

// Bomb case in item dispatcher 0x450F31..0x45112B.
// Reconstructs all gameplay/queue writes through consumption. Following
// 0x45112C constructs a localized status string; it is not modeled here.
void use_bomb(State& s) {
    s.push(0);
    s.push(11, 5); // deferred moncheck 0x4664E4, dispatched at 0x4533EB
    s.push(2);
    s.push(8);
    std::uint32_t reward = 0; // 0x48C594
    const int index = s.y * 11 + s.x; // 0x48C558
    // Builder order is south/east/west/north. Execution order reverses it.
    for (int neighbor : {index + 11, index + 1, index - 1, index - 11}) {
        s.target = neighbor; // Written even for an out-of-bounds neighbor.
        const bool inside = neighbor == index + 11 ? s.y < 10
                          : neighbor == index + 1  ? s.x < 10
                          : neighbor == index - 1  ? s.x > 0
                          : s.y > 0;
        if (!inside) continue;
        const auto classified = classify_tile(s.tiles[neighbor], 0);
        if (classified.kind != 2) continue;
        // No Lucky Gold or cycle multiplier; original uint32 arithmetic.
        reward += s.monster_gold[classified.monster_index];
        push_dissolve(s, neighbor);
    }
    s.gold += reward; // 0x45111F: before any queue animation/callback
    s.bomb = 0;       // 0x451127: consumed even when no target qualifies
}
} // namespace tsw12
