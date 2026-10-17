#include "audio.hpp"
#include "audio_mixer.hpp"
#include "audio_queue.hpp"
#include "tml.h"
#include "tsf.h"
#include <algorithm>
#include <array>
#include <atomic>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_clara.hpp>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#if defined(_MSC_VER) && defined(_DEBUG)
#include <crtdbg.h>
#endif

using namespace tsw;

namespace {
constexpr std::array<const char*, 17> Tracks{"b_067xgw", "b_058xgw", "a_008xgw", "a_118xgw", "a_019xgw",
                                             "b_018xgw", "a_050xgw", "a_085xgw", "a_032xgw", "a_046xgw",
                                             "a_005xgw", "a_007xgw", "b_110xgw", "a_023xgw", "b_117xgw",
                                             "b_014xgw", "a_027xgw"};
constexpr std::array<SoundCue, 8> Effects{SoundCue(1), SoundCue(2), SoundCue(3), SoundCue(4),
                                          SoundCue(7), SoundCue(8), SoundCue(9), SoundCue(10)};
std::string requested_assets, output_directory = TSW_AUDIO_OUTPUT;
std::filesystem::path executable;

const Assets& media() {
    static const Assets assets(
        Assets::select(executable.parent_path(), requested_assets, TSW_ORIGINAL_ASSETS, TSW_ASSETS),
        executable);
    return assets;
}

struct Midi {
    std::unique_ptr<tml_message, decltype(&tml_free)> messages{nullptr, tml_free};
    std::uint64_t frames{};

    explicit Midi(const char* name) {
        const auto bytes = media().midi(name);
        messages.reset(tml_load_memory(bytes.data(), int(bytes.size())));
        REQUIRE(messages);
        auto* last = messages.get();
        while (last->next)
            last = last->next;
        frames = (std::uint64_t(last->time) + 2000) * AudioSampleRate / 1000;
    }
};

std::vector<float> render(AudioMixer& mixer, int frames) {
    std::vector<float> samples(std::size_t(frames) * 2);
    for (int offset = 0; offset < frames; offset += 512)
        mixer.render(samples.data() + offset * 2, std::min(512, frames - offset));
    return samples;
}

double energy(const std::vector<float>& samples) {
    double sum = 0;
    for (float sample : samples) {
        if (!std::isfinite(sample))
            return -1;
        sum += double(sample) * sample;
    }
    return sum;
}

void require_same(const std::vector<float>& actual, const std::vector<float>& expected,
                  std::size_t first = 0) {
    REQUIRE(actual.size() == expected.size());
    auto index = first;
    while (index < actual.size() && std::abs(actual[index] - expected[index]) <= .00001f)
        ++index;
    CAPTURE(index);
    if (index < actual.size()) {
        CAPTURE(actual[index], expected[index]);
    }
    REQUIRE(index == actual.size());
}

void write_wave(const std::vector<float>& samples) {
    std::filesystem::create_directories(output_directory);
    std::ofstream file(std::filesystem::path(output_directory) / "first-floor.wav", std::ios::binary);
    const auto u32 = [&](std::uint32_t value) {
        for (int i = 0; i < 4; ++i)
            file.put(char(value >> (8 * i)));
    };
    const auto u16 = [&](std::uint16_t value) {
        file.put(char(value));
        file.put(char(value >> 8));
    };
    file.write("RIFF", 4);
    u32(36 + std::uint32_t(samples.size() * 2));
    file.write("WAVEfmt ", 8);
    u32(16);
    u16(1);
    u16(2);
    u32(AudioSampleRate);
    u32(AudioSampleRate * 4);
    u16(4);
    u16(16);
    file.write("data", 4);
    u32(std::uint32_t(samples.size() * 2));
    for (float value : samples)
        u16(static_cast<std::uint16_t>(static_cast<std::int16_t>(std::clamp(value, -1.f, 1.f) * 32767)));
    REQUIRE(file.good());
}
} // namespace

TEST_CASE("Effect queue preserves FIFO order, capacity and index wrap", "[queue]") {
    AudioCueQueue queue;
    // Start near integer rollover; published indices are monotonic unsigned counters.
    queue.read = queue.written = UINT32_MAX - 200;
    for (int round = 0; round < 3; ++round) {
        for (std::size_t i = 0; i < AudioCueQueue::Capacity; ++i)
            REQUIRE(queue.push(int(i) + round * 1000));
        REQUIRE_FALSE(queue.push(-1));
        std::vector<int> received;
        queue.consume([&](int cue) { received.push_back(cue); });
        REQUIRE(received.size() == AudioCueQueue::Capacity);
        for (std::size_t i = 0; i < received.size(); ++i)
            REQUIRE(received[i] == int(i) + round * 1000);
        queue.consume([&](int) { FAIL("A consumed cue was delivered twice"); });
    }
}

