//
// Vec4f Unit Tests
//
#include <gtest/gtest.h>
#include <cfloat>

#include "Lib.h"

/*==========================
  Vector property Tests
 ==========================*/

TEST (Vec4f_Test, Length) {
    EXPECT_FLOAT_EQ(5.0f, Vec4f(3.0f, 0.0f, 4.0f, 0.0f).Length());
}

TEST (Vec4f_Test, Zero) {
    Vec4f v = Vec4f(10.0f);

    v.Zero();
    EXPECT_FLOAT_EQ(0.0f, v.Length());
}

TEST (Vec4f_Test, Normalize) {
    Vec4f v = Vec4f(10.0f);

    EXPECT_FLOAT_EQ(1.0f, v.Normalize().Length());

    v.NormalizeSelf();
    EXPECT_FLOAT_EQ(1.0f, v.Length());
}

TEST (Vec4f_Test, ClampLength) {
    EXPECT_EQ(Vec4f(3.0f, 4.0f, 0.0f, 0.0f), Vec4f(6.0f, 8.0f, 0.0f, 0.0f).ClampLength(5.0f));
    EXPECT_EQ(Vec4f(3.0f, 0.0f, 0.0f, 4.0f), Vec4f(1.5f, 0.0f, 0.0f, 2.0f).ClampLength(5.0f, 10.0f));
    EXPECT_EQ(Vec4f(0.0f, 0.0f, 3.0f, 4.0f), Vec4f(0.0f, 0.0f, 3.0f, 4.0f).ClampLength(2.0f, 8.0f));

    Vec4f v = Vec4f(6.0f, 0.0f, 8.0f, 0.0f);
    v.ClampLengthSelf(5.0f);

    EXPECT_EQ(Vec4f(3.0f, 0.0f, 4.0f, 0.0f), v);

    v = Vec4f(1.5f, 0.0f, 2.0f, 0.0f);
    v.ClampLengthSelf(5.0f, 10.0f);

    EXPECT_EQ(Vec4f(3.0f, 0.0f, 4.0f, 0.0f), v);

    v = Vec4f(0.0f, 0.0f, 3.0f, 4.0f);
    v.ClampLengthSelf(2.0f, 6.0f);

    EXPECT_EQ(Vec4f(0.0f, 0.0f, 3.0f, 4.0f), v);
}

TEST (Vec4f_Test, Clamp) {
    EXPECT_EQ(Vec4f(1.0f, 2.0f, 3.0f, 4.0f), Vec4f(2.0f, 2.0f, 2.0f, 2.0f).Clamp(Vec4f(0.0f, 0.0f, 3.0f, 4.0f), Vec4f(1.0f, 10.0f, 4.0f, 6.0f)));
    EXPECT_EQ(Vec4f(2.0f, 2.0f, 2.0f, 2.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f).Clamp(Vec4f(2.0f, 2.0f, 2.0f, 2.0f), Vec4f(4.0f, 5.0f, 6.0f, 7.0f)));
    EXPECT_EQ(Vec4f(4.0f, 4.0f, 4.0f, 4.0f), Vec4f(4.0f, 4.0f, 4.0f, 4.0f).Clamp(Vec4f(1.0f, 2.0f, 3.0f, 4.0f), Vec4f(6.0f, 7.0f, 5.0f, 5.0f)));
}

TEST (Vec4f_Test, ClampSelf) {
    Vec4f v = Vec4f(2.0f, 2.0f, 2.0f, 2.0f);
    v.ClampSelf(Vec4f(0.0f, 0.0f, 3.0f, 4.0f), Vec4f(1.0f, 10.0f, 4.0f, 6.0f));

    EXPECT_EQ(Vec4f(1.0f, 2.0f, 3.0f, 4.0f), v);

    v = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
    v.ClampSelf(Vec4f(2.0f, 2.0f, 2.0f, 2.0f), Vec4f(4.0f, 5.0f, 6.0f, 7.0f));

    EXPECT_EQ(Vec4f(2.0f, 2.0f, 2.0f, 2.0f), v);

    v = Vec4f(4.0f, 4.0f, 4.0f, 4.0f);
    v.ClampSelf(Vec4f(1.0f, 2.0f, 3.0f, 4.0f), Vec4f(6.0f, 7.0f, 5.0f, 5.0f));

    EXPECT_EQ(Vec4f(4.0f, 4.0f, 4.0f, 4.0f), v);
}
/*==========================
  Math Operator Tests
 ==========================*/

