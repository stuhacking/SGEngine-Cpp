/*---  Vector4.h - 4D Vector Header  -------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level Vec4 type.
 */
#ifndef __SGENGINE_VECTOR4_H_
#define __SGENGINE_VECTOR4_H_

namespace sge {

/**
 * 4D Vector. Implement math operations for 4D geometry vectors.
 */
template <typename T>
class Vec4_T {
public:
    /** Vec4 components. */
    T x, y, z, w;

public:
    static const Vec4_T ZERO;
    static const Vec4_T ONE;
    static const Vec4_T X;
    static const Vec4_T Y;
    static const Vec4_T Z;
    static const Vec4_T W;

public:
    /** Construct a default Vec4_T at origin. */
    Vec4_T () : x(0), y(0), z(0), w(0) { }

    /** Fill Constructor. */
    explicit Vec4_T (const T f) : x(f), y(f), z(f), w(f) { }

    /** Construct a Vec4_T using x, y, z, w coordinates. */
    explicit Vec4_T (const T xx, const T yy, const T zz, const T ww)
        : x(xx), y(yy), z(zz), w(ww) { }

    /** Construct a Vec4_T using the x,y,z components of a Vec3f. */
    Vec4_T (const Vec3_T<T> &vec, const T ww) : x(vec.x), y(vec.y), z(vec.z), w(ww) { }

    /** Value access using an index. */
    T operator[] (const u32 index) const;

    /** Reference access using an index. */
    T &operator[] (const u32 index);

    /**
     * Set the values of x, y, z, and w.
     * Destructive.
     *
     * @param xx The X component
     * @param yy The Y component
     * @param zz The Z component
     * @param ww The W component
     */
    void Set (const T xx, const T yy, const T zz, const T ww);

    /**
     * Set the values of x, y, z, and w to 0.0f.
     * Destructive.
     */
    void Zero ();

    /**
     * Get the squared length of this Vec4_T.
     * @return The Vector's Length squared
     */
    T LengthSqr () const;

    /**
     * Get the length of this Vec4_T.
     * @return The Vector's length
     */
    T Length () const;

    /**
     * Set the length of a Vec4_T, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess. Returns
     * a new Vec4_T.
     * @param vec Original Vec4_T
     * @param length The desired new length
     * @return New Vec4_T with adjusted length
     */
    Vec4_T SetLength (const T length) const;

    /**
     * Set the length of this Vec4_T, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess.
     * Destructive.
     * @param length The desired new length
     */
    void SetLengthSelf (const T length);

    /**
     * Set the length of a Vec4_T to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess. Returns
     * a new Vec4_T.
     * @param vec Original Vec4_T
     * @return New normalized Vec4_T
     */
    Vec4_T Normalize () const;

    /**
     * Set the length of this Vec4_T to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess.
     * Destructive.
     */
    void NormalizeSelf ();

    /**
     * Return a new Vec4_T which has been truncated if its length
     * exceeds the limit.
     * @param max Maximum length of Vec4_T
     * @return New (possibly truncated) Vec4_T
     */
    Vec4_T ClampLength (const T max) const;

    /**
     * Return a new Vec4_T which has been extended or truncated
     * if its length is outside the limits.
     * @param min Minimum length of Vec4_T
     * @param max Maximum length of Vec4_T
     * @return New (possibly truncated) Vec4_T
     */
    Vec4_T ClampLength (const T min, const T max) const;

    /**
     * Truncate this Vec4_T if its length exceeds the limit.
     * Destructive.
     * @param max Maximum length of Vec4_T
     */
    void ClampLengthSelf (const T max);

    /**
     * Truncate or extend this Vec4_T if its length is outside
     * the limits.
     * Destructive.
     * @param min Minimum length of Vec4_T
     * @param max Maximum length of Vec4_T
     */
    void ClampLengthSelf (const T min, const T max);

    /**
     * Clamp Vec4_T within minimum and maximum bounds, given by other
     * Vec4_T values.
     * Destructive.
     * @param min Vec4_T minimum bound
     * @param max Vec4_T maximum bound
     */
    void Clamp (const Vec4_T &min, const Vec4_T &max);

    /**
     * Return a copy of this Vec4_T with the components negated.
     */
    Vec4_T operator- () const;

    /**
     * Return a scaled copy of this Vec4_T.
     * @param a Scale factor
     */
    Vec4_T operator* (const T a) const;

    /**
     * Return a scaled copy of a Vec4_T, reversed operands.
     * @param a Scale Factor
     * @param rhs Vec4_T to be scaled
     */
    template <typename U>
    friend Vec4_T<U> operator* (const U a, const Vec4_T<U> &rhs);

    /**
     * Multiply this Vec4_T by another Vec4_T componentwise.
     * @return Result of Vec4_T multiplication
     */
    Vec4_T operator* (const Vec4_T &rhs) const;

    /**
     * Add this Vec4_T to another Vec4_T.
     * @return Result of Vec4_T addition
     */
    Vec4_T operator+ (const Vec4_T &rhs) const;

