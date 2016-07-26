//
// FMath Unit Tests
//
#include <gtest/gtest.h>
#include <cfloat>

#include "Lib.h"

using sge::FMath;

TEST (FMath_Test, Min) {
    EXPECT_EQ(1.0f, FMath::Min(1.0f, 2.0f));
    EXPECT_EQ(-2.0f, FMath::Min(1.0f, -2.0f));
}

TEST (FMath_Test, Max) {
    EXPECT_EQ(2.0f, FMath::Max(1.0f, 2.0f));
    EXPECT_EQ(1.0f, FMath::Max(1.0f, -2.0f));
}

TEST (FMath_Test, ClampFloat) {
    EXPECT_EQ(4.0f, FMath::ClampFloat(4.0f, 0.0f, 10.0f));
    EXPECT_EQ(4.0f, FMath::ClampFloat(2.0f, 4.0f, 10.0f));
    EXPECT_EQ(8.0f, FMath::ClampFloat(12.0f, 0.0f, 8.0f));
}

TEST (FMath_Test, ClampInt) {
    EXPECT_EQ(4, FMath::ClampInt(4, 0, 10));
    EXPECT_EQ(4, FMath::ClampInt(2, 4, 10));
    EXPECT_EQ(8, FMath::ClampInt(12, 0, 8));
}

TEST (FMath_Test, Nearest2Pow) {
    EXPECT_EQ(2, FMath::Nearest2Pow(1));
    EXPECT_EQ(8, FMath::Nearest2Pow(6));
    EXPECT_EQ(512, FMath::Nearest2Pow(260));
    EXPECT_EQ(16, FMath::Nearest2Pow(16));
}

TEST (FMath_Test, ToRatio) {
    EXPECT_EQ(0.5f, FMath::ToRatio(5.0f, 0.0f, 10.0f));
    EXPECT_EQ(2.0f, FMath::ToRatio(12.0f, 10.0f, 11.0f));
}

TEST (FMath_Test, ClampedRatio) {
    EXPECT_EQ(0.5f, FMath::ClampedRatio(5.0f, 0.0f, 10.0f));
    EXPECT_EQ(1.0f, FMath::ClampedRatio(12.0f, 10.0f, 11.0f));
}

TEST (FMath_Test, Lerp) {
    EXPECT_EQ(2.0f, FMath::Lerp(0.5f, 1.0f, 3.0f));
    EXPECT_EQ(1.0f, FMath::Lerp(0.0f, 1.0f, 3.0f));
    EXPECT_EQ(3.0f, FMath::Lerp(1.0f, 1.0f, 3.0f));
    EXPECT_EQ(3.0f, FMath::Lerp(2.0f, 1.0f, 3.0f));
}
