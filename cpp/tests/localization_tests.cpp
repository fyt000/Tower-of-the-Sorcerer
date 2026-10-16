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
            const auto original = Game::original_dialogue(static_cast<DialogueId>(i));
            REQUIRE(localized_dialogue(Language::English, static_cast<DialogueId>(i)) == original);
            if (!original.empty())
                REQUIRE_FALSE(localized_dialogue(language, static_cast<DialogueId>(i)).empty());
        }
    }
    REQUIRE_THROWS(parse_language("unknown"));
    REQUIRE_THROWS(language_id(static_cast<Language>(99)));
    REQUIRE_THROWS(localized_dialogue(Language::Japanese, static_cast<DialogueId>(268)));
    for (const auto language : Languages)
        for (int i = 0; i < 33; ++i)
            REQUIRE(localized_text(language, Game::monster_name(i)) ==
                    localized_dialogue(language, static_cast<DialogueId>(94 + i)));
}

TEST_CASE("Japanese tail is aligned semantically after the English split", "[localization]") {
    REQUIRE(localized_dialogue(Language::Japanese, static_cast<DialogueId>(263)).find("時空の門") !=
            std::string_view::npos);
    REQUIRE(localized_dialogue(Language::Japanese, static_cast<DialogueId>(265)) ==
            "このデータはロードできません。");
    REQUIRE(localized_dialogue(Language::Japanese, static_cast<DialogueId>(266)).find("８８００") !=
            std::string_view::npos);
    REQUIRE(localized_dialogue(Language::Japanese, static_cast<DialogueId>(267)).find("４４００") !=
            std::string_view::npos);
    REQUIRE(localized_dialogue(Language::EnglishFromJapanese, static_cast<DialogueId>(56))
                .find("absorb your power") != std::string_view::npos);
    REQUIRE(localized_dialogue(Language::ChineseFromEnglish, static_cast<DialogueId>(56)).find("合作") !=
            std::string_view::npos);
    REQUIRE(
        localized_dialogue(Language::ChineseFromJapanese, static_cast<DialogueId>(56)).find("吸收你的力量") !=
        std::string_view::npos);
    REQUIRE(localized_opening(Language::Japanese).find("全能") != std::string_view::npos);
    REQUIRE(localized_opening(Language::EnglishFromJapanese).find("omnipotent") != std::string_view::npos);
    REQUIRE(localized_opening(Language::ChineseFromJapanese).find("全能") != std::string_view::npos);
    REQUIRE(localized_opening(Language::ChineseFromEnglish).find("全知") != std::string_view::npos);
}

TEST_CASE("Rendering translates joined speeches and generated statuses in one pass", "[localization]") {
    const auto speech = std::string(Game::original_dialogue(static_cast<DialogueId>(4))) +
                        std::string(Game::original_dialogue(static_cast<DialogueId>(57)));
    REQUIRE(localized_text(Language::Japanese, speech) ==
            std::string(localized_dialogue(Language::Japanese, static_cast<DialogueId>(4))) +
                std::string(localized_dialogue(Language::Japanese, static_cast<DialogueId>(57))));
    REQUIRE(localized_text(Language::ChineseFromEnglish, "Found Super Mattock.") == "获得了鹤嘴锄。");
    REQUIRE(localized_text(Language::ChineseFromEnglish, "Defeated Zombie Knight. Received 20 gold.") ==
            "打倒了丧尸武士。获得了20 金币。");
    REQUIRE(localized_text(Language::English, speech) == speech);
    REQUIRE(localized_text(Language::Japanese, "unrecognized message") == "unrecognized message");
    REQUIRE(localized_text(Language::ChineseFromJapanese, "Warp Staff") == "瞬移之翼");
    REQUIRE(localized_text(Language::Japanese, "Warp Staff") == "空間転移の秘宝");
    REQUIRE(localized_text(Language::EnglishFromJapanese, "Superion Priest") == "High Priest");
}

