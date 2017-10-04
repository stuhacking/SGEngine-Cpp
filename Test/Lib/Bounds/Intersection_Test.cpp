//
// Intersection Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::Line2D;
using sge::Rectangle;
using sge::Circle;
using sge::Ray3D;
using sge::AABB;
using sge::Sphere;

TEST (Intersection_Test, Lines_Should_Intersect) {
    Line2D l1 = Line2D(0.0f, 0.0f, 10.0f, 10.0f);
    Line2D l2 = Line2D(0.0f, 1.0f, 10.0f, 11.0f);
    Line2D l3 = Line2D(2.0f, 0.0f, 2.0f, 10.0f);

    EXPECT_FALSE(sge::Intersects(l1, l2));
    EXPECT_TRUE(sge::Intersects(l1, l3));
    EXPECT_TRUE(sge::Intersects(l2, l3));
}

// Basic Rectangle Tests.
//     8                        +--------------+
//                              |              |
//     7              +----+    |    +----+    |
//                    |    |    |    |    |    |
//     6    +----+    F----+----+    H----+    |
//          |    |         |    |              |
//     5    E----+         |    G--------------+
//                         |    |
//     4         +---------+----+---------+
//               |         |    |         |
//     3    +----+----+    |    |    +----+----+
//          |    |    |    |    |    |    |    |
//     2    |    B----+----+----+----+----+    |
//          |         |    |    |    |         |
//     1    A---------+    C----+    D---------+
//
//     0    1    2    3    4    5    6    7    8
//
static const Rectangle rA = Rectangle(1.0f, 1.0f, 3.0f, 3.0f);
static const Rectangle rB = Rectangle(2.0f, 2.0f, 7.0f, 4.0f);
static const Rectangle rC = Rectangle(4.0f, 1.0f, 5.0f, 6.0f);
static const Rectangle rD = Rectangle(6.0f, 1.0f, 8.0f, 3.0f);
static const Rectangle rE = Rectangle(1.0f, 5.0f, 2.0f, 6.0f);
static const Rectangle rF = Rectangle(3.0f, 6.0f, 4.0f, 7.0f);
static const Rectangle rG = Rectangle(5.0f, 5.0f, 8.0f, 8.0f);
static const Rectangle rH = Rectangle(6.0f, 6.0f, 7.0f, 7.0f);

TEST (Intersection_Test, Rectangles_Should_Intersect) {
    EXPECT_TRUE(sge::Intersects(rA, rA));
    EXPECT_TRUE(sge::Intersects(rA, rB));
    EXPECT_TRUE(sge::Intersects(rB, rA));
    EXPECT_TRUE(sge::Intersects(rB, rC));
    EXPECT_TRUE(sge::Intersects(rC, rB));
    EXPECT_TRUE(sge::Intersects(rB, rD));
    EXPECT_TRUE(sge::Intersects(rF, rC));
    EXPECT_TRUE(sge::Intersects(rC, rF));
    EXPECT_TRUE(sge::Intersects(rC, rG));
    EXPECT_TRUE(sge::Intersects(rG, rH));
    EXPECT_TRUE(sge::Intersects(rH, rG));

    EXPECT_FALSE(sge::Intersects(rE, rA));
    EXPECT_FALSE(sge::Intersects(rA, rE));
}

TEST (Intersection_Test, Rectangles_Should_Contain_Points) {
    EXPECT_TRUE(sge::Contains(rA, Vec2f(2.0f, 2.0f)));
    EXPECT_TRUE(sge::Contains(rC, Vec2f(5.0f, 6.0f)));

    EXPECT_FALSE(sge::Contains(rE, Vec2f(0.0f, 0.0f)));
}

TEST (Intersection_Test, Rectangles_Should_Contain_Rectangles) {
    EXPECT_TRUE(sge::Contains(rG, rH));

    EXPECT_FALSE(sge::Contains(rH, rG));
    EXPECT_FALSE(sge::Contains(rA, rB));
}

