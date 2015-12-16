/*---  Perlin.h - Perlin/Simplex Noise Header  ---------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 * 
 * @brief Define a Perlin/Simplex noise generator.
 */
#ifndef __SHLIB_PERLIN_H_
#define __SHLIB_PERLIN_H_

namespace sge {

/**
 * 1D/2D Perlin Noise.
 */
class Perlin {
public:
    float frequency;
    float amplitude;
    float persistence;
    u32 octaves;

public:
    Perlin(const float p_freq = 1.0f, const float p_amp = 1.0f,
           const float p_pers = 0.5f, const u32 p_oct = 1)
        : frequency(p_freq), amplitude(p_amp),
          persistence(p_pers), octaves(p_oct) {
        SetSeed(1);
    }

    /**
     * Set a new seed value for this noise generator.
     */
    void SetSeed(const s32 seed);

    /**
     * Get the 1D value of this noise at position x.
     */
    float Get(const float x) const;

    /**
     * Get the 2D value of this noise at position (x,y).
     */
    float Get(const float x, const float y) const;

private:
    s32 m_seed;

    float perlin(const float x, const float y) const;
};

// --------------------------------------------------------------------------

inline void Perlin::SetSeed(const s32 seed) {
    s32 s = static_cast<s32>(seed & 0xFF);
    m_seed = 2 + s * s;
}

inline float Perlin::Get(const float x) const {
    return Get(x, 0.0f);
}

inline float Perlin::Get(const float x, const float y) const {
    return amplitude * perlin(x, y);
}

} /* namespace sge */

#endif /* __SHLIB_PERLIN_H_ */
