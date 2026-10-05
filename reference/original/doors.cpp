#include "mechanics.hpp"
#include <stdexcept>

namespace tsw12 {
// 0x47BEAC..0x47C20A. Called at 0x44468F on *every* keyed-door attempt.
// It inspects the old map, before any queued door opening has played.
void doorcheck(State& s) {
    if (s.floor == 39) {
        int sum = 0;
        for (int i : {12, 16, 34, 36, 56, 58, 60}) sum += s.tiles[i];
        // 0x47BF11 and 0x47C09B compare a numeric SUM to seven. In the
        // reachable clock states (yellow door / road / staff), this means
        // all seven cells are untouched yellow doors. No key test exists.
        if (sum == 7 && ((s.target == 38 && s.tiles[14] == 6) ||
                         (s.target == 14 && s.tiles[38] == 6))) {
            s.push(0);
            s.push(6, 36, 43); // Warp Staff, not Ascent/Descent Wing
            s.push(0);
            s.push(1, 2);      // get.wav
            s.push(0);
            s.push(0);
        }
    } else if (s.floor == 43 && s.target == 7 && s.tiles[8] == 93) {
        // 0x47C1C8: convert the contacted door to special road even if
        // handan refused the opening. The next road entry reaches mevent.
        s.push(6, 7, 7);
    }
}

// doorstackin 0x4660D0..0x4664E2 replaces one pending opcode-13 record
// with sixteen blend/frame pairs. Timer rendering itself is outside this
// reference; the exact emitted records are compared with the executable.
static void push_door_open(State& s, int tile) {
    for (int frame = 16; frame >= 1; --frame) {
        s.push(0, 0, frame);
        s.push(13, s.target, tile);
    }
}

// Keyed-door branch of handan 0x4445D3..0x4447C0 (dispatch at 0x444490).
// 0x44BC0C controls/timer setup and Delphi string cleanup are omitted; they
// neither alter the modeled gameplay fields nor append queue records.
void contact_keyed_door(State& s) {
    const int tile = s.tiles.at(s.target);
    std::int32_t* key = nullptr;
    int message = 0, success_message = 0;
    switch (tile) {
    case 1: key = &s.yellow; message = 16; success_message = 4; break;
    case 2: key = &s.blue;   message = 17; success_message = 5; break;
    case 3: key = &s.red;    message = 18; success_message = 6; break;
    default: throw std::invalid_argument("handan door branch requires tile 1, 2 or 3");
    }
    const bool opened = *key > 0;
    if (opened) { --*key; message = success_message; }
    // 0x44468C precedes the opened/refused branch at 0x444694. This is
    // why a no-key bump can reveal the 39F reward or arm the 43F trap.
    doorcheck(s);
    if (opened) {
        s.push(2, message);
        s.push(8);
        push_door_open(s, tile);
        s.push(0);
        s.push(1, 1); // open.wav plays before any doorcheck reward
    } else {
        s.push(2, message);
    }
    // No direct map or hero-position write: the timer executes the stack.
}
} // namespace tsw12
