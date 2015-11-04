//
// Vector2 Unit Tests
//
#include <gtest/gtest.h>
#include <cfloat>

#include "Lib.h"

using sge::FMath;
using sge::Vector2;

/*==========================
  Vector property Tests
 ==========================*/

TEST (Vector2_Test, Length) {
    EXPECT_FLOAT_EQ(5.0f, Vector2(3.0f, 4.0f).Length());
}

TEST (Vector2_Test, Zero) {
    Vector2 v = Vector2(10.0f, 10.0f);

    v.Zero();
    EXPECT_FLOAT_EQ(0.0f, v.Length());
}

TEST (Vector2_Test, Normalize) {
    Vector2 v = Vector2(10.0f, 10.0f);

    EXPECT_FLOAT_EQ(1.0f, v.Normalize().Length());

    v.NormalizeSelf();
    EXPECT_FLOAT_EQ(1.0f, v.Length());
}

TEST (Vector2_Test, ClampLength) {
    EXPECT_EQ(Vector2(3.0f, 4.0f), Vector2(6.0f, 8.0f).ClampLength(5.0f));
    EXPECT_EQ(Vector2(3.0f, 4.0f), Vector2(1.5f, 2.0f).ClampLength(5.0f, 10.0f));
    EXPECT_EQ(Vector2(3.0f, 4.0f), Vector2(3.0f, 4.0f).ClampLength(2.0f, 8.0f));

    Vector2 v = Vector2(6.0f, 8.0f);
    v.ClampLengthSelf(5.0f);

    EXPECT_EQ(Vector2(3.0f, 4.0f), v);
    
    v = Vector2(1.5f, 2.0f);
    v.ClampLengthSelf(5.0f, 10.0f);
    
    EXPECT_EQ(Vector2(3.0f, 4.0f), v);
    
    v = Vector2(3.0f, 4.0f);
    v.ClampLengthSelf(2.0f, 6.0f);

    EXPECT_EQ(Vector2(3.0f, 4.0f), v);
    
}

/*==========================
  Math Operator Tests
 ==========================*/

TEST (Vector2_Test, Add) {
    EXPECT_EQ(Vector2(2.0f, 2.0f), Vector2(2.0f, 2.0f) + Vector2(0.0f, 0.0f));
    EXPECT_EQ(Vector2(2.0f, 2.0f), Vector2(1.0f, 1.0f) + Vector2(1.0f, 1.0f));
    EXPECT_EQ(Vector2(2.0f, 2.0f), Vector2(3.0f, 1.0f) + Vector2(-1.0f, 1.0f));
}

TEST (Vector2_Test, Add_Equals) {
    Vector2 v1 = Vector2(2.0f, 1.0f);

    v1 += Vector2(1.0f, 1.0f);

    EXPECT_EQ(Vector2(3.0f, 2.0f), v1);
}

TEST (Vector2_Test, Sub) {
    EXPECT_EQ(Vector2(2.0f, 2.0f), Vector2(2.0f, 2.0f) - Vector2(0.0f, 0.0f));
    EXPECT_EQ(Vector2(1.0f, 1.0f), Vector2(2.0f, 2.0f) - Vector2(1.0f, 1.0f));
    EXPECT_EQ(Vector2(2.0f, 2.0f), Vector2(3.0f, 1.0f) - Vector2(1.0f, -1.0f));
}

TEST (Vector2_Test, Sub_Equals) {
    Vector2 v1 = Vector2(2.0f, 1.0f);

    v1 -= Vector2(1.0f, 1.0f);

    EXPECT_EQ(Vector2(1.0f, 0.0f), v1);
}

TEST (Vector2_Test, Scale) {
    EXPECT_EQ(Vector2(0.0f, 0.0f), Vector2(2.0f, 2.0f) * 0.0f);
    EXPECT_EQ(Vector2(2.0f, 2.0f), Vector2(2.0f, 2.0f) * 1.0f);
    EXPECT_EQ(Vector2(4.0f, 3.0f), Vector2(2.0f, 1.5f) * 2.0f);
    EXPECT_EQ(Vector2(-6.0f, 4.0f), Vector2(3.0f, -2.0f) * -2.0f);
}

TEST (Vector2_Test, Scale_Equals) {
    Vector2 v1 = Vector2(3.0f, 1.5f);

    v1 *= 2;

    EXPECT_EQ(Vector2(6.0f, 3.0f), v1);
}

TEST (Vector2_Test, NonUniformScale) {
    EXPECT_EQ(Vector2(0.0f, 0.0f), Vector2(2.0f, 2.0f) * Vector2::ZERO);
    EXPECT_EQ(Vector2(2.0f, 4.0f), Vector2(2.0f, 2.0f) * Vector2(1.0f, 2.0f));
    EXPECT_EQ(Vector2(4.0f, 2.0f), Vector2(2.0f, 4.0f) * Vector2(2.0f, 0.5f));
}

TEST (Vector2_Test, NonUniformScale_Equals) {
    Vector2 v1 = Vector2(3.0f, 1.5f);

    v1 *= Vector2(1.5f, 2.0f);

    EXPECT_EQ(Vector2(4.5f, 3.0f), v1);
}

TEST (Vector2_Test, Div) {
    EXPECT_EQ(Vector2(2.0f, 2.0f), Vector2(2.0f, 2.0f) / 1.0f);
    EXPECT_EQ(Vector2(1.0f, 0.75f), Vector2(2.0f, 1.5f) / 2.0f);
    EXPECT_EQ(Vector2(FMath::INFTY, FMath::INFTY), Vector2(3.0f, 2.0f) / 0.0f);
    EXPECT_EQ(Vector2(FMath::INFTY, -FMath::INFTY), Vector2(3.0f, -2.0f) / 0.0f);
}

TEST (Vector2_Test, Div_Equals) {
    Vector2 v1 = Vector2(3.0f, 1.5f);

    v1 /= 2;

    EXPECT_EQ(Vector2(1.5f, 0.75f), v1);
}

/*==========================
  Convenience Tests
 ==========================*/

TEST (Vector2_Test, Operator_Index) {
    Vector2 v = Vector2(10.0f, 5.0f);

    EXPECT_FLOAT_EQ(10.0f, v[0]);
    EXPECT_FLOAT_EQ(5.0f, v[1]);
}

TEST (Vector2_Test, Operator_Index_Set) {
    Vector2 v = Vector2(10.0f, 5.0f);

    v[0] = 2.0f;
    v[1] = 3.0f;

    EXPECT_FLOAT_EQ(2.0f, v[0]);
    EXPECT_FLOAT_EQ(3.0f, v[1]);
}
