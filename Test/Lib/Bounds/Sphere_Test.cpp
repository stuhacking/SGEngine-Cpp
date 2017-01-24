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