TEST (Vec4f_Test, Add) {
    EXPECT_EQ(Vec4f(2.0f), Vec4f(2.0f) + Vec4f(0.0f));
    EXPECT_EQ(Vec4f(2.0f), Vec4f(1.0f) + Vec4f(1.0f));
    EXPECT_EQ(Vec4f(2.0f), Vec4f(3.0f, 1.0f, 0.0f, -2.0f) + Vec4f(-1.0f, 1.0f, 2.0f, 4.0f));
}

TEST (Vec4f_Test, Add_Equals) {
    Vec4f v1 = Vec4f(2.0f, 1.0f, 2.0f, 3.0f);

    v1 += Vec4f(1.0f, 1.0f, -1.0f, 0.0f);

    EXPECT_EQ(Vec4f(3.0f, 2.0f, 1.0f, 3.0f), v1);
}

TEST (Vec4f_Test, Sub) {
    EXPECT_EQ(Vec4f(2.0f), Vec4f(2.0f) - Vec4f(0.0f));
    EXPECT_EQ(Vec4f(1.0f), Vec4f(2.0f) - Vec4f(1.0f));
    EXPECT_EQ(Vec4f(2.0f), Vec4f(3.0f, 1.0f, 4.0f, -1.0f) - Vec4f(1.0f, -1.0f, 2.0f, -3.0f));
}

TEST (Vec4f_Test, Sub_Equals) {
    Vec4f v1 = Vec4f(2.0f, 1.0f, -1.0f, -2.0f);

    v1 -= Vec4f(1.0f);

    EXPECT_EQ(Vec4f(1.0f, 0.0f, -2.0f, -3.0f), v1);
}

TEST (Vec4f_Test, Scale) {
    EXPECT_EQ(Vec4f(0.0f), Vec4f(2.0f) * 0.0f);
    EXPECT_EQ(Vec4f(2.0f), Vec4f(2.0f) * 1.0f);
    EXPECT_EQ(Vec4f(4.0f, 3.0f, 2.0f, 1.0f), Vec4f(2.0f, 1.5f, 1.0f, 0.5f) * 2.0f);
    EXPECT_EQ(Vec4f(-6.0f, 4.0f, -2.0f, 1.0f), Vec4f(3.0f, -2.0f, 1.0f, -0.5f) * -2.0f);
}

TEST (Vec4f_Test, Scale_Equals) {
    Vec4f v1 = Vec4f(3.0f, 1.5f, 2.0f, -3.0f);

    v1 *= 2.0f;

    EXPECT_EQ(Vec4f(6.0f, 3.0f, 4.0f, -6.0f), v1);
}

TEST (Vec4f_Test, NonUniformScale) {
    EXPECT_EQ(Vec4f(0.0f), Vec4f(2.0f) * Vec4f::ZERO);
    EXPECT_EQ(Vec4f(2.0f, 4.0f, 6.0f, 8.0f), Vec4f(2.0f) * Vec4f(1.0f, 2.0f, 3.0f, 4.0f));
    EXPECT_EQ(Vec4f(4.0f, 2.0f, 0.0f, -2.0f), Vec4f(2.0f, 4.0f, 5.0f, 4.0f) * Vec4f(2.0f, 0.5f, 0.0f, -0.5f));
}

TEST (Vec4f_Test, NonUniformScale_Equals) {
    Vec4f v1 = Vec4f(3.0f, 1.5f, 4.0f, 3.0f);

    v1 *= Vec4f(1.5f, 2.0f, 0.5f, -2.0f);

    EXPECT_EQ(Vec4f(4.5f, 3.0f, 2.0f, -6.0f), v1);
}

