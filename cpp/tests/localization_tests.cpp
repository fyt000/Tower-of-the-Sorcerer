#include "tsw/game.hpp"
#include "tsw/localization.hpp"
#include "tsw/settings.hpp"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <fstream>

using namespace tsw;

TEST_CASE("Every C++ language has complete dialogue and stable identifiers", "[localization]") {
    for (const auto language : Languages) {
        REQUIRE(parse_language(language_id(language)) == language);
        REQUIRE_FALSE(language_label(language).empty());
        REQUIRE_FALSE(localized_opening(language).empty());
        for (int i = 0; i < 268; ++i) {
            const auto original = Game::original_dialogue(i);
            REQUIRE(localized_dialogue(Language::English, i) == original);
            if (!original.empty())
                REQUIRE_FALSE(localized_dialogue(language, i).empty());
        }
    }
    REQUIRE_THROWS(parse_language("unknown"));
    REQUIRE_THROWS(language_id(static_cast<Language>(99)));
    REQUIRE_THROWS(localized_dialogue(Language::Japanese, 268));
    for (const auto language : Languages)
        for (int i = 0; i < 33; ++i)
            REQUIRE(localized_text(language, Game::monster_name(i)) == localized_dialogue(language, 94 + i));
}

TEST_CASE("Japanese tail is aligned semantically after the English split", "[localization]") {
    REQUIRE(localized_dialogue(Language::Japanese, 263).find("時空の門") != std::string_view::npos);
    REQUIRE(localized_dialogue(Language::Japanese, 265) == "このデータはロードできません。");
    REQUIRE(localized_dialogue(Language::Japanese, 266).find("８８００") != std::string_view::npos);
    REQUIRE(localized_dialogue(Language::Japanese, 267).find("４４００") != std::string_view::npos);
    REQUIRE(localized_dialogue(Language::EnglishFromJapanese, 56).find("absorb your power") !=
            std::string_view::npos);
    REQUIRE(localized_dialogue(Language::ChineseFromEnglish, 56).find("合作") != std::string_view::npos);
    REQUIRE(localized_dialogue(Language::ChineseFromJapanese, 56).find("吸收你的力量") !=
            std::string_view::npos);
    REQUIRE(localized_opening(Language::Japanese).find("全能") != std::string_view::npos);
    REQUIRE(localized_opening(Language::EnglishFromJapanese).find("omnipotent") != std::string_view::npos);
    REQUIRE(localized_opening(Language::ChineseFromJapanese).find("全能") != std::string_view::npos);
    REQUIRE(localized_opening(Language::ChineseFromEnglish).find("全知") != std::string_view::npos);
}

TEST_CASE("Rendering translates joined speeches and generated statuses in one pass", "[localization]") {
    const auto speech = std::string(Game::original_dialogue(4)) + std::string(Game::original_dialogue(57));
    REQUIRE(localized_text(Language::Japanese, speech) ==
            std::string(localized_dialogue(Language::Japanese, 4)) +
                std::string(localized_dialogue(Language::Japanese, 57)));
    REQUIRE(localized_text(Language::ChineseFromEnglish, "Found Super Mattock.") == "获得了鹤嘴锄。");
    REQUIRE(localized_text(Language::ChineseFromEnglish, "Defeated Zombie Knight. Received 20 gold.") ==
            "打倒了丧尸武士。获得了20 金币。");
    REQUIRE(localized_text(Language::English, speech) == speech);
    REQUIRE(localized_text(Language::Japanese, "unrecognized message") == "unrecognized message");
    REQUIRE(localized_text(Language::ChineseFromJapanese, "Warp Staff") == "瞬移之翼");
    REQUIRE(localized_text(Language::Japanese, "Warp Staff") == "空間転移の秘宝");
    REQUIRE(localized_text(Language::EnglishFromJapanese, "Superion Priest") == "High Priest");
}

TEST_CASE("Unicode wrapping preserves codepoints, paragraphs and words", "[localization]") {
    const auto measure = [](std::string_view s) {
        return float(std::count_if(s.begin(), s.end(), [](unsigned char c) { return (c & 0xc0) != 0x80; }));
    };
    REQUIRE(wrap_localized_text("日本語の文章", 3, measure) == "日本語\nの文章\n");
    REQUIRE(wrap_localized_text("魔法之塔\n\n新的旅途", 4, measure) == "魔法之塔\n\n新的旅途\n");
    REQUIRE(wrap_localized_text("one two three", 7, measure) == "one two\nthree\n");
    REQUIRE(wrap_localized_text("abcdefgh", 3, measure) == "abc\ndef\ngh\n");
    const auto points = localization_codepoints();
    REQUIRE(std::find(points.begin(), points.end(), int(U'塔')) != points.end());
    REQUIRE(std::find(points.begin(), points.end(), int(U'译')) != points.end());
}

TEST_CASE("Language preferences round trip and old settings default to English", "[localization][settings]") {
    const auto path = std::filesystem::path(TSW_TEST_TEMP) / "localization-settings.json";
    for (const auto language : Languages) {
        Settings settings;
        settings.language = language_id(language);
        save_settings(path, settings);
        REQUIRE(load_settings(path).language == language_id(language));
    }
    {
        std::ofstream out(path);
        out << R"({"game_speed":2,"recording":true})";
    }
    REQUIRE(load_settings(path).language == "en");
    {
        std::ofstream out(path);
        out << R"({"language":"bad-id"})";
    }
    REQUIRE_THROWS(load_settings(path));
    std::filesystem::remove(path);
}
