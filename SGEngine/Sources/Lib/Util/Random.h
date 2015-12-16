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
#ifndef __SHLIB_RANDOM_H_
#define __SHLIB_RANDOM_H_

#include <cmath>
#include <ctime>
#include <random>
#include <climits>

namespace sge {

class Random {
public:
    Random();

    Random (const s32 p_seed);

    void SetSeed (const s32 p_seed);

    float NextFloat();

    float NextFloat(const float max);

    float NextFloat(const float min, const float max);

    s32 NextInt();

    s32 NextInt(const s32 max);

    s32 NextInt(const s32 min, const s32 max);

private:
    std::default_random_engine m_generator;
};

inline Random::Random() {
    SetSeed(time(nullptr));
}

inline Random::Random(const s32 p_seed) {
    SetSeed(p_seed);
}

inline void Random::SetSeed(const s32 p_seed) {
    m_generator.seed(p_seed);
}

inline float Random::NextFloat() {
    std::uniform_real_distribution<float> vals(0.0f, 1.0f);
    return vals(m_generator);
}

inline float Random::NextFloat(const float max) {
    std::uniform_real_distribution<float> vals(0.0f, max);
    return vals(m_generator);
}

inline float Random::NextFloat(const float min, const float max) {
    std::uniform_real_distribution<float> vals(min, max);
    return vals(m_generator);
}

inline s32 Random::NextInt() {
    std::uniform_int_distribution<int> vals(0, INT_MAX);
    return vals(m_generator);
}

inline s32 Random::NextInt(const s32 max) {
    std::uniform_int_distribution<int> vals(0, max);
    return vals(m_generator);
}

inline s32 Random::NextInt(const s32 min, const s32 max) {
    std::uniform_int_distribution<int> vals(min, max);
    return vals(m_generator);
}

} /* namespace sge */

#endif /* __SHLIB_RANDOM_H_ */
