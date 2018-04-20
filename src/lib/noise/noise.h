/*---  Noise.h - Static Hashes and Simple Noise Header  ------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Utility functions for generating noise.
 */
#ifndef __SGE_NOISE_H
#define __SGE_NOISE_H

#include "../lib.h"

class noise {
public:
    /**
     * Generate a pseudorandom scalar hash value for coordinate (x, y).
     *
     * @param x x coordinate.
     * @param y y coordinate.
     * @return Pseudorandom hash value.
     */
    static constexpr s32 hash (const s32 x, const s32 y = 0) {
        s32 n = x + y * 57;
        n = (n << 13) ^ n;
        s32 nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
        return nn;
    }

    /**
     * Generate a simple white noise value for coordinate (x, y).
     *
     * @param x x coordinate.
     * @param y y coordinate.
     * @return Simple noise value.
     */
    static constexpr float simpleNoise (const s32 x, const s32 y = 0) {
        float nn = static_cast<float>(noise::hash(x, y));
        return 1.0f - nn / 1073741824.0f;
    }

    /**
     * Generate a smoothed noise value for coordinate (x, y).
     *
     * @param x x coordinate.
     * @param y y coordinate.
     * @return Smoothed noise value.
     */
    static float smoothNoise (float x, float y = 0);

    /**
     * Generate a Perlin like simplex noise value for coordinate (x, y).
     *
     * Implements a cloudy 2D noise pattern similar to Perlin. Changing the frequency
     * and (x, y) offsets allows you to sample from different portions of the field
     * to achieve random patterns.
     *
     * @param x x coordinate.
     * @param y y coordinate.
     * @param pFreq Frequency of pattern (Higher means smaller clouds).
     * @param pAmp Overall amplitude (Adjusts constrast / sharpness).
     * @param pDecay Amount of amplitude decay per iteration.
     * @param pOct Number of iterations of noise to apply.
     * @return Perlin noise value.
     */
    static float perlin (float x, float y,
                         float pFreq = 1.0f, float pAmp = 1.0f,
                         float pDecay = 1.0f, u32 pOct = 1);

    /**
     * Generate a Worley/Cellular noise value for coordinate (x, y).
     *
     * @param x x coordinate.
     * @param y y coordinate.
     * @param pFreq Frequency of pattern (Higher means smaller cells).
     * @param pAmp Overall amplitude (Adjusts contrast / sharpness).
     * @return Worley noise value.
     */
    static float worley (float x, float y,
                         float pFreq = 1.0f, float pAmp = 1.0f);
};

// --------------------------------------------------------------------------

inline float noise::smoothNoise (const float x, const float y) {
    s32 xf = static_cast<s32>(x); // floor of x
    s32 yf = static_cast<s32>(y); // floor of y
    float xFrac = x - xf;
    float yFrac = y - yf;

    float nw = noise::simpleNoise(xf, yf);
    float ne = noise::simpleNoise(xf, yf + 1);
    float sw = noise::simpleNoise(xf + 1, yf);
    float se = noise::simpleNoise(xf + 1, yf + 1);

    float v1 = math::lerp(xFrac, nw, sw);
    float v2 = math::lerp(xFrac, ne, se);

    return math::lerp(yFrac, v1, v2);
}

#endif /* __SGE_NOISE_H */
