/*---  Vector2.h - 2D Vector Header  -------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level 2D Vector type.
 */
#ifndef __SGENGINE_VECTOR2_H_
#define __SGENGINE_VECTOR2_H_

namespace sge {

/**
 * 2D Vector. Implement math operations for 2D geometry vectors.
 */
template <typename T>
class Vec2_T {
public:
    /** Vec2_T components. */
    T x, y;

public:
    static const Vec2_T ZERO;
    static const Vec2_T ONE;
    static const Vec2_T X;
    static const Vec2_T Y;

public:
    /** Construct a default Vec2_T at 0,0. */
    Vec2_T () : x(0), y(0) { }

    /** Fill Constructor. */
    explicit Vec2_T (const T f) : x(f), y(f) { }

    /** Construct a Vec2_T using x, y coordinates. */
    explicit Vec2_T (const T xx, const T yy) : x(xx), y(yy) { }

    /** Value access by index. */
    T operator[] (const u32 index) const;

    /** Reference access by index. */
    T &operator[] (const u32 index);

    /**
     * Set the values of x and y.
     * Destructive.
     *
     * @param xx The X component
     * @param yy The Y component
     */
    void Set (const T xx, const T yy);

    /**
     * Set the values of x and y to 0.0f.
     * Destructive.
     */
    void Zero ();

    /**
     * Get the squared length of this Vec2_T.
     * @return The Vector's Length squared
     */
    T LengthSqr () const;

    /**
     * Get the length of this Vec2_T.
     * @return The Vector's length
     */
    T Length () const;

    /**
     * Set the length of this Vec2_T, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess.
     * Destructive.
     * @param length The desired new length
     */
    void SetLengthSelf (const T length);

    /**
     * Set the length of a Vec2_T, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess. Returns
     * a new Vec2_T.
     * @param length The desired new length
     * @return New Vec2_T with adjusted length
     */
    Vec2_T SetLength (const T length) const;

    /**
     * Set the length of a Vec2_T to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess. Returns
     * a new Vec2_T.
     * @return New normalized Vec2_T
     */
    Vec2_T Normalize () const;

    /**
     * Set the length of this Vec2_T to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess.
     * Destructive.
     */
    void NormalizeSelf ();

    /**
     * Return a new Vec2_T which has been truncated if its length
     * exceeds the limit.
     * @param max Maximum length of Vec2_T
     * @return New clamped Vec2_T
     */
    Vec2_T ClampLength (const T max) const;

    /**
     * Return a new Vec2_T which has been extended or truncated
     * if its length falls outside the limits.
     * @param min Minimum length of Vec2_T
     * @param max Maximum length of Vec2_T
     * @return New clamped Vec2_T
     */
    Vec2_T ClampLength (const T min, const T max) const;

    /**
     * Truncate this Vec2_T if its length exceeds the limit.
     * Destructive.
     * @param max Maximum length of Vec2_T
     */
    void ClampLengthSelf (const T max);

    /**
     * Truncate or extend this Vec2_T if its length is outside
     * the limits.
     * Destructive.
     * @param min Minimum length of Vec2_T
     * @param max Maximum length of Vec2_T
     */
    void ClampLengthSelf (const T min, const T max);

    /**
     * Clamp Vec2_T within minimum and maximum bounds, given by other
     * Vec2_T values.
     * Destructive.
     * @param min Vec2_T minimum bound
     * @param max Vec2_T maximum bound
     */
    void Clamp (const Vec2_T &min, const Vec2_T &max);

    /**
     * Return a copy of this Vec2_T with the components negated.
     */
    Vec2_T operator- () const;

    /**
     * Return a scaled copy of this Vec2_T.
     * @param a Scale factor
     */
    Vec2_T operator* (const T a) const;

    /**
     * Return a scaled copy of a Vec2_T, reversed operands.
     * @param a Scale Factor
     * @param rhs Vec2_T to be scaled
     */
    template <typename U>
    friend Vec2_T<U> operator* (const U a, const Vec2_T<U> &rhs);

    /**
     * Multiply this Vec2_T by another Vec2_T componentwise.
     * @return Result of Vec2_T multiplication
     */
    Vec2_T operator* (const Vec2_T &rhs) const;

    /**
     * Add this Vec2_T to another Vec2_T.
     * @return Result of Vec2_T addition
     */
    Vec2_T operator+ (const Vec2_T &rhs) const;

    /**
     * Subtract another Vec2_T from this Vec2_T.
     * @return Result of Vec2_T subtraction
     */
    Vec2_T operator- (const Vec2_T &rhs) const;

    /**
     * Divide this Vec2_T by a scalar value.
     * @param a Divisor
     * @return Result of Vec2_T division
     */
    Vec2_T operator/ (const T a) const;

    /**
     * Divide this Vec2_T componenetwise by another Vec2_T.
     * @param rhs Divisor
     * @return Result of Vec2_T division
     */
    Vec2_T operator/ (const Vec2_T &rhs) const;

