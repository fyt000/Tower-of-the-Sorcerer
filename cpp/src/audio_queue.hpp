#pragma once
#include <array>
#include <atomic>
#include <cstdint>

namespace tsw {
// One producer (game thread), one consumer (device callback); fixed storage.
struct AudioCueQueue {
    static constexpr std::size_t Capacity = 512;
    std::array<int, Capacity> cues{};
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

static_assert(std::atomic<std::uint32_t>::is_always_lock_free);
} // namespace tsw
