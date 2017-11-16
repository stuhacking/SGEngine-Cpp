//
// Circle bounds Tests
//
#include <gtest/gtest.h>
#include "lib.h"

using sge::Circle;

TEST (Circle_Test, Constructors) {
    EXPECT_EQ(Circle(), Circle(Vec2f(0.0f, 0.0f), -math::Infinity));
    EXPECT_EQ(Circle(Vec2f(1.0f, 2.0f)), Circle(Vec2f(1.0f, 2.0f), -math::Infinity));
}

TEST (Circle_Test, Center) {
    EXPECT_EQ(Vec2f(2.0f, 4.0f), Circle(Vec2f(2.0f, 4.0f), 5.0f).center);
}

TEST (Circle_Test, Area) {
    EXPECT_FLOAT_EQ(28.274334f, Circle(Vec2f(2.0f, 3.0f), 3.0f).area());
}
