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

class Random {
public:
    Random();

    Random(const int p_seed);

    void SetSeed(const int p_seed);

    float NextFloat();

    float NextFloat(const float max);

    float NextFloat(const float min, const float max);

    int NextInt();

    int NextInt(const int max);

    int NextInt(const int min, const int max);

private:
    std::default_random_engine m_generator;
};

inline Random::Random() {
    SetSeed(time(nullptr));
}

inline Random::Random(const int p_seed) {
    SetSeed(p_seed);
}

inline void Random::SetSeed(const int p_seed) {
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

inline int Random::NextInt() {
    std::uniform_int_distribution<int> vals(0, INT_MAX);
    return vals(m_generator);
}

inline int Random::NextInt(const int max) {
    std::uniform_int_distribution<int> vals(0, max);
    return vals(m_generator);
}

inline int Random::NextInt(const int min, const int max) {
    std::uniform_int_distribution<int> vals(min, max);
    return vals(m_generator);
}

#endif /* __SHLIB_RANDOM_H_ */
