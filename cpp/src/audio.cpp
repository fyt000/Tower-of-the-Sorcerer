#include "audio.hpp"
#include "audio_backend.hpp"
#include "audio_mixer.hpp"

namespace tsw {
struct Audio::Impl {
    AudioMixer mixer;
    ma_device device{};
    bool device_ready{};

    explicit Impl(const Assets& assets) : mixer(assets) {
        // The direct device callback avoids raylib's mutex around its stream mixer.
        auto config = ma_device_config_init(ma_device_type_playback);
        config.playback.format = ma_format_f32;
        config.playback.channels = 2;
        config.sampleRate = AudioSampleRate;
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
        // Uninitialization joins the device thread before playback storage is freed.
        if (device_ready)
            ma_device_uninit(&device);
    }

    static void callback(ma_device* device, void* output, const void*, ma_uint32 frames) {
        static_cast<Impl*>(device->pUserData)->mixer.render(static_cast<float*>(output), int(frames));
    }
};

Audio::Audio(const Assets& assets) : impl_(std::make_unique<Impl>(assets)) {}

Audio::~Audio() = default;

bool Audio::available() const {
    return impl_->device_ready;
}

void Audio::mute(bool muted) {
    impl_->mixer.mute(muted);
}

void Audio::suspend(bool suspended) {
    impl_->mixer.suspend(suspended);
}

void Audio::restart(Game& game) {
    impl_->mixer.restart(game);
}

int Audio::track_for_scene(const Game& game) {
    return AudioMixer::track_for_scene(game);
}

void Audio::update(Game& game) {
    impl_->mixer.update(game);
}
} // namespace tsw
