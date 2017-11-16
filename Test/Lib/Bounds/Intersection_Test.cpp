//
// intersection Tests
//
#include <gtest/gtest.h>
#include "lib.h"

using sge::Line2D;
using sge::Rect;
using sge::Circle;
using sge::Ray3D;
using sge::Aabb;
using sge::Sphere;

TEST (intersection_Test, Lines_Should_intersect) {
    Line2D l1 = Line2D(0.0f, 0.0f, 10.0f, 10.0f);
    Line2D l2 = Line2D(0.0f, 1.0f, 10.0f, 11.0f);
    Line2D l3 = Line2D(2.0f, 0.0f, 2.0f, 10.0f);

    EXPECT_FALSE(sge::intersects(l1, l2));
    EXPECT_TRUE(sge::intersects(l1, l3));
    EXPECT_TRUE(sge::intersects(l2, l3));
}

// Basic Rect Tests.
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
static const Rect rA = Rect(1.0f, 1.0f, 3.0f, 3.0f);
static const Rect rB = Rect(2.0f, 2.0f, 7.0f, 4.0f);
static const Rect rC = Rect(4.0f, 1.0f, 5.0f, 6.0f);
static const Rect rD = Rect(6.0f, 1.0f, 8.0f, 3.0f);
static const Rect rE = Rect(1.0f, 5.0f, 2.0f, 6.0f);
static const Rect rF = Rect(3.0f, 6.0f, 4.0f, 7.0f);
static const Rect rG = Rect(5.0f, 5.0f, 8.0f, 8.0f);
static const Rect rH = Rect(6.0f, 6.0f, 7.0f, 7.0f);

TEST (intersection_Test, Rects_Should_intersect) {
    EXPECT_TRUE(sge::intersects(rA, rA));
    EXPECT_TRUE(sge::intersects(rA, rB));
    EXPECT_TRUE(sge::intersects(rB, rA));
    EXPECT_TRUE(sge::intersects(rB, rC));
    EXPECT_TRUE(sge::intersects(rC, rB));
    EXPECT_TRUE(sge::intersects(rB, rD));
    EXPECT_TRUE(sge::intersects(rF, rC));
    EXPECT_TRUE(sge::intersects(rC, rF));
    EXPECT_TRUE(sge::intersects(rC, rG));
    EXPECT_TRUE(sge::intersects(rG, rH));
    EXPECT_TRUE(sge::intersects(rH, rG));

    EXPECT_FALSE(sge::intersects(rE, rA));
    EXPECT_FALSE(sge::intersects(rA, rE));
}

TEST (intersection_Test, Rects_Should_Contain_Points) {
    EXPECT_TRUE(sge::contains(rA, Vec2f(2.0f, 2.0f)));
    EXPECT_TRUE(sge::contains(rC, Vec2f(5.0f, 6.0f)));

    EXPECT_FALSE(sge::contains(rE, Vec2f(0.0f, 0.0f)));
}

