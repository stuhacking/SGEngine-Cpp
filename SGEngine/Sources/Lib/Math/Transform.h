/*---  Transform.h - 3D Transformations Header  --------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Implements 3D translation/rotate/scale transforms.
 */
#ifndef __SHLIB_TRANSFORM_H_
#define __SHLIB_TRANSFORM_H_

namespace sge {

class Transform {
public:
    Vector3 position;
    Vector3 orientation; // Euler Angles
    Vector3 scale;

public:
    Transform (const Vector3 &p_pos = Vector3::ZERO,
               const Vector3 &p_ori = Vector3::ZERO,
               const Vector3 &p_scale = Vector3::ONE)
        : position(p_pos), scale(p_scale) { }

    Matrix4 GetTranslationMatrix () const;

    Matrix4 GetOrientationMatrix () const;

    Matrix4 GetScaleMatrix () const;

    Matrix4 GetTransformationMatrix () const;

    Matrix4 GetViewTransformationMatrix () const;
};

// --------------------------------------------------------------------------

inline Matrix4 Transform::GetTranslationMatrix () const {
    return Matrix4(1.0f,       0.0f,       0.0f,       0.0f,
                   0.0f,       1.0f,       0.0f,       0.0f,
                   0.0f,       0.0f,       1.0f,       0.0f,
                   position.x, position.y, position.z, 1.0f);
}

inline Matrix4 Transform::GetOrientationMatrix () const {
    float xx = TO_RADIANS(orientation.x);
    float yy = TO_RADIANS(orientation.y);
    float zz = TO_RADIANS(orientation.z);

    Matrix3 rot = Matrix3(
        std::cos(zz), -std::sin(zz), 0.0f,
        std::sin(zz), std::cos(zz), 0.0f,
        0.0f, 0.0f, 1.0f);
    rot = rot * Matrix3(
        std::cos(yy), 0.0f, -std::sin(yy),
        0.0f, 1.0f, 0.0f,
        std::sin(yy), 0.0f, std::cos(yy));
    rot = rot * Matrix3(
        1.0f, 0.0f, 0.0f,
        0.0f, std::cos(xx), std::sin(xx),
        0.0f, -std::sin(xx), std::cos(xx));

    return Matrix4(
        rot[0][0], rot[0][1], rot[0][2], 0.0f,
        rot[1][0], rot[1][1], rot[1][2], 0.0f,
        rot[2][0], rot[2][1], rot[2][2], 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
        );
}

inline Matrix4 Transform::GetScaleMatrix () const {
    return Matrix4(scale.x, 0.0f,    0.0f,    0.0f,
                   0.0f,    scale.y, 0.0f,    0.0f,
                   0.0f,    0.0f,    scale.z, 0.0f,
                   0.0f,    0.0f,    0.0f,    1.0f);
}

inline Matrix4 Transform::GetTransformationMatrix () const {
    return GetScaleMatrix() * GetOrientationMatrix() * GetTranslationMatrix();
}

inline Matrix4 Transform::GetViewTransformationMatrix () const {
    return (GetTranslationMatrix() * GetOrientationMatrix() * GetScaleMatrix()).Inverse();
}

} /* namespace sge */

#endif /* __SHLIB_TRANSFORM_H_ */
