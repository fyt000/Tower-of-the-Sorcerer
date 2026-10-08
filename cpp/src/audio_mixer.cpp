#include "audio_mixer.hpp"
#include "audio_queue.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
#define TSF_IMPLEMENTATION
#include "tsf.h"
#define TML_IMPLEMENTATION
#include "tml.h"
#define MINIAUDIO_IMPLEMENTATION
#include "audio_backend.hpp"

namespace tsw {
namespace {
constexpr int SampleRate = AudioSampleRate, MidiChannels = 16, SynthVoices = 256;
constexpr std::size_t EffectVoiceCount = 16;
constexpr std::uint64_t TrackMask = 0xff, PlayingBit = 1 << 8, MutedBit = 1 << 9;
constexpr std::uint64_t SuspendedBit = 1 << 10;
constexpr int RestartShift = 11;
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
        sample = 0;
        ending_sample = track.ending_sample;
        reset_channels();
        return bool(song);
    }

    void event(const tml_message& message) {
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
        const auto release = [](float* samples) { ma_free(samples, nullptr); };
        std::unique_ptr<float, decltype(release)> owned(static_cast<float*>(decoded), release);
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
};
} // namespace

struct AudioMixer::Impl {
    Synth synth;
    std::array<MidiTrack, Tracks.size()> tracks;
    std::array<Effect, EffectFiles.size()> effects;
    AudioCueQueue cues;
    // Only the game thread writes requested state. The callback owns all playback cursors.
    int requested_track = -1;
    bool requested_playing{}, requested_muted{}, requested_suspended{};
    std::uint64_t restart_count{};
    std::atomic<std::uint64_t> request{};
    std::uint64_t previous_request{};

    explicit Impl(const Assets& assets) : synth(assets.soundfont()) {
        for (int i = 5; i < int(Tracks.size()); ++i)
            if (!tracks[i].load(assets.midi(Tracks[i])))
                throw std::runtime_error("Cannot parse MIDI track: " + std::string(Tracks[i]));
        for (int i = 1; i < int(EffectFiles.size()); ++i)
            if (EffectFiles[i])
                effects[i].load(assets.wave(EffectFiles[i]));
    }

    void publish() {
        const auto value = (restart_count << RestartShift) |
                           std::uint64_t(valid_track(requested_track) ? requested_track : 0) |
                           (requested_playing ? PlayingBit : 0) | (requested_muted ? MutedBit : 0) |
                           (requested_suspended ? SuspendedBit : 0);
        request.store(value, std::memory_order_release);
    }

    void render(float* output, int frames) {
        const auto control = request.load(std::memory_order_acquire);
        if ((control >> RestartShift) != (previous_request >> RestartShift)) {
            const int track = int(control & TrackMask);
            if (valid_track(track))
                synth.set_song(tracks[track]);
        }
        previous_request = control;
        if (control & SuspendedBit) {
            std::fill_n(output, frames * 2, 0.f);
            return;
        }
        cues.consume([&](int cue) { effects[cue].play(); });
        if (control & PlayingBit) {
            synth.render(output, frames);
            for (int i = 0; i < frames * 2; ++i)
                output[i] *= .5f;
        } else
            std::fill_n(output, frames * 2, 0.f);
        for (auto& effect : effects)
            effect.mix(output, frames);
        for (int i = 0; i < frames * 2; ++i)
            output[i] = control & MutedBit ? 0.f : std::clamp(output[i], -1.f, 1.f);
    }
};

AudioMixer::AudioMixer(const Assets& assets) : impl_(std::make_unique<Impl>(assets)) {}

AudioMixer::~AudioMixer() = default;

void AudioMixer::render(float* output, int frames) {
    impl_->render(output, frames);
}

void AudioMixer::mute(bool muted) {
    impl_->requested_muted = muted;
    impl_->publish();
}

void AudioMixer::suspend(bool suspended) {
    impl_->requested_suspended = suspended;
    impl_->publish();
}

void AudioMixer::restart(Game& game) {
    impl_->requested_track = -1;
    update(game);
}

int AudioMixer::track_for_scene(const Game& game) {
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

void AudioMixer::update(Game& game) {
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
        else if (cue > 0 && cue < int(EffectFiles.size()) && EffectFiles[cue])
            impl_->cues.push(cue); // Drop excess cues when the fixed queue is full.
    }
    impl_->publish();
    game.sounds.clear();
}
} // namespace tsw
