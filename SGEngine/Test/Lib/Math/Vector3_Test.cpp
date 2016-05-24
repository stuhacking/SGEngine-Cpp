//
// Vec3f Unit Tests
//
#include <gtest/gtest.h>
#include <cfloat>

#include "Lib.h"

using sge::FMath;
using sge::Vec3f;

/*==========================
  Vector property Tests
 ==========================*/

TEST (Vec3f_Test, Length) {
    EXPECT_FLOAT_EQ(5.0f, Vec3f(3.0f, 0.0f, 4.0f).Length());
}

TEST (Vec3f_Test, Zero) {
    Vec3f v = Vec3f(10.0f, 10.0f, 10.0f);

    v.Zero();
    EXPECT_FLOAT_EQ(0.0f, v.Length());
}

TEST (Vec3f_Test, Normalize) {
    Vec3f v = Vec3f(10.0f, 10.0f, 10.0f);

    EXPECT_FLOAT_EQ(1.0f, v.Normalize().Length());

    v.NormalizeSelf();
    EXPECT_FLOAT_EQ(1.0f, v.Length());
}

TEST (Vec3f_Test, ClampLength) {
    EXPECT_EQ(Vec3f(3.0f, 4.0f, 0.0f), Vec3f(6.0f, 8.0f, 0.0f).ClampLength(5.0f));
    EXPECT_EQ(Vec3f(3.0f, 0.0f, 4.0f), Vec3f(1.5f, 0.0f, 2.0f).ClampLength(5.0f, 10.0f));
    EXPECT_EQ(Vec3f(0.0f, 3.0f, 4.0f), Vec3f(0.0f, 3.0f, 4.0f).ClampLength(2.0f, 8.0f));

    Vec3f v = Vec3f(6.0f, 8.0f, 0.0f);
    v.ClampLengthSelf(5.0f);

    EXPECT_EQ(Vec3f(3.0f, 4.0f, 0.0f), v);
    
    v = Vec3f(1.5f, 0.0f, 2.0f);
    v.ClampLengthSelf(5.0f, 10.0f);
    
    EXPECT_EQ(Vec3f(3.0f, 0.0f, 4.0f), v);
    
    v = Vec3f(0.0f, 3.0f, 4.0f);
    v.ClampLengthSelf(2.0f, 6.0f);

    EXPECT_EQ(Vec3f(0.0f, 3.0f, 4.0f), v);
}

/*==========================
  Math Operator Tests
 ==========================*/

TEST (Vec3f_Test, Add) {
    EXPECT_EQ(Vec3f(2.0f), Vec3f(2.0f) + Vec3f(0.0f));
    EXPECT_EQ(Vec3f(2.0f), Vec3f(1.0f) + Vec3f(1.0f));
    EXPECT_EQ(Vec3f(2.0f, 2.0f, 2.0f), Vec3f(3.0f, 1.0f, 0.0f) + Vec3f(-1.0f, 1.0f, 2.0f));
}

TEST (Vec3f_Test, Add_Equals) {
    Vec3f v1 = Vec3f(2.0f, 1.0f, 2.0f);

    v1 += Vec3f(1.0f, 1.0f, -1.0f);

    EXPECT_EQ(Vec3f(3.0f, 2.0f, 1.0f), v1);
}

TEST (Vec3f_Test, Sub) {
    EXPECT_EQ(Vec3f(2.0f), Vec3f(2.0f) - Vec3f(0.0f));
    EXPECT_EQ(Vec3f(1.0f), Vec3f(2.0f) - Vec3f(1.0f));
    EXPECT_EQ(Vec3f(2.0f), Vec3f(3.0f, 1.0f, 4.0f) - Vec3f(1.0f, -1.0f, 2.0f));
}

TEST (Vec3f_Test, Sub_Equals) {
    Vec3f v1 = Vec3f(2.0f, 1.0f, -1.0f);

    v1 -= Vec3f(1.0f);

    EXPECT_EQ(Vec3f(1.0f, 0.0f, -2.0f), v1);
}

TEST (Vec3f_Test, Scale) {
    EXPECT_EQ(Vec3f(0.0f), Vec3f(2.0f) * 0.0f);
    EXPECT_EQ(Vec3f(2.0f), Vec3f(2.0f) * 1.0f);
    EXPECT_EQ(Vec3f(4.0f, 3.0f, 2.0f), Vec3f(2.0f, 1.5f, 1.0f) * 2.0f);
    EXPECT_EQ(Vec3f(-6.0f, 4.0f, -2.0f), Vec3f(3.0f, -2.0f, 1.0f) * -2.0f);
}

TEST (Vec3f_Test, Scale_Equals) {
    Vec3f v1 = Vec3f(3.0f, 1.5f, 2.0f);

    v1 *= 2;

    EXPECT_EQ(Vec3f(6.0f, 3.0f, 4.0f), v1);
}

TEST (Vec3f_Test, NonUniformScale) {
    EXPECT_EQ(Vec3f(0.0f), Vec3f(2.0f) * sge::VEC3F_ZERO);
    EXPECT_EQ(Vec3f(2.0f, 4.0f, 6.0f), Vec3f(2.0f) * Vec3f(1.0f, 2.0f, 3.0f));
    EXPECT_EQ(Vec3f(4.0f, 2.0f, 0.0f), Vec3f(2.0f, 4.0f, 5.0f) * Vec3f(2.0f, 0.5f, 0.0f));
}

TEST (Vec3f_Test, NonUniformScale_Equals) {
    Vec3f v1 = Vec3f(3.0f, 1.5f, 4.0f);

    v1 *= Vec3f(1.5f, 2.0f, 0.5f);

    EXPECT_EQ(Vec3f(4.5f, 3.0f, 2.0f), v1);
}

TEST (Vec3f_Test, Div) {
    EXPECT_EQ(Vec3f(2.0f), Vec3f(2.0f) / 1.0f);
    EXPECT_EQ(Vec3f(1.0f, 0.75f, 0.25f), Vec3f(2.0f, 1.5f, 0.5f) / 2.0f);
    EXPECT_EQ(Vec3f(FMath::INFTY), Vec3f(3.0f, 2.0f, 1.0f) / 0.0f);
    EXPECT_EQ(Vec3f(FMath::INFTY, -FMath::INFTY, FMath::INFTY), Vec3f(3.0f, -2.0f, 1.0f) / 0.0f);
}

TEST (Vec3f_Test, Div_Equals) {
    Vec3f v1 = Vec3f(3.0f, 1.5f, 0.6f);

    v1 /= 2;

    EXPECT_EQ(Vec3f(1.5f, 0.75f, 0.3f), v1);
}

/*==========================
  Convenience Tests
 ==========================*/

TEST (Vec3f_Test, Operator_Index) {
    Vec3f v = Vec3f(10.0f, 5.0f, 2.5f);

    EXPECT_FLOAT_EQ(10.0f, v[0]);
    EXPECT_FLOAT_EQ(5.0f, v[1]);
    EXPECT_FLOAT_EQ(2.5f, v[2]);
}

TEST (Vec3f_Test, Operator_Index_Set) {
    Vec3f v = Vec3f(10.0f, 5.0f, 2.5f);

    v[0] = 2.0f;
    v[1] = 3.0f;
    v[2] = 4.0f;

    EXPECT_FLOAT_EQ(2.0f, v[0]);
    EXPECT_FLOAT_EQ(3.0f, v[1]);
    EXPECT_FLOAT_EQ(4.0f, v[2]);
}
