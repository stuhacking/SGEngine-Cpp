//
// Worley Implementation.
//
#include "../lib.h"

#include <random>

static constexpr int kMaxFeaturePoints = 8;

static std::default_random_engine kRndEngine;
static std::uniform_int_distribution<s8> kFeatureDist(1, kMaxFeaturePoints);
static std::uniform_real_distribution<float> kCoordDist(0.0f, 1.0f);

static float euclidDistance (const Vec2f &a, const Vec2f &b) {

    return (a - b).magSq();
}

float noise::worley (float x,
                     float y,
                     const float pFreq,
                     const float pAmp) {
    float nearest = 0.0f;

    x *= pFreq;
    y *= pFreq;

    bool first = true;
    for (s32 p = -1; p <= 1; ++p) {
        for (s32 q = -1; q <= 1; ++q) {
            s32 sqX = static_cast<s32>(x) + p;
            s32 sqY = static_cast<s32>(y) + q;
            kRndEngine.seed(noise::hash(sqX, sqY));

            for (s32 k = 0, kMax = kFeatureDist(kRndEngine); k < kMax; ++k) {
                Vec2f fp = Vec2f(sqX + kCoordDist(kRndEngine), sqY + kCoordDist(kRndEngine));
                Vec2f v = Vec2f(x, y);

                float distance = euclidDistance(v, fp);
                if (first || distance < nearest) {
                    nearest = distance;
                    first = false;
                }
            }
        }
    }

    return math::clamp(pAmp * nearest, 0.0f, 1.0f) * 2.0f - 1.0f;
}

float noise::perlin (const float x, const float y,
                     const float pFreq, const float pAmp,
                     const float pDecay, const u32 pOct) {
    float t = 0.0f;
    float freq = pFreq;
    float amp = 1.0f;

    for (u32 o = 0; o < pOct; ++o) {
        t += amp * noise::smoothNoise(x * freq, y * freq);
        freq *= 2.0f;
        amp *= pDecay;
    }

    return t * pAmp;
}