    /**
     * Subtract another Vec4_T from this Vec4_T.
     * @return Result of Vec4_T subtraction
     */
    Vec4_T operator- (const Vec4_T &rhs) const;

    /**
     * Divide this Vec4_T by a scalar value.
     * @param a Divisor
     * @return Result of Vec4_T division
     */
    Vec4_T operator/ (const T a) const;

    /**
     * Multiply and mutate this Vec4_T with a scalar value.
     * Destructive.
     * @param Scale Factor
     */
    Vec4_T &operator*= (const T a);

    /**
     * Multiply and mutate this Vec4_T componentwise with another Vec4_T.
     * Destructive.
     */
    Vec4_T &operator*= (const Vec4_T &rhs);

    /**
     * Add and mutate this Vec4_T with another Vec4_T.
     * Destructive.
     */
    Vec4_T &operator+= (const Vec4_T &rhs);

    /**
     * Subtract and mutate this Vec4_T with another Vec4_T.
     * Destructive.
     */
    Vec4_T &operator-= (const Vec4_T &rhs);

    /**
     * Divide and mutate this Vec4_T by a scalar value.
     * Destructive.
     */
    Vec4_T &operator/= (const T a);

    /**
     * Divide and mutate this Vec4_T componentwise with another Vec4_T.
     * Destructive.
     */
    Vec4_T &operator/= (const Vec4_T &rhs);

    T Dot (const Vec4_T &rhs) const;

    Vec4_T Cross (const Vec4_T &rhs) const;

    /** Swizzling */
    Vec3_T<T> xyz () const;

    Vec2_T<T> xy () const;

    Vec2_T<T> xz () const;

    Vec2_T<T> yz () const;

    /**
     * Compare this Vec4_T against another Vec4_T exactly.
     * @return true if this Vec4_T exactly equals the other, false otherwise
     */
    bool Compare (const Vec4_T &other) const;

    /**
     * Compare this Vec4_T against another Vec4_T within a given tolerance.
     * @param threshold Tolerance within which Vec4_T are considered equal
     * @return true if this Vec4_T equals the other within given
     *         tolerance, false otherwise
     */
    bool Compare (const Vec4_T &other, const T threshold) const;

    /**
     * Compare this Vec4_T against another Vec4_T exactly.
     * @return true if this Vec4_T exactly equals the other, false otherwise
     */
    bool operator== (const Vec4_T &other) const;

