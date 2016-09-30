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
    static u64 NanoTime ();

    /**
     * Get the absolute millisecond timestamp measured from the
     * start of the program by querying the High Performance Clock.
     */
    static u64 MillisTime ();

    /**
     * Convert a nanosecond value to seconds as a float value.
     * This function should only be used for converting small values.
     */
    constexpr static float NanoTimeToSeconds (const u64 nanos) {
        return static_cast<float>(nanos / 1000000000.0f);
    }

    /**
     * Convert seconds to nanoseconds.
     */
    constexpr static u64 SecondsToNanoTime (const float seconds) {
        return static_cast<u64>(seconds * 1000000000.0f);
    }

public:
    /**
     * Default Constructor
     * @param scale Time scaling factor, default = 1.
     */
    explicit Clock (const float scale = 1.0f)
        : m_lastTime(0), m_elapsed(0), m_delta(0), m_scale(scale), m_paused(false) {
        m_lastTime = NanoTime();
    }

    /**
     * Update the elapsed time for this clock.
     */
    void Update ();

    /**
     * Step the clock forward by a given number of seconds.
     * Only enabled if the Clock is paused.
     */
    void Step (const float seconds);

    void Pause (const bool pause = true) { m_paused = pause; }

    bool IsPaused () const { return m_paused; }

    void SetScale (const float scale);

    float Scale () const { return m_scale; }

    /**
     * Get the total elapsed time in nanoseconds
     * for this clock.
     */
    u64 Elapsed () const { return m_elapsed; }

    /**
     * Get the elapsed time since the previous update
     * in nanoseconds.
     */
    u32 Delta () const { return m_delta; }

    /**
     * Get the float delta in seconds since the previous
     * update.
     */
    float DeltaSeconds () const;

    /**
     * Get the difference in nanoseconds between this clock
     * and another clock.
     */
    u32 Delta (const Clock &other) const;

private:
    u64 m_lastTime;
    u64 m_elapsed;
    u32 m_delta;

    float m_scale;
    bool m_paused;
};

// --------------------------------------------------------------------------

INLINE void Clock::SetScale (const float scale) {
    m_scale = FMath::ClampFloat(scale, 0.0f, 100.0f);
}

INLINE float Clock::DeltaSeconds () const {
    return NanoTimeToSeconds(m_delta);
}

INLINE u32 Clock::Delta (const Clock &other) const {
    return m_elapsed - other.m_elapsed;
}

} /* namespace sge */

#endif /* __SGE_CLOCK_H */
