// Readable reconstruction of selected English TSW v1.2 routines.
// Original image SHA-256 and executable-probe coverage live in README.md.
// The queue is a stack: push order and execution order are opposites.
#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

namespace tsw12 {
struct Command {
    std::uint16_t opcode, a, b;
};

struct State {
    int floor = 0;                         // 0x4B8698
    int x = 0, y = 0;                      // 0x4B86A0, 0x4B86A4
    int target = 0;                        // 0x48C584
    std::int32_t yellow = 0, red = 0, blue = 0; // 0x4B86A8/AC/B0
    std::uint32_t gold = 0, bomb = 0;       // 0x4B8694, 0x4B86E4
    std::array<std::uint8_t, 121> tiles{};  // 0x4B8934 + floor * 123 + 2
    std::array<std::uint32_t, 33> monster_gold{}; // 0x48991C + index * 16
    std::vector<Command> stack;            // 0x48C74C, cursor 0x48C5AC

    void push(std::uint16_t op, int a = 0, int b = 0) {
        stack.push_back({op, static_cast<std::uint16_t>(a), static_cast<std::uint16_t>(b)});
    }
    std::vector<Command> execution_queue() const {
        return {stack.rbegin(), stack.rend()};
    }
};

struct Classification {
    int kind;             // 0x48C58C: 0 other, 1 brick, 2 enemy, 3 lava
    int monster_index;    // 0x48C5B8; unchanged for non-enemy results
};

void doorcheck(State& s);
void contact_keyed_door(State& s);
Classification classify_tile(std::uint8_t tile, int previous_monster_index);
void use_bomb(State& s);

struct ZenoState {
    std::array<std::int32_t, 3> stats{8000, 5000, 1000}; // 0x489A00/04/08
    bool sealed = false;              // 0x4B88F8
    int cycle_factor_minus_one = 0;   // 0x4B8904
    bool later_cycle = false;         // 0x4B8908
};
bool seal_zeno_on_floor49(const std::array<std::uint8_t, 121>& tiles, ZenoState& z);
void prepare_zeno_at_time_gate(ZenoState& z);
void prepare_zeno_at_floor50_contact(ZenoState& z);
} // namespace tsw12