    /**
     * Compare this Vec4_T against another Vec4_T exactly.
     * @return true if this Vec4_T does not equal the other, false otherwise
     */
    bool operator!= (const Vec4_T &other) const;
};

// Common Vec4 types.
typedef Vec4_T<float> Vec4f;

// --------------------------------------------------------------------------

template <typename T>
INLINE T Vec4_T<T>::operator[] (const u32 index) const {
    return (&x)[index];
}

template <typename T>
INLINE T &Vec4_T<T>::operator[] (const u32 index) {
    return (&x)[index];
}

template <typename T>
INLINE void Vec4_T<T>::Set (const T xx, const T yy, const T zz, const T ww) {
    x = xx;
    y = yy;
    z = zz;
    w = ww;
}

template <typename T>
INLINE void Vec4_T<T>::Zero () {
    x = y = z = w = 0.0f;
}

//==========================
// Vec4_T<T> Length Operators
//==========================

template <typename T>
INLINE T Vec4_T<T>::LengthSqr () const {
    return x * x + y * y + z * z + w * w;
}

template <typename T>
INLINE T Vec4_T<T>::Length () const {
    return sqrt(x * x + y * y + z * z + w * w);
}

template <typename T>
INLINE Vec4_T<T> Vec4_T<T>::SetLength (T length) const {
    T currMag = Length();
    if (currMag == 0.0f) {
        return Vec4_T<T>(*this);
    } else {
        return *this * (length / currMag);
    }
}

template <typename T>
INLINE void Vec4_T<T>::SetLengthSelf (const T length) {
    T currMag = Length();
    if (currMag != 0.0f) {
        *this *= (length / currMag);
    }

}

template <typename T>
INLINE Vec4_T<T> Vec4_T<T>::Normalize () const {
    T currMag = Length();
    if (currMag == 0.0f) {
        return Vec4_T<T>(*this);
    } else {
        return *this / currMag;
    }
}

template <typename T>
INLINE void Vec4_T<T>::NormalizeSelf () {
    T currMag = Length();
    if (currMag != 0.0f) {
        *this /= currMag;
    }
}

template <typename T>
INLINE Vec4_T<T> Vec4_T<T>::ClampLength (const T max) const {
    if (LengthSqr() > (max * max)) {
        return SetLength(max);
    }

    return Vec4_T<T>(*this);
}

template <typename T>
INLINE Vec4_T<T> Vec4_T<T>::ClampLength (const T min, const T max) const {
    T ls = LengthSqr();

    if (ls < (min * min)) {
        return SetLength(min);
    }

    if (ls > (max * max)) {
        return SetLength(max);
    }

    return Vec4_T<T>(*this);
}

template <typename T>
INLINE void Vec4_T<T>::ClampLengthSelf (const T max) {
    if (LengthSqr() > (max * max)) {
        SetLengthSelf(max);
    }
}

template <typename T>
INLINE void Vec4_T<T>::ClampLengthSelf (const T min, const T max) {
    T ls = LengthSqr();

    if (ls < (min * min)) {
        SetLengthSelf(min);
    }

    if (ls > (max * max)) {
        SetLengthSelf(max);
    }
}

template <typename T>
INLINE void Vec4_T<T>::Clamp (const Vec4_T<T> &min, const Vec4_T<T> &max) {
    x = FMath::ClampFloat(x, min.x, max.x);
    y = FMath::ClampFloat(y, min.y, max.y);
    z = FMath::ClampFloat(z, min.z, max.z);
    w = FMath::ClampFloat(w, min.w, max.w);
}

template <typename T>
INLINE Vec4_T<T> Vec4_T<T>::operator- () const {
    return Vec4_T<T>(-x, -y, -z, -w);
}

//==========================
// Vec4_T<T> Operators
//==========================

template <typename T>
INLINE Vec4_T<T> Vec4_T<T>::operator* (const T rhs) const {
    return Vec4_T<T>(x * rhs, y * rhs, z * rhs, w * rhs);
}

template <typename T>
INLINE Vec4_T<T> operator* (const T a, const Vec4_T<T> &rhs) {
    return Vec4_T<T>(a * rhs.x, a * rhs.y, a * rhs.z, a * rhs.w);
}

template <typename T>
INLINE Vec4_T<T> Vec4_T<T>::operator* (const Vec4_T<T> &rhs) const {
    return Vec4_T<T>(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

template <typename T>
INLINE Vec4_T<T> Vec4_T<T>::operator+ (const Vec4_T<T> &rhs) const {
    return Vec4_T<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

template <typename T>
INLINE Vec4_T<T> Vec4_T<T>::operator- (const Vec4_T<T> &rhs) const {
    return Vec4_T<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

template <typename T>
INLINE Vec4_T<T> Vec4_T<T>::operator/ (const T a) const {
    T inva = 1.0f / a;
    return Vec4_T<T>(x * inva, y * inva, z * inva, w * inva);
}

template <typename T>
INLINE Vec4_T<T> &Vec4_T<T>::operator*= (const T a) {
    x *= a;
    y *= a;
    z *= a;
    w *= a;

    return *this;
}

template <typename T>
INLINE Vec4_T<T> &Vec4_T<T>::operator*= (const Vec4_T<T> &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;

    return *this;
}

template <typename T>
INLINE Vec4_T<T> &Vec4_T<T>::operator+= (const Vec4_T<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;

    return *this;
}

template <typename T>
INLINE Vec4_T<T> &Vec4_T<T>::operator-= (const Vec4_T<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;

    return *this;
}

template <typename T>
INLINE Vec4_T<T> &Vec4_T<T>::operator/= (const T a) {
    T inva = 1.0f / a;
    x *= inva;
    y *= inva;
    z *= inva;
    w *= inva;

    return *this;
}

template <typename T>
INLINE Vec4_T<T> &Vec4_T<T>::operator/= (const Vec4_T<T> &rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;

    return *this;
}

// Dot product.
template <typename T>
INLINE T Vec4_T<T>::Dot (const Vec4_T<T> &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

template <typename T>
INLINE Vec3_T<T> Vec4_T<T>::xyz () const {
    return Vec3_T<T>(x, y, z);
}

template <typename T>
INLINE Vec2_T<T> Vec4_T<T>::xy () const {
    return Vec2_T<T>(x, y);
}

template <typename T>
INLINE Vec2_T<T> Vec4_T<T>::xz () const {
    return Vec2_T<T>(x, z);
}

template <typename T>
INLINE Vec2_T<T> Vec4_T<T>::yz () const {
    return Vec2_T<T>(y, z);
}

//==========================
// Vec4_T<T> Comparison
//==========================

// This comparison may be inaccurate, prefer Compare(val, threshold)
// where possible.
template <typename T>
INLINE bool Vec4_T<T>::Compare (const Vec4_T<T> &other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

template <typename T>
INLINE bool Vec4_T<T>::Compare (const Vec4_T<T> &other, const T threshold) const {
    if (fabs(x - other.x) > threshold)
        return false;
    if (fabs(y - other.y) > threshold)
        return false;
    if (fabs(z - other.z) > threshold)
        return false;
    if (fabs(w - other.w) > threshold)
        return false;

    return true;
}

template <typename T>
INLINE bool Vec4_T<T>::operator== (const Vec4_T<T> &other) const {
    return Compare(other);
}

template <typename T>
INLINE bool Vec4_T<T>::operator!= (const Vec4_T<T> &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_VECTOR4_H_ */
