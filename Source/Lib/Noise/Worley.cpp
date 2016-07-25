//
// Worley Implementation.
//
#include "../Lib.h"

#include <random>

namespace sge {

static constexpr u32 MAX_FEATURE_POINTS = 8;

static std::default_random_engine generator;
static std::uniform_int_distribution<s8> features(1, MAX_FEATURE_POINTS);
static std::uniform_real_distribution<float> coords(0.0f, 1.0f);

static float euclidDistance(const Vec2f &a, const Vec2f &b) {
    return (a - b).LengthSqr();
}

float Noise::Worley(float x, float y,
                    const float p_freq, const float p_amp) {
    s32 sqX, sqY;
    Vec2f fp, v;
    bool first = true;
    float nearest = 0.0f;

    x *= p_freq;
    y *= p_freq;

    for (s32 p = -1; p <= 1; ++p) {
        for (s32 q = -1; q <= 1; ++q) {
            sqX = static_cast<s32>(x) + p;
            sqY = static_cast<s32>(y) + q;
            generator.seed(Noise::Hash(sqX, sqY));

            for (s8 k = 0, kMax = features(generator); k < kMax; ++k) {
                fp.Set(sqX + coords(generator), sqY + coords(generator));
                v.Set(x, y);

                float distance = euclidDistance(v, fp);
                if (first || distance < nearest) {
                    nearest = distance;
                    first = false;
                }
            }
        }
    }

    return FMath::ClampFloat(p_amp * nearest, 0.0f, 1.0f) * 2.0f - 1.0f;
}

} /* namespace sge */
