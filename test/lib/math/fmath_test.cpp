//
// math Unit Tests
//
#include <gtest/gtest.h>
#include <cfloat>

#include "lib.h"

TEST (math_Test, Min) {
    EXPECT_EQ(1.0f, math::min(1.0f, 2.0f));
    EXPECT_EQ(-2.0f, math::min(1.0f, -2.0f));
}

TEST (math_Test, Max) {
    EXPECT_EQ(2.0f, math::max(1.0f, 2.0f));
    EXPECT_EQ(1.0f, math::max(1.0f, -2.0f));
}

TEST (math_Test, ClampFloat) {
    EXPECT_EQ(4.0f, math::clamp(4.0f, 0.0f, 10.0f));
    EXPECT_EQ(4.0f, math::clamp(2.0f, 4.0f, 10.0f));
    EXPECT_EQ(8.0f, math::clamp(12.0f, 0.0f, 8.0f));
}

TEST (math_Test, ClampInt) {
    EXPECT_EQ(4, math::clamp(4, 0, 10));
    EXPECT_EQ(4, math::clamp(2, 4, 10));
    EXPECT_EQ(8, math::clamp(12, 0, 8));
}

TEST (math_Test, Nearest2Pow) {
    EXPECT_EQ(2, math::nearest2Pow(1));
    EXPECT_EQ(8, math::nearest2Pow(6));
    EXPECT_EQ(512, math::nearest2Pow(260));
    EXPECT_EQ(16, math::nearest2Pow(16));
}

TEST (math_Test, ToRatio) {
    EXPECT_EQ(0.5f, math::toRatio(5.0f, 0.0f, 10.0f));
    EXPECT_EQ(2.0f, math::toRatio(12.0f, 10.0f, 11.0f));
}

TEST (math_Test, ClampedRatio) {
    EXPECT_EQ(0.5f, math::clampRatio(5.0f, 0.0f, 10.0f));
    EXPECT_EQ(1.0f, math::clampRatio(12.0f, 10.0f, 11.0f));
}

TEST (math_Test, Lerp) {
    EXPECT_EQ(2.0f, math::lerp(0.5f, 1.0f, 3.0f));
    EXPECT_EQ(1.0f, math::lerp(0.0f, 1.0f, 3.0f));
    EXPECT_EQ(3.0f, math::lerp(1.0f, 1.0f, 3.0f));
    EXPECT_EQ(3.0f, math::lerp(2.0f, 1.0f, 3.0f));
}
