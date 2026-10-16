#pragma once
#include "tsw/game_state.hpp"
#include <glaze/json.hpp>

// Runtime v3 keeps its original JSON keys and numeric enum representation.
// Member names may improve without invalidating an existing worker checkpoint.
template <> struct glz::meta<tsw::Hero> {
    static constexpr auto modify = glz::object("highest_floor_stair", &tsw::Hero::highest_floor_stair_kind);
};

template <> struct glz::meta<tsw::EnemyInfo> {
    static constexpr auto modify = glz::object("row", &tsw::EnemyInfo::monster_index);
};

template <> struct glz::meta<tsw::Visual> {
    static constexpr auto modify = glz::object("enemy_index", &tsw::Visual::monster_index);
};

template <> struct glz::meta<tsw::GameState::Fight> {
    using T = tsw::GameState::Fight;
    static constexpr auto modify = glz::object("enemy", &T::monster_index, "hero_hits", &T::hero_strike_count,
                                               "enemy_hits", &T::enemy_strike_count);
};
