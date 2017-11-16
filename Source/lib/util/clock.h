/*---  Clock.h - Clock Header  -------------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a Clock class and timing functions using
 *   the system's High Frequency Timer via std::chrono.
 */
#ifndef __SGE_CLOCK_H
#define __SGE_CLOCK_H

namespace sge {

/**
 * Clock Class.
 */
class Clock {
public:
    /**
     * Get the absolute nanosecond timestamp measured from the
     * start of the program by querying the High Performance Clock.
     */
    static u64 nanoTime ();

    /**
     * Get the absolute millisecond timestamp measured from the
     * start of the program by querying the High Performance Clock.
     */
    static u64 millisTime ();

    /**
     * Convert a nanosecond value to seconds as a float value.
     * This function should only be used for converting small values.
     */
    static constexpr float nanoToSeconds (const u64 nanos) {
        return static_cast<float>(nanos / 1000000000.0f);
    }

    /**
     * Convert seconds to nanoseconds.
     */
    constexpr static u64 secondsToNano (const float seconds) {
        return static_cast<u64>(seconds * 1000000000.0f);
    }

public:
    /**
     * Default Constructor
     * @param scale Time scaling factor, default = 1.
     */
    explicit Clock (const float scale = 1.0f)
        : mLastTime(0), mElapsed(0), mDelta(0), mScale(scale), mPaused(false) {
        mLastTime = nanoTime();
    }

    /**
     * Update the elapsed time for this clock.
     */
    void update ();

    /**
     * Step the clock forward by a given number of seconds.
     * Only enabled if the Clock is paused.
     */
    void step (const float seconds);

    void pause (const bool pause = true) { mPaused = pause; }

    bool isPaused () const { return mPaused; }

    void setScale (const float scale);

    float scale () const { return mScale; }

    /**
     * Get the total elapsed time in nanoseconds
     * for this clock.
     */
    u64 elapsed () const { return mElapsed; }

    /**
     * Get the elapsed time since the previous update
     * in nanoseconds.
     */
    u64 delta () const { return mDelta; }

    /**
     * Get the float delta in seconds since the previous
     * update.
     */
    float deltaSeconds () const;

    /**
     * Get the difference in nanoseconds between this clock
     * and another clock.
     */
    u64 difference (const Clock &other) const;

private:
    u64 mLastTime;
    u64 mElapsed;
    u64 mDelta;

    float mScale;
    bool mPaused;
};

// --------------------------------------------------------------------------

inline void Clock::setScale (const float scale) {
    mScale = math::clampFloat(scale, 0.0f, 100.0f);
}

inline float Clock::deltaSeconds () const {
    return nanoToSeconds(mDelta);
}

inline u64 Clock::difference (const Clock &other) const {
    return mElapsed - other.mElapsed;
}

} /* namespace sge */

#endif /* __SGE_CLOCK_H */
