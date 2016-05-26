//
// Transformations Tests
//
#include <gtest/gtest.h>

#include "Lib.h"

using sge::Vec3f;
using sge::Vec4f;
using sge::Mat4f;
using sge::Transform;

// Helper: Apply transform to position vector3
static Vec3f apply_transform_position (const Transform &tr, const Vec3f &v_in) {
    Mat4f M = tr.GetTransformationMatrix();
    Vec4f v = Vec4f(v_in, 1.0f);
    Vec4f result = M * v;

    return result.xyz();
}

// Helper: Apply transform to direction vector3
static Vec3f apply_transform_direction (const Transform &tr, const Vec3f &v_in) {
    Mat4f M = tr.GetTransformationMatrix();
    Vec4f v = Vec4f(v_in, 0.0f);
    Vec4f result = M * v;

    return result.xyz();
}

TEST (Transform_Test, Translation_Matrix) {
    Transform t = Transform();
    t.position = Vec3f(1.0f, 2.0f, 3.0f);

    Mat4f m = t.GetTranslationMatrix();

    EXPECT_EQ(Vec4f(5.0f, 6.0f, 7.0f, 1.0f), m * Vec4f(4.0f, 4.0f, 4.0f, 1.0f));
    EXPECT_EQ(Vec4f(4.0f, 4.0f, 4.0f, 0.0f), m * Vec4f(4.0f, 4.0f, 4.0f, 0.0f));
}

TEST (Transform_Test, Scale_Matrix) {
    Transform t = Transform();
    t.scale = Vec3f(0.5f, 2.0f, 3.0f);

    Mat4f m = t.GetScaleMatrix();

    EXPECT_EQ(Vec4f(2.0f, 4.0f, 3.0f, 1.0f), m * Vec4f(4.0f, 2.0f, 1.0f, 1.0f));
    EXPECT_EQ(Vec4f(2.0f, 8.0f, 12.0f, 0.0f), m * Vec4f(4.0f, 4.0f, 4.0f, 0.0f));
}

TEST (Transform_Test, No_Transform) {
    Vec3f v = sge::Vec3f::ZERO;

    EXPECT_EQ(v, apply_transform_position(Transform(), v));
    EXPECT_EQ(v, apply_transform_direction(Transform(), v));
}

TEST (Transform_Test, Clear_Transform) {
    Vec3f v = sge::Vec3f::ZERO;
    Transform t = Transform();
    t.position += Vec3f(2.0f, 2.0f, 2.0f);

    EXPECT_EQ(Vec3f(2.0f, 2.0f, 2.0f), apply_transform_position(t, v));
    EXPECT_EQ(sge::Vec3f::ZERO, apply_transform_direction(t, v));

    t.Clear();

    EXPECT_EQ(sge::Vec3f::ZERO, apply_transform_position(t, v));
    EXPECT_EQ(sge::Vec3f::ZERO, apply_transform_direction(t, v));
}
