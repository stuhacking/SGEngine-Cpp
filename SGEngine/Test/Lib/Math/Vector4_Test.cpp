//
// Vector4 Unit Tests
//
#include <gtest/gtest.h>
#include <cfloat>

#include "Lib.h"

using sge::FMath;
using sge::Vector4;

/*==========================
  Vector property Tests
 ==========================*/

TEST (Vector4_Test, Length) {
    EXPECT_FLOAT_EQ(5.0f, Vector4(3.0f, 0.0f, 4.0f, 0.0f).Length());
}

TEST (Vector4_Test, Zero) {
    Vector4 v = Vector4(10.0f);

    v.Zero();
    EXPECT_FLOAT_EQ(0.0f, v.Length());
}

TEST (Vector4_Test, Normalize) {
    Vector4 v = Vector4(10.0f);

    EXPECT_FLOAT_EQ(1.0f, v.Normalize().Length());

    v.NormalizeSelf();
    EXPECT_FLOAT_EQ(1.0f, v.Length());
}

TEST (Vector4_Test, ClampLength) {
    EXPECT_EQ(Vector4(3.0f, 4.0f, 0.0f, 0.0f), Vector4(6.0f, 8.0f, 0.0f, 0.0f).ClampLength(5.0f));
    EXPECT_EQ(Vector4(3.0f, 0.0f, 0.0f, 4.0f), Vector4(1.5f, 0.0f, 0.0f, 2.0f).ClampLength(5.0f, 10.0f));
    EXPECT_EQ(Vector4(0.0f, 0.0f, 3.0f, 4.0f), Vector4(0.0f, 0.0f, 3.0f, 4.0f).ClampLength(2.0f, 8.0f));

    Vector4 v = Vector4(6.0f, 0.0f, 8.0f, 0.0f);
    v.ClampLengthSelf(5.0f);

    EXPECT_EQ(Vector4(3.0f, 0.0f, 4.0f, 0.0f), v);
    
    v = Vector4(1.5f, 0.0f, 2.0f, 0.0f);
    v.ClampLengthSelf(5.0f, 10.0f);
    
    EXPECT_EQ(Vector4(3.0f, 0.0f, 4.0f, 0.0f), v);
    
    v = Vector4(0.0f, 0.0f, 3.0f, 4.0f);
    v.ClampLengthSelf(2.0f, 6.0f);

    EXPECT_EQ(Vector4(0.0f, 0.0f, 3.0f, 4.0f), v);
}

/*==========================
  Math Operator Tests
 ==========================*/

TEST (Vector4_Test, Add) {
    EXPECT_EQ(Vector4(2.0f), Vector4(2.0f) + Vector4(0.0f));
    EXPECT_EQ(Vector4(2.0f), Vector4(1.0f) + Vector4(1.0f));
    EXPECT_EQ(Vector4(2.0f), Vector4(3.0f, 1.0f, 0.0f, -2.0f) + Vector4(-1.0f, 1.0f, 2.0f, 4.0f));
}

TEST (Vector4_Test, Add_Equals) {
    Vector4 v1 = Vector4(2.0f, 1.0f, 2.0f, 3.0f);

    v1 += Vector4(1.0f, 1.0f, -1.0f, 0.0f);

    EXPECT_EQ(Vector4(3.0f, 2.0f, 1.0f, 3.0f), v1);
}

TEST (Vector4_Test, Sub) {
    EXPECT_EQ(Vector4(2.0f), Vector4(2.0f) - Vector4(0.0f));
    EXPECT_EQ(Vector4(1.0f), Vector4(2.0f) - Vector4(1.0f));
    EXPECT_EQ(Vector4(2.0f), Vector4(3.0f, 1.0f, 4.0f, -1.0f) - Vector4(1.0f, -1.0f, 2.0f, -3.0f));
}

TEST (Vector4_Test, Sub_Equals) {
    Vector4 v1 = Vector4(2.0f, 1.0f, -1.0f, -2.0f);

    v1 -= Vector4(1.0f);

    EXPECT_EQ(Vector4(1.0f, 0.0f, -2.0f, -3.0f), v1);
}

