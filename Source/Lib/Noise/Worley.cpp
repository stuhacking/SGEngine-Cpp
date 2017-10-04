//
// Worley Implementation.
//
#include "../Lib.h"

#include <random>

static constexpr u32 MAX_FEATURE_POINTS = 8;

static std::default_random_engine generator;
static std::uniform_int_distribution<i8> features(1, MAX_FEATURE_POINTS);
static std::uniform_real_distribution<float> coords(0.0f, 1.0f);

static float euclidDistance (const Vec2f &a, const Vec2f &b) {

    return (a - b).LengthSqr();
}

float Noise::Worley (float x,
                     float y,
                     const float p_freq,
                     const float p_amp) {
    float nearest = 0.0f;

    x *= p_freq;
    y *= p_freq;

    bool first = true;
    for (i32 p = -1; p <= 1; ++p) {
        for (i32 q = -1; q <= 1; ++q) {
            i32 sqX = static_cast<i32>(x) + p;
            i32 sqY = static_cast<i32>(y) + q;
            generator.seed(Noise::Hash(sqX, sqY));

            for (i32 k = 0, kMax = features(generator); k < kMax; ++k) {
                Vec2f fp = Vec2f(sqX + coords(generator), sqY + coords(generator));
                Vec2f v = Vec2f(x, y);

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
