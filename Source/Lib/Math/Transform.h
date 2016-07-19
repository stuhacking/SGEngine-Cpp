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
    Quat4f orientation;
    Vec3f scale;

public:
    /**
     * Create a new Transformation.
     */
    explicit Transform (const Vec3f &p_pos = Vec3f::ZERO,
                        const Quat4f &p_ori = Quat4f::IDENTITY,
                        const Vec3f &p_scale = Vec3f::ONE)
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
     * Return a Mat4f representing the translation component
     * of this Transform.
     */
    Mat4f GetTranslationMatrix () const;

    /**
     * Return a Mat4f representing the orientation/rotation component
     * of this Transform.
     */
    Mat4f GetOrientationMatrix () const;

    /**
     * Return a Mat4f representing the scale component of this
     * Transform.
     */
    Mat4f GetScaleMatrix () const;

    /**
     * Return a Mat4f representing complete model transformation
     * of this Transform.
     */
    Mat4f GetTransformationMatrix () const;

    /**
     * Return a Mat4f representing the view transformation (i.e.
     * components are applied in reverse order and the final Matrix is
     * inverted. Use this if you want to transform the camera/viewport.)
     */
    Mat4f GetViewTransformationMatrix () const;
};

// --------------------------------------------------------------------------

INLINE void Transform::Clear () {
    position = Vec3f::ZERO;
    orientation = Quat4f::IDENTITY;
    scale = Vec3f::ONE;
}

INLINE Vec3f Transform::Up () const {
    return orientation.Rotate(Vec3f::Y);
}

INLINE Vec3f Transform::Forward () const {
    return orientation.Rotate(Vec3f::Z);
}

INLINE Vec3f Transform::Right () const {
    return orientation.Rotate(Vec3f::X);
}

INLINE void Transform::Rotate (const Vec3f &axis, const float angle) {
    orientation *= Quat4f::AxisAngle(axis, angle);
    orientation.NormalizeSelf();
}

INLINE Mat4f Transform::GetTranslationMatrix () const {
    return Mat4f(1.0f,       0.0f,       0.0f,       0.0f,
                 0.0f,       1.0f,       0.0f,       0.0f,
                 0.0f,       0.0f,       1.0f,       0.0f,
                 position.x, position.y, position.z, 1.0f);
}

INLINE Mat4f Transform::GetOrientationMatrix () const {
    Vec3f u = Up();
    Vec3f f = Forward();
    Vec3f r = Right();

    return Mat4f(
        r.x,  r.y,  r.z, 0.0f,
        u.x,  u.y,  u.z, 0.0f,
        f.x,  f.y,  f.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
        );
}

INLINE Mat4f Transform::GetScaleMatrix () const {
    return Mat4f(scale.x, 0.0f,    0.0f,    0.0f,
                 0.0f,    scale.y, 0.0f,    0.0f,
                 0.0f,    0.0f,    scale.z, 0.0f,
                 0.0f,    0.0f,    0.0f,    1.0f);
}

INLINE Mat4f Transform::GetTransformationMatrix () const {
    return GetScaleMatrix() * GetOrientationMatrix() * GetTranslationMatrix();
}

INLINE Mat4f Transform::GetViewTransformationMatrix () const {
    return (GetTranslationMatrix() * GetOrientationMatrix() * GetScaleMatrix()).Inverse();
}

} /* namespace sge */

#endif /* __SGENGINE_TRANSFORM_H_ */
