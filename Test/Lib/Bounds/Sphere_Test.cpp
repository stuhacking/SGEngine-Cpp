//
// Sphere bounds Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::FMath;
using sge::Vec3f;
using sge::Sphere;

TEST (Sphere_Test, Constructors) {
    EXPECT_EQ(Sphere(), Sphere(Vec3f(0.0f, 0.0f, 0.0f), -FMath::INFTY));
    EXPECT_EQ(Sphere(Vec3f(1.0f, 2.0f, 3.0f)), Sphere(Vec3f(1.0f, 2.0f, 3.0f), -FMath::INFTY));
}

TEST (Sphere_Test, Center) {
    EXPECT_EQ(Vec3f(2.0f, 4.0f, 6.0f), Sphere(Vec3f(2.0f, 4.0f, 6.0f), 5.0f).center);
}

TEST (Sphere_Test, Area) {
    EXPECT_FLOAT_EQ(113.09734f, Sphere(Vec3f(2.0f, 3.0f, 4.0f), 3.0f).Volume());
}

// Basic Spheres
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
static const Sphere A = Sphere(Vec3f(3.0f, 3.0f, 3.0f), 1.0f);
static const Sphere B = Sphere(Vec3f(5.0f, 3.0f, 3.0f), 2.0f);
static const Sphere C = Sphere(Vec3f(7.0f, 7.0f, 7.0f), 0.5f);
static const Sphere D = Sphere(Vec3f(2.0f, 3.0f, 4.0f), 4.0f);
static const Sphere E = Sphere();

TEST (Sphere_Test, Intersects) {
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

TEST (Sphere_Test, ContainsPoint) {
    EXPECT_TRUE(A.Contains(Vec3f(2.0f, 3.0f, 3.0f)));
    EXPECT_TRUE(C.Contains(Vec3f(6.8f, 7.0f, 7.2f)));

    EXPECT_FALSE(B.Contains(Vec3f(2.0f, 6.0f, 6.0f)));
}

TEST (Sphere_Test, Contains) {
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
