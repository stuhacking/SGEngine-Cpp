//
// Vec4f Unit Tests
//
#include <gtest/gtest.h>
#include <cfloat>

#include "lib.h"

/*==========================
  Vector property Tests
 ==========================*/

TEST (Vec4f_Test, Length) {
    EXPECT_FLOAT_EQ(5.0f, Vec4f(3.0f, 0.0f, 4.0f, 0.0f).mag());
}

TEST (Vec4f_Test, Zero) {
    Vec4f v = Vec4f(10.0f);

    v.zero();
    EXPECT_FLOAT_EQ(0.0f, v.mag());
}

TEST (Vec4f_Test, Normalize) {
    Vec4f v = Vec4f(10.0f);

    EXPECT_FLOAT_EQ(1.0f, v.normalize().mag());

    v.normalizeSelf();
    EXPECT_FLOAT_EQ(1.0f, v.mag());
}

TEST (Vec4f_Test, ClampLength) {
    EXPECT_EQ(Vec4f(3.0f, 4.0f, 0.0f, 0.0f), Vec4f(6.0f, 8.0f, 0.0f, 0.0f).clampMag(5.0f));
    EXPECT_EQ(Vec4f(3.0f, 0.0f, 0.0f, 4.0f), Vec4f(1.5f, 0.0f, 0.0f, 2.0f).clampMag(5.0f, 10.0f));
    EXPECT_EQ(Vec4f(0.0f, 0.0f, 3.0f, 4.0f), Vec4f(0.0f, 0.0f, 3.0f, 4.0f).clampMag(2.0f, 8.0f));

    Vec4f v = Vec4f(6.0f, 0.0f, 8.0f, 0.0f);
    v.clampMagSelf(5.0f);

    EXPECT_EQ(Vec4f(3.0f, 0.0f, 4.0f, 0.0f), v);

    v = Vec4f(1.5f, 0.0f, 2.0f, 0.0f);
    v.clampMagSelf(5.0f, 10.0f);

    EXPECT_EQ(Vec4f(3.0f, 0.0f, 4.0f, 0.0f), v);

    v = Vec4f(0.0f, 0.0f, 3.0f, 4.0f);
    v.clampMagSelf(2.0f, 6.0f);

    EXPECT_EQ(Vec4f(0.0f, 0.0f, 3.0f, 4.0f), v);
}

TEST (Vec4f_Test, Clamp) {
    EXPECT_EQ(Vec4f(1.0f, 2.0f, 3.0f, 4.0f), Vec4f(2.0f, 2.0f, 2.0f, 2.0f).clamp(Vec4f(0.0f, 0.0f, 3.0f, 4.0f), Vec4f(1.0f, 10.0f, 4.0f, 6.0f)));
    EXPECT_EQ(Vec4f(2.0f, 2.0f, 2.0f, 2.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f).clamp(Vec4f(2.0f, 2.0f, 2.0f, 2.0f), Vec4f(4.0f, 5.0f, 6.0f, 7.0f)));
    EXPECT_EQ(Vec4f(4.0f, 4.0f, 4.0f, 4.0f), Vec4f(4.0f, 4.0f, 4.0f, 4.0f).clamp(Vec4f(1.0f, 2.0f, 3.0f, 4.0f), Vec4f(6.0f, 7.0f, 5.0f, 5.0f)));
}

TEST (Vec4f_Test, ClampSelf) {
    Vec4f v = Vec4f(2.0f, 2.0f, 2.0f, 2.0f);
    v.clampSelf(Vec4f(0.0f, 0.0f, 3.0f, 4.0f), Vec4f(1.0f, 10.0f, 4.0f, 6.0f));

    EXPECT_EQ(Vec4f(1.0f, 2.0f, 3.0f, 4.0f), v);

    v = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
    v.clampSelf(Vec4f(2.0f, 2.0f, 2.0f, 2.0f), Vec4f(4.0f, 5.0f, 6.0f, 7.0f));

    EXPECT_EQ(Vec4f(2.0f, 2.0f, 2.0f, 2.0f), v);

    v = Vec4f(4.0f, 4.0f, 4.0f, 4.0f);
    v.clampSelf(Vec4f(1.0f, 2.0f, 3.0f, 4.0f), Vec4f(6.0f, 7.0f, 5.0f, 5.0f));

    EXPECT_EQ(Vec4f(4.0f, 4.0f, 4.0f, 4.0f), v);
}
/*==========================
  math Operator Tests
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
    EXPECT_EQ(Vec4f(0.0f), Vec4f(2.0f) * Vec4f_Zero);
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
    EXPECT_EQ(Vec4f(math::kInfty), Vec4f(3.0f, 2.0f, 1.0f, 0.5f) / 0.0f);
    EXPECT_EQ(Vec4f(math::kInfty, -math::kInfty, math::kInfty, -math::kInfty), Vec4f(3.0f, -2.0f, 1.0f, -4.0f) / 0.0f);
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

    EXPECT_TRUE(Vec4f(1.245f, 2.345f, 4.056f, 7.168f).compare(Vec4f(1.24f, 2.34f, 4.05f, 7.16f), 0.01f));
    EXPECT_FALSE(Vec4f(1.245f, 2.345f, 4.056f, 7.168f).compare(Vec4f(1.24f, 2.34f, 4.05f, 7.16f), 0.001f));
}

TEST (Vec4f_Test, Swizzle_Vec2f) {
    EXPECT_EQ(Vec2f(1.0f, 2.0f), Vec4f(1.0f, 2.0f, 3.0f, 4.0f).xy());
    EXPECT_EQ(Vec2f(1.0f, 3.0f), Vec4f(1.0f, 2.0f, 3.0f, 4.0f).xz());
    EXPECT_EQ(Vec2f(2.0f, 3.0f), Vec4f(1.0f, 2.0f, 3.0f, 4.0f).yz());
}

TEST (Vec4f_Test, Swizzle_Vec3f) {
    EXPECT_EQ(Vec3f(1.0f, 2.0f, 3.0f), Vec4f(1.0f, 2.0f, 3.0f, 4.0f).xyz());
}
