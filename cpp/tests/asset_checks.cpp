#include "audio_backend.hpp"
#include "desktop_checks.hpp"
#include "embedded_media.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace tsw {
namespace {
bool decodes_wave(const std::vector<unsigned char>& bytes) {
    auto config = ma_decoder_config_init(ma_format_f32, 2, 44100);
    ma_uint64 frames{};
    void* decoded{};
    if (ma_decode_memory(bytes.data(), bytes.size(), &config, &frames, &decoded) != MA_SUCCESS)
        return false;
    const auto* samples = static_cast<float*>(decoded);
    const bool valid = frames && std::all_of(samples, samples + frames * 2,
                                             [](float sample) { return std::isfinite(sample); });
    ma_free(decoded, nullptr);
    return valid;
}

bool same_pixels(Image left, Image right) {
    if (left.width != right.width || left.height != right.height)
        return false;
    auto* a = LoadImageColors(left);
    auto* b = LoadImageColors(right);
    bool same = true;
    for (int i = 0; i < left.width * left.height; ++i)
        same &= a[i].r == b[i].r && a[i].g == b[i].g && a[i].b == b[i].b && a[i].a == b[i].a;
    UnloadImageColors(a);
    UnloadImageColors(b);
    return same;
}
} // namespace

int verify_assets(const Assets& original, const Assets& extracted, const std::filesystem::path& executable,
                  const std::filesystem::path& output) {
    std::filesystem::create_directories(output);
    int checks = 0;
    const auto require = [&](bool condition, const std::string& description) {
        if (!condition)
            throw std::runtime_error("Asset check failed: " + description);
        ++checks;
    };
    require(original.original_layout() && !extracted.original_layout(),
            "Both distinct asset layouts are tested");
    const auto compare_image = [&](std::string_view name) {
        auto raw = original.image(name), converted = extracted.image(name);
        const bool same = same_pixels(raw, converted);
        UnloadImage(raw);
        UnloadImage(converted);
        require(same, "Original BMP/OZ pixels match the extracted PNG: " + std::string(name));
    };
    compare_image("original-atlas");
    compare_image("original-background-atlas");
    for (const auto name : SceneImageNames)
        compare_image(name);
    constexpr std::array<std::string_view, 17> Tracks{
        "b_067xgw", "b_058xgw", "a_008xgw", "a_118xgw", "a_019xgw", "b_018xgw",
        "a_050xgw", "a_085xgw", "a_032xgw", "a_046xgw", "a_005xgw", "a_007xgw",
        "b_110xgw", "a_023xgw", "b_117xgw", "b_014xgw", "a_027xgw"};
    for (const auto name : Tracks)
        require(original.midi(name) == extracted.midi(name),
                "Original MIDI bytes are unchanged: " + std::string(name));
    for (const auto name : {"open", "get", "taisen", "zeno", "3f", "20f", "kai", "kai2"}) {
        const auto bytes = original.wave(name);
        require(bytes == extracted.wave(name), "Original WAV bytes are unchanged: " + std::string(name));
        require(decodes_wave(bytes), "Original WAV decodes: " + std::string(name));
    }
    require(original.soundfont() == read_embedded_media(executable, EmbeddedMedia::Soundfont),
            "Embedded soundfont matches the soundfont selected by the runtime");
    require(Assets::select(original.root(), {}, {}, extracted.root()) == original.root(),
            "Original layout beside the replacement takes precedence over extracted assets");
    bool rejected = false;
    try {
        Assets::select(original.root(), output / "absent", original.root(), extracted.root());
    } catch (const std::exception&) {
        rejected = true;
    }
    require(rejected, "An invalid explicit asset directory never silently falls back");
    rejected = false;
    try {
        read_embedded_media(executable, static_cast<EmbeddedMedia>(999));
    } catch (const std::exception&) {
        rejected = true;
    }
    require(rejected, "A missing embedded resource reports an error");
    const auto truncated = output / "truncated.exe";
    {
        std::ofstream file(truncated, std::ios::binary | std::ios::trunc);
        file << "MZ";
    }
    rejected = false;
    try {
        read_embedded_media(truncated, EmbeddedMedia::Soundfont);
    } catch (const std::exception&) {
        rejected = true;
    }
    require(rejected, "Truncated PE headers are rejected before resource reads");
    std::filesystem::remove(truncated);
    const auto broken_root = output / "broken-original";
    std::filesystem::create_directories(broken_root / "Data3");
    const auto broken_atlas = broken_root / "Data3/Chtable.oz";
    {
        std::ofstream file(broken_atlas, std::ios::binary | std::ios::trunc);
        file << "BM";
    }
    rejected = false;
    try {
        Assets broken(broken_root, executable);
        auto image = broken.image("original-atlas");
        UnloadImage(image);
    } catch (const std::exception&) {
        rejected = true;
    }
    require(rejected, "An unreadable original atlas cannot silently use a converted fallback");
    std::filesystem::remove(broken_atlas);
    std::filesystem::remove(broken_root / "Data3");
    std::filesystem::remove(broken_root);
    std::ofstream report(output / "asset-report.json");
    report << "{\n  \"passed\": " << checks << ",\n  \"images\": 31,\n  \"midi\": 17,\n  \"wav\": 8,\n"
           << "  \"limits\": \"Decoded asset equivalence, embedded media and selection/error checks.\"\n}\n";
    std::cout << checks
              << " asset checks passed; original bitmap pixels and audio bytes match extracted assets\n";
    return 0;
}
} // namespace tsw
