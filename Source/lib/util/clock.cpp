//
// Clock Implementation.
//
#include "../lib.h"

#include <chrono>

namespace sge {

// Initialize the internal high-res clock.
static const auto gProgramStart = std::chrono::high_resolution_clock::now();

u64 Clock::nanoTime () {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now - gProgramStart).count();
}

u64 Clock::millisTime () {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - gProgramStart).count();
}

// Clock Instance Methods

void Clock::update () {
    u64 currentTime = nanoTime();

    if (!mPaused) {
        u64 realDelta = currentTime - mLastTime;
        u64 scaledDelta = static_cast<u64>(realDelta * mScale);

        mLastTime = currentTime;
        mElapsed += scaledDelta;
        mDelta = scaledDelta;
    } else {
        mLastTime = currentTime;
        mDelta = 0;
    }
}

void Clock::step (const float seconds) {
    if (mPaused) {
        u64 scaledDelta = static_cast<u64>(secondsToNano(seconds) * mScale);
        mLastTime = nanoTime();
        mElapsed += scaledDelta;
        mDelta = scaledDelta;
    }
}

} /* namespace sge */
