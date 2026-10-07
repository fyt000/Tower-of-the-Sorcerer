#if defined(_WIN32)
#define NOMINMAX
#define NOGDI
#define NOUSER
#endif
#include "audio.hpp"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <vector>

namespace {
thread_local bool in_audio_callback{};
thread_local std::uint64_t callback_memory_operations{};
void* audio_malloc(std::size_t size) {
    if (in_audio_callback)
        ++callback_memory_operations;
    return std::malloc(size);
}
void* audio_realloc(void* pointer, std::size_t size) {
    if (in_audio_callback)
        ++callback_memory_operations;
    return std::realloc(pointer, size);
}
void audio_free(void* pointer) {
    if (in_audio_callback && pointer)
        ++callback_memory_operations;
    std::free(pointer);
}
struct CallbackScope {
    CallbackScope() { in_audio_callback = true; }
    ~CallbackScope() { in_audio_callback = false; }
};
} // namespace
#define TSF_MALLOC audio_malloc
#define TSF_REALLOC audio_realloc
#define TSF_FREE audio_free
#define TSF_IMPLEMENTATION
#include "tsf.h"
#define TML_IMPLEMENTATION
#include "tml.h"
// The direct device callback avoids raylib's mutex around its stream mixer.
#define MA_MALLOC audio_malloc
#define MA_REALLOC audio_realloc
#define MA_FREE audio_free
#define MA_NO_ENGINE
#define MA_NO_NODE_GRAPH
#define MA_NO_RESOURCE_MANAGER
#define MA_NO_GENERATION
#define MA_NO_ENCODING
#define MA_NO_FLAC
#define MA_NO_MP3
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

