#pragma once
#include <utility>

namespace tsw {
// Recovered numeric domains. Save-backed fields retain the Delphi values.
enum class RasterMode : int {
    Inactive = -1,
    OpeningDissolve = 0,
    OpeningStory = 1,
    EndingDissolve = 2,
    EndingShrink = 4,
    EndingStory = 5,
    EndingImages = 6,
    EndingCard = 7,
    ClosingCard = 8,
    Title = 9,
    VampireTransformation = 10
};
enum class ShopKind : int { None, Altar, Merchant };
enum class AltarUpgrade : int { HitPoints, Attack, Defense };
enum class MerchantChoice : int { Accept = 0 };
enum class HintState : int { Unheard, Heard, Recorded };
// Flight travel and stair kinds use the same original values, independently of hero facing.
enum class FlightDirection : int { None, Up, Down };
enum class StairKind : int { None, Up, Down };
enum class HeroField : int { HitPoints, Attack, Defense, Gold };
enum class EquipmentTier : int { None, Iron, Silver, Knight, Holy, Sacred };
enum class FairyCategory : int { None, Floor10, Floor20, Floor25, Floor40, Floor49 };
enum class MusicTrack : int {
    Disabled = 0,
    // These legacy save values have no MIDI file. Preserve them on round trips.
    Reserved1 = 1,
    Reserved2 = 2,
    Reserved3 = 3,
    Reserved4 = 4,
    Floors1To10 = 5,
    Floors11To20 = 6,
    Floor25Arrival = 7,
    Floors31To40 = 8,
    Floors41To49 = 9,
    Floor50 = 10,
    CaptureTitle = 11,
    Fairy = 12,
    TimeGate = 13,
    TrackA046 = 14, // Original media slot; no recovered gameplay assignment.
    Floor10 = 15,
    Floor20 = 16,
    Floors21To30 = 17,
    Floor40 = 18,
    Floor49 = 19,
    Closing = 20,
    Floor0 = 21
};

constexpr bool music_enabled(MusicTrack track) {
    return track != MusicTrack::Disabled;
}

constexpr bool valid_music_track(MusicTrack track) {
    return track >= MusicTrack::Disabled && track <= MusicTrack::Floor0;
}

constexpr bool valid_raster_mode(RasterMode mode) {
    return mode >= RasterMode::Inactive && mode <= RasterMode::VampireTransformation &&
           std::to_underlying(mode) != 3;
}
} // namespace tsw
