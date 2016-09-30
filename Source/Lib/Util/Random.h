/*---  Random.h - Random Number Generator Header  ------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a wrapper around stl random generators.
 */
#ifndef __SGE_RANDOM_H
#define __SGE_RANDOM_H

#include <cmath>
#include <ctime>
#include <random>
#include <climits>

namespace sge {

/**
 * A Pseudo-random Number Generator which is a wrapper around
 * C++11 random and uniform_*_distribution functions.
 *
 * Default and single argument overloads will assume you want a
 * positive value, unless you explicitly negative values.
 */
class Random {
public:
    /**
     * Create a Random Number Generator with a seed
     * based on the current epoch time.
     */
    Random();

    /**
     * Create a Random Number Generator with a
     * given seed.
     */
    explicit Random (const s64 p_seed);

    /**
     * Set the seed value of this Random Number Generator.
     */
    void SetSeed (const s64 p_seed);

    /**
     * Return a random float value in the range 0..1.
     */
    float NextFloat();

    /**
     * Return a random float value in the range 0..max.
     */
    float NextFloat(const float max);

    /**
     * Return a random float value with given range min..max.
     */
    float NextFloat(const float min, const float max);

    /**
     * Return a random integer in the random 0..INT_MAX.
     */
    s32 NextInt();

    /**
     * Return a random integer in the range 0..max.
     */
    s32 NextInt(const s32 max);

    /**
     * Return a random integer in the given range min..max.
     */
    s32 NextInt(const s32 min, const s32 max);

private:
    std::default_random_engine m_generator;
};

INLINE Random::Random() {
    SetSeed(time(nullptr));
}

INLINE Random::Random(const s64 p_seed) {
    SetSeed(p_seed);
}

INLINE void Random::SetSeed(const s64 p_seed) {
    m_generator.seed(p_seed);
}

INLINE float Random::NextFloat() {
    std::uniform_real_distribution<float> vals(0.0f, 1.0f);
    return vals(m_generator);
}

INLINE float Random::NextFloat(const float max) {
    std::uniform_real_distribution<float> vals(0.0f, max);
    return vals(m_generator);
}

INLINE float Random::NextFloat(const float min, const float max) {
    std::uniform_real_distribution<float> vals(min, max);
    return vals(m_generator);
}

INLINE s32 Random::NextInt() {
    std::uniform_int_distribution<int> vals(0, INT_MAX);
    return vals(m_generator);
}

INLINE s32 Random::NextInt(const s32 max) {
    std::uniform_int_distribution<int> vals(0, max);
    return vals(m_generator);
}

INLINE s32 Random::NextInt(const s32 min, const s32 max) {
    std::uniform_int_distribution<int> vals(min, max);
    return vals(m_generator);
}

} /* namespace sge */

#endif /* __SGE_RANDOM_H */
