#pragma once
#include "tsw/dialogue_ids.hpp"

namespace tsw {
namespace msg {
// Recovered Op::Message operands remain integers at the command/probe boundary.
enum Code : int {
    Refresh = 0,     // Keep the current classification when executing an opcode.
    Empty = Refresh, // Clear text when this is the current classification.
    Prepared = 1,
    OldMan = 12,
    Merchant = 13,
    Fairy = 14,
    Thief = 15,
    MissingKey = 16,
    Stairs = 19,
    Altar = 24,
    Lava = 52,
    SnowFailed = 65,
    MagicianA = 110,
    MagicianB = 111,
    Pincer = 112,
};

// Later cycles use a separate pair of magician status entries in the catalog.
inline constexpr int BacksideMagicOffset = 28;
} // namespace msg

// Retain the catalog identity and numeric operand until presentation chooses a language.
struct StatusMessage {
    DialogueId text = DialogueId::StatusOffset;
    int amount{};
    int monster_index = -1;
    bool formatted = true; // Static opcodes can address a fragment that also has a result template.
    friend bool operator==(const StatusMessage&, const StatusMessage&) = default;
};
} // namespace tsw
