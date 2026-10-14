#include "tsw/localization.hpp"
#include "localization_data.hpp"
#include <algorithm>
#include <cctype>
#include <set>
#include <stdexcept>

namespace tsw {
namespace {
std::size_t index(Language language) {
    const auto value = static_cast<std::size_t>(language);
    if (value >= Languages.size())
        throw std::invalid_argument("Invalid display language");
    return value;
}

std::size_t utf8_size(unsigned char first) {
    return first < 0x80 ? 1 : first < 0xe0 ? 2 : first < 0xf0 ? 3 : 4;
}

bool word(unsigned char c) {
    return std::isalnum(c) || c == '_';
}

bool boundary(std::string_view source, std::size_t at, std::string_view key) {
    return (!word(key.front()) || !at || !word(source[at - 1])) &&
           (!word(key.back()) || at + key.size() == source.size() || !word(source[at + key.size()]));
}
} // namespace

std::string_view language_id(Language language) {
    return localization_data::Ids.at(index(language));
}

std::string_view language_label(Language language) {
    return localization_data::Labels.at(index(language));
}

Language parse_language(std::string_view id) {
    for (const auto language : Languages)
        if (language_id(language) == id)
            return language;
    throw std::invalid_argument("Unknown language: " + std::string(id));
}

std::string_view localized_dialogue(Language language, int id) {
    return localization_data::Dialogues.at(index(language)).at(id);
}

std::string_view localized_opening(Language language) {
    return localization_data::Openings.at(index(language));
}

std::string_view localized_ending(Language language) {
    return localization_data::Endings.at(index(language));
}

std::string localized_text(Language language, std::string_view source) {
    const auto column = index(language);
    if (language == Language::English)
        return std::string(source);
    for (const auto& entry : localization_data::Text)
        if (source == entry.source)
            return std::string(entry.text[column]);
    // Single pass over canonical input: translated output is never recursively substituted.
    std::string result;
    bool translated = false;
    for (std::size_t at = 0; at < source.size();) {
        bool matched = false;
        for (const auto& entry : localization_data::Text)
            if (entry.compose && source.substr(at).starts_with(entry.source) &&
                boundary(source, at, entry.source)) {
                result += entry.text[column];
                translated = true;
                at += entry.source.size();
                matched = true;
                break;
            }
        if (!matched)
            result += source[at++];
    }
    if (translated &&
        (language == Language::Japanese || language == Language::ChineseFromJapanese ||
         language == Language::ChineseFromEnglish) &&
        result.ends_with('.')) {
        result.pop_back();
        result += "。";
    }
    return result;
}

std::vector<int> localization_codepoints() {
    std::set<int> points;
    for (int i = 32; i < 127; ++i)
        points.insert(i);
    const auto add = [&](std::string_view text) {
        for (std::size_t at = 0; at < text.size();) {
            const auto first = static_cast<unsigned char>(text[at]);
            const auto size = utf8_size(first);
            int cp = first & (size == 1 ? 0x7f : size == 2 ? 0x1f : size == 3 ? 0x0f : 0x07);
            for (std::size_t i = 1; i < size && at + i < text.size(); ++i)
                cp = (cp << 6) | (static_cast<unsigned char>(text[at + i]) & 0x3f);
            if (cp >= 32)
                points.insert(cp);
            at += size;
        }
    };
    for (const auto& entries : localization_data::Dialogues)
        for (const auto text : entries)
            add(text);
    for (const auto& entry : localization_data::Text)
        for (const auto text : entry.text)
            add(text);
    for (const auto text : localization_data::Labels)
        add(text);
    for (const auto text : localization_data::Openings)
        add(text);
    for (const auto text : localization_data::Endings)
        add(text);
    return {points.begin(), points.end()};
}

std::string wrap_localized_text(std::string_view source, float limit,
                                const std::function<float(std::string_view)>& measure) {
    std::string result, line, token;
    const auto emit = [&] {
        if (!line.empty() && measure(line + token) > limit) {
            while (!line.empty() && line.back() == ' ')
                line.pop_back();
            result += line + '\n';
            line.clear();
        }
        // Split even an oversized Latin word without splitting a UTF-8 codepoint.
        for (std::size_t at = 0; at < token.size();) {
            const auto size = std::min(utf8_size(static_cast<unsigned char>(token[at])), token.size() - at);
            const auto glyph = token.substr(at, size);
            if (!line.empty() && measure(line + glyph) > limit) {
                result += line + '\n';
                line.clear();
            }
            line += glyph;
            at += size;
        }
        token.clear();
    };
    for (std::size_t at = 0; at < source.size();) {
        const auto size = std::min(utf8_size(static_cast<unsigned char>(source[at])), source.size() - at);
        const auto glyph = source.substr(at, size);
        if (glyph == "\n") {
            emit();
            result += line + '\n';
            line.clear();
        } else if (glyph == " ") {
            emit();
            if (!line.empty())
                line += ' ';
        } else if (size > 1) {
            emit();
            token = glyph;
            emit();
        } else {
            token += glyph;
        }
        at += size;
    }
    emit();
    if (!line.empty())
        result += line + '\n';
    return result;
}
} // namespace tsw
