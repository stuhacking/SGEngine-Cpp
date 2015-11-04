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
    Quaternion orientation;
    Vector3 scale;

public:
    Transform (const Vector3 &p_pos = Vector3::ZERO,
               const Quaternion &p_ori = Quaternion::IDENTITY,
               const Vector3 &p_scale = Vector3::ONE)
        : position(p_pos), scale(p_scale) { }

    Matrix4 GetTranslationMatrix () const;

    Matrix4 GetOrientationMatrix () const;

    Matrix4 GetScaleMatrix () const;

    Matrix4 GetTransformationMatrix () const;
};

// --------------------------------------------------------------------------
    
inline Matrix4 Transform::GetTranslationMatrix () const {
    return Matrix4(1.0f,       0.0f,       0.0f,       0.0f,
                   0.0f,       1.0f,       0.0f,       0.0f,
                   0.0f,       0.0f,       1.0f,       0.0f,
                   position.x, position.y, position.z, 1.0f);
}

inline Matrix4 Transform::GetOrientationMatrix () const {
    return Matrix4::IDENTITY;
}

inline Matrix4 Transform::GetScaleMatrix () const {
    return Matrix4(scale.x, 0.0f,    0.0f,    0.0f,
                   0.0f,    scale.y, 0.0f,    0.0f,
                   0.0f,    0.0f,    scale.z, 0.0f,
                   0.0f,    0.0f,    0.0f,    1.0f);
}

inline Matrix4 Transform::GetTransformationMatrix () const {
    return Matrix4(scale.x,    0.0f,       0.0f,       0.0f,
                   0.0f,       scale.y,    0.0f,       0.0f,
                   0.0f,       0.0f,       scale.z,    0.0f,
                   position.x, position.y, position.z, 1.0f);
}

} /* namespace sge */

#endif /* __SHLIB_TRANSFORM_H_ */
