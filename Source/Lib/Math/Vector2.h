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
#ifndef __SGE_VECTOR2_H
#define __SGE_VECTOR2_H

/**
 * 2D Vector. Implement math operations for 2D geometry vectors.
 */
class Vec2f {
public:
    float x = 0; /**< x coordinate. */
    float y = 0; /**< y coordinate. */

public:
    static const Vec2f ZERO;
    static const Vec2f ONE;
    static const Vec2f X;
    static const Vec2f Y;

public:
    /** Default Constructor. */
    Vec2f () = default;

    /** Fill Constructor. */
    explicit Vec2f (const float f) : x(f), y(f) { }

    /** Construct a Vec2f using x, y coordinates. */
    explicit Vec2f (const float xx, const float yy) : x(xx), y(yy) { }

    /** Value access by index. */
    float operator[] (const std::size_t index) const;

    /** Reference access by index. */
    float &operator[] (const std::size_t index);

    /**
     * Set the values of x and y.
     * Destructive.
     *
     * @param xx The X component
     * @param yy The Y component
     */
    void Set (const float xx, const float yy);

    /**
     * Set the values of x and y to 0.0f.
     * Destructive.
     */
    void Zero ();

    /**
     * Get the squared length of this Vec2f.
     *
     * @return The Vector's Length squared
     */
    float LengthSqr () const;

    /**
     * Get the length of this Vec2f.
     *
     * @return The Vector's length
     */
    float Length () const;

    /**
     * Set the length of this Vec2f, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess.
     * Destructive.
     *
     * @param length The desired new length
     */
    void SetLengthSelf (const float length);

    /**
     * Set the length of a Vec2f, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess. Returns
     * a new Vec2f.
     *
     * @param length The desired new length
     * @return New Vec2f with adjusted length
     */
    Vec2f SetLength (const float length) const;

    /**
     * Set the length of a Vec2f to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess. Returns
     * a new Vec2f.
     *
     * @return New normalized Vec2f
     */
    Vec2f Normalize () const;

    /**
     * Set the length of this Vec2f to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess.
     * Destructive.
     */
    void NormalizeSelf ();

    /**
     * Return a new Vec2f which has been truncated if its length
     * exceeds the limit.
     *
     * @param max Maximum length of Vec2f
     * @return New clamped Vec2f
     */
    Vec2f ClampLength (const float max) const;

    /**
     * Return a new Vec2f which has been extended or truncated
     * if its length falls outside the limits.
     *
     * @param min Minimum length of Vec2f
     * @param max Maximum length of Vec2f
     * @return New clamped Vec2f
     */
    Vec2f ClampLength (const float min, const float max) const;

    /**
     * Truncate this Vec2f if its length exceeds the limit.
     * Destructive.
     *
     * @param max Maximum length of Vec2f
     */
    void ClampLengthSelf (const float max);

    /**
     * Truncate or extend this Vec2f if its length is outside
     * the limits.
     * Destructive.
     *
     * @param min Minimum length of Vec2f
     * @param max Maximum length of Vec2f
     */
    void ClampLengthSelf (const float min, const float max);

    /**
     * Return a new Vec2f Clamped between minimum and maximum
     * bounds, given by other Vec2f values.
     *
     * @param min Vec2f minimum bound
     * @param max Vec2f maximum bound
     */
    Vec2f Clamp (const Vec2f &min, const Vec2f &max) const;

    /**
     * Clamp Vec2f within minimum and maximum bounds, given by other
     * Vec2f values.
     * Destructive.
     *
     * @param min Vec2f minimum bound
     * @param max Vec2f maximum bound
     */
    void ClampSelf (const Vec2f &min, const Vec2f &max);

    /**
     * Return the dot product of this Vec2f and another Vec2f.
     *
     * @return Vec2f Dot Product
     */
    float Dot (const Vec2f &rhs) const;

    /**
     * Return the cross product of this Vec2f and another Vec2f.
     *
     * @return Vec2f Cross Product
     */
    float Cross (const Vec2f &rhs) const;

    /**
     * Return the mirror of this Vec2f about an arbitrary axis.
     *
     * @param axis The axis of symmetry
     * @return Result of mirroring this Vec2f about axis
     */
    Vec2f Mirror (const Vec2f &axis) const;

    /**
     * Compare this Vec2f against another Vec2f.
     *
     * @return true if this Vec2f equals the other, false otherwise.
     */
    bool Compare (const Vec2f &other) const;

    /**
     * Compare this Vec2f against another Vec2f within a given tolerance.
     *
     * @param threshold Tolerance within which Vec2f are considered equal
     * @return true if this Vec2f equals the other within given
     *         tolerance, false otherwise
     */
    bool Compare (const Vec2f &other, const float threshold) const;

    /**
     * Compare this Vec2f against another Vec2f exactly.
     *
     * @return true if this Vec2f exactly equals the other, false otherwise
     */
    bool operator== (const Vec2f &other) const;

    /**
     * Compare this Vec2f against another Vec2f exactly.
     *
     * @return true if this Vec2f does not equal the other, false otherwise
     */
    bool operator!= (const Vec2f &other) const;
};

// --------------------------------------------------------------------------

inline float Vec2f::operator[] (const std::size_t index) const {
    return (&x)[index];
}

