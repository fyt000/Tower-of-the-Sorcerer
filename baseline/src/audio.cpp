#include "audio.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <vector>
#define TSF_IMPLEMENTATION
#include "tsf.h"
#define TML_IMPLEMENTATION
#include "tml.h"

namespace baseline {
namespace {
constexpr int SampleRate = 44100;
constexpr std::size_t EffectVoiceCount = 16;
constexpr std::array<const char*, 22> Tracks{
    nullptr,    nullptr,    nullptr,    nullptr,    nullptr,    "b_067xgw", "b_058xgw", "a_008xgw",
    "a_118xgw", "a_019xgw", "b_018xgw", "a_050xgw", "a_085xgw", "a_032xgw", "a_046xgw", "a_005xgw",
    "a_007xgw", "b_110xgw", "a_023xgw", "b_117xgw", "b_014xgw", "a_027xgw"};
struct MidiDeleter {
    void operator()(tml_message* messages) const { tml_free(messages); }
};
struct MidiTrack {
    std::unique_ptr<tml_message, MidiDeleter> messages;
    std::uint64_t ending_sample{};
    bool load(const std::vector<unsigned char>& bytes) {
        messages.reset(tml_load_memory(bytes.data(), int(bytes.size())));
        ending_sample = 0;
        if (!messages)
            return false;
        auto* last = messages.get();
        while (last->next)
            last = last->next;
        ending_sample = (std::uint64_t(last->time) + 2000) * SampleRate / 1000;
        return true;
    }
};
struct Synth {
    tsf* font{};
    MidiTrack owned_track;
    tml_message *song{}, *next{};
    std::uint64_t sample{}, ending_sample{};
    std::size_t dispatched{};
    explicit Synth(const std::vector<unsigned char>& bytes) {
        font = tsf_load_memory(bytes.data(), int(bytes.size()));
        if (font) {
            tsf_set_output(font, TSF_STEREO_INTERLEAVED, SampleRate, -8);
            tsf_set_max_voices(font, 256);
            reset_channels();
        }
    }
    ~Synth() {
        if (font)
            tsf_close(font);
    }
    void reset_channels() {
        tsf_reset(font);
        for (int channel = 0; channel < 16; ++channel)
            tsf_channel_set_presetnumber(font, channel, 0, channel == 9);
    }
    bool set_song(const MidiTrack& track) {
        song = next = track.messages.get();
        sample = 0;
        dispatched = 0;
        ending_sample = track.ending_sample;
        if (font)
            reset_channels();
        return font && song;
    }
    bool load(const std::vector<unsigned char>& bytes) {
        owned_track.load(bytes);
        return set_song(owned_track);
    }
    void event(const tml_message& message) {
        ++dispatched;
        switch (message.type) {
        case TML_PROGRAM_CHANGE:
            tsf_channel_set_presetnumber(font, message.channel, message.program, message.channel == 9);
            break;
        case TML_NOTE_ON:
            if (message.velocity)
                tsf_channel_note_on(font, message.channel, message.key, float(message.velocity) / 127);
            else
                tsf_channel_note_off(font, message.channel, message.key);
            break;
        case TML_NOTE_OFF:
            tsf_channel_note_off(font, message.channel, message.key);
            break;
        case TML_PITCH_BEND:
            tsf_channel_set_pitchwheel(font, message.channel, message.pitch_bend);
            break;
        case TML_CONTROL_CHANGE:
            tsf_channel_midi_control(font, message.channel, message.control, message.control_value);
            break;
        default:
            break;
        }
    }
    void render(float* output, int frames) {
        if (!font || !song) {
            std::fill(output, output + frames * 2, 0.f);
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
            if (!count)
                continue;
            tsf_render_float(font, output, count, 0);
            sample += count;
            frames -= count;
            output += count * 2;
        }
    }
};
} // namespace
struct Audio::Impl {
    static Impl* active;
    std::mutex mutex;
    Synth synth;
    std::array<MidiTrack, Tracks.size()> tracks;
    AudioStream stream{};
    struct Effect {
        Sound source{};
        std::array<Sound, EffectVoiceCount> voices{};
        std::size_t next{};
        void play() {
            if (!source.frameCount)
                return;
            // Aliases share sample data but have independent playback cursors.
            for (std::size_t offset = 0; offset < voices.size(); ++offset) {
                const auto index = (next + offset) % voices.size();
                if (!IsSoundPlaying(voices[index])) {
                    PlaySound(voices[index]);
                    next = (index + 1) % voices.size();
                    return;
                }
            }
            // An exceptional burst replaces the oldest voice, keeping memory bounded.
            StopSound(voices[next]);
            PlaySound(voices[next]);
            next = (next + 1) % voices.size();
        }
    };
    std::array<Effect, 11> effects{};
    bool device{}, music_playing = true;
    int track = -1;
    explicit Impl(const Assets& assets) : synth(assets.soundfont()) {
        constexpr std::array<const char*, 11> Files{nullptr, "open", "get", "taisen", "zeno", nullptr,
                                                    nullptr, "3f",   "20f", "kai",    "kai2"};
        std::array<std::vector<unsigned char>, 11> effect_bytes;
        for (int i = 1; i < int(Files.size()); ++i)
            if (Files[i])
                effect_bytes[i] = assets.wave(Files[i]);
        // Track changes only select parsed messages; no file I/O, parsing or freeing
        // takes place while the audio callback is waiting for the synth lock.
        for (int i = 5; i < int(Tracks.size()); ++i)
            if (!tracks[i].load(assets.midi(Tracks[i])))
                throw std::runtime_error("Cannot parse MIDI track: " + std::string(Tracks[i]));
        InitAudioDevice();
        device = IsAudioDeviceReady();
        if (!device)
            return;
        SetAudioStreamBufferSizeDefault(2048);
        stream = LoadAudioStream(SampleRate, 32, 2);
        active = this;
        SetAudioStreamCallback(stream, callback);
        SetAudioStreamVolume(stream, 0.5f);
        PlayAudioStream(stream);
        for (int i = 1; i < 11; ++i)
            if (Files[i]) {
                const auto& bytes = effect_bytes[i];
                auto wave = LoadWaveFromMemory(".wav", bytes.data(), int(bytes.size()));
                auto& effect = effects[i];
                effect.source = LoadSoundFromWave(wave);
                for (auto& voice : effect.voices)
                    voice = LoadSoundAlias(effect.source);
                UnloadWave(wave);
            }
    }
    ~Impl() {
        if (!device)
            return;
        StopAudioStream(stream);
        UnloadAudioStream(stream);
        active = nullptr;
        for (auto& effect : effects)
            if (effect.source.frameCount) {
                for (auto voice : effect.voices)
                    UnloadSoundAlias(voice);
                UnloadSound(effect.source);
            }
        CloseAudioDevice();
    }
    static void callback(void* buffer, unsigned int frames) {
        auto* self = active;
        if (!self) {
            std::memset(buffer, 0, frames * 2 * sizeof(float));
            return;
        }
        std::lock_guard lock(self->mutex);
        if (self->music_playing)
            self->synth.render(static_cast<float*>(buffer), int(frames));
        else
            std::memset(buffer, 0, frames * 2 * sizeof(float));
    }
};
Audio::Impl* Audio::Impl::active = nullptr;
Audio::Audio(const Assets& assets) : impl_(std::make_unique<Impl>(assets)) {}
Audio::~Audio() = default;
bool Audio::available() const {
    return impl_->device && impl_->synth.font;
}
void Audio::mute(bool muted) {
    if (!impl_->device)
        return;
    SetAudioStreamVolume(impl_->stream, muted ? 0.f : 0.5f);
    for (auto& effect : impl_->effects)
        if (effect.source.frameCount)
            for (auto voice : effect.voices)
                SetSoundVolume(voice, muted ? 0.f : 1.f);
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
    if (track != impl_->track) {
        std::lock_guard lock(impl_->mutex);
        impl_->track = track;
        if (track >= 5 && track < int(Tracks.size()))
            impl_->synth.set_song(impl_->tracks[track]);
        impl_->music_playing = track >= 5 && track < int(Tracks.size());
    }
    for (auto sound : game.sounds) {
        const int cue = int(sound);
        if (sound == SoundCue::MusicStop || sound == SoundCue::MusicStart) {
            std::lock_guard lock(impl_->mutex);
            impl_->music_playing = sound == SoundCue::MusicStart;
        } else if (impl_->device && cue > 0 && cue < int(impl_->effects.size()))
            impl_->effects[cue].play();
    }
    game.sounds.clear();
}
bool Audio::verify_tracks(const Assets& assets) {
    Synth synth(assets.soundfont());
    if (!synth.font)
        return false;
    std::vector<float> block(2048 * 2);
    constexpr std::array<int, 5> BlockSizes{1, 127, 512, 2048, 333};
    std::size_t total_messages = 0;
    for (int track = 5; track < int(Tracks.size()); ++track) {
        if (!synth.load(assets.midi(Tracks[track])))
            return false;
        std::size_t messages = 0;
        for (auto* message = synth.song; message; message = message->next) {
            ++messages;
            if (message->type == TML_PROGRAM_CHANGE &&
                tsf_get_presetindex(synth.font, message->channel == 9 ? 128 : 0, message->program) < 0) {
                std::cerr << "Missing MIDI program " << int(message->program) << " in " << Tracks[track]
                          << '\n';
                return false;
            }
        }
        double energy = 0;
        std::size_t block_index = 0;
        while (synth.sample < synth.ending_sample) {
            const int frames = int(std::min<std::uint64_t>(BlockSizes[block_index++ % BlockSizes.size()],
                                                           synth.ending_sample - synth.sample));
            synth.render(block.data(), frames);
            for (int i = 0; i < frames * 2; ++i) {
                const float value = block[i];
                if (!std::isfinite(value))
                    return false;
                energy += double(value) * value;
            }
        }
        if (energy < 1 || synth.next || synth.dispatched != messages)
            return false;
        synth.render(block.data(), 1);
        if (synth.sample != 1)
            return false;
        total_messages += messages;
        std::cout << "MIDI " << Tracks[track] << ": " << messages << " messages dispatched; loop verified\n"
                  << std::flush;
    }
    std::cout << "17 complete MIDI tracks: " << total_messages
              << " messages; programs available; finite, nonzero stereo synthesis\n";
    return true;
}
bool Audio::verify_playback(const Assets& assets) {
    Audio audio(assets);
    if (!audio.available())
        return false;
    audio.mute(true);
    Game game;
    game.hero.music_track = 5;
    audio.update(game);
    int tested_effects = 0;
    for (auto& effect : audio.impl_->effects) {
        if (!effect.source.frameCount)
            continue;
        ++tested_effects;
        // These go through the same cue queue as gameplay, including a burst
        // beyond the pool size. Muting leaves playback cursors running.
        const auto cue = static_cast<SoundCue>(&effect - audio.impl_->effects.data());
        game.sounds.assign(4, cue);
        audio.update(game);
        const auto playing = [&]() {
            return std::size_t(std::count_if(effect.voices.begin(), effect.voices.end(), IsSoundPlaying));
        };
        if (playing() != 4)
            return false;
        game.sounds.assign(effect.voices.size() * 2, cue);
        audio.update(game);
        if (playing() != effect.voices.size())
            return false;
        for (auto voice : effect.voices)
            StopSound(voice);
    }
    if (tested_effects != 8)
        return false;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    {
        std::lock_guard lock(audio.impl_->mutex);
        if (!audio.impl_->synth.sample)
            return false;
    }
    for (int track = 6; track < int(Tracks.size()); ++track) {
        game.hero.music_track = track;
        audio.update(game);
        std::lock_guard lock(audio.impl_->mutex);
        if (audio.impl_->synth.song != audio.impl_->tracks[track].messages.get())
            return false;
    }
    std::cout << "Audio device: eight WAV effects retain four overlapping voices; bursts stay bounded; "
                 "sample clock and 17 cached track selections passed\n";
    return true;
}
bool Audio::render_test(const Assets& assets, std::string_view midi, const std::filesystem::path& output) {
    Synth synth(assets.soundfont());
    if (!synth.load(assets.midi(midi)))
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
    // Standard PCM WAV for repeatable inspection, without opening the audio device.
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
} // namespace baseline