namespace tsw {
namespace {
constexpr int SampleRate = 44100, MidiChannels = 16, SynthVoices = 256;
constexpr std::size_t EffectVoiceCount = 16, CueQueueCapacity = 512;
constexpr std::uint64_t TrackMask = 0xff, PlayingBit = 1 << 8, MutedBit = 1 << 9;
constexpr int RestartShift = 10;
static_assert(std::atomic<std::uint64_t>::is_always_lock_free);
static_assert(std::atomic<std::uint32_t>::is_always_lock_free);
constexpr std::array<const char*, 22> Tracks{
    nullptr,    nullptr,    nullptr,    nullptr,    nullptr,    "b_067xgw", "b_058xgw", "a_008xgw",
    "a_118xgw", "a_019xgw", "b_018xgw", "a_050xgw", "a_085xgw", "a_032xgw", "a_046xgw", "a_005xgw",
    "a_007xgw", "b_110xgw", "a_023xgw", "b_117xgw", "b_014xgw", "a_027xgw"};
constexpr std::array<const char*, 11> EffectFiles{nullptr, "open", "get", "taisen", "zeno", nullptr,
                                                  nullptr, "3f",   "20f", "kai",    "kai2"};
bool valid_track(int track) {
    return track >= 5 && track < int(Tracks.size());
}
struct MidiDeleter {
    void operator()(tml_message* messages) const { tml_free(messages); }
};
struct MidiTrack {
    std::unique_ptr<tml_message, MidiDeleter> messages;
    std::uint64_t ending_sample{};
    bool load(const std::vector<unsigned char>& bytes) {
        messages.reset(tml_load_memory(bytes.data(), int(bytes.size())));
        if (!messages)
            return false;
        auto* last = messages.get();
        while (last->next)
            last = last->next;
        ending_sample = (std::uint64_t(last->time) + 2000) * SampleRate / 1000;
        return true;
    }
};
struct FontDeleter {
    void operator()(tsf* font) const { tsf_close(font); }
};
struct Synth {
    std::unique_ptr<tsf, FontDeleter> font;
    std::array<tsf_channel, MidiChannels> channel_defaults{};
    tml_message *song{}, *next{};
    std::uint64_t sample{}, ending_sample{};
    std::size_t dispatched{};
    explicit Synth(const std::vector<unsigned char>& bytes)
        : font(tsf_load_memory(bytes.data(), int(bytes.size()))) {
        if (!font)
            throw std::runtime_error("Cannot load MIDI soundfont");
        tsf_set_output(font.get(), TSF_STEREO_INTERLEAVED, SampleRate, -8);
        if (!tsf_set_max_voices(font.get(), SynthVoices) ||
            !tsf_channel_set_presetnumber(font.get(), MidiChannels - 1, 0, false))
            throw std::runtime_error("Cannot preallocate MIDI voices and channels");
        for (int channel = 0; channel < MidiChannels; ++channel)
            if (!tsf_channel_set_presetnumber(font.get(), channel, 0, channel == 9))
                throw std::runtime_error("Missing default MIDI instrument");
        std::copy_n(font->channels->channels, MidiChannels, channel_defaults.begin());
    }
    void reset_channels() {
        // tsf_reset frees channels. Keep its quick release, then restore the pinned
        // TSF defaults in place so every MIDI event retains preallocated storage.
        for (int channel = 0; channel < MidiChannels; ++channel)
            tsf_channel_sounds_off_all(font.get(), channel);
        std::copy(channel_defaults.begin(), channel_defaults.end(), font->channels->channels);
        font->channels->activeChannel = 0;
    }
    bool set_song(const MidiTrack& track) {
        song = next = track.messages.get();
        sample = dispatched = 0;
        ending_sample = track.ending_sample;
        reset_channels();
        return bool(song);
    }
    void event(const tml_message& message) {
        ++dispatched;
        switch (message.type) {
        case TML_PROGRAM_CHANGE:
            tsf_channel_set_presetnumber(font.get(), message.channel, message.program, message.channel == 9);
            break;
        case TML_NOTE_ON:
            if (message.velocity)
                tsf_channel_note_on(font.get(), message.channel, message.key, float(message.velocity) / 127);
            else
                tsf_channel_note_off(font.get(), message.channel, message.key);
            break;
        case TML_NOTE_OFF:
            tsf_channel_note_off(font.get(), message.channel, message.key);
            break;
        case TML_PITCH_BEND:
            tsf_channel_set_pitchwheel(font.get(), message.channel, message.pitch_bend);
            break;
        case TML_CONTROL_CHANGE:
            tsf_channel_midi_control(font.get(), message.channel, message.control, message.control_value);
            break;
        default:
            break;
        }
    }
    void render(float* output, int frames) {
        if (!song) {
            std::fill_n(output, frames * 2, 0.f);
            return;
        }
        while (frames > 0) {
            while (next && std::uint64_t(next->time) * SampleRate / 1000 <= sample) {
                event(*next);
                next = next->next;
            }
            if (!next && sample >= ending_sample) {
                reset_channels();
                next = song;
                sample = 0;
                continue;
            }
            const auto boundary = next ? std::uint64_t(next->time) * SampleRate / 1000 : ending_sample;
            const int count = int(std::min<std::uint64_t>(frames, boundary - sample));
            tsf_render_float(font.get(), output, count, 0);
            sample += count;
            frames -= count;
            output += count * 2;
        }
    }
};
// One producer (game thread), one consumer (device callback); fixed storage.
struct CueQueue {
    std::array<int, CueQueueCapacity> cues{};
    std::atomic<std::uint32_t> read{}, written{};
    bool push(int cue) {
        const auto end = written.load(std::memory_order_relaxed);
        if (end - read.load(std::memory_order_acquire) == cues.size())
            return false;
        cues[end % cues.size()] = cue;
        written.store(end + 1, std::memory_order_release);
        return true;
    }
    template <typename Play> void consume(Play play) {
        auto begin = read.load(std::memory_order_relaxed);
        const auto end = written.load(std::memory_order_acquire);
        while (begin != end)
            play(cues[begin++ % cues.size()]);
        read.store(begin, std::memory_order_release);
    }
};
struct Effect {
    struct Voice {
        std::size_t cursor{};
        std::uint64_t started{};
        bool playing{};
    };
    std::vector<float> samples;
    std::array<Voice, EffectVoiceCount> voices{};
    std::uint64_t sequence{};
    void load(const std::vector<unsigned char>& bytes) {
        auto config = ma_decoder_config_init(ma_format_f32, 2, SampleRate);
        ma_uint64 frames{};
        void* decoded{};
        if (ma_decode_memory(bytes.data(), bytes.size(), &config, &frames, &decoded) != MA_SUCCESS)
            throw std::runtime_error("Cannot decode WAV effect");
        std::unique_ptr<float, decltype(&audio_free)> owned(static_cast<float*>(decoded), audio_free);
        samples.assign(owned.get(), owned.get() + frames * 2);
    }
    void play() {
        auto voice = std::find_if(voices.begin(), voices.end(), [](const auto& v) { return !v.playing; });
        if (voice == voices.end())
            voice = std::min_element(voices.begin(), voices.end(),
                                     [](const auto& a, const auto& b) { return a.started < b.started; });
        *voice = {0, ++sequence, true};
    }
    void mix(float* output, int frames) {
        for (auto& voice : voices) {
            if (!voice.playing)
                continue;
            const auto count = std::min(std::size_t(frames) * 2, samples.size() - voice.cursor);
            for (std::size_t i = 0; i < count; ++i)
                output[i] += samples[voice.cursor + i];
            voice.cursor += count;
            voice.playing = voice.cursor < samples.size();
        }
    }
    unsigned playing() const {
        return unsigned(
            std::count_if(voices.begin(), voices.end(), [](const auto& voice) { return voice.playing; }));
    }
};
} // namespace
struct Audio::Impl {
    Synth synth;
    std::array<MidiTrack, Tracks.size()> tracks;
    std::array<Effect, EffectFiles.size()> effects;
    CueQueue cues;
    ma_device device{};
    bool device_ready{};
    // Only the game thread writes requested state. The callback owns all playback cursors.
    int requested_track = -1;
    bool requested_playing{}, requested_muted{};
    std::uint64_t restart_count{};
    std::atomic<std::uint64_t> request{}, applied_request{}, sample_snapshot{}, audible_samples{},
        memory_operations{};
    std::uint64_t previous_request{};
    std::size_t dropped_cues{};
    explicit Impl(const Assets& assets, bool start_device = true) : synth(assets.soundfont()) {
        for (int i = 5; i < int(Tracks.size()); ++i)
            if (!tracks[i].load(assets.midi(Tracks[i])))
                throw std::runtime_error("Cannot parse MIDI track: " + std::string(Tracks[i]));
        for (int i = 1; i < int(EffectFiles.size()); ++i)
            if (EffectFiles[i])
                effects[i].load(assets.wave(EffectFiles[i]));
        if (!start_device)
            return;
        auto config = ma_device_config_init(ma_device_type_playback);
        config.playback.format = ma_format_f32;
        config.playback.channels = 2;
        config.sampleRate = SampleRate;
        config.periodSizeInFrames = 512;
        config.noPreSilencedOutputBuffer = MA_TRUE;
        config.noClip = MA_TRUE;
        config.dataCallback = callback;
        config.pUserData = this;
        if (ma_device_init(nullptr, &config, &device) != MA_SUCCESS)
            return;
        if (ma_device_start(&device) != MA_SUCCESS) {
            ma_device_uninit(&device);
            return;
        }
        device_ready = true;
    }
    ~Impl() {
        // Uninitialization joins the device thread before tracks, samples or synth are freed.
        if (device_ready)
            ma_device_uninit(&device);
    }
    void publish() {
        const auto value = (restart_count << RestartShift) |
                           std::uint64_t(valid_track(requested_track) ? requested_track : 0) |
                           (requested_playing ? PlayingBit : 0) | (requested_muted ? MutedBit : 0);
        request.store(value, std::memory_order_release);
    }
    void render(float* output, int frames) {
        CallbackScope scope;
        const auto allocations_before = callback_memory_operations;
        const auto control = request.load(std::memory_order_acquire);
        if ((control >> RestartShift) != (previous_request >> RestartShift)) {
            const int track = int(control & TrackMask);
            if (valid_track(track))
                synth.set_song(tracks[track]);
        }
        previous_request = control;
        cues.consume([&](int cue) { effects[cue].play(); });
        if (control & PlayingBit) {
            synth.render(output, frames);
            for (int i = 0; i < frames * 2; ++i)
                output[i] *= .5f;
        } else
            std::fill_n(output, frames * 2, 0.f);
        for (auto& effect : effects)
            effect.mix(output, frames);
        std::uint64_t nonzero{};
        for (int i = 0; i < frames * 2; ++i) {
            nonzero += output[i] != 0;
            output[i] = control & MutedBit ? 0.f : std::clamp(output[i], -1.f, 1.f);
        }
        audible_samples.fetch_add(nonzero, std::memory_order_relaxed);
        memory_operations.fetch_add(callback_memory_operations - allocations_before,
                                    std::memory_order_relaxed);
        sample_snapshot.store(synth.sample, std::memory_order_relaxed);
        applied_request.store(control, std::memory_order_release);
    }
    static void callback(ma_device* device, void* output, const void*, ma_uint32 frames) {
        static_cast<Impl*>(device->pUserData)->render(static_cast<float*>(output), int(frames));
    }
};
Audio::Audio(const Assets& assets) : impl_(std::make_unique<Impl>(assets)) {}
Audio::~Audio() = default;
bool Audio::available() const {
    return impl_->device_ready;
}
void Audio::mute(bool muted) {
    impl_->requested_muted = muted;
    impl_->publish();
}
void Audio::restart(Game& game) {
    impl_->requested_track = -1;
    update(game);
}
int Audio::track_for_scene(const Game& game) {
    if (!game.hero.music_track)
        return 0;
    // 0x4526C0 title callback and 0x482E60 closing card select their own MIDI.
    constexpr int CaptureTitleTrack = 11, ClosingTrack = 20;
    switch (game.visual.raster_mode) {
    case 9:
    case 0:
    case 1:
        return CaptureTitleTrack;
    case 7:
    case 8:
        return ClosingTrack;
    default:
        return game.hero.music_track;
    }
}
void Audio::update(Game& game) {
    const int track = track_for_scene(game);
    if (track != impl_->requested_track) {
        impl_->requested_track = track;
        ++impl_->restart_count;
        impl_->requested_playing = valid_track(track);
    }
    for (auto sound : game.sounds) {
        const int cue = int(sound);
        if (sound == SoundCue::MusicStop || sound == SoundCue::MusicStart)
            impl_->requested_playing = sound == SoundCue::MusicStart;
        else if (cue > 0 && cue < int(EffectFiles.size()) && EffectFiles[cue] && !impl_->cues.push(cue))
            ++impl_->dropped_cues;
    }
    impl_->publish();
    game.sounds.clear();
}
bool Audio::verify_wave(const std::vector<unsigned char>& bytes) {
    Effect effect;
    effect.load(bytes);
    return !effect.samples.empty() && std::all_of(effect.samples.begin(), effect.samples.end(),
                                                  [](float sample) { return std::isfinite(sample); });
}
bool Audio::verify_tracks(const Assets& assets) {
    Synth synth(assets.soundfont());
    std::vector<float> block(2048 * 2);
    constexpr std::array<int, 5> BlockSizes{1, 127, 512, 2048, 333};
    std::size_t total_messages = 0;
    for (int track = 5; track < int(Tracks.size()); ++track) {
        MidiTrack midi;
        if (!midi.load(assets.midi(Tracks[track])))
            return false;
        std::size_t messages = 0;
        for (auto* message = midi.messages.get(); message; message = message->next) {
            ++messages;
            if (message->type == TML_PROGRAM_CHANGE &&
                tsf_get_presetindex(synth.font.get(), message->channel == 9 ? 128 : 0, message->program) < 0)
                return false;
        }
        double energy = 0;
        std::size_t block_index = 0;
        const auto allocations_before = callback_memory_operations;
        {
            CallbackScope scope;
            synth.set_song(midi);
            while (synth.sample < synth.ending_sample) {
                const int frames = int(std::min<std::uint64_t>(BlockSizes[block_index++ % BlockSizes.size()],
                                                               synth.ending_sample - synth.sample));
                synth.render(block.data(), frames);
                for (int i = 0; i < frames * 2; ++i) {
                    if (!std::isfinite(block[i]))
                        return false;
                    energy += double(block[i]) * block[i];
                }
            }
            if (energy < 1 || synth.next || synth.dispatched != messages)
                return false;
            synth.render(block.data(), 1);
        }
        if (synth.sample != 1 || callback_memory_operations != allocations_before)
            return false;
        total_messages += messages;
        std::cout << "MIDI " << Tracks[track] << ": " << messages
                  << " messages dispatched; loop without allocation\n"
                  << std::flush;
    }
    std::cout << "17 complete MIDI tracks: " << total_messages
              << " messages; programs available; finite, nonzero stereo synthesis\n";
    return true;
}
bool Audio::verify_playback(const Assets& assets) {
    Impl offline(assets, false);
    std::array<float, 512 * 2> block{};
    int tested_effects = 0;
    for (int cue = 1; cue < int(EffectFiles.size()); ++cue) {
        if (!EffectFiles[cue])
            continue;
        ++tested_effects;
        for (int i = 0; i < 4; ++i)
            offline.cues.push(cue);
        offline.render(block.data(), 1);
        if (offline.effects[cue].playing() != 4)
            return false;
        for (std::size_t i = 0; i < EffectVoiceCount * 2; ++i)
            offline.cues.push(cue);
        offline.render(block.data(), 1);
        if (offline.effects[cue].playing() != EffectVoiceCount)
            return false;
        for (auto& voice : offline.effects[cue].voices)
            voice.playing = false;
    }
    if (tested_effects != 8 || offline.memory_operations.load())
        return false;
    for (std::size_t i = 0; i < CueQueueCapacity; ++i)
        if (!offline.cues.push(1))
            return false;
    if (offline.cues.push(1))
        return false;
    offline.render(block.data(), 512);
    if (!offline.cues.push(1))
        return false;
    Audio audio(assets);
    if (!audio.available())
        return false;
    audio.mute(true);
    Game game;
    audio.restart(game);
    const auto wait_for = [](auto predicate) {
        const auto until = std::chrono::steady_clock::now() + std::chrono::seconds(8);
        while (!predicate()) {
            if (std::chrono::steady_clock::now() >= until)
                return false;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        return true;
    };
    const auto applied = [&]() {
        return audio.impl_->applied_request.load(std::memory_order_acquire) ==
               audio.impl_->request.load(std::memory_order_acquire);
    };
    // The original first-floor MIDI has a roughly three-second silent lead-in.
    if (!wait_for([&]() { return applied() && audio.impl_->audible_samples.load() > 0; }))
        return false;
    game.sounds.push_back(SoundCue::MusicStop);
    audio.update(game);
    if (!wait_for(applied))
        return false;
    const auto stopped_at = audio.impl_->sample_snapshot.load();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if (audio.impl_->sample_snapshot.load() != stopped_at)
        return false;
    game.sounds.push_back(SoundCue::MusicStart);
    audio.update(game);
    if (!wait_for([&]() { return applied() && audio.impl_->sample_snapshot.load() > stopped_at; }))
        return false;
    // A new game on the same track must recover from a scene's MusicStop.
    game.sounds.push_back(SoundCue::MusicStop);
    audio.update(game);
    game.new_game();
    audio.restart(game);
    if (!wait_for(applied) || !(audio.impl_->applied_request.load() & PlayingBit))
        return false;
    for (int track = 6; track < int(Tracks.size()); ++track) {
        game.hero.music_track = track;
        audio.update(game);
        if (!wait_for(applied) || int(audio.impl_->applied_request.load() & TrackMask) != track)
            return false;
    }
    if (audio.impl_->memory_operations.load())
        return false;
    std::cout << "Audio: eight WAV pools, bounded cue bursts, startup music, pause/resume, same-track "
                 "restart and 17 device track selections passed; callback allocations/frees=0\n";
    return true;
}
bool Audio::render_test(const Assets& assets, std::string_view midi, const std::filesystem::path& output) {
    Synth synth(assets.soundfont());
    MidiTrack track;
    if (!track.load(assets.midi(midi)) || !synth.set_song(track))
        return false;
    std::vector<float> samples(SampleRate * 2 * 6);
    synth.render(samples.data(), SampleRate * 6);
    double energy = 0;
    for (float value : samples) {
        if (!std::isfinite(value))
            return false;
        energy += double(value) * value;
    }
    if (energy < 1)
        return false;
    std::ofstream file(output, std::ios::binary);
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
    u32(SampleRate);
    u32(SampleRate * 4);
    u16(4);
    u16(16);
    file.write("data", 4);
    u32(std::uint32_t(samples.size() * 2));
    for (float value : samples)
        u16(static_cast<std::uint16_t>(static_cast<std::int16_t>(std::clamp(value, -1.f, 1.f) * 32767)));
    return bool(file);
}
} // namespace tsw
