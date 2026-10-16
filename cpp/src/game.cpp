#include "tsw/game.hpp"
#include "fairy_dialogue.hpp"
#include "original_constants.hpp"
#include "tsw/localization.hpp"
#include <algorithm>
#include <stdexcept>

namespace tsw {
namespace {

constexpr std::array<int, CellCount> spiral() {
    std::array<int, CellCount> result{};
    int n = 0;
    for (int inset = 0; inset <= BoardWidth / 2; ++inset) {
        const int end = BoardWidth - 1 - inset;
        for (int y = inset; y <= end; ++y)
            result[n++] = cell(inset, y);
        for (int x = inset + 1; x <= end; ++x)
            result[n++] = cell(x, end);
        if (end > inset) {
            for (int y = end - 1; y >= inset; --y)
                result[n++] = cell(end, y);
            for (int x = end - 1; x > inset; --x)
                result[n++] = cell(x, inset);
        }
    }
    return result;
}

constexpr auto StairOrder = spiral();

int signed_word(std::uint16_t value) {
    return value < 32768 ? value : int(value) - 65536;
}
} // namespace

Game::Game() {
    new_game();
}

void Game::new_game() {
    run_history = {};
    ending_summary.reset();
    original_save_record_.reset();
    hero = Hero{};
    floors = original::Maps;
    monsters = original::Monsters;
    commands.clear();
    dialogue.reset();
    fight_.reset();
    visual = Visual{};
    sounds.clear();
    stopped_ = false;
    shop_kind_ = ShopKind::None;
    checkpoint_requested = false;
    contact_index = cell(hero.x, hero.y);
    scratch_index = neighbor_index = door_opened = 0;
    message_code = msg::Empty;
    prepared_status_ = {};
    displayed_status_.reset();
    status = "Find the princess at the top of the tower.";
}

void Game::initialize_cycle() {
    // 0x455CB8: cycle 2 resets gold/items; cycle 3 and later preserve them.
    const Hero carried = hero;
    const int factor = hero.cycle_factor_minus_one, later = hero.later_cycle;
    new_game();
    hero.cycle_factor_minus_one = factor;
    hero.later_cycle = later;
    if (factor) {
        hero.hp = carried.hp;
        hero.attack = carried.attack;
        hero.defense = carried.defense;
    }
    if (later) {
        hero.gold = carried.gold;
        hero.highest_floor = carried.highest_floor;
        hero.items = carried.items;
        hero.equipment_found = carried.equipment_found;
    }
    run_history.dragon_slayer_acquired = inventory(Item::DragonSlayer) > 0;
}

void Game::next_cycle() {
    const EndingSummary summary{hero, run_history};
    if (!hero.cycle_factor_minus_one)
        hero.cycle_factor_minus_one = BacksideFactor - 1;
    else
        hero.later_cycle = 1;
    initialize_cycle();
    ending_summary = summary;
    status = "The backside tower begins.";
}

std::string_view Game::item_name(Item item) {
    return item_definition(item).name;
}

std::string_view Game::monster_name(int index) {
    return original::MonsterNames.at(index);
}

std::string_view Game::original_dialogue(DialogueId id) {
    return original::Dialogue.at(std::to_underlying(id));
}

void Game::push(Op op, int a, int b) {
    commands.push_back({op, static_cast<std::uint16_t>(a), static_cast<std::uint16_t>(b)});
}

bool Game::busy() const {
    return dialogue.has_value() || fight_.has_value() || !commands.empty() || stopped_ || hero.hp <= 0;
}

bool Game::move(Direction direction) {
    if (busy())
        return false;
    hero.facing = direction;
    int x = hero.x, y = hero.y;
    switch (direction) {
    case Direction::Up:
        --y;
        break;
    case Direction::Down:
        ++y;
        break;
    case Direction::Left:
        --x;
        break;
    case Direction::Right:
        ++x;
        break;
    }
    if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardWidth)
        return false;
    contact_index = cell(x, y);
    contact();
    return true;
}

void Game::expand_door() {
    if (commands.empty() || commands.back().op != Op::DoorFrame)
        throw std::logic_error("Door expansion without a door request");
    const Command request = commands.back();
    commands.pop_back();
    // 0x4660D0 inserts descending frames; playback is ascending.
    for (int frame = 16; frame >= 1; --frame) {
        push(Op::Wait, 0, frame);
        push(Op::DoorFrame, request.a, request.b);
    }
}

void Game::update_status(int code) {
    // Opcode zero refreshes the current classification; one publishes prepared text.
    if (code != msg::Refresh)
        message_code = code;
    publish_status();
}

void Game::publish_status() {
    if (message_code < msg::Empty || !valid_dialogue(DialogueId::StatusOffset + message_code))
        return;
    displayed_status_ =
        message_code == msg::Prepared
            ? prepared_status_
            : StatusMessage{.text = DialogueId::StatusOffset + message_code, .formatted = false};
    status = localized_status_message(Language::English, *displayed_status_);
}

