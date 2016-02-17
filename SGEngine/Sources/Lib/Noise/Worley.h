/*---  Worley.h - Cellular Noise Header  ---------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 * 
 * @brief Define a Worley/Cellular noise generator.
 */
#ifndef __SGENGINE_WORLEY_H_
#define __SGENGINE_WORLEY_H_

namespace sge {

/**
 * 2D Cellular Noise.
 */
class Worley {
public:
    float frequency;
    float amplitude;

public:
    Worley(const float p_freq = 1.0f, const float p_amp = 1.0f)
        : frequency(p_freq), amplitude(p_amp) {
        SetSeed(1);
    }

    /**
     * Set the seed of this noise generator.
     */
    void SetSeed(const s32 seed);

    /**
     * Get the 2D value of this noise generator at position (x,y).
     */
    float Get(const float x, const float y) const;

private:
    s32 m_seed;

    float worley(const float x, const float y) const;
};

// --------------------------------------------------------------------------

inline void Worley::SetSeed(const s32 seed) {
    s32 s = static_cast<s32>(seed & 0xFF);
    m_seed = 2 + s * s;
}

inline float Worley::Get(const float x, const float y) const {
    return worley(x * frequency, y * frequency);
}

} /* namespace sge */

#endif /* __SGENGINE_WORLEY_H_ */
