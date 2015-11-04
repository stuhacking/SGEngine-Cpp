//
// Perlin Implementation.
//
#include "../Lib.h"

namespace sge {

float Perlin::perlin(const float x, const float y) const {
    float t = 0.0f;
    float freq = frequency;
    float amp = 1.0f;

    for (int o = 0, oMax = octaves; o < oMax; o++) {
        t += amp * Noise::SmoothNoise(x * freq + m_seed, y * freq + m_seed);
        freq *= 2.0f;
        amp *= persistence;
    }

    return t;
}

} /* namespace sge */