void Game::show_dialogue(SpeechId id) {
    if (std::to_underlying(id) < 1 || std::to_underlying(id) > std::ssize(original::Dialogue))
        throw std::runtime_error("Invalid original speech ID");
    dialogue = Dialogue{std::string(original_dialogue(dialogue_for(id))), continuation_for(id), false, {}};
    if (is_fairy_speech(id))
        dialogue->text =
            detail::compose_fairy_dialogue(hero.fairy_score, hero.fairy_rank, hero.fairy_visits,
                                           [](DialogueId index) { return original_dialogue(index); });
    // These conversations store their final paragraph in a separate text entry.
    switch (id) {
    case SpeechId::ThiefFirstDeparture:
        dialogue->text += original_dialogue(DialogueId::ThiefFirstEquipmentAdvice);
        break;
    case SpeechId::ThiefSecondDeparture:
        dialogue->text += original_dialogue(DialogueId::ThiefSecondEquipmentAdvice);
        break;
    case SpeechId::ZenoRevealsPlan:
        dialogue->text += original_dialogue(DialogueId::ZenoPlan);
        break;
    }
}

bool Game::continue_dialogue() {
    if (!dialogue || dialogue->shop)
        return false;
    const auto stage = dialogue->continuation;
    dialogue.reset();
    continue_original(stage);
    return true;
}

void Game::finish_commands(bool continue_speech) {
    // A finite guard detects accidental endless command production in tests/loaders.
    for (std::size_t count = 0; count < 10000000; ++count) {
        if (dialogue) {
            if (continue_speech && !dialogue->shop)
                continue_dialogue();
            else
                return;
        }
        if (!run_one())
            return;
    }
    throw std::runtime_error("Command drain exceeded ten million operations");
}

