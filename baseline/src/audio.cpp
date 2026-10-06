#include "audio.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mutex>
#include <vector>
#define TSF_IMPLEMENTATION
#include "tsf.h"
#define TML_IMPLEMENTATION
#include "tml.h"

namespace baseline {
namespace {
constexpr int SampleRate = 44100;
constexpr std::array<const char*, 22> Tracks{
    nullptr,    nullptr,    nullptr,    nullptr,    nullptr,    "b_067xgw", "b_058xgw", "a_008xgw",
    "a_118xgw", "a_019xgw", "b_018xgw", "a_050xgw", "a_085xgw", "a_032xgw", "a_046xgw", "a_005xgw",
    "a_007xgw", "b_110xgw", "a_023xgw", "b_117xgw", "b_014xgw", "a_027xgw"};
struct Synth {
    tsf* font{};
    tml_message *song{}, *next{};
    std::uint64_t sample{}, ending_sample{};
    explicit Synth(const std::filesystem::path& file) {
        font = tsf_load_filename(file.string().c_str());
        if (font) {
            tsf_set_output(font, TSF_STEREO_INTERLEAVED, SampleRate, -8);
            tsf_set_max_voices(font, 256);
            reset_channels();
        }
    }
    ~Synth() {
        if (song)
            tml_free(song);
        if (font)
            tsf_close(font);
    }
    void reset_channels() {
        tsf_reset(font);
        for (int channel = 0; channel < 16; ++channel)
            tsf_channel_set_presetnumber(font, channel, 0, channel == 9);
    }
    bool set_song(tml_message* loaded) {
        if (song)
            tml_free(song);
        song = next = loaded;
        sample = 0;
        ending_sample = 0;
        if (font)
            reset_channels();
        if (song) {
            auto* last = song;
            while (last->next)
                last = last->next;
            ending_sample = (std::uint64_t(last->time) + 2000) * SampleRate / 1000;
        }
        return font && song;
    }
    bool load(const std::filesystem::path& file) {
        return set_song(tml_load_filename(file.string().c_str()));
    }
    void event(const tml_message& message) {
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
    std::filesystem::path assets;
    AudioStream stream{};
    std::array<Sound, 11> effects{};
    bool device{}, music_playing = true;
    int track = -1;
    Impl(const std::filesystem::path& folder, const std::filesystem::path& font)
        : synth(font), assets(folder) {
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
        constexpr std::array<const char*, 11> Files{nullptr, "open", "get", "taisen", "zeno", nullptr,
                                                    nullptr, "3f",   "20f", "kai",    "kai2"};
        for (int i = 1; i < 11; ++i)
            if (Files[i])
                effects[i] = LoadSound((assets / "wav" / (std::string(Files[i]) + ".wav")).string().c_str());
    }
    ~Impl() {
        if (!device)
            return;
        StopAudioStream(stream);
        UnloadAudioStream(stream);
        active = nullptr;
        for (auto sound : effects)
            if (sound.frameCount)
                UnloadSound(sound);
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
Audio::Audio(const std::filesystem::path& assets, const std::filesystem::path& font)
    : impl_(std::make_unique<Impl>(assets, font)) {}
Audio::~Audio() = default;
bool Audio::available() const {
    return impl_->device && impl_->synth.font;
}
void Audio::mute(bool muted) {
    if (!impl_->device)
        return;
    SetAudioStreamVolume(impl_->stream, muted ? 0.f : 0.5f);
    for (auto sound : impl_->effects)
        if (sound.frameCount)
            SetSoundVolume(sound, muted ? 0.f : 1.f);
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
        // Parse MIDI before taking the callback's lock, so disk reads cannot starve audio.
        tml_message* loaded =
            track >= 5 && track < int(Tracks.size())
                ? tml_load_filename(
                      (impl_->assets / "midi" / (std::string(Tracks[track]) + ".mid")).string().c_str())
                : nullptr;
        std::lock_guard lock(impl_->mutex);
        impl_->track = track;
        if (loaded)
            impl_->synth.set_song(loaded);
        impl_->music_playing = impl_->track != 0;
    }
    for (auto sound : game.sounds) {
        const int cue = int(sound);
        if (sound == SoundCue::MusicStop || sound == SoundCue::MusicStart) {
            std::lock_guard lock(impl_->mutex);
            impl_->music_playing = sound == SoundCue::MusicStart;
        } else if (impl_->device && cue > 0 && cue < 11 && impl_->effects[cue].frameCount)
            PlaySound(impl_->effects[cue]);
    }
    game.sounds.clear();
}
bool Audio::verify_tracks(const std::filesystem::path& assets, const std::filesystem::path& font) {
    Synth synth(font);
    if (!synth.font)
        return false;
    std::vector<float> block(SampleRate * 2);
    for (int track = 5; track < int(Tracks.size()); ++track) {
        if (!synth.load(assets / "midi" / (std::string(Tracks[track]) + ".mid")))
            return false;
        for (auto* message = synth.song; message; message = message->next)
            if (message->type == TML_PROGRAM_CHANGE &&
                tsf_get_presetindex(synth.font, message->channel == 9 ? 128 : 0, message->program) < 0) {
                std::cerr << "Missing MIDI program " << int(message->program) << " in " << Tracks[track]
                          << '\n';
                return false;
            }
        double energy = 0;
        for (int second = 0; second < 6; ++second) {
            synth.render(block.data(), SampleRate);
            for (float value : block) {
                if (!std::isfinite(value))
                    return false;
                energy += double(value) * value;
            }
        }
        if (energy < 1)
            return false;
    }
    std::cout << "17 MIDI tracks: programs available; finite, nonzero stereo synthesis\n";
    return true;
}
bool Audio::render_test(const std::filesystem::path& midi, const std::filesystem::path& font,
                        const std::filesystem::path& output) {
    Synth synth(font);
    if (!synth.load(midi))
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