TEST_CASE("Effect queue delivers concurrent producer bursts without loss", "[queue]") {
    constexpr int Count = 20000;
    AudioCueQueue queue;
    std::atomic<bool> stop{};
    std::vector<int> received;
    received.reserve(Count);
    std::thread producer([&]() {
        for (int i = 0; i < Count && !stop.load(); ++i)
            while (!queue.push(i) && !stop.load())
                std::this_thread::yield();
    });
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    while (received.size() < Count && std::chrono::steady_clock::now() < deadline) {
        queue.consume([&](int cue) { received.push_back(cue); });
        std::this_thread::yield();
    }
    stop = true;
    producer.join();
    REQUIRE(received.size() == Count);
    for (int i = 0; i < Count; ++i)
        REQUIRE(received[i] == i);
}

TEST_CASE("Every original MIDI program exists in the soundfont", "[midi]") {
    const auto bytes = media().soundfont();
    std::unique_ptr<tsf, decltype(&tsf_close)> font(tsf_load_memory(bytes.data(), int(bytes.size())),
                                                    tsf_close);
    REQUIRE(font);
    std::size_t messages = 0;
    for (const auto* name : Tracks) {
        CAPTURE(name);
        Midi midi(name);
        for (auto* message = midi.messages.get(); message; message = message->next) {
            ++messages;
            if (message->type == TML_PROGRAM_CHANGE) {
                CAPTURE(message->channel, message->program);
                REQUIRE(tsf_get_presetindex(font.get(), message->channel == 9 ? 128 : 0, message->program) >=
                        0);
            }
        }
    }
    REQUIRE(messages == 35343);
}

TEST_CASE("All original tracks synthesize and loop across varied callback sizes", "[midi]") {
    AudioMixer mixer(media());
    Game game;
    constexpr std::array<int, 5> BlockSizes{1, 127, 512, 2048, 333};
    std::array<float, 2048 * 2> block{};
    for (std::size_t track = 0; track < Tracks.size(); ++track) {
        CAPTURE(Tracks[track]);
        Midi midi(Tracks[track]);
        game.hero.music_track = static_cast<MusicTrack>(int(track) + 5);
        mixer.restart(game);
        std::uint64_t remaining = midi.frames;
        std::size_t index = 0;
        double sum = 0;
        bool finite = true;
        while (remaining) {
            const int frames =
                int(std::min<std::uint64_t>(remaining, BlockSizes[index++ % BlockSizes.size()]));
            mixer.render(block.data(), frames);
            for (int i = 0; i < frames * 2; ++i) {
                finite &= std::isfinite(block[i]) && std::abs(block[i]) <= 1.f;
                sum += double(block[i]) * block[i];
            }
            remaining -= frames;
        }
        REQUIRE(finite);
        REQUIRE(sum > 1);
        const auto looped = render(mixer, AudioSampleRate * 6);
        REQUIRE(energy(looped) > 1);
        if (track == 0)
            write_wave(looped);
    }
}

TEST_CASE("Startup music retains the original silent lead-in", "[playback]") {
    AudioMixer mixer(media());
    Game game;
    mixer.restart(game);
    const auto samples = render(mixer, AudioSampleRate * 6);
    REQUIRE(std::all_of(samples.begin(), samples.begin() + AudioSampleRate * 2 * 2,
                        [](float sample) { return sample == 0; }));
    REQUIRE(energy(samples) > 1);
}

TEST_CASE("Pausing freezes music and resuming continues the same samples", "[playback]") {
    AudioMixer mixer(media()), continuous(media());
    Game game, reference;
    mixer.restart(game);
    continuous.restart(reference);
    require_same(render(mixer, AudioSampleRate * 5), render(continuous, AudioSampleRate * 5));
    game.sounds.push_back(SoundCue::MusicStop);
    mixer.update(game);
    REQUIRE(game.sounds.empty());
    REQUIRE(energy(render(mixer, 512 * 8)) == 0);
    game.sounds.push_back(SoundCue::MusicStart);
    mixer.update(game);
    require_same(render(mixer, 512 * 8), render(continuous, 512 * 8));
}

