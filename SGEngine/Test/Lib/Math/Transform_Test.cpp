//
// Transformations Tests
//
#include <gtest/gtest.h>

#include "Lib.h"

using sge::Vector3;
using sge::Vector4;
using sge::Matrix4;
using sge::Transform;

// Helper: Apply transform to position vector3
static Vector3 apply_transform_position (const Transform &tr, const Vector3 &v_in) {
    Matrix4 M = tr.GetTransformationMatrix();
    Vector4 v = Vector4(v_in, 1.0f);
    Vector4 result = M * v;

    return result.xyz();
}

// Helper: Apply transform to direction vector3
static Vector3 apply_transform_direction (const Transform &tr, const Vector3 &v_in) {
    Matrix4 M = tr.GetTransformationMatrix();
    Vector4 v = Vector4(v_in, 0.0f);
    Vector4 result = M * v;

    return result.xyz();
}

TEST (Transform_Test, Translation_Matrix) {
    Transform t = Transform();
    t.position = Vector3(1.0f, 2.0f, 3.0f);

    Matrix4 m = t.GetTranslationMatrix();

    EXPECT_EQ(Vector4(5.0f, 6.0f, 7.0f, 1.0f), m * Vector4(4.0f, 4.0f, 4.0f, 1.0f));
    EXPECT_EQ(Vector4(4.0f, 4.0f, 4.0f, 0.0f), m * Vector4(4.0f, 4.0f, 4.0f, 0.0f));
}

TEST (Transform_Test, Scale_Matrix) {
    Transform t = Transform();
    t.scale = Vector3(0.5f, 2.0f, 3.0f);

    Matrix4 m = t.GetScaleMatrix();

    EXPECT_EQ(Vector4(2.0f, 4.0f, 3.0f, 1.0f), m * Vector4(4.0f, 2.0f, 1.0f, 1.0f));
    EXPECT_EQ(Vector4(2.0f, 8.0f, 12.0f, 0.0f), m * Vector4(4.0f, 4.0f, 4.0f, 0.0f));
}

TEST (Transform_Test, No_Transform) {
    Vector3 v = Vector3::ZERO;

    EXPECT_EQ(v, apply_transform_position(Transform(), v));
    EXPECT_EQ(v, apply_transform_direction(Transform(), v));
}

TEST (Transform_Test, Clear_Transform) {
    Vector3 v = Vector3::ZERO;
    Transform t = Transform();
    t.position += Vector3(2.0f, 2.0f, 2.0f);

    EXPECT_EQ(Vector3(2.0f, 2.0f, 2.0f), apply_transform_position(t, v));
    EXPECT_EQ(Vector3::ZERO, apply_transform_direction(t, v));

    t.Clear();

    EXPECT_EQ(Vector3::ZERO, apply_transform_position(t, v));
    EXPECT_EQ(Vector3::ZERO, apply_transform_direction(t, v));
}
