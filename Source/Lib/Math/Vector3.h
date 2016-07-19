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
#ifndef __SGENGINE_VECTOR3_H_
#define __SGENGINE_VECTOR3_H_

namespace sge {

/**
 * 3D Vector. Implements math operations for 3D geometry vectors.
 */
class Vec3f {
public:
    /** Vec3 components. */
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

public:
    static const Vec3f ZERO;
    static const Vec3f ONE;
    static const Vec3f X;
    static const Vec3f Y;
    static const Vec3f Z;

public:
    /** Default Constructor. */
    Vec3f () = default;

    /** Fill Constructor. */
    explicit Vec3f (const float f) : x(f), y(f), z(f) { }

    /** Construct a Vec3f using x, y, z coordinates. */
    explicit Vec3f (const float xx, const float yy, const float zz)
        : x(xx), y(yy), z(zz) { }

    /** Value access using an index. */
    float operator[] (const u32 index) const;

    /** Reference access using an index. */
    float &operator[] (const u32 index);

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
     * Set the values of x, y, and z to 0.0f.
     * Destructive.
     */
    void Zero ();

    /**
     * Get the squared length of this Vec3f.
     * @return The Vector's Length squared
     */
    float LengthSqr () const;

    /**
     * Get the length of this Vec3f.
     * @return The Vector's length
     */
    float Length () const;

    /**
     * Set the length of a Vec3f, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess.
     * @param length The desired new length
     * @return New Vec3f with adjusted length
     */
    Vec3f SetLength (const float length) const;

    /**
     * Set the length of this Vec3f, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess.
     * Destructive.
     * @param length The desired new length
     */
    void SetLengthSelf (const float length);

    /**
     * Set the length of a Vec3f to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess.
     * @return New normalized Vec3f
     */
    Vec3f Normalize () const;

    /**
     * Set the length of this Vec3f to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess.
     * Destructive.
     */
    void NormalizeSelf ();

    /**
     * Return a new Vec3f which has been truncated if its length
     * exceeds the limit.
     * @param max Maximum length of Vec3f
     * @return New clamped Vec3f
     */
    Vec3f ClampLength (const float max) const;

    /**
     * Return a new Vec3f which has been truncated if its length
     * exceeds the limit.
     * @param min Minimum length of Vec3f
     * @param max Maximum length of Vec3f
     * @return New clamped Vec3f
     */
    Vec3f ClampLength (const float min, const float max) const;

    /**
     * Truncate this Vec3f if its length exceeds the limit.
     * Destructive.
     * @param max Maximum length of Vec3f
     */
    void ClampLengthSelf (const float max);

    /**
     * Truncate this Vec3f if its length exceeds the limit.
     * Destructive.
     * @param min Minimum length of Vec3f
     * @param max Maximum length of Vec3f
     */
    void ClampLengthSelf (const float min, const float max);

    /**
     * Clamp Vec3f within minimum and maximum bounds, given by other
     * Vec3f values.
     * Destructive.
     * @param min Vec3f minimum bound
     * @param max Vec3f maximum bound
     */
    void Clamp (const Vec3f &min, const Vec3f &max);

    /**
     * Return a copy of this Vec3f with the components negated.
     */
    Vec3f operator- () const;

    /**
     * Return a scaled copy of this Vec3f.
     * @param a Scale factor
     */
    Vec3f operator* (const float a) const;

    /**
     * Return a scaled copy of a Vec3f, reversed operands.
     * @param a Scale Factor
     * @param rhs Vec3f to be scaled
     */
    friend Vec3f operator* (const float a, const Vec3f &rhs);

    /**
     * Multiply this Vec3f by another Vec3f componentwise.
     * @return Result of Vec3f multiplication
     */
    Vec3f operator* (const Vec3f &rhs) const;

    /**
     * Add this Vec3f to another Vec3f.
     * @return Result of Vec3f addition
     */
    Vec3f operator+ (const Vec3f &rhs) const;

    /**
     * Subtract another Vec3f from this Vec3f.
     * @return Result of Vec3f subtraction
     */
    Vec3f operator- (const Vec3f &rhs) const;

    /**
     * Divide this Vec3f by a scalar value.
     * @param a Divisor
     * @return Result of Vec3f division
     */
    Vec3f operator/ (const float a) const;

