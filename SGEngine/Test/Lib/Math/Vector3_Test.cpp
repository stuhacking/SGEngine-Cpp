//
// Vector3 Unit Tests
//
#include <gtest/gtest.h>
#include <cfloat>

#include "Lib.h"

using sge::FMath;
using sge::Vector3;

/*==========================
  Vector property Tests
 ==========================*/

TEST (Vector3_Test, Length) {
    EXPECT_FLOAT_EQ(5.0f, Vector3(3.0f, 0.0f, 4.0f).Length());
}

TEST (Vector3_Test, Zero) {
    Vector3 v = Vector3(10.0f, 10.0f, 10.0f);

    v.Zero();
    EXPECT_FLOAT_EQ(0.0f, v.Length());
}

TEST (Vector3_Test, Normalize) {
    Vector3 v = Vector3(10.0f, 10.0f, 10.0f);

    EXPECT_FLOAT_EQ(1.0f, v.Normalize().Length());

    v.NormalizeSelf();
    EXPECT_FLOAT_EQ(1.0f, v.Length());
}

TEST (Vector3_Test, ClampLength) {
    EXPECT_EQ(Vector3(3.0f, 4.0f, 0.0f), Vector3(6.0f, 8.0f, 0.0f).ClampLength(5.0f));
    EXPECT_EQ(Vector3(3.0f, 0.0f, 4.0f), Vector3(1.5f, 0.0f, 2.0f).ClampLength(5.0f, 10.0f));
    EXPECT_EQ(Vector3(0.0f, 3.0f, 4.0f), Vector3(0.0f, 3.0f, 4.0f).ClampLength(2.0f, 8.0f));

    Vector3 v = Vector3(6.0f, 8.0f, 0.0f);
    v.ClampLengthSelf(5.0f);

    EXPECT_EQ(Vector3(3.0f, 4.0f, 0.0f), v);
    
    v = Vector3(1.5f, 0.0f, 2.0f);
    v.ClampLengthSelf(5.0f, 10.0f);
    
    EXPECT_EQ(Vector3(3.0f, 0.0f, 4.0f), v);
    
    v = Vector3(0.0f, 3.0f, 4.0f);
    v.ClampLengthSelf(2.0f, 6.0f);

    EXPECT_EQ(Vector3(0.0f, 3.0f, 4.0f), v);
}

/*==========================
  Math Operator Tests
 ==========================*/

TEST (Vector3_Test, Add) {
    EXPECT_EQ(Vector3(2.0f), Vector3(2.0f) + Vector3(0.0f));
    EXPECT_EQ(Vector3(2.0f), Vector3(1.0f) + Vector3(1.0f));
    EXPECT_EQ(Vector3(2.0f, 2.0f, 2.0f), Vector3(3.0f, 1.0f, 0.0f) + Vector3(-1.0f, 1.0f, 2.0f));
}

TEST (Vector3_Test, Add_Equals) {
    Vector3 v1 = Vector3(2.0f, 1.0f, 2.0f);

    v1 += Vector3(1.0f, 1.0f, -1.0f);

    EXPECT_EQ(Vector3(3.0f, 2.0f, 1.0f), v1);
}

TEST (Vector3_Test, Sub) {
    EXPECT_EQ(Vector3(2.0f), Vector3(2.0f) - Vector3(0.0f));
    EXPECT_EQ(Vector3(1.0f), Vector3(2.0f) - Vector3(1.0f));
    EXPECT_EQ(Vector3(2.0f), Vector3(3.0f, 1.0f, 4.0f) - Vector3(1.0f, -1.0f, 2.0f));
}

TEST (Vector3_Test, Sub_Equals) {
    Vector3 v1 = Vector3(2.0f, 1.0f, -1.0f);

    v1 -= Vector3(1.0f);

    EXPECT_EQ(Vector3(1.0f, 0.0f, -2.0f), v1);
}

TEST (Vector3_Test, Scale) {
    EXPECT_EQ(Vector3(0.0f), Vector3(2.0f) * 0.0f);
    EXPECT_EQ(Vector3(2.0f), Vector3(2.0f) * 1.0f);
    EXPECT_EQ(Vector3(4.0f, 3.0f, 2.0f), Vector3(2.0f, 1.5f, 1.0f) * 2.0f);
    EXPECT_EQ(Vector3(-6.0f, 4.0f, -2.0f), Vector3(3.0f, -2.0f, 1.0f) * -2.0f);
}

TEST (Vector3_Test, Scale_Equals) {
    Vector3 v1 = Vector3(3.0f, 1.5f, 2.0f);

    v1 *= 2;

    EXPECT_EQ(Vector3(6.0f, 3.0f, 4.0f), v1);
}

TEST (Vector3_Test, NonUniformScale) {
    EXPECT_EQ(Vector3(0.0f), Vector3(2.0f) * Vector3::ZERO);
    EXPECT_EQ(Vector3(2.0f, 4.0f, 6.0f), Vector3(2.0f) * Vector3(1.0f, 2.0f, 3.0f));
    EXPECT_EQ(Vector3(4.0f, 2.0f, 0.0f), Vector3(2.0f, 4.0f, 5.0f) * Vector3(2.0f, 0.5f, 0.0f));
}

TEST (Vector3_Test, NonUniformScale_Equals) {
    Vector3 v1 = Vector3(3.0f, 1.5f, 4.0f);

    v1 *= Vector3(1.5f, 2.0f, 0.5f);

    EXPECT_EQ(Vector3(4.5f, 3.0f, 2.0f), v1);
}

TEST (Vector3_Test, Div) {
    EXPECT_EQ(Vector3(2.0f), Vector3(2.0f) / 1.0f);
    EXPECT_EQ(Vector3(1.0f, 0.75f, 0.25f), Vector3(2.0f, 1.5f, 0.5f) / 2.0f);
    EXPECT_EQ(Vector3(FMath::INFTY), Vector3(3.0f, 2.0f, 1.0f) / 0.0f);
    EXPECT_EQ(Vector3(FMath::INFTY, -FMath::INFTY, FMath::INFTY), Vector3(3.0f, -2.0f, 1.0f) / 0.0f);
}

TEST (Vector3_Test, Div_Equals) {
    Vector3 v1 = Vector3(3.0f, 1.5f, 0.6f);

    v1 /= 2;

    EXPECT_EQ(Vector3(1.5f, 0.75f, 0.3f), v1);
}

/*==========================
  Convenience Tests
 ==========================*/

TEST (Vector3_Test, Operator_Index) {
    Vector3 v = Vector3(10.0f, 5.0f, 2.5f);

    EXPECT_FLOAT_EQ(10.0f, v[0]);
    EXPECT_FLOAT_EQ(5.0f, v[1]);
    EXPECT_FLOAT_EQ(2.5f, v[2]);
}

TEST (Vector3_Test, Operator_Index_Set) {
    Vector3 v = Vector3(10.0f, 5.0f, 2.5f);

    v[0] = 2.0f;
    v[1] = 3.0f;
    v[2] = 4.0f;

    EXPECT_FLOAT_EQ(2.0f, v[0]);
    EXPECT_FLOAT_EQ(3.0f, v[1]);
    EXPECT_FLOAT_EQ(4.0f, v[2]);
}