    /**
     * Multiply and mutate this Vec2_T with a scalar value.
     * Destructive.
     * @param Scale Factor
     */
    Vec2_T &operator*= (const T a);

    /**
     * Multiply and mutate this Vec2_T componentwise with another Vec2_T.
     * Destructive.
     */
    Vec2_T &operator*= (const Vec2_T &rhs);

    /**
     * Add and mutate this Vec2_T with another Vec2_T.
     * Destructive.
     */
    Vec2_T &operator+= (const Vec2_T &rhs);

    /**
     * Subtract and mutate this Vec2_T with another Vec2_T.
     * Destructive.
     */
    Vec2_T &operator-= (const Vec2_T &rhs);

    /**
     * Divide and mutate this Vec2_T by a scalar value.
     * Destructive.
     */
    Vec2_T &operator/= (const T a);

    /**
     * Divide and mutate this Vec2_T componentwise with another Vec2_T.
     * Destructive.
     */
    Vec2_T &operator/= (const Vec2_T &rhs);

    /**
     * Return the dot product of this Vec2_T and another Vec2_T.
     * @return Vec2_T Dot Product
     */
    T Dot (const Vec2_T &rhs) const;

    /**
     * Return the cross product of this Vec2_T and another Vec2_T.
     * @return Vec2_T Cross Product
     */
    T Cross (const Vec2_T &rhs) const;

    /**
     * Return the mirror of this Vec2_T about an arbitrary axis.
     * @param axis The axis of symmetry
     * @return Result of mirroring this Vec2_T about axis
     */
    Vec2_T Mirror (const Vec2_T &axis) const;

    /**
     * Compare this Vec2_T against another Vec2_T exactly.
     * @return true if this Vec2_T exactly equals the other, false otherwise
     */
    bool Compare (const Vec2_T &other) const;

    /**
     * Compare this Vec2_T against another Vec2_T within a given tolerance.
     * @param threshold Tolerance within which Vec2_T are considered equal
     * @return true if this Vec2_T equals the other within given
     *         tolerance, false otherwise
     */
    bool Compare (const Vec2_T &other, const T threshold) const;

    /**
     * Compare this Vec2_T against another Vec2_T exactly.
     * @return true if this Vec2_T exactly equals the other, false otherwise
     */
    bool operator== (const Vec2_T &other) const;

