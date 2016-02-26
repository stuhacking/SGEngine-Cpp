//
// Clock Implementation.
//
#include "../Lib.h"

#include <chrono>

namespace sge {

// Initialize the internal high-res clock.
static auto GLOBAL_START = std::chrono::high_resolution_clock::now();

u64 Clock::NanoTime() {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now - GLOBAL_START).count();
}

u64 Clock::MillisTime () {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - GLOBAL_START).count();
}

// Clock Instance Methods

void Clock::Update () {
    u64 currentTime = NanoTime();
    if (!m_paused) {
        u32 realDelta = currentTime - m_lastTime;
        u32 scaledDelta = realDelta * m_scale;

        m_lastTime = currentTime;
        m_elapsed += scaledDelta;
        m_delta = scaledDelta;
    } else {
        m_lastTime = currentTime;
        m_delta = 0;
    }
}

void Clock::Step (const float seconds) {
    if (m_paused) {
        u32 scaledDelta = SecondsToNanoTime(seconds) * m_scale;
        m_lastTime = NanoTime();
        m_elapsed += scaledDelta;
        m_delta = scaledDelta;
    }
}

} /* namespace sge */