inline float &Vec2f::operator[] (const std::size_t index) {
    return (&x)[index];
}

inline void Vec2f::Set (const float xx, const float yy) {
    x = xx;
    y = yy;
}

inline void Vec2f::Zero () {
    x = y = 0;
}

//==========================
// Vec2f Operators
//==========================

/** Negate. */
inline Vec2f operator- (const Vec2f &v) {
    return Vec2f(-v.x, -v.y);
}

/** Multiply by scalar. */
inline Vec2f operator* (const Vec2f &v, const float a) {
    return Vec2f(a * v.x, a * v.y);
}

/** Multiply by scalar. */
inline Vec2f operator* (const float a, const Vec2f &v) {
    return Vec2f(a * v.x, a * v.y);
}

/** Piecewise multiplication. */
inline Vec2f operator* (const Vec2f &a, const Vec2f &b) {
    return Vec2f(a.x * b.x, a.y * b.y);
}

/** Addition. */
inline Vec2f operator+ (const Vec2f &a, const Vec2f &b) {
    return Vec2f(a.x + b.x, a.y + b.y);
}

/** Subtraction. */
inline Vec2f operator- (const Vec2f &a, const Vec2f &b) {
    return Vec2f(a.x - b.x, a.y - b.y);
}

/** Division. */
inline Vec2f operator/ (const Vec2f &v, const float a) {
    float inva = 1.0f / a;
    return Vec2f(v.x * inva, v.y * inva);
}

/** Multiply by scalar in place. */
inline Vec2f& operator*= (Vec2f &v, const float a) {
    v.x *= a;
    v.y *= a;

    return v;
}

/** Piecewise multiplication in place. */
inline Vec2f& operator*= (Vec2f &a, const Vec2f &b) {
    a.x *= b.x;
    a.y *= b.y;

    return a;
}

/** Addition in place. */
inline Vec2f& operator+= (Vec2f &a, const Vec2f &b) {
    a.x += b.x;
    a.y += b.y;

    return a;
}

/** Subtraction in place. */
inline Vec2f& operator-= (Vec2f &a, const Vec2f &b) {
    a.x -= b.x;
    a.y -= b.y;

    return a;
}

/** Division in place. */
inline Vec2f& operator/= (Vec2f &v, const float a) {
    float inva = 1.0f / a;
    v.x *= inva;
    v.y *= inva;

    return v;
}

/** Piecewise division in place. */
inline Vec2f& operator/= (Vec2f &a, const Vec2f &b) {
    a.x /= b.x;
    a.y /= b.y;

    return a;
}

//==========================
// Vec2f Length Operators
//==========================

inline float Vec2f::LengthSqr () const {
    return x * x + y * y;
}

inline float Vec2f::Length () const {
    return sqrt(x * x + y * y);
}

inline Vec2f Vec2f::SetLength (const float length) const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return *this;
    }

    return *this * (length / currMag);
}

inline void Vec2f::SetLengthSelf (const float length) {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this *= (length / currMag);
    }
}

inline Vec2f Vec2f::Normalize () const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return *this;
    }

    return *this / currMag;
}

inline void Vec2f::NormalizeSelf () {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this /= currMag;
    }
}

inline Vec2f Vec2f::ClampLength (const float max) const {
    if (LengthSqr() > (max * max)) {
        return SetLength(max);
    }

    return *this;
}

inline Vec2f Vec2f::ClampLength (const float min, const float max) const {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        return SetLength(min);
    }

    if (ls > (max * max)) {
        return SetLength(max);
    }

    return *this;
}

inline void Vec2f::ClampLengthSelf (const float max) {
    if (LengthSqr() > (max * max)) {
        SetLengthSelf(max);
    }
}

inline void Vec2f::ClampLengthSelf (const float min, const float max) {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        SetLengthSelf(min);
    }

    if (ls > (max * max)) {
        SetLengthSelf(max);
    }
}

inline Vec2f Vec2f::Clamp (const Vec2f &min, const Vec2f &max) const {
    return Vec2f(FMath::ClampFloat(x, min.x, max.x),
                 FMath::ClampFloat(y, min.y, max.y));
}

inline void Vec2f::ClampSelf (const Vec2f &min, const Vec2f &max) {
    x = FMath::ClampFloat(x, min.x, max.x);
    y = FMath::ClampFloat(y, min.y, max.y);
}

inline float Vec2f::Dot (const Vec2f &rhs) const {
    return x * rhs.x + y * rhs.y;
}

inline float Vec2f::Cross (const Vec2f &rhs) const {
    return x * rhs.y - y * rhs.x;
}

inline Vec2f Vec2f::Mirror (const Vec2f &axis) const {
    return 2.0f * this->Dot(axis) * axis - *this;
}

//==========================
// Vec2f Comparisons
//==========================

inline bool Vec2f::Compare (const Vec2f &other) const {
    return x == other.x && y == other.y;
}

inline bool Vec2f::Compare (const Vec2f &other, const float threshold) const {
    return (fabsf(x - other.x) <= threshold) &&
           (fabsf(y - other.y) <= threshold);
}

inline bool Vec2f::operator== (const Vec2f &other) const {
    return Compare(other);
}

inline bool Vec2f::operator!= (const Vec2f &other) const {
    return !Compare(other);
}

#endif /* __SGE_VECTOR2_H */
