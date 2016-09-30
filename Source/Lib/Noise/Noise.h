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
#ifndef __SGENGINE_NOISE_H_
#define __SGENGINE_NOISE_H_

#include "../Lib.h"

namespace sge {

class Noise {
public:
    static s32 Hash (const s32 x, const s32 y = 0);

    static float SimpleNoise (const s32 x, const s32 y = 0);

    static float SmoothNoise (const float x, const float y = 0);

    static float Perlin (const float x, const float y,
                         const float p_freq = 1.0f, const float p_amp = 1.0f,
                         const float p_decay = 1.0f, const u32 p_oct = 1);

    static float Worley (const float x, const float y,
                         const float p_freq = 1.0f, const float p_amp = 1.0f);
};

// --------------------------------------------------------------------------

INLINE s32 Noise::Hash (const s32 x, const s32 y) {
    s32 n = x + y * 57;
    n = (n << 13) ^ n;
    s32 nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
    return nn;
}

INLINE float Noise::SimpleNoise (const s32 x, const s32 y) {
    s32 nn = Noise::Hash(x, y);
    return 1.0f - (static_cast<float>(nn) / 1073741824.0f);
}

INLINE float Noise::SmoothNoise (const float x, const float y) {
    s32 xf = static_cast<s32>(x); // floor of x
    s32 yf = static_cast<s32>(y); // floor of y
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

} /* namespace sge */

#endif /* __SGENGINE_NOISE_H_ */
