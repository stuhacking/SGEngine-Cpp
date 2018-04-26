//
// Vec3f Unit Tests
//
#include <gtest/gtest.h>
#include <cfloat>

#include "lib.h"

/*==========================
  Vector property Tests
 ==========================*/

TEST (Vec3f_Test, Length) {
    EXPECT_FLOAT_EQ(5.0f, Vec3f(3.0f, 0.0f, 4.0f).mag());
}

TEST (Vec3f_Test, Zero) {
    Vec3f v = Vec3f(10.0f, 10.0f, 10.0f);

    v.zero();
    EXPECT_FLOAT_EQ(0.0f, v.mag());
}

TEST (Vec3f_Test, Normalize) {
    Vec3f v = Vec3f(10.0f, 10.0f, 10.0f);

    EXPECT_FLOAT_EQ(1.0f, v.normalize().mag());

    v.normalizeSelf();
    EXPECT_FLOAT_EQ(1.0f, v.mag());
}

TEST (Vec3f_Test, ClampLength) {
    EXPECT_EQ(Vec3f(3.0f, 4.0f, 0.0f), Vec3f(6.0f, 8.0f, 0.0f).clampMag(5.0f));
    EXPECT_EQ(Vec3f(3.0f, 0.0f, 4.0f), Vec3f(1.5f, 0.0f, 2.0f).clampMag(5.0f, 10.0f));
    EXPECT_EQ(Vec3f(0.0f, 3.0f, 4.0f), Vec3f(0.0f, 3.0f, 4.0f).clampMag(2.0f, 8.0f));

    Vec3f v = Vec3f(6.0f, 8.0f, 0.0f);
    v.clampMagSelf(5.0f);

    EXPECT_EQ(Vec3f(3.0f, 4.0f, 0.0f), v);

    v = Vec3f(1.5f, 0.0f, 2.0f);
    v.clampMagSelf(5.0f, 10.0f);

    EXPECT_EQ(Vec3f(3.0f, 0.0f, 4.0f), v);

    v = Vec3f(0.0f, 3.0f, 4.0f);
    v.clampMagSelf(2.0f, 6.0f);

    EXPECT_EQ(Vec3f(0.0f, 3.0f, 4.0f), v);
}

TEST (Vec3f_Test, Clamp) {
    EXPECT_EQ(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(2.0f, 2.0f, 2.0f).clamp(Vec3f(0.0f, 0.0f, 3.0f), Vec3f(1.0f, 10.0f, 4.0f)));
    EXPECT_EQ(Vec3f(2.0f, 2.0f, 2.0f), Vec3f(1.0f, 1.0f, 1.0f).clamp(Vec3f(2.0f, 2.0f, 2.0f), Vec3f(4.0f, 5.0f, 6.0f)));
    EXPECT_EQ(Vec3f(4.0f, 4.0f, 4.0f), Vec3f(4.0f, 4.0f, 4.0f).clamp(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(6.0f, 7.0f, 5.0f)));
}

TEST (Vec3f_Test, ClampSelf) {
    Vec3f v = Vec3f(2.0f, 2.0f, 2.0f);
    v.clampSelf(Vec3f(0.0f, 0.0f, 3.0f), Vec3f(1.0f, 10.0f, 4.0f));

    EXPECT_EQ(Vec3f(1.0f, 2.0f, 3.0f), v);

    v = Vec3f(1.0f, 1.0f, 1.0f);
    v.clampSelf(Vec3f(2.0f, 2.0f, 2.0f), Vec3f(4.0f, 5.0f, 6.0f));

    EXPECT_EQ(Vec3f(2.0f, 2.0f, 2.0f), v);

    v = Vec3f(4.0f, 4.0f, 4.0f);
    v.clampSelf(Vec3f(1.0f, 2.0f, 3.0f), Vec3f(6.0f, 7.0f, 5.0f));

    EXPECT_EQ(Vec3f(4.0f, 4.0f, 4.0f), v);
}

