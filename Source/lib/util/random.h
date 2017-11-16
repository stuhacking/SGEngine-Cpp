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
 * C++ Std random and uniform_*_distribution functions.
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
    explicit Random (const s64 pSeed);

    /**
     * Set the seed value of this Random Number Generator.
     */
    void SetSeed (const s64 pSeed);

    /**
     * Return a random float value in the range 0..1.
     */
    float nextFloat ();

    /**
     * Return a random float value in the range 0..max.
     */
    float nextFloat (const float max);

    /**
     * Return a random float value with given range min..max.
     */
    float nextFloat (const float min, const float max);

    /**
     * Return a random integer in the random 0..INT_MAX.
     */
    s32 nextInt ();

    /**
     * Return a random integer in the range 0..max.
     */
    s32 nextInt (const s32 max);

    /**
     * Return a random integer in the given range min..max.
     */
    s32 nextInt (const s32 min, const s32 max);

private:
    std::default_random_engine mGenerator;
    std::uniform_int_distribution<int> mIntVals;
    std::uniform_real_distribution<float> mFloatVals;
};

// --------------------------------------------------------------------------

inline Random::Random() {
    SetSeed(time(nullptr));
}

inline Random::Random(const s64 pSeed) {
    SetSeed(pSeed);
}

inline void Random::SetSeed(const s64 pSeed) {
    mGenerator.seed(pSeed);
}

inline float Random::nextFloat () {
    return mFloatVals(mGenerator, std::uniform_real_distribution<float>::param_type{0.0f, 1.0f});
}

inline float Random::nextFloat (const float max) {
    return mFloatVals(mGenerator, std::uniform_real_distribution<float>::param_type{0.0f, max});
}

inline float Random::nextFloat (const float min, const float max) {
    return mFloatVals(mGenerator, std::uniform_real_distribution<float>::param_type{min, max});
}

inline s32 Random::nextInt () {
    return mIntVals(mGenerator, std::uniform_int_distribution<int>::param_type{0, INT_MAX});
}

inline s32 Random::nextInt (const s32 max) {
    return mIntVals(mGenerator, std::uniform_int_distribution<int>::param_type{0, max});
}

inline s32 Random::nextInt (const s32 min, const s32 max) {
    return mIntVals(mGenerator, std::uniform_int_distribution<int>::param_type{min, max});
}

} /* namespace sge */

#endif /* __SGE_RANDOM_H */
