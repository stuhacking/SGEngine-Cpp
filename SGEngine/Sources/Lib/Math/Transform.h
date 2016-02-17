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
    Vector3 position;
    Quaternion orientation;
    Vector3 scale;

public:
    Transform (const Vector3 &p_pos = Vector3::ZERO,
               const Quaternion &p_ori = Quaternion::IDENTITY,
               const Vector3 &p_scale = Vector3::ONE)
        : position(p_pos), orientation(p_ori), scale(p_scale) { }

    /**
     * Clear transformations on this Transform.
     * Destructive.
     */
    void Clear ();

    /**
     * Get the Local Up Vector.
     */
    Vector3 Up () const;
    
    /**
     * Get the Local Forward Vector.
     */
    Vector3 Forward () const;
    
    /**
     * Get the Local Right Vector.
     */
    Vector3 Right () const;

    void Rotate (const Vector3 &axis, const float angle);

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

inline void Transform::Clear () {
    position = Vector3::ZERO;
    orientation = Quaternion::IDENTITY;
    scale = Vector3::ONE;
}

inline Vector3 Transform::Up () const {
    return orientation.Rotate(Vector3::Y);
}

inline Vector3 Transform::Forward () const {
    return orientation.Rotate(Vector3::Z);
}

inline Vector3 Transform::Right () const {
    return orientation.Rotate(Vector3::X);
}

inline void Transform::Rotate (const Vector3 &axis, const float angle) {
    orientation *= Quaternion::AxisAngle(axis, TO_RADIANS(angle));
}

inline Matrix4 Transform::GetTranslationMatrix () const {
    return Matrix4(1.0f,       0.0f,       0.0f,       0.0f,
                   0.0f,       1.0f,       0.0f,       0.0f,
                   0.0f,       0.0f,       1.0f,       0.0f,
                   position.x, position.y, position.z, 1.0f);
}

inline Matrix4 Transform::GetOrientationMatrix () const {
    Vector3 u = Up();
    Vector3 f = Forward();
    Vector3 r = Right();

    return Matrix4(
        r.x,  r.y,  r.z, 0.0f,
        u.x,  u.y,  u.z, 0.0f,
        f.x,  f.y,  f.z, 0.0f,
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

#endif /* __SGENGINE_TRANSFORM_H_ */