    /**
     * Compare this Vec2_T against another Vec2_T exactly.
     * @return true if this Vec2_T does not equal the other, false otherwise
     */
    bool operator!= (const Vec2_T &other) const;
};

// Common Vec2 types.
typedef Vec2_T<float> Vec2f;

// --------------------------------------------------------------------------

template <typename T>
INLINE T Vec2_T<T>::operator[] (const u32 index) const {
    return (&x)[index];
}

template <typename T>
INLINE T &Vec2_T<T>::operator[] (const u32 index) {
    return (&x)[index];
}

template <typename T>
INLINE void Vec2_T<T>::Set (const T xx, const T yy) {
    x = xx;
    y = yy;
}

template <typename T>
INLINE void Vec2_T<T>::Zero () {
    x = y = 0.0f;
}

//==========================
// Vec2_T<T> Length Operators
//==========================

template <typename T>
INLINE T Vec2_T<T>::LengthSqr () const {
    return x * x + y * y;
}

template <typename T>
INLINE T Vec2_T<T>::Length () const {
    return sqrt(x * x + y * y);
}

template <typename T>
INLINE Vec2_T<T> Vec2_T<T>::SetLength (T length) const {
    T currMag = Length();
    if (currMag == 0.0f) {
        return Vec2_T<T>(*this);
    } else {
        return *this * (length / currMag);
    }
}

template <typename T>
INLINE void Vec2_T<T>::SetLengthSelf (const T length) {
    T currMag = Length();
    if (currMag != 0.0f) {
        *this *= (length / currMag);
    }
}

template <typename T>
INLINE Vec2_T<T> Vec2_T<T>::Normalize () const {
    T currMag = Length();
    if (currMag == 0.0f) {
        return Vec2_T<T>(*this);
    } else {
        return *this / currMag;
    }
}

template <typename T>
INLINE void Vec2_T<T>::NormalizeSelf () {
    T currMag = Length();
    if (currMag != 0.0f) {
        *this /= currMag;
    }
}

template <typename T>
INLINE Vec2_T<T> Vec2_T<T>::ClampLength (const T max) const {
    if (LengthSqr() > (max * max)) {
        return SetLength(max);
    }

    return Vec2_T<T>(*this);
}

template <typename T>
INLINE Vec2_T<T> Vec2_T<T>::ClampLength (const T min, const T max) const {
    T ls = LengthSqr();

    if (ls < (min * min)) {
        return SetLength(min);
    }

    if (ls > (max * max)) {
        return SetLength(max);
    }

    return Vec2_T<T>(*this);
}

template <typename T>
INLINE void Vec2_T<T>::ClampLengthSelf (const T max) {
    if (LengthSqr() > (max * max)) {
        SetLengthSelf(max);
    }
}

template <typename T>
INLINE void Vec2_T<T>::ClampLengthSelf (const T min, const T max) {
    T ls = LengthSqr();

    if (ls < (min * min)) {
        SetLengthSelf(min);
    }

    if (ls > (max * max)) {
        SetLengthSelf(max);
    }
}

template <typename T>
INLINE void Vec2_T<T>::Clamp (const Vec2_T<T> &min, const Vec2_T<T> &max) {
    x = FMath::ClampFloat(x, min.x, max.x);
    y = FMath::ClampFloat(y, min.y, max.y);
}

//==========================
// Vec2_T<T> Operators
//==========================

template <typename T>
INLINE Vec2_T<T> Vec2_T<T>::operator- () const {
    return Vec2_T<T>(-x, -y);
}

template <typename T>
INLINE Vec2_T<T> Vec2_T<T>::operator* (const T rhs) const {
    return Vec2_T<T>(x * rhs, y * rhs);
}

template <typename T>
INLINE Vec2_T<T> operator* (const T a, const Vec2_T<T> &rhs) {
    return Vec2_T<T>(a * rhs.x, a * rhs.y);
}

template <typename T>
INLINE Vec2_T<T> Vec2_T<T>::operator* (const Vec2_T<T> &rhs) const {
    return Vec2_T<T>(x * rhs.x, y * rhs.y);
}

template <typename T>
INLINE Vec2_T<T> Vec2_T<T>::operator+ (const Vec2_T<T> &rhs) const {
    return Vec2_T<T>(x + rhs.x, y + rhs.y);
}

template <typename T>
INLINE Vec2_T<T> Vec2_T<T>::operator- (const Vec2_T<T> &rhs) const {
    return Vec2_T<T>(x - rhs.x, y - rhs.y);
}

template <typename T>
INLINE Vec2_T<T> Vec2_T<T>::operator/ (const T a) const {
    T inva = 1.0f / a;
    return Vec2_T<T>(x * inva, y * inva);
}

template <typename T>
INLINE Vec2_T<T> Vec2_T<T>::operator/ (const Vec2_T<T> &rhs) const {
    return Vec2_T<T>(x / rhs.x, y / rhs.y);
}

template <typename T>
INLINE Vec2_T<T> &Vec2_T<T>::operator*= (const T a) {
    x *= a;
    y *= a;

    return *this;
}

template <typename T>
INLINE Vec2_T<T> &Vec2_T<T>::operator*= (const Vec2_T<T> &rhs) {
    x *= rhs.x;
    y *= rhs.y;

    return *this;
}

template <typename T>
INLINE Vec2_T<T> &Vec2_T<T>::operator+= (const Vec2_T<T> &rhs) {
    x += rhs.x;
    y += rhs.y;

    return *this;
}

template <typename T>
INLINE Vec2_T<T> &Vec2_T<T>::operator-= (const Vec2_T<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

template <typename T>
INLINE Vec2_T<T> &Vec2_T<T>::operator/= (const T a) {
    T inva = 1.0f / a;
    x *= inva;
    y *= inva;

    return *this;
}

template <typename T>
INLINE Vec2_T<T> &Vec2_T<T>::operator/= (const Vec2_T<T> &rhs) {
    x /= rhs.x;
    y /= rhs.y;

    return *this;
}

template <typename T>
INLINE T Vec2_T<T>::Dot (const Vec2_T<T> &rhs) const {
    return x * rhs.x + y * rhs.y;
}

template <typename T>
INLINE T Vec2_T<T>::Cross (const Vec2_T<T> &rhs) const {
    return x * rhs.y - y * rhs.x;
}

template <typename T>
INLINE Vec2_T<T> Vec2_T<T>::Mirror (const Vec2_T<T> &axis) const {
    return 2.0f * this->Dot(axis) * axis - *this;
}

//==========================
// Vec2_T<T> Comparisons
//==========================

// This comparison may be inaccurate, prefer Compare(val, threshold)
// where possible.
template <typename T>
INLINE bool Vec2_T<T>::Compare (const Vec2_T<T> &other) const {
    return x == other.x && y == other.y;
}

template <typename T>
INLINE bool Vec2_T<T>::Compare (const Vec2_T<T> &other, const T threshold) const {
    if (fabsf(x - other.x) > threshold)
        return false;
    if (fabsf(y - other.y) > threshold)
        return false;

    return true;
}

template <typename T>
INLINE bool Vec2_T<T>::operator== (const Vec2_T<T> &other) const {
    return Compare(other);
}

template <typename T>
INLINE bool Vec2_T<T>::operator!= (const Vec2_T<T> &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_VECTOR2_H_ */
