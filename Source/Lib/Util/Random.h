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
    explicit Random (const i64 p_seed);

    /**
     * Set the seed value of this Random Number Generator.
     */
    void SetSeed (const i64 p_seed);

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
    i32 NextInt();

    /**
     * Return a random integer in the range 0..max.
     */
    i32 NextInt(const i32 max);

    /**
     * Return a random integer in the given range min..max.
     */
    i32 NextInt(const i32 min, const i32 max);

private:
    std::default_random_engine m_generator;
    std::uniform_int_distribution<int> m_intVals;
    std::uniform_real_distribution<float> m_floatVals;
};

inline Random::Random() {
    SetSeed(time(nullptr));
}

inline Random::Random(const i64 p_seed) {
    SetSeed(p_seed);
}

inline void Random::SetSeed(const i64 p_seed) {
    m_generator.seed(p_seed);
}

inline float Random::NextFloat() {
    return m_floatVals(m_generator, std::uniform_real_distribution<float>::param_type{0.0f, 1.0f});
}

inline float Random::NextFloat(const float max) {
    return m_floatVals(m_generator, std::uniform_real_distribution<float>::param_type{0.0f, max});
}

inline float Random::NextFloat(const float min, const float max) {
    return m_floatVals(m_generator, std::uniform_real_distribution<float>::param_type{min, max});
}

inline i32 Random::NextInt() {
    return m_intVals(m_generator, std::uniform_int_distribution<int>::param_type{0, INT_MAX});
}

inline i32 Random::NextInt(const i32 max) {
    return m_intVals(m_generator, std::uniform_int_distribution<int>::param_type{0, max});
}

inline i32 Random::NextInt(const i32 min, const i32 max) {
    return m_intVals(m_generator, std::uniform_int_distribution<int>::param_type{min, max});
}

} /* namespace sge */

#endif /* __SGE_RANDOM_H */
