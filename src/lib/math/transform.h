/**--  Transform.h - 3D Transformations Header  --------------------*- C++ -*---
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
#ifndef __SGE_TRANSFORM_H
#define __SGE_TRANSFORM_H

class Transform {
public:
    Vec3f position;
    Quat4f orientation;
    Vec3f scale;

public:
    /**
     * Create a new Transformation.
     */
    explicit Transform (const Vec3f &p_pos = Vec3f_Zero,
                        const Quat4f &p_ori = Quat4f_Identity,
                        const Vec3f &p_scale = Vec3f_One)
          : position(p_pos), orientation(p_ori), scale(p_scale) { }

    /**
     * Clear transformations on this Transform.
     * Destructive.
     */
    void reset ();

    /**
     * Get the Local Up Vector.
     */
    Vec3f up () const;

    /**
     * Get the Local Forward Vector.
     */
    Vec3f forward () const;

    /**
     * Get the Local Right Vector.
     */
    Vec3f right () const;

    /**
     * Rotate this transform by angles in radians about
     * an axis in Local Space.
     * Destructive.
     */
    void rotateL (const float angle, const Vec3f &axis);

    /**
     * Rotate this transform by angles in radians about
     * an axis in World Space.
     * Destructive.
     */
    void rotateW (const float angle, const Vec3f &axis);

    /**
     * Return a Mat4f representing the translation component
     * of this Transform.
     */
    Mat4f translationMatrix () const;

    /**
     * Return a Mat4f representing the orientation/rotation component
     * of this Transform.
     */
    Mat4f orientationMatrix () const;

    /**
     * Return a Mat4f representing the scale component of this
     * Transform.
     */
    Mat4f scaleMatrix () const;

    /**
     * Return a Mat4f representing complete model transformation
     * of this Transform.
     */
    Mat4f transformationMatrix () const;

    /**
     * Return a Mat4f representing the view transformation (i.e.
     * components are applied in reverse order and the final Matrix is
     * inverted. Use this if you want to transform the camera/viewport.)
     */
    Mat4f viewTransformationMatrix () const;
};

// --------------------------------------------------------------------------

inline void Transform::reset () {
    position = Vec3f_Zero;
    orientation = Quat4f_Identity;
    scale = Vec3f_One;
}

inline Vec3f Transform::up () const {
    return orientation.rotate(Vec3f_Y);
}

inline Vec3f Transform::forward () const {
    return orientation.rotate(Vec3f_Z);
}

inline Vec3f Transform::right () const {
    return orientation.rotate(Vec3f_X);
}

inline void Transform::rotateL (const float angle, const Vec3f &axis) {
    orientation *= Quat4f(angle, axis);
    orientation.normalizeSelf();
}

inline void Transform::rotateW (const float angle, const Vec3f &axis) {
    orientation = Quat4f(angle, axis) * orientation;
    orientation.normalizeSelf();
}

inline Mat4f Transform::translationMatrix () const {
    return Mat4f(1.0f,       0.0f,       0.0f,       0.0f,
                 0.0f,       1.0f,       0.0f,       0.0f,
                 0.0f,       0.0f,       1.0f,       0.0f,
                 position.x, position.y, position.z, 1.0f);
}

inline Mat4f Transform::orientationMatrix () const {
    Vec3f u = up();
    Vec3f f = forward();
    Vec3f r = right();

    return Mat4f(
        r.x,  r.y,  r.z,  0.0f,
        u.x,  u.y,  u.z,  0.0f,
        f.x,  f.y,  f.z,  0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
        );
}

inline Mat4f Transform::scaleMatrix () const {
    return Mat4f(scale.x, 0.0f,    0.0f,    0.0f,
                 0.0f,    scale.y, 0.0f,    0.0f,
                 0.0f,    0.0f,    scale.z, 0.0f,
                 0.0f,    0.0f,    0.0f,    1.0f);
}

inline Mat4f Transform::transformationMatrix () const {
    return translationMatrix() * orientationMatrix() * scaleMatrix();
}

inline Mat4f Transform::viewTransformationMatrix () const {
    return transformationMatrix().inverse();
}

#endif /* __SGE_TRANSFORM_H */