/*==========================
  math Operator Tests
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
    EXPECT_EQ(Vec3f(0.0f), Vec3f(2.0f) * Vec3f_Zero);
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
    EXPECT_EQ(Vec3f(math::kInfty), Vec3f(3.0f, 2.0f, 1.0f) / 0.0f);
    EXPECT_EQ(Vec3f(math::kInfty, -math::kInfty, math::kInfty), Vec3f(3.0f, -2.0f, 1.0f) / 0.0f);
}

TEST (Vec3f_Test, Div_Equals) {
    Vec3f v1 = Vec3f(3.0f, 1.5f, 0.6f);

    v1 /= 2;

    EXPECT_EQ(Vec3f(1.5f, 0.75f, 0.3f), v1);
}

TEST (Vec3f_Test, Dot) {
    EXPECT_EQ(32.0f, Vec3f(1.0f, 2.0f, 3.0f).dot(Vec3f(4.0f, 5.0f, 6.0f)));
}

TEST (Vec3f_Test, Cross) {
    EXPECT_EQ(Vec3f(-3.0f, 6.0f, -3.0f), Vec3f(1.0f, 2.0f, 3.0f).cross(Vec3f(4.0f, 5.0f, 6.0f)));
}

TEST (Vec3f_Test, Mirror) {
    EXPECT_TRUE(Vec3f(3.0f, 2.0f, 1.0f).compare(Vec3f(1.0f, 2.0f, 3.0f).mirror(Vec3f(0.5f, 0.5f, 0.5f).normalize()), 0.00001f));

    EXPECT_EQ(Vec3f(-1.5f, 2.0f, 4.0f), Vec3f(2.0f, -1.5f, -4.0f).mirror(Vec3f(0.5f, 0.5f, 0.0f).normalize()));
}

TEST (Vec3f_Test, Rotate) {
    Vec3f v = Vec3f(1.0f, 0.0f, 0.0f);

    EXPECT_TRUE(Vec3f(0.0f, 1.0f, 0.0f).compare(v.rotate(math::rad(90.0f), Vec3f(0.0f, 0.0f, 1.0f)), 0.0001f));

    v.rotateSelf(math::rad(90.0f), Vec3f(0.0f, 0.0f, 1.0f));

    EXPECT_TRUE(Vec3f(0.0f, 1.0f, 0.0f).compare(v, 0.0001f));
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

TEST (Vec3f_Test, Comparison) {
    EXPECT_TRUE(Vec3f(1.0f, 1.0f, 1.0f) == Vec3f(1.0f, 1.0f, 1.0f));
    EXPECT_FALSE(Vec3f(1.0f, 2.0f, 3.0f) != Vec3f(1.0f, 2.0f, 3.0f));

    EXPECT_TRUE(Vec3f(1.0f, 2.0f, 3.0f) != Vec3f(3.0f, 4.0f, 5.0f));
    EXPECT_FALSE(Vec3f(1.0f, 2.0f, 3.0f) == Vec3f(3.0f, 4.0f, 5.0f));

    EXPECT_TRUE(Vec3f(1.245f, 2.345f, 4.056f).compare(Vec3f(1.24f, 2.34f, 4.05f), 0.01f));
    EXPECT_FALSE(Vec3f(1.245f, 2.345f, 4.056f).compare(Vec3f(1.24f, 2.34f, 4.05f), 0.001f));
}

TEST (Vec3f_Test, Swizzle_Vec2f) {
    EXPECT_EQ(Vec2f(1.0f, 2.0f), Vec3f(1.0f, 2.0f, 3.0f).xy());
    EXPECT_EQ(Vec2f(1.0f, 3.0f), Vec3f(1.0f, 2.0f, 3.0f).xz());
    EXPECT_EQ(Vec2f(2.0f, 3.0f), Vec3f(1.0f, 2.0f, 3.0f).yz());
}