TEST (intersection_Test, Rects_Should_Contain_Rects) {
    EXPECT_TRUE(sge::contains(rG, rH));

    EXPECT_FALSE(sge::contains(rH, rG));
    EXPECT_FALSE(sge::contains(rA, rB));
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

TEST (intersection_Test, Circles_Should_intersect) {
    EXPECT_TRUE(sge::intersects(cA, cB));
    EXPECT_TRUE(sge::intersects(cB, cA));
    EXPECT_TRUE(sge::intersects(cB, cD));
    EXPECT_TRUE(sge::intersects(cD, cB));
    EXPECT_TRUE(sge::intersects(cB, cA));
    EXPECT_TRUE(sge::intersects(cA, cD));

    EXPECT_FALSE(sge::intersects(cA, cC));
    EXPECT_FALSE(sge::intersects(cC, cD));

    EXPECT_FALSE(sge::intersects(cE, cA));
    EXPECT_FALSE(sge::intersects(cE, cB));
    EXPECT_FALSE(sge::intersects(cE, cC));
    EXPECT_FALSE(sge::intersects(cE, cD));
}

TEST (intersection_Test, Circles_Should_contains_Points) {
    EXPECT_TRUE(sge::contains(cA, Vec2f(2.0f, 3.0f)));
    EXPECT_TRUE(sge::contains(cC, Vec2f(6.8f, 7.0f)));

    EXPECT_FALSE(sge::contains(cB, Vec2f(2.0f, 6.0f)));
}

TEST (intersection_Test, Circles_Should_Contain_Circles) {
    EXPECT_TRUE(sge::contains(cD, cA));
    EXPECT_FALSE(sge::contains(cD, cC));
    EXPECT_FALSE(sge::contains(cD, cB));
    EXPECT_FALSE(sge::contains(cA, cD));

    EXPECT_TRUE(sge::contains(cA, cE));
    EXPECT_TRUE(sge::contains(cB, cE));
    EXPECT_TRUE(sge::contains(cC, cE));

    EXPECT_FALSE(sge::contains(cE, cA));
    EXPECT_FALSE(sge::contains(cE, cB));
    EXPECT_FALSE(sge::contains(cE, cC));
    EXPECT_FALSE(sge::contains(cE, cD));
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
static const Aabb bA = Aabb(1.0f, 1.0f, 1.0f, 3.0f, 3.0f, 3.0f);
static const Aabb bB = Aabb(2.0f, 2.0f, 2.0f, 7.0f, 4.0f, 7.0f);
static const Aabb bC = Aabb(4.0f, 1.0f, 3.0f, 5.0f, 6.0f, 5.0f);
static const Aabb bD = Aabb(6.0f, 1.0f, 5.0f, 8.0f, 3.0f, 8.0f);
static const Aabb bE = Aabb(1.0f, 5.0f, 3.0f, 2.0f, 6.0f, 4.0f);
static const Aabb bF = Aabb(3.0f, 6.0f, 5.0f, 4.0f, 7.0f, 7.0f);
static const Aabb bG = Aabb(5.0f, 5.0f, 2.0f, 8.0f, 8.0f, 5.0f);
static const Aabb bH = Aabb(6.0f, 6.0f, 3.0f, 7.0f, 7.0f, 4.0f);

TEST (intersection_Test, Aabbs_Should_intersect) {
    EXPECT_TRUE(sge::intersects(bA, bA));
    EXPECT_TRUE(sge::intersects(bA, bB));
    EXPECT_TRUE(sge::intersects(bB, bA));
    EXPECT_TRUE(sge::intersects(bB, bC));
    EXPECT_TRUE(sge::intersects(bC, bB));
    EXPECT_TRUE(sge::intersects(bB, bD));
    EXPECT_TRUE(sge::intersects(bF, bC));
    EXPECT_TRUE(sge::intersects(bC, bF));
    EXPECT_TRUE(sge::intersects(bC, bG));
    EXPECT_TRUE(sge::intersects(bG, bH));
    EXPECT_TRUE(sge::intersects(bH, bG));

    EXPECT_FALSE(sge::intersects(bE, bA));
    EXPECT_FALSE(sge::intersects(bA, bE));
}

TEST (intersection_Test, Aabbs_Should_Contain_Points) {
    EXPECT_TRUE(sge::contains(bA, Vec3f(2.0f, 2.0f, 2.0f)));
    EXPECT_TRUE(sge::contains(bC, Vec3f(5.0f, 6.0f, 5.0f)));

    EXPECT_FALSE(sge::contains(bE, Vec3f(0.0f, 0.0f, 0.0f)));
}

TEST (intersection_Test, Aabbs_Should_Contain_Aabbs) {
    EXPECT_TRUE(sge::contains(bG, bH));

    EXPECT_FALSE(sge::contains(bH, bG));
    EXPECT_FALSE(sge::contains(bA, bB));
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

TEST (intersection_Test, Spheres_Should_intersect) {
    EXPECT_TRUE(sge::intersects(sA, sB));
    EXPECT_TRUE(sge::intersects(sB, sA));
    EXPECT_TRUE(sge::intersects(sB, sD));
    EXPECT_TRUE(sge::intersects(sD, sB));
    EXPECT_TRUE(sge::intersects(sB, sA));
    EXPECT_TRUE(sge::intersects(sA, sD));

    EXPECT_FALSE(sge::intersects(sA, sC));
    EXPECT_FALSE(sge::intersects(sC, sD));

    EXPECT_FALSE(sge::intersects(sE, sA));
    EXPECT_FALSE(sge::intersects(sE, sB));
    EXPECT_FALSE(sge::intersects(sE, sC));
    EXPECT_FALSE(sge::intersects(sE, sD));
}

TEST (intersection_Test, Spheres_Should_Contain_Points) {
    EXPECT_TRUE(sge::contains(sA, Vec3f(2.0f, 3.0f, 3.0f)));
    EXPECT_TRUE(sge::contains(sC, Vec3f(6.8f, 7.0f, 7.2f)));

    EXPECT_FALSE(sge::contains(sB, Vec3f(2.0f, 6.0f, 6.0f)));
}

TEST (intersection_Test, Spheres_Should_Contain_Spheres) {
    EXPECT_TRUE(sge::contains(sD, sA));
    EXPECT_FALSE(sge::contains(sD, sC));
    EXPECT_FALSE(sge::contains(sD, sB));
    EXPECT_FALSE(sge::contains(sA, sD));

    EXPECT_TRUE(sge::contains(sA, sE));
    EXPECT_TRUE(sge::contains(sB, sE));
    EXPECT_TRUE(sge::contains(sC, sE));

    EXPECT_FALSE(sge::contains(sE, sA));
    EXPECT_FALSE(sge::contains(sE, sB));
    EXPECT_FALSE(sge::contains(sE, sC));
    EXPECT_FALSE(sge::contains(sE, sD));
}