// Basic Circle Tests.
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
static const Circle cA = Circle(Vec2f(3.0f, 3.0f), 1.0f);
static const Circle cB = Circle(Vec2f(5.0f, 3.0f), 2.0f);
static const Circle cC = Circle(Vec2f(7.0f, 7.0f), 0.5f);
static const Circle cD = Circle(Vec2f(2.0f, 3.0f), 4.0f);
static const Circle cE = Circle();

TEST (Intersection_Test, Circles_Should_Intersect) {
    EXPECT_TRUE(sge::Intersects(cA, cB));
    EXPECT_TRUE(sge::Intersects(cB, cA));
    EXPECT_TRUE(sge::Intersects(cB, cD));
    EXPECT_TRUE(sge::Intersects(cD, cB));
    EXPECT_TRUE(sge::Intersects(cB, cA));
    EXPECT_TRUE(sge::Intersects(cA, cD));

    EXPECT_FALSE(sge::Intersects(cA, cC));
    EXPECT_FALSE(sge::Intersects(cC, cD));

    EXPECT_FALSE(sge::Intersects(cE, cA));
    EXPECT_FALSE(sge::Intersects(cE, cB));
    EXPECT_FALSE(sge::Intersects(cE, cC));
    EXPECT_FALSE(sge::Intersects(cE, cD));
}

TEST (Intersection_Test, Circles_Should_Contains_Points) {
    EXPECT_TRUE(sge::Contains(cA, Vec2f(2.0f, 3.0f)));
    EXPECT_TRUE(sge::Contains(cC, Vec2f(6.8f, 7.0f)));

    EXPECT_FALSE(sge::Contains(cB, Vec2f(2.0f, 6.0f)));
}

TEST (Intersection_Test, Circles_Should_Contain_Circles) {
    EXPECT_TRUE(sge::Contains(cD, cA));
    EXPECT_FALSE(sge::Contains(cD, cC));
    EXPECT_FALSE(sge::Contains(cD, cB));
    EXPECT_FALSE(sge::Contains(cA, cD));

    EXPECT_TRUE(sge::Contains(cA, cE));
    EXPECT_TRUE(sge::Contains(cB, cE));
    EXPECT_TRUE(sge::Contains(cC, cE));

    EXPECT_FALSE(sge::Contains(cE, cA));
    EXPECT_FALSE(sge::Contains(cE, cB));
    EXPECT_FALSE(sge::Contains(cE, cC));
    EXPECT_FALSE(sge::Contains(cE, cD));
}

// Basic Axis-aligned Box Tests
//     8                        +--------------5
//                              |              |
//     7              +----7    |    +----4    |
//                    |    |    |    |    |    |
//     6    +----4   F5----+----5   H3----+    |
//          |    |         |    |              |
//     5   E3----+         |   G2--------------+
//                         |    |
//     4         +---------+----+---------7
//               |         |    |         |
//     3    +----+----3    |    |    +----+----8
//          |    |    |    |    |    |    |    |
//     2    |   B2----+----+----+----+----+    |
//          |         |    |    |    |         |
//     1   A1---------+   C3----+   D5---------+
//
//     0    1    2    3    4    5    6    7    8
//
static const AABB bA = AABB(1.0f, 1.0f, 1.0f, 3.0f, 3.0f, 3.0f);
static const AABB bB = AABB(2.0f, 2.0f, 2.0f, 7.0f, 4.0f, 7.0f);
static const AABB bC = AABB(4.0f, 1.0f, 3.0f, 5.0f, 6.0f, 5.0f);
static const AABB bD = AABB(6.0f, 1.0f, 5.0f, 8.0f, 3.0f, 8.0f);
static const AABB bE = AABB(1.0f, 5.0f, 3.0f, 2.0f, 6.0f, 4.0f);
static const AABB bF = AABB(3.0f, 6.0f, 5.0f, 4.0f, 7.0f, 7.0f);
static const AABB bG = AABB(5.0f, 5.0f, 2.0f, 8.0f, 8.0f, 5.0f);
static const AABB bH = AABB(6.0f, 6.0f, 3.0f, 7.0f, 7.0f, 4.0f);

