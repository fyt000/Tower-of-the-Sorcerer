#include "desktop_checks.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace tsw {
namespace {
void fixture(Game& game, DesktopUi& ui, const std::string& smoke) {
    if (smoke == "capture") {
        game.hero.floor = 3;
        game.hero.x = 4;
        game.hero.y = 9;
        game.move(Direction::Up);
    } else if (smoke == "stairs") {
        game.hero.x = 0;
        game.hero.y = 1;
        game.move(Direction::Up);
    } else if (smoke == "fight") {
        game.hero.x = game.hero.y = 5;
        game.hero.attack = game.hero.defense = 10;
        game.hero.hp = 1000;
        game.tile(1, cell(5, 4)) = GreenSlime;
        game.move(Direction::Up);
    } else if (smoke == "floor10" || smoke == "fairy") {
        game.hero.floor = 10;
        game.hero.x = 5;
        game.hero.y = smoke == "floor10" ? 4 : 5;
        if (smoke == "fairy") {
            game.tile(10, cell(5, 4)) = Fairy;
            game.move(Direction::Up);
        } else
            game.check_floor();
    } else if (smoke == "inventory" || smoke == "items" || smoke == "item" || smoke == "flight" ||
               smoke == "enemies") {
        game.hero.items.fill(1);
        game.inventory(Item::WarpStaff) = 5;
        game.hero.yellow_keys = 4;
        game.hero.blue_keys = 2;
        game.hero.red_keys = 1;
        game.hero.highest_floor = 7;
        ui.inventory = smoke == "inventory";
        ui.enemies = smoke == "enemies";
        ui.selected_item = smoke == "item" ? int(Item::Bomb) : -1;
        ui.flight = smoke == "flight" ? 5 : -1;
        game.status = "Click an item to inspect or use it. [I] opens the inventory.";
    } else if (smoke == "shop") {
        game.hero.x = game.hero.y = 5;
        game.hero.gold = 100;
        game.tile(1, cell(5, 4)) = Altar;
        game.move(Direction::Up);
    } else if (smoke == "ending") {
        game.hero.floor = 50;
        game.hero.x = game.hero.y = 5;
        game.tile(50, cell(5, 4)) = Zeno;
        game.move(Direction::Up);
    } else if (smoke == "help")
        ui.help = true;
    else if (smoke == "backside")
        game.hero.cycle_factor_minus_one = BacksideFactor - 1;
}
} // namespace

int verify_smoke(DesktopSession& session, const std::string& name, const std::filesystem::path& output) {
    std::filesystem::create_directories(output);
    auto& game = session.game;
    auto& ui = session.ui;
    auto& renderer = session.renderer;
    const auto require = [&](bool condition, const char* description) {
        if (!condition)
            throw std::runtime_error(name + ": " + description);
    };
    fixture(game, ui, name);
    session.audio.restart(game);
    bool ending_pause = false, slot_pause = false, slot_restore = false;
    if (name == "slots") {
        for (int number = 1; number <= ManualSaveSlotCount; ++number) {
            game.new_game();
            game.hero.floor = number;
            game.hero.hp = 1000 + number * 100;
            game.hero.cycle_factor_minus_one = number >= 5 ? 43 : 0;
            game.hero.later_cycle = number >= 7;
            session.dispatch({Action::SaveSlot, number});
        }
        game.new_game();
        game.push(Op::Wait);
        session.dispatch({Action::OpenLoadSlots});
        require(std::all_of(ui.save_slots.begin(), ui.save_slots.end(),
                            [](const auto& slot) { return slot.state == SaveSlotState::Ready; }),
                "All eight slots must be readable");
    }
    for (int frame = 0; frame < 400; ++frame) {
        renderer.advance(1.f);
        if (name == "slots" && frame == 90) {
            slot_pause = game.commands.size() == 1 && ui.save_picker == SavePicker::Load;
            session.dispatch({Action::LoadSlot, 8});
            slot_restore = !game.busy() && game.hero.floor == 8 && game.hero.hp == 1800 &&
                           game.hero.cycle_factor_minus_one == 43 && game.hero.later_cycle;
            session.dispatch({Action::OpenSaveSlots});
        }
        if (ui.ending_wait) {
            const auto commands = game.commands;
            session.advance_commands(1.f);
            ending_pause = game.busy() && game.visual.raster_mode == 8 &&
                           game.hero.cycle_factor_minus_one == 0 && game.commands == commands;
            session.dispatch({Action::ContinueEnding});
        }
        if (game.dialogue && !game.dialogue->shop)
            session.dispatch({Action::Continue});
        session.advance_commands(1.f);
        renderer.draw(game, ui, {-1, -1});
        renderer.present();
    }
    const auto& hero = game.hero;
    if (name == "capture")
        require(hero.floor == 2 && hero.hp == 400, "Capture must finish at the prison");
    if (name == "stairs")
        require(hero.floor == 2, "Stairs must arrive on the next floor");
    if (name == "fight")
        require(hero.gold > 0, "Completed combat must give its reward");
    if (name == "ending")
        require(ending_pause && hero.cycle_factor_minus_one == BacksideFactor - 1,
                "Ending must pause at the card, then enter the backside");
    if (name == "slots")
        require(slot_pause && slot_restore, "Slot picker must pause commands and restore slot eight");
    if (name == "fairy") {
        Game checkpoint;
        checkpoint.load(output / "saves/save0.dat", SaveKind::Checkpoint);
        require(checkpoint.hero.fairy_visits == 1 && checkpoint.hero.fairy_score == 415 &&
                    checkpoint.tile(10, 27) == Road,
                "Completed Fairy scene must write the raw checkpoint");
    }
    require(renderer.screenshot(output / (name + ".png")), "Screenshot must be written");
    std::cout << "Desktop " << name << ": floor=" << hero.floor << " hp=" << hero.hp << " gold=" << hero.gold
              << '\n';
    return 0;
}
} // namespace tsw
