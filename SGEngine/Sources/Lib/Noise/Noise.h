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
    static int Hash (const int x, const int y);

    static float SimpleNoise (const int x, const int y);

    static float SmoothNoise (const float x, const float y);
};

// --------------------------------------------------------------------------

inline int Noise::Hash (const int x, const int y) {
    int n = x + y * 57;
    n = (n << 13) ^ n;
    int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
    return nn;
}

inline float Noise::SimpleNoise (const int x, const int y) {
    int nn = Noise::Hash(x, y);
    return 1.0f - (static_cast<float>(nn) / 1073741824.0f);
}

inline float Noise::SmoothNoise (const float x, const float y) {
    int xf = static_cast<int>(x); // floor of x
    int yf = static_cast<int>(y); // floor of y
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
