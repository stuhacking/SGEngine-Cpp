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

#include "../Lib.h"

class Noise {
public:
    /**
     * Generate a pseudorandom scalar hash value for coordinate (x, y).
     *
     * @param x x coordinate.
     * @param y y coordinate.
     * @return Pseudorandom hash value.
     */
    static i32 Hash (const i32 x, const i32 y = 0);

    /**
     * Generate a simple white noise value for coordinate (x, y).
     *
     * @param x x coordinate.
     * @param y y coordinate.
     * @return Simple noise value.
     */
    static float SimpleNoise (const i32 x, const i32 y = 0);

    /**
     * Generate a smoothed noise value for coordinate (x, y).
     *
     * @param x x coordinate.
     * @param y y coordinate.
     * @return Smoothed noise value.
     */
    static float SmoothNoise (const float x, const float y = 0);

    /**
     * Generate a Perlin like simplex noise value for coordinate (x, y).
     *
     * Implements a cloudy 2D noise pattern similar to Perlin. Changing the frequency
     * and (x, y) offsets allows you to sample from different portions of the field
     * to achieve random patterns.
     *
     * @param x x coordinate.
     * @param y y coordinate.
     * @param p_freq Frequency of pattern (Higher means smaller clouds).
     * @param p_amp Overall amplitude (Adjusts constrast / sharpness).
     * @param p_decay Amount of amplitude decay per iteration.
     * @param p_oct Number of iterations of noise to apply.
     * @return Perlin noise value.
     */
    static float Perlin (const float x, const float y,
                         const float p_freq = 1.0f, const float p_amp = 1.0f,
                         const float p_decay = 1.0f, const u32 p_oct = 1);

    /**
     * Generate a Worley/Cellular noise value for coordinate (x, y).
     *
     * @param x x coordinate.
     * @param y y coordinate.
     * @param p_freq Frequency of pattern (Higher means smaller cells).
     * @param p_amp Overall amplitude (Adjusts contrast / sharpness).
     * @return Worley noise value.
     */
    static float Worley (const float x, const float y,
                         const float p_freq = 1.0f, const float p_amp = 1.0f);
};

// --------------------------------------------------------------------------

inline i32 Noise::Hash (const i32 x, const i32 y) {
    i32 n = x + y * 57;
    n = (n << 13) ^ n;
    i32 nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
    return nn;
}

inline float Noise::SimpleNoise (const i32 x, const i32 y) {
    i32 nn = Noise::Hash(x, y);
    return 1.0f - (static_cast<float>(nn) / 1073741824.0f);
}

inline float Noise::SmoothNoise (const float x, const float y) {
    i32 xf = static_cast<i32>(x); // floor of x
    i32 yf = static_cast<i32>(y); // floor of y
    float xFrac = x - xf;
    float yFrac = y - yf;

    float nw = Noise::SimpleNoise(xf, yf);
    float ne = Noise::SimpleNoise(xf, yf + 1);
    float sw = Noise::SimpleNoise(xf + 1, yf);
    float se = Noise::SimpleNoise(xf + 1, yf + 1);

    float v1 = FMath::Lerp(xFrac, nw, sw);
    float v2 = FMath::Lerp(xFrac, ne, se);

    return FMath::Lerp(yFrac, v1, v2);
}

#endif /* __SGE_NOISE_H */
