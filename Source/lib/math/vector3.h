/*---  Vector3.h - 3D Vector Header  -------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level Vec3 type.
 */
#ifndef __SGE_VECTOR3_H
#define __SGE_VECTOR3_H

#include <cfloat>

/**
 * 3D Vector. Implements math operations for 3D geometry vectors.
 */
class Vec3f {
public:
    float x = 0; /**< x coordinate. */
    float y = 0; /**< y coordinate. */
    float z = 0; /**< z coordinate. */

public:
    /** Default Constructor. */
    Vec3f () = default;

    /** Fill Constructor. */
    explicit Vec3f (const float f)
          : x(f), y(f), z(f) { }

    /** Construct a Vec3f using x, y, z coordinates. */
    explicit Vec3f (const float xx, const float yy, const float zz)
          : x(xx), y(yy), z(zz) { }

    /** Value access using an index. */
    float operator[] (const std::size_t index) const { return (&x)[index]; }

    /** Reference access using an index. */
    float &operator[] (const std::size_t index) { return (&x)[index]; }

    /**
     * Set the values of x, y, and z to 0.0f.
     * Destructive.
     */
    void zero () { x = y = z = 0; }

    /**
     * Set the values of x, y, and z.
     * Destructive.
     *
     * @param xx The X component
     * @param yy The Y component
     * @param zz The Z component
     */
    void Set (const float xx, const float yy, const float zz);

    /**
     * Get the squared magnitude of this Vec3f.
     *
     * @return The Vector's magnitude squared
     */
    float magSq () const;

    /**
     * Get the magnitude of this Vec3f.
     *
     * @return The Vector's magnitude
     */
    float mag () const;

    /**
     * Set the magnitude of a Vec3f, maintaining direction. If the
     * magnitude is currently 0.0f then we don't attempt to guess.
     *
     * @param pMag The desired new magnitude
     * @return New Vec3f with adjusted magnitude
     */
    Vec3f setMag (const float pMag) const;

    /**
     * Set the magnitude of this Vec3f, maintaining direction. If the
     * magnitude is currently 0.0f then we don't attempt to guess.
     * Destructive.
     *
     * @param pMag The desired new magnitude
     */
    void setMagSelf (const float pMag);

    /**
     * Set the magnitude of a Vec3f to 1.0f, maintaining direction. If
     * the current magnitude is 0.0f then we don't attempt to guess.
     *
     * @return New normalized Vec3f
     */
    Vec3f normalize () const;

    /**
     * Set the magnitude of this Vec3f to 1.0f, maintaining direction. If
     * the current magnitude is 0.0f then we don't attempt to guess.
     * Destructive.
     */
    void normalizeSelf ();

    /**
     * Return a new Vec3f which has been truncated if its magnitude
     * exceeds the limit.
     *
     * @param max Maximum magnitude of Vec3f
     * @return New clamped Vec3f
     */
    Vec3f clampMag (const float max) const;

    /**
     * Return a new Vec3f which has been truncated if its magnitude
     * exceeds the limit.
     *
     * @param min Minimum magnitude of Vec3f
     * @param max Maximum magnitude of Vec3f
     * @return New clamped Vec3f
     */
    Vec3f clampMag (const float min, const float max) const;

    /**
     * Truncate this Vec3f if its magnitude exceeds the limit.
     * Destructive.
     *
     * @param max Maximum magnitude of Vec3f
     */
    void clampMagSelf (const float max);

    /**
     * Truncate this Vec3f if its magnitude exceeds the limit.
     * Destructive.
     *
     * @param min Minimum magnitude of Vec3f
     * @param max Maximum magnitude of Vec3f
     */
    void clampMagSelf (const float min, const float max);

    /**
     * Clamp Vec3f within minimum and maximum bounds, given by other
     * Vec3f values.
     *
     * @param min Vec3f minimum bound
     * @param max Vec3f maximum bound
     */
    Vec3f clamp (const Vec3f &min, const Vec3f &max) const;