TEST_CASE("Mute silences music and effects while their clocks advance", "[playback]") {
    AudioMixer mixer(media()), continuous(media());
    Game game, reference;
    mixer.restart(game);
    continuous.restart(reference);
    render(mixer, AudioSampleRate * 4);
    render(continuous, AudioSampleRate * 4);
    game.sounds.push_back(Effects[3]);
    reference.sounds.push_back(Effects[3]);
    mixer.update(game);
    continuous.update(reference);
    mixer.mute(true);
    REQUIRE(energy(render(mixer, 512 * 8)) == 0);
    render(continuous, 512 * 8);
    mixer.mute(false);
    require_same(render(mixer, 512 * 8), render(continuous, 512 * 8));
}

TEST_CASE("New game and same-track restart recover from a music stop", "[playback]") {
    AudioMixer mixer(media());
    Game game;
    mixer.restart(game);
    const auto initial = render(mixer, AudioSampleRate * 6);
    REQUIRE(energy(initial) > 1);
    for (bool new_game : {false, true}) {
        game.sounds.push_back(SoundCue::MusicStop);
        mixer.update(game);
        REQUIRE(energy(render(mixer, 512)) == 0);
        if (new_game)
            game.new_game();
        mixer.restart(game);
        // Quick note releases retain their short tails; compare after the first 100 ms.
        require_same(render(mixer, AudioSampleRate * 6), initial, AudioSampleRate / 10 * 2);
    }
}

TEST_CASE("WAV bursts overlap with sixteen voices and a bounded cue queue", "[effects]") {
    AudioMixer mixer(media()), single(media());
    Game game, reference;
    game.hero.music_track = reference.hero.music_track = MusicTrack::Disabled;
    for (auto effect : Effects) {
        CAPTURE(int(effect));
        reference.sounds.push_back(effect);
        single.update(reference);
        auto expected = render(single, 512);
        REQUIRE(energy(expected) > 0);
        for (int count : {4, 32, 1024}) {
            for (int i = 0; i < count; ++i)
                game.sounds.push_back(effect);
            mixer.update(game);
            auto overlapping = render(mixer, 512);
            auto scaled = expected;
            for (auto& value : scaled)
                value = std::clamp(value * std::min(count, 16), -1.f, 1.f);
            require_same(overlapping, scaled);
            // Advance beyond the longest supplied WAV so each burst starts independently.
            render(mixer, AudioSampleRate * 20);
        }
        render(single, AudioSampleRate * 20);
    }
}

TEST_CASE("Accelerated bursts retain one cue per effect and preserve the attack samples", "[effects]") {
    for (float speed : {2.f, 3.f, 10.f}) {
        CAPTURE(speed);
        AudioMixer mixer(media()), single(media());
        mixer.speed(speed);
        single.speed(speed);
        Game game, reference;
        game.hero.music_track = reference.hero.music_track = MusicTrack::Disabled;
        for (auto effect : Effects) {
            CAPTURE(int(effect));
            game.sounds.assign(1024, effect);
            reference.sounds = {effect};
            mixer.update(game);
            single.update(reference);
            const auto actual = render(mixer, 512);
            REQUIRE(energy(actual) > 0);
            require_same(actual, render(single, 512));
            render(mixer, AudioSampleRate * 10);
            render(single, AudioSampleRate * 10);
        }
    }
}

TEST_CASE("Accelerated sound keeps distinct cues and the original effect pitch", "[effects]") {
    AudioMixer mixer(media()), pickup(media()), door(media());
    mixer.speed(10);
    Game game, get, open;
    game.hero.music_track = get.hero.music_track = open.hero.music_track = MusicTrack::Disabled;
    game.sounds = {SoundCue::Get, SoundCue::Open, SoundCue::Get, SoundCue::Open};
    get.sounds = {SoundCue::Get};
    open.sounds = {SoundCue::Open};
    mixer.update(game);
    pickup.update(get);
    door.update(open);
    auto expected = render(pickup, AudioSampleRate * 8 / 100);
    const auto other = render(door, AudioSampleRate * 8 / 100);
    for (std::size_t i = 0; i < expected.size(); ++i)
        expected[i] = std::clamp(expected[i] + other[i], -1.f, 1.f);
    require_same(render(mixer, AudioSampleRate * 8 / 100), expected);
}