    /**
     * Multiply and mutate this Vec3f with a scalar value.
     * Destructive.
     * @param Scale Factor
     */
    Vec3f &operator*= (const float a);

    /**
     * Multiply and mutate this Vec3f componentwise with another Vec3f.
     * Destructive.
     */
    Vec3f &operator*= (const Vec3f &rhs);

    /**
     * Add and mutate this Vec3f with another Vec3f.
     * Destructive.
     */
    Vec3f &operator+= (const Vec3f &rhs);

    /**
     * Subtract and mutate this Vec3f with another Vec3f.
     * Destructive.
     */
    Vec3f &operator-= (const Vec3f &rhs);

    /**
     * Divide and mutate this Vec3f by a scalar value.
     * Destructive.
     */
    Vec3f &operator/= (const float a);

    /**
     * Divide and mutate this Vec3f componentwise with another Vec3f.
     * Destructive.
     */
    Vec3f &operator/= (const Vec3f &rhs);

    /**
     * Return the dot product of this Vec3f and another Vec3f.
     * @return Vec3f Dot Product
     */
    float Dot (const Vec3f &rhs) const;

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
    Vec3f Cross (const Vec3f &rhs) const;

    /**
     * Return the mirror of this Vec3f about an arbitrary axis.
     * @param axis The axis of symmetry
     * @return Result of mirroring this Vec3f about axis
     */
    Vec3f Mirror (const Vec3f &axis) const;

    /**
     * Return the result of rotation this Vec3f by an angle around an
     * axis of rotation.
     * @param angle Angle of rotation in degrees
     * @param axis Axis of rotation as a Unit Vec3f
     * @return New rotated Vec3f
     */
    Vec3f Rotate (const float angle, const Vec3f &axis) const;

    /**
     * Return the result of rotation this Vec3f by an angle around an
     * axis of rotation.
     * Destructive.
     * @param angle Angle of rotation in degrees
     * @param axis Axis of rotation as a Unit Vec3f
     */
    void RotateSelf (const float angle, const Vec3f &axis);

    /** Swizzling */
    Vec2f xy () const;

    Vec2f xz () const;

    Vec2f yz () const;

    /**
     * Compare this Vec3f against another Vec3f exactly.
     * @return true if this Vec3f exactly equals the other, false otherwise
     */
    bool Compare (const Vec3f &other) const;

    /**
     * Compare this Vec3f against another Vec3f within a given tolerance.
     * @param threshold Tolerance within which Vec3f are considered equal
     * @return true if this Vec3f equals the other within given
     *         tolerance, false otherwise
     */
    bool Compare (const Vec3f &other, const float threshold) const;

    /**
     * Compare this Vec3f against another Vec3f exactly.
     * @return true if this Vec3f exactly equals the other, false otherwise
     */
    bool operator== (const Vec3f &other) const;

    /**
     * Compare this Vec3f against another Vec3f exactly.
     * @return true if this Vec3f does not equal the other, false otherwise
     */
    bool operator!= (const Vec3f &other) const;
};

// --------------------------------------------------------------------------

INLINE float Vec3f::operator[] (const u32 index) const {
    return (&x)[index];
}

INLINE float &Vec3f::operator[] (const u32 index) {
    return (&x)[index];
}

INLINE void Vec3f::Set (const float xx, const float yy, const float zz) {
    x = xx;
    y = yy;
    z = zz;
}

INLINE void Vec3f::Zero () {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

//==========================
// Vec3f Length Operators
//==========================

INLINE float Vec3f::LengthSqr () const {
    return x * x + y * y + z * z;
}

INLINE float Vec3f::Length () const {
    return sqrt(x * x + y * y + z * z);
}

INLINE Vec3f Vec3f::SetLength (const float length) const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return Vec3f(*this);
    } else {
        return *this * (length / currMag);
    }
}

INLINE void Vec3f::SetLengthSelf (const float length) {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this *= (length / currMag);
    }

}

INLINE Vec3f Vec3f::Normalize () const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return Vec3f(*this);
    } else {
        return *this / currMag;
    }
}

INLINE void Vec3f::NormalizeSelf () {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this /= currMag;
    }
}

