#include "mechanics.hpp"

namespace tsw12 {
// The two Zeno sprites share ONE monster-table row. Floor numbers select
// event branches, not independent boss definitions. Gold is never scaled
// by these handlers. Presentation and other F49 gate/reward branches live
// in moncheck separately; this excerpt reconstructs its stat/flag writes.

// moncheck 0x46B4DB..0x46B597: called after normal combat and from Bomb's
// deferred [11,5,0] record. This does not require a center Zeno tile test.
// It also runs on decoy death, before its loot clears the corners. That
// loot builder overwrites the queued seal speech, but preserves these
// direct arithmetic writes: delaying the decoy fight until after the gate
// can therefore re-seal the shared F50 row.
bool seal_zeno_on_floor49(const std::array<std::uint8_t, 121>& tiles, ZenoState& z) {
    int edges = 0, corners = 0;
    for (int i : {16, 26, 28, 38}) edges += tiles[i];
    for (int i : {15, 17, 37, 39}) corners += tiles[i];
    if (edges != 24 || corners != 372 || z.sealed) return false;
    z.sealed = true; // 0x46B55C, before three signed IDIV instructions
    for (auto& stat : z.stats) stat /= 10; // Truncation, not fixed 800/500/100
    return true;
}

// ichicheck F24 time-gate branch 0x470506..0x470571. Reaching F50 by a
// wing doesn't call this function. The gate consumes its special-road tile.
void prepare_zeno_at_time_gate(ZenoState& z) {
    if (z.sealed) {
        z.sealed = false;
        for (auto& stat : z.stats) stat *= 10;
    }
    if (z.cycle_factor_minus_one != 0 && !z.later_cycle) {
        z.stats = {1000, 625, 125}; // Second-cycle scripted first-strike fight
    }
    // First and later cycles retain this row. Neither writes a fixed base
    // row here. Sealing AFTER the gate therefore leaves the F50 row weaker.
}

// handan F50 Zeno contact 0x4463A1..0x4463D9.
void prepare_zeno_at_floor50_contact(ZenoState& z) {
    if (z.cycle_factor_minus_one != 0 && !z.later_cycle) {
        z.stats = {1000, 625, 125};
    }
    // First cycle queues the ending without combat (0x4463DE onward).
    // Later cycles call taisen with the CURRENT row (0x4463D1). They do
    // not reverse the seal, clear its flag, or restore full boss stats.
}
} // namespace tsw12
