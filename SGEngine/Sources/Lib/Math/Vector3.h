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

#include <cmath> // fabs

namespace sge {

/**
 * 3D Vector. Implements math operations for 3D geometry vectors.
 */
template <typename T>
class Vec3_T {
public:
    /** Vec3 components. */
    T x, y, z;

public:
    /** Construct a default Vec3_T at origin. */
             Vec3_T () : x(0), y(0), z(0) { }

    /** Fill Constructor. */
    explicit Vec3_T (const T f) : x(f), y(f), z(f) { }

    /** Construct a Vec3_T using x, y, z coordinates. */
    explicit Vec3_T (const T xx, const T yy, const T zz)
        : x(xx), y(yy), z(zz) { }

    /** Value access using an index. */
    T operator[] (const u32 index) const;

    /** Reference access using an index. */
    T &operator[] (const u32 index);

    /**
     * Set the values of x, y, and z.
     * Destructive.
     *
     * @param xx The X component
     * @param yy The Y component
     * @param zz The Z component
     */
    void Set (const T xx, const T yy, const T zz);

    /**
     * Set the values of x, y, and z to 0.0f.
     * Destructive.
     */
    void Zero ();

    /**
     * Get the squared length of this Vec3_T.
     * @return The Vector's Length squared
     */
    T LengthSqr () const;

    /**
     * Get the length of this Vec3_T.
     * @return The Vector's length
     */
    T Length () const;

    /**
     * Set the length of a Vec3_T, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess.
     * @param length The desired new length
     * @return New Vec3_T with adjusted length
     */
    Vec3_T SetLength (const T length) const;

    /**
     * Set the length of this Vec3_T, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess.
     * Destructive.
     * @param length The desired new length
     */
    void SetLengthSelf (const T length);

    /**
     * Set the length of a Vec3_T to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess.
     * @return New normalized Vec3_T
     */
    Vec3_T Normalize () const;

    /**
     * Set the length of this Vec3_T to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess.
     * Destructive.
     */
    void NormalizeSelf ();

    /**
     * Return a new Vec3_T which has been truncated if its length
     * exceeds the limit.
     * @param max Maximum length of Vec3_T
     * @return New clamped Vec3_T
     */
    Vec3_T ClampLength (const T max) const;

    /**
     * Return a new Vec3_T which has been truncated if its length
     * exceeds the limit.
     * @param min Minimum length of Vec3_T
     * @param max Maximum length of Vec3_T
     * @return New clamped Vec3_T
     */
    Vec3_T ClampLength (const T min, const T max) const;

    /**
     * Truncate this Vec3_T if its length exceeds the limit.
     * Destructive.
     * @param max Maximum length of Vec3_T
     */
    void ClampLengthSelf (const T max);

    /**
     * Truncate this Vec3_T if its length exceeds the limit.
     * Destructive.
     * @param min Minimum length of Vec3_T
     * @param max Maximum length of Vec3_T
     */
    void ClampLengthSelf (const T min, const T max);

    /**
     * Clamp Vec3_T within minimum and maximum bounds, given by other
     * Vec3_T values.
     * Destructive.
     * @param min Vec3_T minimum bound
     * @param max Vec3_T maximum bound
     */
    void Clamp (const Vec3_T &min, const Vec3_T &max);

    /**
     * Return a copy of this Vec3_T with the components negated.
     */
    Vec3_T operator- () const;

    /**
     * Return a scaled copy of this Vec3_T.
     * @param a Scale factor
     */
    Vec3_T operator* (const T a) const;

    /**
     * Return a scaled copy of a Vec3_T, reversed operands.
     * @param a Scale Factor
     * @param rhs Vec3_T to be scaled
     */
    template <typename U>
    friend Vec3_T<U> operator* (const T a, const Vec3_T<U> &rhs);