TEST_CASE("Accelerated strikes are skipped within 70 ms and resume without a backlog", "[effects]") {
    AudioMixer mixer(media()), reference(media());
    mixer.speed(10);
    reference.speed(10);
    Game game, expected;
    game.hero.music_track = expected.hero.music_track = MusicTrack::Disabled;
    game.sounds = expected.sounds = {SoundCue::Strike};
    mixer.update(game);
    reference.update(expected);
    for (int i = 0; i < 7; ++i) {
        require_same(render(mixer, AudioSampleRate / 100), render(reference, AudioSampleRate / 100));
        if (i < 6) {
            game.sounds = {SoundCue::Strike};
            mixer.update(game);
        }
    }
    // At 70 ms, a fresh strike must actually start; it fades the old strike in 10 ms.
    game.sounds = {SoundCue::Strike};
    mixer.update(game);
    render(mixer, AudioSampleRate / 100);
    AudioMixer fresh(media());
    game.sounds = {SoundCue::Strike};
    fresh.update(game);
    render(fresh, AudioSampleRate / 100);
    require_same(render(mixer, 512), render(fresh, 512));
    render(mixer, AudioSampleRate);
    REQUIRE(energy(render(mixer, 512)) == 0);
}

TEST_CASE("Accelerated retriggers crossfade away older copies of the same effect", "[effects]") {
    AudioMixer mixer(media());
    mixer.speed(3);
    Game game;
    game.hero.music_track = MusicTrack::Disabled;
    for (int i = 0; i < 12; ++i) {
        game.sounds = {SoundCue::Stairs};
        mixer.update(game);
        render(mixer, AudioSampleRate / 100);
        AudioMixer fresh(media());
        game.sounds = {SoundCue::Stairs};
        fresh.update(game);
        render(fresh, AudioSampleRate / 100);
        // Once the short crossfade ends, only the newest attack remains.
        require_same(render(mixer, 512), render(fresh, 512));
    }
}

TEST_CASE("Accelerated long effects fade out sooner without changing their attack", "[effects]") {
    for (float speed : {3.f, 10.f}) {
        CAPTURE(speed);
        AudioMixer mixer(media()), original(media());
        mixer.speed(speed);
        Game game, reference;
        game.hero.music_track = reference.hero.music_track = MusicTrack::Disabled;
        game.sounds = reference.sounds = {SoundCue::Stairs};
        mixer.update(game);
        original.update(reference);
        require_same(render(mixer, AudioSampleRate * 8 / 100), render(original, AudioSampleRate * 8 / 100));
        render(mixer, AudioSampleRate / 2);
        render(original, AudioSampleRate / 2);
        REQUIRE(energy(render(mixer, AudioSampleRate / 10)) == 0);
        REQUIRE(energy(render(original, AudioSampleRate / 10)) > 0);
    }
}

TEST_CASE("Changing animation speed leaves music timing and samples unchanged", "[playback]") {
    AudioMixer mixer(media()), original(media());
    Game game, reference;
    mixer.restart(game);
    original.restart(reference);
    for (float speed : {1.f, 3.f, 10.f, .5f, 1.f}) {
        mixer.speed(speed);
        require_same(render(mixer, AudioSampleRate * 3), render(original, AudioSampleRate * 3));
    }
}

TEST_CASE("Scenes select title and ending music without changing saved music", "[playback]") {
    Game game;
    for (int mode : {9, 0, 1}) {
        game.visual.raster_mode = static_cast<RasterMode>(mode);
        REQUIRE(AudioMixer::track_for_scene(game) == 11);
    }
    for (int mode : {7, 8}) {
        game.visual.raster_mode = static_cast<RasterMode>(mode);
        REQUIRE(AudioMixer::track_for_scene(game) == 20);
    }
    game.visual.raster_mode = RasterMode::Inactive;
    REQUIRE(AudioMixer::track_for_scene(game) == std::to_underlying(game.hero.music_track));
    game.hero.music_track = MusicTrack::Disabled;
    for (int mode : {-1, 0, 7}) {
        game.visual.raster_mode = static_cast<RasterMode>(mode);
        REQUIRE(AudioMixer::track_for_scene(game) == 0);
    }
}

TEST_CASE("Invalid cues and disabled music leave the mixer silent", "[playback]") {
    AudioMixer mixer(media());
    Game game;
    game.hero.music_track = MusicTrack::Disabled;
    game.sounds = {SoundCue(0), SoundCue(99)};
    mixer.restart(game);
    REQUIRE(game.sounds.empty());
    REQUIRE(energy(render(mixer, 512)) == 0);
}