    /**
     * Clamp Vec3f within minimum and maximum bounds, given by other
     * Vec3f values.
     * Destructive.
     *
     * @param min Vec3f minimum bound
     * @param max Vec3f maximum bound
     */
    void clampSelf (const Vec3f &min, const Vec3f &max);

    /**
     * Return the dot product of this Vec3f and another Vec3f.
     *
     * @return Vec3f Dot Product
     */
    float dot (const Vec3f &rhs) const;

    /**
     * Return the cross product of this Vec3f and another Vec3f. The
     * resulting Vec3f is perpendicular to A and B.
     *
     *    AxB
     *     ^
     *     |  B
     *     | /
     *     |/
     *     +--------> A
     *     |
     *     v
     *    BxA
     *
     * @return Vec2f Cross Product
     */
    Vec3f cross (const Vec3f &rhs) const;

    /**
     * Return the mirror of this Vec3f about an arbitrary axis.
     *
     * @param axis The axis of symmetry
     * @return Result of mirroring this Vec3f about axis
     */
    Vec3f mirror (const Vec3f &axis) const;

    /**
     * Return the result of rotation this Vec3f by an angle around an
     * axis of rotation.
     *
     * @param angle Angle of rotation in degrees
     * @param axis Axis of rotation as a Unit Vec3f
     * @return New rotated Vec3f
     */
    Vec3f rotate (const float angle, const Vec3f &axis) const;

    /**
     * Return the result of rotation this Vec3f by an angle around an
     * axis of rotation.
     * Destructive.
     *
     * @param angle Angle of rotation in degrees
     * @param axis Axis of rotation as a Unit Vec3f
     */
    void rotateSelf (const float angle, const Vec3f &axis);

    static Vec3f random (const s32 seed);

    /** Swizzling */
    Vec2f xy () const { return Vec2f(x, y); }
    Vec2f xz () const { return Vec2f(x, z); }
    Vec2f yz () const { return Vec2f(y, z); }

    /**
     * Compare this Vec3f against another Vec3f.
     *
     * @return true if this Vec3f equals the other, false otherwise.
     */
    bool compare (const Vec3f &other) const;

    /**
     * Compare this Vec3f against another Vec3f within a given tolerance.
     *
     * @param threshold Tolerance within which Vec3f are considered equal
     * @return true if this Vec3f equals the other within given
     *         tolerance, false otherwise
     */
    bool compare (const Vec3f &other, const float threshold) const;

};

extern const Vec3f Vec3f_Zero;
extern const Vec3f Vec3f_One;
extern const Vec3f Vec3f_X;
extern const Vec3f Vec3f_Y;
extern const Vec3f Vec3f_Z;

// --------------------------------------------------------------------------

inline void Vec3f::Set (const float xx, const float yy, const float zz) {
    x = xx;
    y = yy;
    z = zz;
}

//==========================
// Vec3f Operators
//==========================

/** Negate. */
inline Vec3f operator- (const Vec3f &v) {
    return Vec3f(-v.x, -v.y, -v.z);
}

/** Multiply by scalar. */
inline Vec3f operator* (const Vec3f &v, const float a) {
    return Vec3f(a * v.x, a * v.y, a * v.z);
}

/** Multiply by scalar. */
inline Vec3f operator* (const float a, const Vec3f &v) {
    return Vec3f(a * v.x, a * v.y, a * v.z);
}

/** Piecewise multiplication. */
inline Vec3f operator* (const Vec3f &a, const Vec3f &b) {
    return Vec3f(a.x * b.x, a.y * b.y, a.z * b.z);
}

