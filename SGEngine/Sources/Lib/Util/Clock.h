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
#ifndef __SGENGINE_CLOCK_H_
#define __SGENGINE_CLOCK_H_

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
        return static_cast<float>(nanos / SECONDS);
    }

    /**
     * Convert seconds to nanoseconds.
     */
    constexpr static u64 SecondsToNanoTime (const float seconds) {
        return static_cast<u64>(seconds * SECONDS);
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

    void SetScale (const float scale) { m_scale = scale; }

    /**
     * Get the total elapsed time in nanoseconds
     * for this clock.
     */
    u64 Elapsed () const { return m_elapsed; }

    /**
     * Get the elapsed time since the previous update
     * in nanoseconds.
     */
    u64 Delta () const { return m_delta; }

    /**
     * Get the float delta in seconds since the previous
     * update.
     */
    float DeltaSeconds () const;

    /**
     * Get the difference in nanoseconds between this clock
     * and another clock.
     */
    u64 Delta (const Clock &other) const;

private:
    u64 m_lastTime;
    u64 m_elapsed;
    u64 m_delta;

    float m_scale;
    bool m_paused;

private:
    constexpr static const float SECONDS = 1000000000.0f;
};

// --------------------------------------------------------------------------

inline float Clock::DeltaSeconds () const {
    return NanoTimeToSeconds(m_delta);
}

inline u64 Clock::Delta (const Clock &other) const {
    return m_elapsed - other.m_elapsed;
}

} /* namespace sge */

#endif /* __SGENGINE_CLOCK_H_ */
