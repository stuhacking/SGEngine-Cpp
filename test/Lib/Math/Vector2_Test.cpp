//
// Vec2f Unit Tests
//
#include <gtest/gtest.h>
#include <cfloat>

#include "lib.h"

/*==========================
  Vector property Tests
 ==========================*/

TEST (Vec2f_Test, Length) {
    EXPECT_FLOAT_EQ(5.0f, Vec2f(3.0f, 4.0f).mag());
}

TEST (Vec2f_Test, Zero) {
    Vec2f v = Vec2f(10.0f, 10.0f);

    v.zero();
    EXPECT_FLOAT_EQ(0.0f, v.mag());
}

TEST (Vec2f_Test, Normalize) {
    Vec2f v = Vec2f(10.0f, 10.0f);

    EXPECT_FLOAT_EQ(1.0f, v.normalize().mag());

    v.normalizeSelf();
    EXPECT_FLOAT_EQ(1.0f, v.mag());
}

TEST (Vec2f_Test, ClampLength) {
    EXPECT_EQ(Vec2f(3.0f, 4.0f), Vec2f(6.0f, 8.0f).clampMag(5.0f));
    EXPECT_EQ(Vec2f(3.0f, 4.0f), Vec2f(1.5f, 2.0f).clampMag(5.0f, 10.0f));
    EXPECT_EQ(Vec2f(3.0f, 4.0f), Vec2f(3.0f, 4.0f).clampMag(2.0f, 8.0f));

    Vec2f v = Vec2f(6.0f, 8.0f);
    v.clampMagSelf(5.0f);

    EXPECT_EQ(Vec2f(3.0f, 4.0f), v);

    v = Vec2f(1.5f, 2.0f);
    v.clampMagSelf(5.0f, 10.0f);

    EXPECT_EQ(Vec2f(3.0f, 4.0f), v);

    v = Vec2f(3.0f, 4.0f);
    v.clampMagSelf(2.0f, 6.0f);

    EXPECT_EQ(Vec2f(3.0f, 4.0f), v);

}

TEST (Vec2f_Test, Clamp) {
    EXPECT_EQ(Vec2f(1.0f, 2.0f), Vec2f(2.0f, 2.0f).clamp(Vec2f(0.0f, 0.0f), Vec2f(1.0f, 10.0f)));
    EXPECT_EQ(Vec2f(2.0f, 2.0f), Vec2f(1.0f, 1.0f).clamp(Vec2f(2.0f, 2.0f), Vec2f(4.0f, 5.0f)));
    EXPECT_EQ(Vec2f(4.0f, 4.0f), Vec2f(4.0f, 4.0f).clamp(Vec2f(1.0f, 2.0f), Vec2f(6.0f, 7.0f)));
}

TEST (Vec2f_Test, ClampSelf) {
    Vec2f v = Vec2f(2.0f, 2.0f);
    v.clampSelf(Vec2f(0.0f, 0.0f), Vec2f(1.0f, 10.0f));

    EXPECT_EQ(Vec2f(1.0f, 2.0f), v);

    v = Vec2f(1.0f, 1.0f);
    v.clampSelf(Vec2f(2.0f, 2.0f), Vec2f(4.0f, 5.0f));

    EXPECT_EQ(Vec2f(2.0f, 2.0f), v);

    v = Vec2f(4.0f, 4.0f);
    v.clampSelf(Vec2f(1.0f, 2.0f), Vec2f(6.0f, 7.0f));

    EXPECT_EQ(Vec2f(4.0f, 4.0f), v);
}

/*==========================
  Math Operator Tests
 ==========================*/

TEST (Vec2f_Test, Negate) {
    EXPECT_EQ(Vec2f(-1.0f, 2.0f), -Vec2f(1.0f, -2.0f));
}

TEST (Vec2f_Test, Add) {
    EXPECT_EQ(Vec2f(2.0f, 2.0f), Vec2f(2.0f, 2.0f) + Vec2f(0.0f, 0.0f));
    EXPECT_EQ(Vec2f(2.0f, 2.0f), Vec2f(1.0f, 1.0f) + Vec2f(1.0f, 1.0f));
    EXPECT_EQ(Vec2f(2.0f, 2.0f), Vec2f(3.0f, 1.0f) + Vec2f(-1.0f, 1.0f));
}

TEST (Vec2f_Test, Add_Equals) {
    Vec2f v1 = Vec2f(2.0f, 1.0f);

    v1 += Vec2f(1.0f, 1.0f);

    EXPECT_EQ(Vec2f(3.0f, 2.0f), v1);
}

TEST (Vec2f_Test, Sub) {
    EXPECT_EQ(Vec2f(2.0f, 2.0f), Vec2f(2.0f, 2.0f) - Vec2f(0.0f, 0.0f));
    EXPECT_EQ(Vec2f(1.0f, 1.0f), Vec2f(2.0f, 2.0f) - Vec2f(1.0f, 1.0f));
    EXPECT_EQ(Vec2f(2.0f, 2.0f), Vec2f(3.0f, 1.0f) - Vec2f(1.0f, -1.0f));
}

