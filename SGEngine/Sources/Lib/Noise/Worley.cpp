//
// Worley Implementation.
//
#include "../Lib.h"

#include <random>

namespace sge {

#define MAX_FEATURE_POINTS 8

static std::default_random_engine generator;
static std::uniform_int_distribution<int> features(1, MAX_FEATURE_POINTS);
static std::uniform_real_distribution<float> coords(0.0f, 1.0f);

static float euclidDistance(const Vector2 &a, const Vector2 &b) {
    return (a - b).LengthSqr();
}

float Worley::worley(const float x, const float y) const {
    int sqX, sqY;
    Vector2 fp, v;
    bool first = true;
    float nearest = 0.0f;

    for (int p = -1; p <= 1; p++) {
        for (int q = -1; q <= 1; q++) {
            sqX = static_cast<int>(x) + p;
            sqY = static_cast<int>(y) + q;
            generator.seed(Noise::Hash(sqX + m_seed, sqY + m_seed));

            for (int k = 0, kMax = features(generator); k < kMax; k++) {
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