bool Game::run_one(Command* executed) {
    if (dialogue || stopped_)
        return false;
    if (fight_ && commands.size() == fight_->base_commands)
        battle_step();
    if (commands.empty()) {
        visual.overlay_cell = visual.door_cell = -1;
        visual.battle = false;
        visual.layers.fill({});
        return false;
    }
    const Command command = commands.back();
    commands.pop_back();
    if (executed)
        *executed = command;
    const int a = signed_word(command.a), b = signed_word(command.b);
    switch (command.op) {
    case Op::Wait:
        break;
    case Op::Sound:
        sounds.push_back(static_cast<SoundCue>(a));
        break;
    case Op::Message:
        update_status(a);
        break;
    case Op::Defeat:
        hero.hp = 0;
        visual.dead = true;
        stopped_ = true;
        commands.clear();
        fight_.reset();
        status = "The hero has fallen. Restore a saved game or start again.";
        break;
    case Op::EnemyStrike: {
        const int enemy_damage_per_strike = std::max(
            0, monsters.at(visual.monster_index).attack * (hero.cycle_factor_minus_one + 1) - hero.defense);
        hero.hp = std::max(0, hero.hp - enemy_damage_per_strike);
        break;
    }
    case Op::HeroStrike: {
        const int enemy = visual.monster_index;
        const int hit = std::max(0, hero.attack * attack_multiplier(enemy, visual.enemy_first) -
                                        monsters.at(enemy).defense * (hero.cycle_factor_minus_one + 1));
        visual.enemy_hp = std::max(0, visual.enemy_hp - hit);
        break;
    }
    case Op::SetTile:
    case Op::WriteTile:
        tile(hero.floor, a) = static_cast<std::uint8_t>(b);
        visual.layers.at(a) = {};
        if (a == visual.overlay_cell)
            visual.overlay_cell = -1;
        break;
    case Op::Reward:
        hero.gold += a * (inventory(Item::LuckyGold) + 1);
        break;
    case Op::UpdateInventory:
        break;
    case Op::Overlay:
        visual.overlay_cell = a;
        visual.mask = b;
        if (commands.empty() || commands.back().op != Op::Wait)
            throw std::logic_error("Overlay has no color operands");
        visual.underlying = commands.back().a;
        visual.color = commands.back().b;
        visual.layers.at(a) = {visual.mask, visual.color, visual.underlying};
        break;
    case Op::Dialogue:
        show_dialogue(static_cast<SpeechId>(a));
        break;
    case Op::Callback:
        switch (static_cast<Callback>(a)) {
        case Callback::Capture: {
            hero.sword = hero.shield = EquipmentTier::None;
            hero.equipment_found[4] = hero.equipment_found[SacredShieldFlag] = 0;
            if (!hero.cycle_factor_minus_one) {
                hero.hp = 400;
                hero.attack = hero.defense = 10;
            } else
                hero.items.fill(0);
            hero.floor = hero.highest_floor = 2;
            hero.x = 2;
            hero.y = 7;
            visual.hide_hero = false;
            visual.raster_mode = RasterMode::Inactive;
            change_music_for_floor();
            push(Op::Wait);
            push(Op::Callback, Callback::RestoreBoard);
            push(Op::Wait);
            queue_speech(SpeechId::ThiefWakesHero);
            push(Op::Wait);
            queue_speech(SpeechId::ThiefCallsHero);
            push(Op::Wait);
            queue_speech(SpeechId::Unconscious);
            push(Op::Wait);
            queue_speech(SpeechId::Unconscious);
            push(Op::UpdateInventory);
            push(Op::Message);
            break;
        }
        case Callback::SummonZeno:
            tile(hero.floor, cell(5, 2)) = Zeno;
            summon(cell(5, 2), Zeno);
            break;
        case Callback::SummonGuards:
            summon_guards();
            break;
        case Callback::Transformation:
            visual.raster_frame = b;
            transform_vampire();
            break;
        case Callback::CheckGuards:
            check_guards();
            break;
        case Callback::NextCycle:
            next_cycle();
            break;
        case Callback::Title:
            visual.raster_mode = RasterMode::Title;
            break;
        case Callback::RestoreBoard:
            visual.raster_mode = RasterMode::Inactive;
            visual.hide_hero = false;
            break;
        case Callback::BattleEnd:
            visual.battle = false;
            break;
        case Callback::ForcedBattle:
            contact_index = b;
            battle(true);
            break;
        case Callback::Teleport:
            hero.floor = b;
            hero.highest_floor_stair_kind =
                StairKind::None; // Original floor-change callback redraws the map.
            if (b == 50) {
                hero.x = floors.at(b).up_landing % BoardWidth;
                hero.y = floors.at(b).up_landing / BoardWidth;
                hero.facing = Direction::Up;
            }
            visual.raster_mode = RasterMode::Inactive;
            break;
        case Callback::RasterScene:
            visual.raster_frame = b;
            visual.raster_mode =
                commands.empty() ? RasterMode::OpeningDissolve : static_cast<RasterMode>(commands.back().a);
            break;
        case Callback::HideHero:
            visual.hide_hero = true;
            break;
        case Callback::HidePanels:
        case Callback::CacheScene:
            // VCL callbacks 14/15 affect the compositor, not gameplay state.
            break;
        }
        break;
    case Op::MoveTile:
        tile(hero.floor, b) = tile(hero.floor, a);
        tile(hero.floor, a) = Road;
        visual.layers.at(a) = visual.layers.at(b) = {};
        break;
    case Op::DoorFrame: {
        visual.door_cell = a;
        visual.door_mode = b;
        visual.door_tile = tile(hero.floor, a);
        if (commands.empty() || commands.back().op != Op::Wait)
            throw std::logic_error("Door frame has no frame operand");
        visual.door_frame = commands.back().b;
        if (visual.door_frame == 16) {
            tile(hero.floor, a) = b == int(DoorMotion::CloseGate)   ? SealedGate
                                  : b == int(DoorMotion::RaiseWall) ? Wall
                                                                    : Road;
        }
        break;
    }
    case Op::LargeMonsterStrike:
        visual.enemy_hp = std::max(
            0, visual.enemy_hp - std::max(0, hero.attack - monsters.at(visual.monster_index).defense *
                                                               (hero.cycle_factor_minus_one + 1)));
        break;
    case Op::FloorMusic:
        change_music_for_floor();
        break;
    case Op::HpDelta:
        hero.hp = std::max(0, hero.hp + a);
        if (!hero.hp)
            queue_death();
        break;
    case Op::PincerDamage:
        hero.hp /= 2;
        if (!hero.hp)
            queue_death();
        break;
    case Op::SetHeroValue:
        // Original (&hero.hp)[a] write. Keep explicit slot names instead of pointer arithmetic.
        switch (static_cast<HeroField>(a)) {
        case HeroField::HitPoints:
            hero.hp = b;
            break;
        case HeroField::Attack:
            hero.attack = b;
            break;
        case HeroField::Defense:
            hero.defense = b;
            break;
        case HeroField::Gold:
            hero.gold = b;
            break;
        default:
            throw std::runtime_error("Unmapped original hero write slot");
        }
        break;
    case Op::MovementFrame:
        break;
    case Op::StairFrame:
        if (b < 1 || b > CellCount)
            throw std::runtime_error("Invalid stair sequence index");
        visual.stair_revealing = a == 1;
        visual.stair_cover[StairOrder[b - 1]] = a == 0;
        if (a == 1 && b == CellCount)
            visual.stair_source_floor = -1;
        break;
    case Op::DeathScene:
        visual.dead = true;
        break;
    }
    return true;
}

void Game::queue_death() {
    commands.clear();
    fight_.reset();
    push(Op::Defeat);
    push(Op::Wait);
    push(Op::DeathScene);
}

int Game::animation_offset(int t) const {
    if (t == Lava || t == StarVoid)
        return 147;
    if (t == Altar)
        return 2;
    // Completing the second gate conversation freezes its two map frames.
    if (t == TimeGate || t == TimeGate2)
        return hero.speech_seen(SpeechId::HeroFindsDoll) == 1 ? 0 : 1;
    if ((t >= Merchant && t <= OldMan2) || (t >= GreenSlime && t <= Vampire + 1) ||
        (t >= GoldenKnight && t <= 157))
        return 1;
    if ((t >= OctopusFirst && t <= 105) || (t >= DragonFirst && t <= 123))
        return 9;
    return 0;
}
} // namespace tsw