TEST (Vec2f_Test, Sub_Equals) {
    Vec2f v1 = Vec2f(2.0f, 1.0f);

    v1 -= Vec2f(1.0f, 1.0f);

    EXPECT_EQ(Vec2f(1.0f, 0.0f), v1);
}

TEST (Vec2f_Test, Scale) {
    EXPECT_EQ(Vec2f(0.0f, 0.0f), Vec2f(2.0f, 2.0f) * 0.0f);
    EXPECT_EQ(Vec2f(2.0f, 2.0f), Vec2f(2.0f, 2.0f) * 1.0f);
    EXPECT_EQ(Vec2f(4.0f, 3.0f), Vec2f(2.0f, 1.5f) * 2.0f);
    EXPECT_EQ(Vec2f(-6.0f, 4.0f), Vec2f(3.0f, -2.0f) * -2.0f);
}

TEST (Vec2f_Test, Scale_Equals) {
    Vec2f v1 = Vec2f(3.0f, 1.5f);

    v1 *= 2.0f;

    EXPECT_EQ(Vec2f(6.0f, 3.0f), v1);
}

TEST (Vec2f_Test, NonUniformScale) {
    EXPECT_EQ(Vec2f(0.0f, 0.0f), Vec2f(2.0f, 2.0f) * Vec2f_Zero);
    EXPECT_EQ(Vec2f(2.0f, 4.0f), Vec2f(2.0f, 2.0f) * Vec2f(1.0f, 2.0f));
    EXPECT_EQ(Vec2f(4.0f, 2.0f), Vec2f(2.0f, 4.0f) * Vec2f(2.0f, 0.5f));
}

TEST (Vec2f_Test, NonUniformScale_Equals) {
    Vec2f v1 = Vec2f(3.0f, 1.5f);

    v1 *= Vec2f(1.5f, 2.0f);

    EXPECT_EQ(Vec2f(4.5f, 3.0f), v1);
}

TEST (Vec2f_Test, Div) {
    EXPECT_EQ(Vec2f(2.0f, 2.0f), Vec2f(2.0f, 2.0f) / 1.0f);
    EXPECT_EQ(Vec2f(1.0f, 0.75f), Vec2f(2.0f, 1.5f) / 2.0f);
    EXPECT_EQ(Vec2f(math::kInfty, math::kInfty), Vec2f(3.0f, 2.0f) / 0.0f);
    EXPECT_EQ(Vec2f(math::kInfty, -math::kInfty), Vec2f(3.0f, -2.0f) / 0.0f);
}

TEST (Vec2f_Test, Div_Equals) {
    Vec2f v1 = Vec2f(3.0f, 1.5f);

    v1 /= 2.0f;

    EXPECT_EQ(Vec2f(1.5f, 0.75f), v1);
}

TEST (Vec2f_Test, Dot) {
    EXPECT_EQ(11.0f, Vec2f(1.0f, 2.0f).dot(Vec2f(3.0f, 4.0f)));
}

TEST (Vec2f_Test, Cross) {
    EXPECT_EQ(27.0f, Vec2f(-1.0f, 7.0f).cross(Vec2f(-5.0f, 8.0f)));
}

TEST (Vec2f_Test, Mirror) {
    EXPECT_EQ(Vec2f(0.0f, -1.0f), Vec2f(0.0f, 1.0f).mirror(Vec2f(1.0f, 0.0f)));
    EXPECT_EQ(Vec2f(4.0f, -6.0f), Vec2f(-6.0f, 4.0f).mirror(Vec2f(0.5f, 0.5f).normalize()));
}

/*==========================
  Convenience Tests
 ==========================*/

TEST (Vec2f_Test, Operator_Index) {
    Vec2f v = Vec2f(10.0f, 5.0f);

    EXPECT_FLOAT_EQ(10.0f, v[0]);
    EXPECT_FLOAT_EQ(5.0f, v[1]);
}

TEST (Vec2f_Test, Operator_Index_Set) {
    Vec2f v = Vec2f(10.0f, 5.0f);

    v[0] = 2.0f;
    v[1] = 3.0f;

    EXPECT_FLOAT_EQ(2.0f, v[0]);
    EXPECT_FLOAT_EQ(3.0f, v[1]);
}

TEST (Vec2f_Test, Comparison) {
    EXPECT_TRUE(Vec2f(1.0f, 1.0f) == Vec2f(1.0f, 1.0f));
    EXPECT_FALSE(Vec2f(1.0f, 2.0f) != Vec2f(1.0f, 2.0f));

    EXPECT_TRUE(Vec2f(1.0f, 2.0f) != Vec2f(3.0f, 4.0f));
    EXPECT_FALSE(Vec2f(1.0f, 2.0f) == Vec2f(3.0f, 4.0f));

    EXPECT_TRUE(Vec2f(1.245f, 2.345f).compare(Vec2f(1.24f, 2.34f), 0.01f));
    EXPECT_FALSE(Vec2f(1.245f, 2.345f).compare(Vec2f(1.24f, 2.34f), 0.001f));
}
