//
// Circle bounds Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::FMath;
using sge::Vec2f;
using sge::Circle;

TEST (Circle_Test, Constructors) {
    EXPECT_EQ(Circle(), Circle(Vec2f(0.0f, 0.0f), -FMath::INFTY));
    EXPECT_EQ(Circle(Vec2f(1.0f, 2.0f)), Circle(Vec2f(1.0f, 2.0f), -FMath::INFTY));    
}

// Basic Circles
//     8       .......
//                    ....              .....
//     7              D   ...          .  C  .
//                           ..         .....
//     6                     .......
//                        ...    .  ...
//     5          ........        ..   ..
//              ..     . ..         .    .
//     4       .       .   .        .    .
//            .       .     .        .    .
//     3      .   A   .     .     B   .   .
//            .       .     .         .   .
//     2       .       .   .          .  .
//              ..     . ..           .  .
//     1          ........            ...
//                        ...       ...
//     0    1    2    3    4    5    6    7    8
//
static const Circle A = Circle(Vec2f(3.0f, 3.0f), 1.0f);
static const Circle B = Circle(Vec2f(5.0f, 3.0f), 2.0f);
static const Circle C = Circle(Vec2f(7.0f, 7.0f), 0.5f);
static const Circle D = Circle(Vec2f(2.0f, 3.0f), 4.0f);
static const Circle E = Circle();

TEST (Circle_Test, Intersects) {
    EXPECT_TRUE(A.Intersects(B));
    EXPECT_TRUE(B.Intersects(A));
    EXPECT_TRUE(B.Intersects(D));
    EXPECT_TRUE(D.Intersects(B));
    EXPECT_TRUE(B.Intersects(A));
    EXPECT_TRUE(A.Intersects(D));

    EXPECT_FALSE(A.Intersects(C));
    EXPECT_FALSE(C.Intersects(D));

    EXPECT_FALSE(E.Intersects(A));
    EXPECT_FALSE(E.Intersects(B));
    EXPECT_FALSE(E.Intersects(C));
    EXPECT_FALSE(E.Intersects(D));
}

TEST (Circle_Test, ContainsPoint) {
    EXPECT_TRUE(A.Contains(Vec2f(2.0f, 3.0f)));
    EXPECT_TRUE(C.Contains(Vec2f(6.8f, 7.0f)));

    EXPECT_FALSE(B.Contains(Vec2f(2.0f, 6.0f)));
}

TEST (Circle_Test, Contains) {
    EXPECT_TRUE(D.Contains(A));
    EXPECT_FALSE(D.Contains(C));
    EXPECT_FALSE(D.Contains(B));
    EXPECT_FALSE(A.Contains(D));

    EXPECT_TRUE(A.Contains(E));
    EXPECT_TRUE(B.Contains(E));
    EXPECT_TRUE(C.Contains(E));
    
    EXPECT_FALSE(E.Contains(A));
    EXPECT_FALSE(E.Contains(B));
    EXPECT_FALSE(E.Contains(C));
    EXPECT_FALSE(E.Contains(D));
}
