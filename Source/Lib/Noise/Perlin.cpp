//
// Perlin Implementation.
//
#include "../Lib.h"

float Noise::Perlin (const float x, const float y,
                    const float p_freq, const float p_amp,
                    const float p_decay, const u32 p_oct) {
    float t = 0.0f;
    float freq = p_freq;
    float amp = 1.0f;

    for (u32 o = 0; o < p_oct; ++o) {
        t += amp * Noise::SmoothNoise(x * freq, y * freq);
        freq *= 2.0f;
        amp *= p_decay;
    }

    return t * p_amp;
}
