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
#ifndef __SGENGINE_TRANSFORM_H_
#define __SGENGINE_TRANSFORM_H_

namespace sge {

class Transform {
public:
    Vec3f position;
    Quaternion orientation;
    Vec3f scale;

public:
    Transform (const Vec3f &p_pos = VEC3F_ZERO,
               const Quaternion &p_ori = Quaternion::IDENTITY,
               const Vec3f &p_scale = VEC3F_ONE)
        : position(p_pos), orientation(p_ori), scale(p_scale) { }

    /**
     * Clear transformations on this Transform.
     * Destructive.
     */
    void Clear ();

    /**
     * Get the Local Up Vector.
     */
    Vec3f Up () const;

    /**
     * Get the Local Forward Vector.
     */
    Vec3f Forward () const;

    /**
     * Get the Local Right Vector.
     */
    Vec3f Right () const;

    /**
     * Rotate this transform by angles in radians about
     * axis.
     * Destructive.
     */
    void Rotate (const Vec3f &axis, const float angle);

    /**
     * Return a Matrix4 representing the translation component
     * of this Transform.
     */
    Matrix4 GetTranslationMatrix () const;

    /**
     * Return a Matrix4 representing the orientation/rotation component
     * of this Transform.
     */
    Matrix4 GetOrientationMatrix () const;

    /**
     * Return a Matrix4 representing the scale component of this
     * Transform.
     */
    Matrix4 GetScaleMatrix () const;

    /**
     * Return a Matrix4 representing complete model transformation
     * of this Transform.
     */
    Matrix4 GetTransformationMatrix () const;

    /**
     * Return a Matrix4 representing the view transformation (i.e.
     * components are applied in reverse order and the final Matrix is
     * inverted. Use this if you want to transform the camera/viewport.)
     */
    Matrix4 GetViewTransformationMatrix () const;
};

// --------------------------------------------------------------------------

INLINE void Transform::Clear () {
    position = VEC3F_ZERO;
    orientation = Quaternion::IDENTITY;
    scale = VEC3F_ONE;
}

INLINE Vec3f Transform::Up () const {
    return orientation.Rotate(VEC3F_Y);
}

INLINE Vec3f Transform::Forward () const {
    return orientation.Rotate(VEC3F_Z);
}

INLINE Vec3f Transform::Right () const {
    return orientation.Rotate(VEC3F_X);
}

INLINE void Transform::Rotate (const Vec3f &axis, const float angle) {
    orientation *= Quaternion::AxisAngle(axis, angle);
    orientation.NormalizeSelf();
}

INLINE Matrix4 Transform::GetTranslationMatrix () const {
    return Matrix4(1.0f,       0.0f,       0.0f,       0.0f,
                   0.0f,       1.0f,       0.0f,       0.0f,
                   0.0f,       0.0f,       1.0f,       0.0f,
                   position.x, position.y, position.z, 1.0f);
}

INLINE Matrix4 Transform::GetOrientationMatrix () const {
    Vec3f u = Up();
    Vec3f f = Forward();
    Vec3f r = Right();

    return Matrix4(
        r.x,  r.y,  r.z, 0.0f,
        u.x,  u.y,  u.z, 0.0f,
        f.x,  f.y,  f.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
        );
}

INLINE Matrix4 Transform::GetScaleMatrix () const {
    return Matrix4(scale.x, 0.0f,    0.0f,    0.0f,
                   0.0f,    scale.y, 0.0f,    0.0f,
                   0.0f,    0.0f,    scale.z, 0.0f,
                   0.0f,    0.0f,    0.0f,    1.0f);
}

INLINE Matrix4 Transform::GetTransformationMatrix () const {
    return GetScaleMatrix() * GetOrientationMatrix() * GetTranslationMatrix();
}

INLINE Matrix4 Transform::GetViewTransformationMatrix () const {
    return (GetTranslationMatrix() * GetOrientationMatrix() * GetScaleMatrix()).Inverse();
}

} /* namespace sge */

#endif /* __SGENGINE_TRANSFORM_H_ */