/** Addition. */
inline Vec3f operator+ (const Vec3f &a, const Vec3f &b) {
    return Vec3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

/** Subtraction. */
inline Vec3f operator- (const Vec3f &a, const Vec3f &b) {
    return Vec3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

/** Division. */
inline Vec3f operator/ (const Vec3f &v, const float a) {
    float inva = 1.0f / a;
    return Vec3f(v.x * inva, v.y * inva, v.z * inva);
}

/** Multiply by scalar in place. */
inline Vec3f& operator*= (Vec3f &v, const float a) {
    v.x *= a;
    v.y *= a;
    v.z *= a;

    return v;
}

/** Piecewise multiplication in place. */
inline Vec3f& operator*= (Vec3f &a, const Vec3f &b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;

    return a;
}

/** Addition in place. */
inline Vec3f& operator+= (Vec3f &a, const Vec3f &b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;

    return a;
}

/** Subtraction in place. */
inline Vec3f& operator-= (Vec3f &a, const Vec3f &b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;

    return a;
}

/** Division in place. */
inline Vec3f& operator/= (Vec3f &v, const float a) {
    float inva = 1.0f / a;
    v.x *= inva;
    v.y *= inva;
    v.z *= inva;

    return v;
}

/** Piecewise division in place. */
inline Vec3f& operator/= (Vec3f &a, const Vec3f &b) {
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;

    return a;
}

//==========================
// Vec3f Length Operators
//==========================

inline float Vec3f::magSq () const {
    return x * x + y * y + z * z;
}

inline float Vec3f::mag () const {
    return sqrt(x * x + y * y + z * z);
}

inline Vec3f Vec3f::setMag (const float pMag) const {
    float currMag = mag();
    if (currMag == 0.0f) {
        return *this;
    }

    return *this * (pMag / currMag);
}

inline void Vec3f::setMagSelf (const float pMag) {
    float currMag = mag();
    if (currMag != 0.0f) {
        *this *= (pMag / currMag);
    }

}

inline Vec3f Vec3f::normalize () const {
    float currMag = mag();
    if (currMag == 0.0f) {
        return *this;
    }

    return *this / currMag;
}

inline void Vec3f::normalizeSelf () {
    float currMag = mag();
    if (currMag != 0.0f) {
        *this /= currMag;
    }
}

inline Vec3f Vec3f::clampMag (const float max) const {
    if (magSq() > (max * max)) {
        return setMag(max);
    }

    return *this;
}

inline Vec3f Vec3f::clampMag (const float min, const float max) const {
    float ls = magSq();

    if (ls < (min * min)) {
        return setMag(min);
    }

    if (ls > (max * max)) {
        return setMag(max);
    }

    return *this;
}

inline void Vec3f::clampMagSelf (const float max) {
    if (magSq() > (max * max)) {
        setMagSelf(max);
    }
}

inline void Vec3f::clampMagSelf (const float min, const float max) {
    float ls = magSq();

    if (ls < (min * min)) {
        setMagSelf(min);
    }

    if (ls > (max * max)) {
        setMagSelf(max);
    }
}

inline Vec3f Vec3f::clamp (const Vec3f &min, const Vec3f &max) const {
    return Vec3f(math::clampFloat(x, min.x, max.x),
                 math::clampFloat(y, min.y, max.y),
                 math::clampFloat(z, min.z, max.z));
}

inline void Vec3f::clampSelf (const Vec3f &min, const Vec3f &max) {
    x = math::clampFloat(x, min.x, max.x);
    y = math::clampFloat(y, min.y, max.y);
    z = math::clampFloat(z, min.z, max.z);
}

// Dot product.
inline float Vec3f::dot (const Vec3f &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

// Vec3f Cross Product.
inline Vec3f Vec3f::cross (const Vec3f &rhs) const {
    return Vec3f(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z,
                 x * rhs.y - y * rhs.x);
}

inline Vec3f Vec3f::mirror (const Vec3f &axis) const {
    return 2.0f * this->dot(axis) * axis - *this;
}

//==========================
// Vec3f Comparison
//==========================

inline bool Vec3f::compare (const Vec3f &other) const {
    return x == other.x && y == other.y && z == other.z;
}

inline bool Vec3f::compare (const Vec3f &other, const float threshold) const {
    return (fabsf(x - other.x) <= threshold) &&
           (fabsf(y - other.y) <= threshold) &&
           (fabsf(z - other.z) <= threshold);
}

inline bool operator== (const Vec3f &a, const Vec3f &b) {
    return a.compare(b);
}

inline bool operator!= (const Vec3f &a, const Vec3f &b) {
    return !a.compare(b);
}

#endif /* __SGE_VECTOR3_H */
