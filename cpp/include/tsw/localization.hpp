#pragma once
#include "tsw/dialogue_ids.hpp"
#include "tsw/status_message.hpp"
#include <array>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace tsw {
class Game;
// Display preference only: saves, replay hashes and game commands retain canonical text.
enum class Language { English, Japanese, EnglishFromJapanese, ChineseFromJapanese, ChineseFromEnglish };
inline constexpr std::array<Language, 5> Languages{
    Language::English, Language::Japanese, Language::EnglishFromJapanese, Language::ChineseFromJapanese,
    Language::ChineseFromEnglish};
std::string_view language_id(Language);
std::string_view language_label(Language);
Language parse_language(std::string_view);
// Zero-based catalog index, unlike the one-based Op::Dialogue speech ID.
std::string_view localized_dialogue(Language, DialogueId id);
std::string localized_fairy_dialogue(Language, int score, int rank, int visits);
std::string localized_text(Language, std::string_view);
std::string localized_status_message(Language, const StatusMessage&);
std::string localized_status(Language, const Game&);
std::string_view localized_opening(Language);
std::string_view localized_ending(Language);
std::vector<int> localization_codepoints();
// UTF-8 boundaries are also respected for unspaced CJK text and oversized words.
std::string wrap_localized_text(std::string_view, float limit,
                                const std::function<float(std::string_view)>& measure);
} // namespace tsw
