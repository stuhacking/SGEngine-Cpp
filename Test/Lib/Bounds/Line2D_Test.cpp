//
// Line2D Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::FMath;
using sge::Vec2f;
using sge::Line2D;

TEST (Line2D_Test, Constructors) {
    EXPECT_EQ(Line2D(1.0f, 2.0f, 3.0f, 4.0f),
              Line2D(Vec2f(1.0f, 2.0f), Vec2f(3.0f, 4.0f)));
}

TEST (Line2D_Test, Length) {
    EXPECT_EQ(Vec2f(2.0f, 2.0f).Length(), Line2D(0.0f, 0.0f, 2.0f, 2.0f).Length());
    EXPECT_EQ(Vec2f(-5.0f, 5.0f).Length(), Line2D(2.0f, 3.0f, -3.0f, 8.0f).Length());
}

TEST (Line2D_Test, Extrapolate) {
    EXPECT_EQ(Vec2f(2.0f, 2.0f), Line2D(2.0f, 2.0f, 4.0f, 4.0f).Extrapolate(0.0f));
    EXPECT_EQ(Vec2f(3.0f, 3.0f), Line2D(2.0f, 2.0f, 4.0f, 4.0f).Extrapolate(0.5f));
    EXPECT_EQ(Vec2f(6.0f, 6.0f), Line2D(2.0f, 2.0f, 4.0f, 4.0f).Extrapolate(2.0f));
}

TEST (Line2D_Test, Intersects) {
    Line2D l1 = Line2D(0.0f, 0.0f, 10.0f, 10.0f);
    Line2D l2 = Line2D(0.0f, 1.0f, 10.0f, 11.0f);
    Line2D l3 = Line2D(2.0f, 0.0f, 2.0f, 10.0f);

    EXPECT_FALSE(l1.Intersects(l2));
    EXPECT_TRUE(l1.Intersects(l3));
    EXPECT_TRUE(l2.Intersects(l3));
}

TEST (Line2D_Test, Intersection) {
    Line2D l1 = Line2D(0.0f, 0.0f, 10.0f, 10.0f);
    Line2D l2 = Line2D(0.0f, 1.0f, 10.0f, 11.0f);
    Line2D l3 = Line2D(2.0f, 0.0f, 2.0f, 10.0f);

    EXPECT_FLOAT_EQ(FMath::INFTY, l1.Intersection(l2).Length());
    EXPECT_EQ(Vec2f(2.0f, 2.0f), l1.Intersection(l3));
}
