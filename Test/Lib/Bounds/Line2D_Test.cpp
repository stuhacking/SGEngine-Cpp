//
// Line2D Tests
//
#include <gtest/gtest.h>
#include "lib.h"

using sge::Line2D;

TEST (Line2D_Test, Constructors) {
    EXPECT_EQ(Line2D(1.0f, 2.0f, 3.0f, 4.0f),
              Line2D(Vec2f(1.0f, 2.0f), Vec2f(3.0f, 4.0f)));
}

TEST (Line2D_Test, Length) {
    EXPECT_EQ(Vec2f(2.0f, 2.0f).mag(), Line2D(0.0f, 0.0f, 2.0f, 2.0f).length());
    EXPECT_EQ(Vec2f(-5.0f, 5.0f).mag(), Line2D(2.0f, 3.0f, -3.0f, 8.0f).length());
}

TEST (Line2D_Test, Extrapolate) {
    EXPECT_EQ(Vec2f(2.0f, 2.0f), Line2D(2.0f, 2.0f, 4.0f, 4.0f).extrapolate(0.0f));
    EXPECT_EQ(Vec2f(3.0f, 3.0f), Line2D(2.0f, 2.0f, 4.0f, 4.0f).extrapolate(0.5f));
    EXPECT_EQ(Vec2f(6.0f, 6.0f), Line2D(2.0f, 2.0f, 4.0f, 4.0f).extrapolate(2.0f));
}

TEST (Line2D_Test, Intersection) {
    Line2D l1 = Line2D(0.0f, 0.0f, 10.0f, 10.0f);
    Line2D l2 = Line2D(0.0f, 1.0f, 10.0f, 11.0f);
    Line2D l3 = Line2D(2.0f, 0.0f, 2.0f, 10.0f);

    EXPECT_FLOAT_EQ(math::Infinity, l1.intersection(l2).mag());
    EXPECT_EQ(Vec2f(2.0f, 2.0f), l1.intersection(l3));
}