    /**
     * Multiply this Vec3_T by another Vec3_T componentwise.
     * @return Result of Vec3_T multiplication
     */
    Vec3_T operator* (const Vec3_T &rhs) const;

    /**
     * Add this Vec3_T to another Vec3_T.
     * @return Result of Vec3_T addition
     */
    Vec3_T operator+ (const Vec3_T &rhs) const;

    /**
     * Subtract another Vec3_T from this Vec3_T.
     * @return Result of Vec3_T subtraction
     */
    Vec3_T operator- (const Vec3_T &rhs) const;

    /**
     * Divide this Vec3_T by a scalar value.
     * @param a Divisor
     * @return Result of Vec3_T division
     */
    Vec3_T operator/ (const T a) const;

    /**
     * Multiply and mutate this Vec3_T with a scalar value.
     * Destructive.
     * @param Scale Factor
     */
    Vec3_T &operator*= (const T a);

    /**
     * Multiply and mutate this Vec3_T componentwise with another Vec3_T.
     * Destructive.
     */
    Vec3_T &operator*= (const Vec3_T &rhs);

    /**
     * Add and mutate this Vec3_T with another Vec3_T.
     * Destructive.
     */
    Vec3_T &operator+= (const Vec3_T &rhs);

    /**
     * Subtract and mutate this Vec3_T with another Vec3_T.
     * Destructive.
     */
    Vec3_T &operator-= (const Vec3_T &rhs);

    /**
     * Divide and mutate this Vec3_T by a scalar value.
     * Destructive.
     */
    Vec3_T &operator/= (const T a);

    /**
     * Divide and mutate this Vec3_T componentwise with another Vec3_T.
     * Destructive.
     */
    Vec3_T &operator/= (const Vec3_T &rhs);

    /**
     * Return the dot product of this Vec3_T and another Vec3_T.
     * @return Vec3_T Dot Product
     */
    T Dot (const Vec3_T &rhs) const;

    /**
     * Return the cross product of this Vec3_T and another Vec3_T. The
     * resulting Vec3_T is perpendicular to A and B.
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
    Vec3_T Cross (const Vec3_T &rhs) const;

    /**
     * Return the mirror of this Vec3_T about an arbitrary axis.
     * @param axis The axis of symmetry
     * @return Result of mirroring this Vec3_T about axis
     */
    Vec3_T Mirror (const Vec3_T &axis) const;

    /**
     * Return the result of rotation this Vec3_T by an angle around an
     * axis of rotation.
     * @param angle Angle of rotation in degrees
     * @param axis Axis of rotation as a Unit Vec3_T
     * @return New rotated Vec3_T
     */
    Vec3_T Rotate (const T angle, const Vec3_T &axis) const;

    /**
     * Return the result of rotation this Vec3_T by an angle around an
     * axis of rotation.
     * Destructive.
     * @param angle Angle of rotation in degrees
     * @param axis Axis of rotation as a Unit Vec3_T
     */
    void RotateSelf (const T angle, const Vec3_T &axis);

    /** Swizzling */
    Vec2_T<T> xy () const;

    Vec2_T<T> xz () const;

    Vec2_T<T> yz () const;

    /**
     * Compare this Vec3_T against another Vec3_T exactly.
     * @return true if this Vec3_T exactly equals the other, false otherwise
     */
    bool Compare (const Vec3_T &other) const;

    /**
     * Compare this Vec3_T against another Vec3_T within a given tolerance.
     * @param threshold Tolerance within which Vec3_T are considered equal
     * @return true if this Vec3_T equals the other within given
     *         tolerance, false otherwise
     */
    bool Compare (const Vec3_T &other, const T threshold) const;

    /**
     * Compare this Vec3_T against another Vec3_T exactly.
     * @return true if this Vec3_T exactly equals the other, false otherwise
     */
    bool operator== (const Vec3_T &other) const;

