//
// Circle bounds Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::Vector2;
using sge::Circle;

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
static const Circle A = Circle(Vector2(3.0f, 3.0f), 1.0f);
static const Circle B = Circle(Vector2(5.0f, 3.0f), 2.0f);
static const Circle C = Circle(Vector2(7.0f, 7.0f), 0.5f);
static const Circle D = Circle(Vector2(2.0f, 3.0f), 4.0f);

TEST (Circle_Test, Intersects) {
    EXPECT_TRUE(A.Intersects(B));
    EXPECT_TRUE(B.Intersects(A));
    EXPECT_TRUE(B.Intersects(D));
    EXPECT_TRUE(D.Intersects(B));
    EXPECT_TRUE(B.Intersects(A));
    EXPECT_TRUE(A.Intersects(D));

    EXPECT_FALSE(A.Intersects(C));
    EXPECT_FALSE(C.Intersects(D));
}

TEST (Circle_Test, ContainsPoint) {
    EXPECT_TRUE(A.Contains(Vector2(2.0f, 3.0f)));
    EXPECT_TRUE(C.Contains(Vector2(6.8f, 7.0f)));

    EXPECT_FALSE(B.Contains(Vector2(2.0f, 6.0f)));
}

TEST (Circle_Test, Contains) {
    EXPECT_TRUE(D.Contains(A));
    EXPECT_FALSE(D.Contains(C));
    EXPECT_FALSE(D.Contains(B));
    EXPECT_FALSE(A.Contains(D));
}