TEST_CASE("Fairy speeches use readable language-specific spacing and punctuation", "[localization][npcs]") {
    struct Speeches {
        Language language;
        std::string_view ranked, unranked, low_score;
    };

    // Literal rendered prose catches joins between fragments, including the
    // English-from-Japanese rank suffix that begins with a period instead of a word.
    constexpr std::array cases{
        Speeches{
            Language::English,
            "Congratulations! You win the 3 place with the points which you got. I'm going to register "
            "your score. Judging by your vital power, offensive power, defensive power, and number of "
            "keys, you have 134 points. Congratulations! Your score is GREAT! I give you the special "
            "rank of BRAVE MAN. You may as well play as good as you have from this point on.",
            "Judging by your vital power, offensive power, defensive power, and number of keys, you "
            "have 201 points. Do you wish to go on? I give you the special rank of FIGHTER GOD. "
            "It was nice fight so far.",
            "Judging by your vital power, offensive power, defensive power, and number of keys, you "
            "have 0 points. If you have that many points, you might want to reconsider going higher... =)"},
        Speeches{
            Language::EnglishFromJapanese,
            "Congratulations! Your score placed 3. I'll record it in the rankings. Judging your ability "
            "by your HP, defense, attack, and keys so far, your score is 134 points. Congratulations! "
            "A perfect score! I award you the title Brave. Keep it up as you go on.",
            "Judging your ability by your HP, defense, attack, and keys so far, your score is 201 points. "
            "You've done well. I award you the title God of Battle. Well done making it this far.",
            "Judging your ability by your HP, defense, attack, and keys so far, your score is 0 points. "
            "At this score, pressing onward will be very difficult."},
        Speeches{Language::Japanese,
                 "おめでとう！得点が第3位の成績でした。スコアに登録しておきます。"
                 "「この階までのあなたの生命力、防御力、攻撃力、鍵の個数からあなたの実力を評価すると・・・"
                 "134点です。おめでとう！満点です。あなたには『勇者』の称号を差し上げましょう。"
                 "これから先もこの調子でね。」",
                 "「この階までのあなたの生命力、防御力、攻撃力、鍵の個数からあなたの実力を評価すると・・・"
                 "201点です。よくがんばりましたね。あなたには『闘神』の称号を差し上げましょう。"
                 "ここまでおつかれさまでした。」",
                 "「この階までのあなたの生命力、防御力、攻撃力、鍵の個数からあなたの実力を評価すると・・・"
                 "0点です。うーん、この点数だとこれから先へ進むのは、かなり無理があるでしょう。」"},
        Speeches{Language::ChineseFromJapanese,
                 "恭喜！你的得分排在第3名。已登记到排行榜。"
                 "「根据到这一层为止的生命、防御、攻击和钥匙数量，评估你的实力，得分为……"
                 "134分。恭喜！满分！授予你『勇者』的称号。之后也要保持这个势头。」",
                 "「根据到这一层为止的生命、防御、攻击和钥匙数量，评估你的实力，得分为……"
                 "201分。你很努力了。授予你『斗神』的称号。能走到这里，辛苦你了。」",
                 "「根据到这一层为止的生命、防御、攻击和钥匙数量，评估你的实力，得分为……"
                 "0分。嗯，这个分数的话，继续前进会相当勉强。」"},
        Speeches{Language::ChineseFromEnglish,
                 "恭喜！凭借这个得分，你获得了第3名。我会登记你的得分。"
                 "根据你的生命、攻击、防御和钥匙数量，你的得分为134分。恭喜！你的得分很棒！"
                 "我授予你特别称号：勇者。接下来也要像之前一样好好发挥。",
                 "根据你的生命、攻击、防御和钥匙数量，你的得分为201分。你想继续前进吗？"
                 "我授予你特别称号：斗神。到目前为止，你战斗得不错。",
                 "根据你的生命、攻击、防御和钥匙数量，你的得分为0分。"
                 "这个分数的话，或许该重新考虑是否继续往上走…… =)"}};
    for (const auto& speeches : cases) {
        CAPTURE(language_id(speeches.language));
        REQUIRE(localized_fairy_dialogue(speeches.language, 134, 3, 3) == speeches.ranked);
        REQUIRE(localized_fairy_dialogue(speeches.language, 201, 0, 4) == speeches.unranked);
        REQUIRE(localized_fairy_dialogue(speeches.language, 0, 0, 1) == speeches.low_score);
    }
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
