//
// Worley Implementation.
//
#include "../Lib.h"

#include <random>

namespace sge {

#define MAX_FEATURE_POINTS 8

static std::default_random_engine generator;
static std::uniform_int_distribution<s8> features(1, MAX_FEATURE_POINTS);
static std::uniform_real_distribution<float> coords(0.0f, 1.0f);

static float euclidDistance(const Vec2f &a, const Vec2f &b) {
    return (a - b).LengthSqr();
}

float Worley::worley(const float x, const float y) const {
    s32 sqX, sqY;
    Vec2f fp, v;
    bool first = true;
    float nearest = 0.0f;

    for (s8 p = -1; p <= 1; ++p) {
        for (s8 q = -1; q <= 1; ++q) {
            sqX = static_cast<s32>(x) + p;
            sqY = static_cast<s32>(y) + q;
            generator.seed(Noise::Hash(sqX + m_seed, sqY + m_seed));

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

    return FMath::ClampFloat(amplitude * nearest, 0.0f, 1.0f);
}

} /* namespace sge */
