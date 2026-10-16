#pragma once
#include "tsw/planner.hpp"
#include <array>
#include <memory>
#include <string>

namespace tsw::planner::detail {
struct History {
    std::shared_ptr<const History> parent;
    std::vector<PlayerInput> inputs;
};

struct Node {
    Game game;
    std::shared_ptr<const History> history;
    int input_count{};
    double score{};
    std::uint64_t allocation{};
};

struct Paths {
    std::array<int, CellCount> prev, distance;
    std::array<Direction, CellCount> direction;
};

struct Policy {
    int goal = 51;
    int max_purchases = 1;
    SearchPolicy early_policy = SearchPolicy::Balanced;
    bool hp_buys = false;
    bool atomic_events = true;
    bool defer_merchant_hp = true;
    bool reserve_early_potions = true;
};

int neighbor(int position, Direction);
PlayerInput move(Direction);
PlayerInput use(Item, int floor = -1);
PlayerInput choose(int);
bool input(Game&, const PlayerInput&, std::vector<PlayerInput>&);
std::vector<Direction> path(const Paths&, int target);
int farm_gold(const Game&, int tile);
bool dominates(const Hero&, const Hero&);
std::vector<PlayerInput> history(const Node&);
bool same_progress(const Game&, const Game&);
Route continue_route(std::span<const PlayerInput>, const Route&, std::size_t split, bool repair_access);

class Engine {
  public:
    explicit Engine(Policy policy = {}) : config(policy) {}

    Policy config;
    std::uint64_t evaluations{}, rejects{};
    double movement_cost(const Game&, int) const;
    Paths roads(const Game&) const;
    Paths room_paths(const Game&, int, int avoided_cell = -1) const;
    bool eligible(const Game&, int) const;
    bool free_tile(const Game&, int) const;
    bool walk(Game&, const Paths&, int, std::vector<PlayerInput>&) const;
    void normalize_local(Game&, std::vector<PlayerInput>&) const;
    void normalize(Game&, std::vector<PlayerInput>&) const;
    bool fly_to(Game&, int, std::vector<PlayerInput>&) const;
    std::vector<std::pair<Game, std::vector<PlayerInput>>> flight_origins(const Game&) const;
    std::string signature(const Game&) const;
    double rank(const Game&) const;
    void attach(Node&, const Node&, std::vector<PlayerInput>) const;
    std::vector<Node> expand(const Node&);
};
} // namespace tsw::planner::detail