TEST (Vec4f_Test, Div) {
    EXPECT_EQ(Vec4f(2.0f), Vec4f(2.0f) / 1.0f);
    EXPECT_EQ(Vec4f(1.0f, 0.75f, 0.25f, 0.125f), Vec4f(2.0f, 1.5f, 0.5f, 0.25f) / 2.0f);
    EXPECT_EQ(Vec4f(FMath::INFTY), Vec4f(3.0f, 2.0f, 1.0f, 0.5f) / 0.0f);
    EXPECT_EQ(Vec4f(FMath::INFTY, -FMath::INFTY, FMath::INFTY, -FMath::INFTY), Vec4f(3.0f, -2.0f, 1.0f, -4.0f) / 0.0f);
}

TEST (Vec4f_Test, Div_Equals) {
    Vec4f v1 = Vec4f(3.0f, 1.5f, 0.6f, 2.0f);

    v1 /= 2.0f;

    EXPECT_EQ(Vec4f(1.5f, 0.75f, 0.3f, 1.0f), v1);
}

TEST (Vec4f_Test, Dot) {
    EXPECT_EQ(70.0f, Vec4f(1.0f, 2.0f, 3.0f, 4.0f).Dot(Vec4f(5.0f, 6.0f, 7.0f, 8.0f)));
}

/*==========================
  Convenience Tests
 ==========================*/

TEST (Vec4f_Test, Operator_Index) {
    Vec4f v = Vec4f(10.0f, 5.0f, 2.5f, 1.0f);

    EXPECT_FLOAT_EQ(10.0f, v[0]);
    EXPECT_FLOAT_EQ(5.0f, v[1]);
    EXPECT_FLOAT_EQ(2.5f, v[2]);
    EXPECT_FLOAT_EQ(1.0f, v[3]);
}

TEST (Vec4f_Test, Operator_Index_Set) {
    Vec4f v = Vec4f(10.0f, 5.0f, 2.5f, 1.0f);

    v[0] = 2.0f;
    v[1] = 3.0f;
    v[2] = 4.0f;
    v[3] = 5.0f;

    EXPECT_FLOAT_EQ(2.0f, v[0]);
    EXPECT_FLOAT_EQ(3.0f, v[1]);
    EXPECT_FLOAT_EQ(4.0f, v[2]);
    EXPECT_FLOAT_EQ(5.0f, v[3]);
}

TEST (Vec4f_Test, Comparison) {
    EXPECT_TRUE(Vec4f(1.0f, 1.0f, 1.0f, 1.0f) == Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
    EXPECT_FALSE(Vec4f(1.0f, 2.0f, 3.0f, 4.0f) != Vec4f(1.0f, 2.0f, 3.0f, 4.0f));

    EXPECT_TRUE(Vec4f(1.0f, 2.0f, 3.0f, 4.0f) != Vec4f(3.0f, 4.0f, 5.0f, 6.0f));
    EXPECT_FALSE(Vec4f(1.0f, 2.0f, 3.0f, 4.0f) == Vec4f(3.0f, 4.0f, 5.0f, 6.0f));

    EXPECT_TRUE(Vec4f(1.245f, 2.345f, 4.056f, 7.168f).Compare(Vec4f(1.24f, 2.34f, 4.05f, 7.16f), 0.01f));
    EXPECT_FALSE(Vec4f(1.245f, 2.345f, 4.056f, 7.168f).Compare(Vec4f(1.24f, 2.34f, 4.05f, 7.16f), 0.001f));
}

TEST (Vec4f_Test, Swizzle_Vec2f) {
    EXPECT_EQ(Vec2f(1.0f, 2.0f), Vec4f(1.0f, 2.0f, 3.0f, 4.0f).xy());
    EXPECT_EQ(Vec2f(1.0f, 3.0f), Vec4f(1.0f, 2.0f, 3.0f, 4.0f).xz());
    EXPECT_EQ(Vec2f(2.0f, 3.0f), Vec4f(1.0f, 2.0f, 3.0f, 4.0f).yz());
}

TEST (Vec4f_Test, Swizzle_Vec3f) {
    EXPECT_EQ(Vec3f(1.0f, 2.0f, 3.0f), Vec4f(1.0f, 2.0f, 3.0f, 4.0f).xyz());
}