INLINE Vec3f Vec3f::ClampLength (const float max) const {
    if (LengthSqr() > (max * max)) {
        return SetLength(max);
    }

    return Vec3f(*this);
}

INLINE Vec3f Vec3f::ClampLength (const float min, const float max) const {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        return SetLength(min);
    }

    if (ls > (max * max)) {
        return SetLength(max);
    }

    return Vec3f(*this);
}

INLINE void Vec3f::ClampLengthSelf (const float max) {
    if (LengthSqr() > (max * max)) {
        SetLengthSelf(max);
    }
}

INLINE void Vec3f::ClampLengthSelf (const float min, const float max) {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        SetLengthSelf(min);
    }

    if (ls > (max * max)) {
        SetLengthSelf(max);
    }
}

INLINE void Vec3f::Clamp (const Vec3f &min, const Vec3f &max) {
    x = FMath::ClampFloat(x, min.x, max.x);
    y = FMath::ClampFloat(y, min.y, max.y);
    z = FMath::ClampFloat(z, min.z, max.z);
}

//==========================
// Vec3f Operators
//==========================

INLINE Vec3f Vec3f::operator- () const {
    return Vec3f(-x, -y, -z);
}

INLINE Vec3f Vec3f::operator* (const float rhs) const {
    return Vec3f(x * rhs, y * rhs, z * rhs);
}

INLINE Vec3f operator* (const float a, const Vec3f &rhs) {
    return Vec3f(a * rhs.x, a * rhs.y, a * rhs.z);
}

INLINE Vec3f Vec3f::operator* (const Vec3f &rhs) const {
    return Vec3f(x * rhs.x, y * rhs.y, z * rhs.z);
}

INLINE Vec3f Vec3f::operator+ (const Vec3f &rhs) const {
    return Vec3f(x + rhs.x, y + rhs.y, z + rhs.z);
}

INLINE Vec3f Vec3f::operator- (const Vec3f &rhs) const {
    return Vec3f(x - rhs.x, y - rhs.y, z - rhs.z);
}

INLINE Vec3f Vec3f::operator/ (const float a) const {
    float inva = 1.0f / a;
    return Vec3f(x * inva, y * inva, z * inva);
}

INLINE Vec3f &Vec3f::operator*= (const float a) {
    x *= a;
    y *= a;
    z *= a;

    return *this;
}

INLINE Vec3f &Vec3f::operator*= (const Vec3f &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;

    return *this;
}

INLINE Vec3f &Vec3f::operator+= (const Vec3f &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
}

INLINE Vec3f &Vec3f::operator-= (const Vec3f &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;

    return *this;
}

INLINE Vec3f &Vec3f::operator/= (const float a) {
    float inva = 1.0f / a;
    x *= inva;
    y *= inva;
    z *= inva;

    return *this;
}

INLINE Vec3f &Vec3f::operator/= (const Vec3f &rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;

    return *this;
}

// Dot product.
INLINE float Vec3f::Dot (const Vec3f &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

// Vec3f Cross Product.
INLINE Vec3f Vec3f::Cross (const Vec3f &rhs) const {
    return Vec3f(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

INLINE Vec3f Vec3f::Mirror (const Vec3f &axis) const {
    return 2.0f * this->Dot(axis) * axis - *this;
}

INLINE Vec2f Vec3f::xy () const {
    return Vec2f(x, y);
}

INLINE Vec2f Vec3f::xz () const {
    return Vec2f(x, z);
}

INLINE Vec2f Vec3f::yz () const {
    return Vec2f(y, z);
}

//==========================
// Vec3f Comparison
//==========================

// This comparison may be inaccurate, prefer Compare(val, threshold)
// where possible.
INLINE bool Vec3f::Compare (const Vec3f &other) const {
    return x == other.x && y == other.y && z == other.z;
}

INLINE bool Vec3f::Compare (const Vec3f &other, const float threshold) const {
    if (fabs(x - other.x) > threshold)
        return false;
    if (fabs(y - other.y) > threshold)
        return false;
    if (fabs(z - other.z) > threshold)
        return false;

    return true;
}

INLINE bool Vec3f::operator== (const Vec3f &other) const {
    return Compare(other);
}

INLINE bool Vec3f::operator!= (const Vec3f &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_VECTOR3_H_ */