TEST_CASE("The native audio device starts, switches tracks and shuts down", "[device]") {
    for (int run = 0; run < 2; ++run) {
        Audio audio(media());
        REQUIRE(audio.available());
        audio.mute(true);
        Game game;
        audio.restart(game);
        for (int track = 5; track <= 21; ++track) {
            game.hero.music_track = static_cast<MusicTrack>(track);
            game.sounds = {SoundCue::MusicStop, SoundCue::MusicStart, Effects[track % Effects.size()]};
            audio.update(game);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        // Destruction must join the callback before releasing its playback storage.
    }
}

#if defined(_MSC_VER) && defined(_DEBUG)
namespace {
thread_local std::size_t* heap_operations{};

int count_heap_operation(int, void*, std::size_t, int, long, const unsigned char*, int) {
    if (heap_operations)
        ++*heap_operations;
    return 1;
}

struct HeapCounter {
    _CRT_ALLOC_HOOK previous;

    explicit HeapCounter(std::size_t& count) : previous(_CrtSetAllocHook(count_heap_operation)) {
        heap_operations = &count;
    }

    ~HeapCounter() {
        heap_operations = nullptr;
        _CrtSetAllocHook(previous);
    }
};
} // namespace

TEST_CASE("Prepared playback performs no heap operations", "[allocation]") {
    std::size_t calibration = 0;
    {
        HeapCounter counter(calibration);
        void* pointer = std::malloc(16);
        pointer = std::realloc(pointer, 32);
        std::free(pointer);
    }
    REQUIRE(calibration >= 3);
    AudioMixer mixer(media());
    Game game;
    std::array<std::uint64_t, Tracks.size()> lengths{};
    for (std::size_t i = 0; i < Tracks.size(); ++i)
        lengths[i] = Midi(Tracks[i]).frames;
    std::array<float, 512 * 2> block{};
    std::size_t operations = 0;
    for (std::size_t track = 0; track < Tracks.size(); ++track) {
        game.hero.music_track = static_cast<MusicTrack>(int(track) + 5);
        game.sounds.assign(AudioCueQueue::Capacity, Effects[track % Effects.size()]);
        mixer.restart(game);
        {
            HeapCounter counter(operations);
            auto remaining = lengths[track];
            while (remaining) {
                const int frames = int(std::min<std::uint64_t>(remaining, 512));
                mixer.render(block.data(), frames);
                remaining -= frames;
            }
            mixer.render(block.data(), 512); // Cross the loop and reset channels in existing storage.
        }
        CAPTURE(Tracks[track]);
        REQUIRE(operations == 0);
    }
    game.sounds = {SoundCue::MusicStop};
    mixer.update(game);
    {
        HeapCounter counter(operations);
        mixer.render(block.data(), 512);
    }
    game.sounds = {SoundCue::MusicStart};
    mixer.update(game);
    mixer.mute(true);
    {
        HeapCounter counter(operations);
        mixer.render(block.data(), 512);
    }
    mixer.mute(false);
    mixer.restart(game);
    {
        HeapCounter counter(operations);
        mixer.render(block.data(), 512);
    }
    mixer.suspend(true);
    {
        HeapCounter counter(operations);
        mixer.render(block.data(), 512);
    }
    mixer.suspend(false);
    {
        HeapCounter counter(operations);
        mixer.render(block.data(), 512);
    }
    REQUIRE(operations == 0);
}
#endif

TEST_CASE("Replay suspension freezes both music and effect cursors", "[playback]") {
    AudioMixer mixer(media()), reference(media());
    Game game, expected;
    game.sounds = expected.sounds = {SoundCue::Get};
    mixer.restart(game);
    reference.restart(expected);
    require_same(render(mixer, 1024), render(reference, 1024));
    mixer.suspend(true);
    REQUIRE(energy(render(mixer, AudioSampleRate * 4)) == 0);
    mixer.suspend(false);
    require_same(render(mixer, AudioSampleRate * 4), render(reference, AudioSampleRate * 4));
}

int main(int argc, char** argv) try {
    Catch::Session session;
    auto cli = session.cli() |
               Catch::Clara::Opt(requested_assets, "DIR")["--assets"]("Original or extracted game assets") |
               Catch::Clara::Opt(output_directory, "DIR")["--output-dir"]("Generated audio test files");
    session.cli(cli);
    const int result = session.applyCommandLine(argc, argv);
    if (result)
        return result;
    executable = std::filesystem::path(GetApplicationDirectory()) / std::filesystem::path(argv[0]).filename();
#ifdef _WIN32
    if (!std::filesystem::exists(executable))
        executable += ".exe";
#endif
    return session.run();
} catch (const std::exception& error) {

    std::cerr << error.what() << '\n';
    return 1;
}