TEST (Vector4_Test, Scale) {
    EXPECT_EQ(Vector4(0.0f), Vector4(2.0f) * 0.0f);
    EXPECT_EQ(Vector4(2.0f), Vector4(2.0f) * 1.0f);
    EXPECT_EQ(Vector4(4.0f, 3.0f, 2.0f, 1.0f), Vector4(2.0f, 1.5f, 1.0f, 0.5f) * 2.0f);
    EXPECT_EQ(Vector4(-6.0f, 4.0f, -2.0f, 1.0f), Vector4(3.0f, -2.0f, 1.0f, -0.5f) * -2.0f);
}

TEST (Vector4_Test, Scale_Equals) {
    Vector4 v1 = Vector4(3.0f, 1.5f, 2.0f, -3.0f);

    v1 *= 2;

    EXPECT_EQ(Vector4(6.0f, 3.0f, 4.0f, -6.0f), v1);
}

TEST (Vector4_Test, NonUniformScale) {
    EXPECT_EQ(Vector4(0.0f), Vector4(2.0f) * Vector4::ZERO);
    EXPECT_EQ(Vector4(2.0f, 4.0f, 6.0f, 8.0f), Vector4(2.0f) * Vector4(1.0f, 2.0f, 3.0f, 4.0f));
    EXPECT_EQ(Vector4(4.0f, 2.0f, 0.0f, -2.0f), Vector4(2.0f, 4.0f, 5.0f, 4.0f) * Vector4(2.0f, 0.5f, 0.0f, -0.5f));
}

TEST (Vector4_Test, NonUniformScale_Equals) {
    Vector4 v1 = Vector4(3.0f, 1.5f, 4.0f, 3.0f);

    v1 *= Vector4(1.5f, 2.0f, 0.5f, -2.0f);

    EXPECT_EQ(Vector4(4.5f, 3.0f, 2.0f, -6.0f), v1);
}

TEST (Vector4_Test, Div) {
    EXPECT_EQ(Vector4(2.0f), Vector4(2.0f) / 1.0f);
    EXPECT_EQ(Vector4(1.0f, 0.75f, 0.25f, 0.125f), Vector4(2.0f, 1.5f, 0.5f, 0.25f) / 2.0f);
    EXPECT_EQ(Vector4(FMath::INFTY), Vector4(3.0f, 2.0f, 1.0f, 0.5f) / 0.0f);
    EXPECT_EQ(Vector4(FMath::INFTY, -FMath::INFTY, FMath::INFTY, -FMath::INFTY), Vector4(3.0f, -2.0f, 1.0f, -4.0f) / 0.0f);
}

TEST (Vector4_Test, Div_Equals) {
    Vector4 v1 = Vector4(3.0f, 1.5f, 0.6f, 2.0f);

    v1 /= 2;

    EXPECT_EQ(Vector4(1.5f, 0.75f, 0.3f, 1.0f), v1);
}

/*==========================
  Convenience Tests
 ==========================*/

TEST (Vector4_Test, Operator_Index) {
    Vector4 v = Vector4(10.0f, 5.0f, 2.5f, 1.0f);

    EXPECT_FLOAT_EQ(10.0f, v[0]);
    EXPECT_FLOAT_EQ(5.0f, v[1]);
    EXPECT_FLOAT_EQ(2.5f, v[2]);
    EXPECT_FLOAT_EQ(1.0f, v[3]);
}

TEST (Vector4_Test, Operator_Index_Set) {
    Vector4 v = Vector4(10.0f, 5.0f, 2.5f, 1.0f);

    v[0] = 2.0f;
    v[1] = 3.0f;
    v[2] = 4.0f;
    v[3] = 5.0f;

    EXPECT_FLOAT_EQ(2.0f, v[0]);
    EXPECT_FLOAT_EQ(3.0f, v[1]);
    EXPECT_FLOAT_EQ(4.0f, v[2]);
    EXPECT_FLOAT_EQ(5.0f, v[3]);
}