    /**
     * Compare this Vec3_T against another Vec3_T exactly.
     * @return true if this Vec3_T does not equal the other, false otherwise
     */
    bool operator!= (const Vec3_T &other) const;
};

// Common Vec3 Types.
typedef Vec3_T<float> Vec3f;

extern const Vec3f VEC3F_ZERO;
extern const Vec3f VEC3F_ONE;
extern const Vec3f VEC3F_X;
extern const Vec3f VEC3F_Y;
extern const Vec3f VEC3F_Z;
// --------------------------------------------------------------------------

template <typename T>
INLINE T Vec3_T<T>::operator[] (const u32 index) const {
    return (&x)[index];
}

template <typename T>
INLINE T &Vec3_T<T>::operator[] (const u32 index) {
    return (&x)[index];
}

template <typename T>
INLINE void Vec3_T<T>::Set (const T xx, const T yy, const T zz) {
    x = xx;
    y = yy;
    z = zz;
}

template <typename T>
INLINE void Vec3_T<T>::Zero () {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

//==========================
// Vec3_T<T> Length Operators
//==========================

template <typename T>
INLINE T Vec3_T<T>::LengthSqr () const {
    return x * x + y * y + z * z;
}

template <typename T>
INLINE T Vec3_T<T>::Length () const {
    return sqrt(x * x + y * y + z * z);
}

template <typename T>
INLINE Vec3_T<T> Vec3_T<T>::SetLength (T length) const {
    T currMag = Length();
    if (currMag == 0.0f) {
        return Vec3_T<T>(*this);
    } else {
        return *this * (length / currMag);
    }
}

template <typename T>
INLINE void Vec3_T<T>::SetLengthSelf (const T length) {
    T currMag = Length();
    if (currMag != 0.0f) {
        *this *= (length / currMag);
    }

}

template <typename T>
INLINE Vec3_T<T> Vec3_T<T>::Normalize () const {
    T currMag = Length();
    if (currMag == 0.0f) {
        return Vec3_T<T>(*this);
    } else {
        return *this / currMag;
    }
}

template <typename T>
INLINE void Vec3_T<T>::NormalizeSelf () {
    T currMag = Length();
    if (currMag != 0.0f) {
        *this /= currMag;
    }
}

template <typename T>
INLINE Vec3_T<T> Vec3_T<T>::ClampLength (const T max) const {
    if (LengthSqr() > (max * max)) {
        return SetLength(max);
    }

    return Vec3_T<T>(*this);
}

template <typename T>
INLINE Vec3_T<T> Vec3_T<T>::ClampLength (const T min, const T max) const {
    T ls = LengthSqr();

    if (ls < (min * min)) {
        return SetLength(min);
    }

    if (ls > (max * max)) {
        return SetLength(max);
    }

    return Vec3_T<T>(*this);
}

template <typename T>
INLINE void Vec3_T<T>::ClampLengthSelf (const T max) {
    if (LengthSqr() > (max * max)) {
        SetLengthSelf(max);
    }
}

template <typename T>
INLINE void Vec3_T<T>::ClampLengthSelf (const T min, const T max) {
    T ls = LengthSqr();

    if (ls < (min * min)) {
        SetLengthSelf(min);
    }

    if (ls > (max * max)) {
        SetLengthSelf(max);
    }
}

template <typename T>
INLINE void Vec3_T<T>::Clamp (const Vec3_T<T> &min, const Vec3_T<T> &max) {
    x = FMath::ClampFloat(x, min.x, max.x);
    y = FMath::ClampFloat(y, min.y, max.y);
    z = FMath::ClampFloat(z, min.z, max.z);
}

//==========================
// Vec3_T<T> Operators
//==========================

template <typename T>
INLINE Vec3_T<T> Vec3_T<T>::operator- () const {
    return Vec3_T<T>(-x, -y, -z);
}

template <typename T>
INLINE Vec3_T<T> Vec3_T<T>::operator* (const T rhs) const {
    return Vec3_T<T>(x * rhs, y * rhs, z * rhs);
}

template <typename T>
INLINE Vec3_T<T> operator* (const T a, const Vec3_T<T> &rhs) {
    return Vec3_T<T>(a * rhs.x, a * rhs.y, a * rhs.z);
}

template <typename T>
INLINE Vec3_T<T> Vec3_T<T>::operator* (const Vec3_T<T> &rhs) const {
    return Vec3_T<T>(x * rhs.x, y * rhs.y, z * rhs.z);
}

template <typename T>
INLINE Vec3_T<T> Vec3_T<T>::operator+ (const Vec3_T<T> &rhs) const {
    return Vec3_T<T>(x + rhs.x, y + rhs.y, z + rhs.z);
}

template <typename T>
INLINE Vec3_T<T> Vec3_T<T>::operator- (const Vec3_T<T> &rhs) const {
    return Vec3_T<T>(x - rhs.x, y - rhs.y, z - rhs.z);
}

template <typename T>
INLINE Vec3_T<T> Vec3_T<T>::operator/ (const T a) const {
    T inva = 1.0f / a;
    return Vec3_T<T>(x * inva, y * inva, z * inva);
}

template <typename T>
INLINE Vec3_T<T> &Vec3_T<T>::operator*= (const T a) {
    x *= a;
    y *= a;
    z *= a;

    return *this;
}

template <typename T>
INLINE Vec3_T<T> &Vec3_T<T>::operator*= (const Vec3_T<T> &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;

    return *this;
}

template <typename T>
INLINE Vec3_T<T> &Vec3_T<T>::operator+= (const Vec3_T<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
}

template <typename T>
INLINE Vec3_T<T> &Vec3_T<T>::operator-= (const Vec3_T<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;

    return *this;
}

template <typename T>
INLINE Vec3_T<T> &Vec3_T<T>::operator/= (const T a) {
    T inva = 1.0f / a;
    x *= inva;
    y *= inva;
    z *= inva;

    return *this;
}

template <typename T>
INLINE Vec3_T<T> &Vec3_T<T>::operator/= (const Vec3_T<T> &rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;

    return *this;
}

// Dot product.
template <typename T>
INLINE T Vec3_T<T>::Dot (const Vec3_T<T> &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

// Vec3_T<T> Cross Product.
template <typename T>
INLINE Vec3_T<T> Vec3_T<T>::Cross (const Vec3_T<T> &rhs) const {
    return Vec3_T<T>(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

template <typename T>
INLINE Vec3_T<T> Vec3_T<T>::Mirror (const Vec3_T<T> &axis) const {
    return 2.0f * this->Dot(axis) * axis - *this;
}

template <typename T>
INLINE Vec2_T<T> Vec3_T<T>::xy () const {
    return Vec2f(x, y);
}

template <typename T>
INLINE Vec2_T<T> Vec3_T<T>::xz () const {
    return Vec2f(x, z);
}

template <typename T>
INLINE Vec2_T<T> Vec3_T<T>::yz () const {
    return Vec2f(y, z);
}

//==========================
// Vec3_T<T> Comparison
//==========================

// This comparison may be inaccurate, prefer Compare(val, threshold)
// where possible.
template <typename T>
INLINE bool Vec3_T<T>::Compare (const Vec3_T<T> &other) const {
    return x == other.x && y == other.y && z == other.z;
}

template <typename T>
INLINE bool Vec3_T<T>::Compare (const Vec3_T<T> &other, const T threshold) const {
    if (fabs(x - other.x) > threshold)
        return false;
    if (fabs(y - other.y) > threshold)
        return false;
    if (fabs(z - other.z) > threshold)
        return false;

    return true;
}

template <typename T>
INLINE bool Vec3_T<T>::operator== (const Vec3_T<T> &other) const {
    return Compare(other);
}

template <typename T>
INLINE bool Vec3_T<T>::operator!= (const Vec3_T<T> &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_VECTOR3_H_ */
