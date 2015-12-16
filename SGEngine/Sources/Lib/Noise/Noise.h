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
#ifndef __SHLIB_NOISE_H_
#define __SHLIB_NOISE_H_

#include "../Lib.h"

namespace sge {

class Noise {
public:
    static s32 Hash (const s32 x, const s32 y);

    static float SimpleNoise (const s32 x, const s32 y);

    static float SmoothNoise (const float x, const float y);
};

// --------------------------------------------------------------------------

inline s32 Noise::Hash (const s32 x, const s32 y) {
    s32 n = x + y * 57;
    n = (n << 13) ^ n;
    s32 nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
    return nn;
}

inline float Noise::SimpleNoise (const s32 x, const s32 y) {
    s32 nn = Noise::Hash(x, y);
    return 1.0f - (static_cast<float>(nn) / 1073741824.0f);
}

inline float Noise::SmoothNoise (const float x, const float y) {
    s32 xf = static_cast<s32>(x); // floor of x
    s32 yf = static_cast<s32>(y); // floor of y
    float xFrac = x - xf;
    float yFrac = y - yf;

    float nw = Noise::SimpleNoise(xf, yf);
    float ne = Noise::SimpleNoise(xf, yf + 1);
    float sw = Noise::SimpleNoise(xf + 1, yf);
    float se = Noise::SimpleNoise(xf + 1, yf + 1);

    float v1 = FMath::CosInterpolate(nw, sw, xFrac);
    float v2 = FMath::CosInterpolate(ne, se, xFrac);

    return FMath::CosInterpolate(v1, v2, yFrac);
}

} /* namespace sge */

#endif /* __SHLIB_NOISE_H_ */
