#pragma once
#include "tsw/dialogue_ids.hpp"
#include <format>
#include <string>
#include <string_view>

namespace tsw::detail {

// English separates words/sentences with a space; Japanese and Chinese join
// directly. Catalog padding is inconsistent, so normalize it at those joins.
template <class Text>
std::string compose_fairy_dialogue(int score, int rank, int visits, const Text& text,
                                   std::string_view separator = " ") {
    using enum DialogueId;
    const auto fragment = [&](DialogueId id) {
        const std::string_view value = text(id);
        const auto first = value.find_first_not_of(' ');
        return first == std::string_view::npos ? std::string_view{}
                                               : value.substr(first, value.find_last_not_of(' ') - first + 1);
    };
    const auto numbered = [&](DialogueId prefix, int value, DialogueId suffix) {
        // Numeric suffixes carry their own grammar: " points.", ". I'll...",
        // "点です。", etc. Preserve that padding/punctuation without adding more.
        return std::format("{}{}{}{}", fragment(prefix), separator, value, text(suffix));
    };
    std::string result;
    const auto append = [&](std::string_view sentence) {
        if (!result.empty())
            result += separator;
        result += sentence;
    };
    if (rank > 0)
        append(numbered(FairyRankPrefix, rank, FairyRankSuffix));
    append(numbered(FairyScorePrefix, score, FairyScoreSuffix));
    if (score < 50)
        append(fragment(FairyReconsider));
    else if (score < 60)
        append(fragment(FairyBelowAverage));
    else if (score < 80)
        append(fragment(FairyOrdinary));
    else if (score < 100)
        append(fragment(FairyDoingFine));
    else if (score <= 9999) {
        // The recovered routine awards no title above 9999; retain that bound.
        append(fragment(score <= 140 ? FairyGreatScore : FairyContinue));
        const auto title = score <= 120   ? FairyFighter
                           : score <= 140 ? FairyBrave
                           : score <= 160 ? FairyHero
                           : score <= 200 ? FairySwordEmperor
                                          : FairyFighterGod;
        append(std::format("{}{}{}{}", fragment(FairyTitlePrefix), separator, fragment(title),
                           fragment(FairyTitleSuffix)));
        // speak_fairy has already counted the current visit.
        append(fragment(visits <= 3 ? FairyKeepGoing : FairyFarewell));
    }
    return result;
}
} // namespace tsw::detail