TEST (Intersection_Test, AABBs_Should_Intersect) {
    EXPECT_TRUE(sge::Intersects(bA, bA));
    EXPECT_TRUE(sge::Intersects(bA, bB));
    EXPECT_TRUE(sge::Intersects(bB, bA));
    EXPECT_TRUE(sge::Intersects(bB, bC));
    EXPECT_TRUE(sge::Intersects(bC, bB));
    EXPECT_TRUE(sge::Intersects(bB, bD));
    EXPECT_TRUE(sge::Intersects(bF, bC));
    EXPECT_TRUE(sge::Intersects(bC, bF));
    EXPECT_TRUE(sge::Intersects(bC, bG));
    EXPECT_TRUE(sge::Intersects(bG, bH));
    EXPECT_TRUE(sge::Intersects(bH, bG));

    EXPECT_FALSE(sge::Intersects(bE, bA));
    EXPECT_FALSE(sge::Intersects(bA, bE));
}

TEST (Intersection_Test, AABBs_Should_Contain_Points) {
    EXPECT_TRUE(sge::Contains(bA, Vec3f(2.0f, 2.0f, 2.0f)));
    EXPECT_TRUE(sge::Contains(bC, Vec3f(5.0f, 6.0f, 5.0f)));

    EXPECT_FALSE(sge::Contains(bE, Vec3f(0.0f, 0.0f, 0.0f)));
}

TEST (Intersection_Test, AABBs_Should_Contain_AABBs) {
    EXPECT_TRUE(sge::Contains(bG, bH));

    EXPECT_FALSE(sge::Contains(bH, bG));
    EXPECT_FALSE(sge::Contains(bA, bB));
}

// Basic Sphere Tests.
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
static const Sphere sA = Sphere(Vec3f(3.0f, 3.0f, 3.0f), 1.0f);
static const Sphere sB = Sphere(Vec3f(5.0f, 3.0f, 3.0f), 2.0f);
static const Sphere sC = Sphere(Vec3f(7.0f, 7.0f, 7.0f), 0.5f);
static const Sphere sD = Sphere(Vec3f(2.0f, 3.0f, 4.0f), 4.0f);
static const Sphere sE = Sphere();

TEST (Intersection_Test, Spheres_Should_Intersect) {
    EXPECT_TRUE(sge::Intersects(sA, sB));
    EXPECT_TRUE(sge::Intersects(sB, sA));
    EXPECT_TRUE(sge::Intersects(sB, sD));
    EXPECT_TRUE(sge::Intersects(sD, sB));
    EXPECT_TRUE(sge::Intersects(sB, sA));
    EXPECT_TRUE(sge::Intersects(sA, sD));

    EXPECT_FALSE(sge::Intersects(sA, sC));
    EXPECT_FALSE(sge::Intersects(sC, sD));

    EXPECT_FALSE(sge::Intersects(sE, sA));
    EXPECT_FALSE(sge::Intersects(sE, sB));
    EXPECT_FALSE(sge::Intersects(sE, sC));
    EXPECT_FALSE(sge::Intersects(sE, sD));
}

TEST (Intersection_Test, Spheres_Should_Contain_Points) {
    EXPECT_TRUE(sge::Contains(sA, Vec3f(2.0f, 3.0f, 3.0f)));
    EXPECT_TRUE(sge::Contains(sC, Vec3f(6.8f, 7.0f, 7.2f)));

    EXPECT_FALSE(sge::Contains(sB, Vec3f(2.0f, 6.0f, 6.0f)));
}

TEST (Intersection_Test, Spheres_Should_Contain_Spheres) {
    EXPECT_TRUE(sge::Contains(sD, sA));
    EXPECT_FALSE(sge::Contains(sD, sC));
    EXPECT_FALSE(sge::Contains(sD, sB));
    EXPECT_FALSE(sge::Contains(sA, sD));

    EXPECT_TRUE(sge::Contains(sA, sE));
    EXPECT_TRUE(sge::Contains(sB, sE));
    EXPECT_TRUE(sge::Contains(sC, sE));

    EXPECT_FALSE(sge::Contains(sE, sA));
    EXPECT_FALSE(sge::Contains(sE, sB));
    EXPECT_FALSE(sge::Contains(sE, sC));
    EXPECT_FALSE(sge::Contains(sE, sD));
}
