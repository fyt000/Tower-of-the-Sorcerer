#pragma once
#include <array>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace tsw {
// Display preference only: saves, replay hashes and game commands retain canonical text.
enum class Language { English, Japanese, EnglishFromJapanese, ChineseFromJapanese, ChineseFromEnglish };
inline constexpr std::array<Language, 5> Languages{
    Language::English, Language::Japanese, Language::EnglishFromJapanese, Language::ChineseFromJapanese,
    Language::ChineseFromEnglish};
std::string_view language_id(Language);
std::string_view language_label(Language);
Language parse_language(std::string_view);
std::string_view localized_dialogue(Language, int id);
std::string localized_text(Language, std::string_view);
std::string_view localized_opening(Language);
std::string_view localized_ending(Language);
std::vector<int> localization_codepoints();
// UTF-8 boundaries are also respected for unspaced CJK text and oversized words.
std::string wrap_localized_text(std::string_view, float limit,
                                const std::function<float(std::string_view)>& measure);
} // namespace tsw
