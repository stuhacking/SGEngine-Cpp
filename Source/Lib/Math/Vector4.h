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
#ifndef __SGE_VECTOR4_H
#define __SGE_VECTOR4_H

/**
 * 4D Vector. Implement math operations for 4D geometry vectors.
 */
class Vec4f {
public:
    /** Vec4 components. */
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;

public:
    static const Vec4f ZERO;
    static const Vec4f ONE;
    static const Vec4f X;
    static const Vec4f Y;
    static const Vec4f Z;
    static const Vec4f W;

public:
    /** Default Constructor. */
    Vec4f () = default;

    /** Fill Constructor. */
    explicit Vec4f (const float f) : x(f), y(f), z(f), w(f) { }

    /** Construct a Vec4f using x, y, z, w coordinates. */
    explicit Vec4f (const float xx, const float yy, const float zz, const float ww)
        : x(xx), y(yy), z(zz), w(ww) { }

    /** Construct a Vec4f using the x,y,z components of a Vec3f. */
    Vec4f (const Vec3f &vec, const float ww) : x(vec.x), y(vec.y), z(vec.z), w(ww) { }

    /** Value access using an index. */
    float operator[] (const std::size_t index) const;

    /** Reference access using an index. */
    float &operator[] (const std::size_t index);

    /**
     * Set the values of x, y, z, and w.
     * Destructive.
     *
     * @param xx The X component
     * @param yy The Y component
     * @param zz The Z component
     * @param ww The W component
     */
    void Set (const float xx, const float yy, const float zz, const float ww);

    /**
     * Set the values of x, y, z, and w to 0.0f.
     * Destructive.
     */
    void Zero ();

    /**
     * Get the squared length of this Vec4f.
     * @return The Vector's Length squared
     */
    float LengthSqr () const;

    /**
     * Get the length of this Vec4f.
     * @return The Vector's length
     */
    float Length () const;

    /**
     * Set the length of a Vec4f, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess. Returns
     * a new Vec4f.
     * @param vec Original Vec4f
     * @param length The desired new length
     * @return New Vec4f with adjusted length
     */
    Vec4f SetLength (const float length) const;

    /**
     * Set the length of this Vec4f, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess.
     * Destructive.
     * @param length The desired new length
     */
    void SetLengthSelf (const float length);

    /**
     * Set the length of a Vec4f to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess. Returns
     * a new Vec4f.
     * @param vec Original Vec4f
     * @return New normalized Vec4f
     */
    Vec4f Normalize () const;

    /**
     * Set the length of this Vec4f to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess.
     * Destructive.
     */
    void NormalizeSelf ();

    /**
     * Return a new Vec4f which has been truncated if its length
     * exceeds the limit.
     * @param max Maximum length of Vec4f
     * @return New (possibly truncated) Vec4f
     */
    Vec4f ClampLength (const float max) const;

    /**
     * Return a new Vec4f which has been extended or truncated
     * if its length is outside the limits.
     * @param min Minimum length of Vec4f
     * @param max Maximum length of Vec4f
     * @return New (possibly truncated) Vec4f
     */
    Vec4f ClampLength (const float min, const float max) const;

    /**
     * Truncate this Vec4f if its length exceeds the limit.
     * Destructive.
     * @param max Maximum length of Vec4f
     */
    void ClampLengthSelf (const float max);

    /**
     * Truncate or extend this Vec4f if its length is outside
     * the limits.
     * Destructive.
     * @param min Minimum length of Vec4f
     * @param max Maximum length of Vec4f
     */
    void ClampLengthSelf (const float min, const float max);

    /**
     * Clamp Vec4f within minimum and maximum bounds, given by other
     * Vec4f values.
     *
     * @param min Vec4f minimum bound
     * @param max Vec4f maximum bound
     */
    Vec4f Clamp (const Vec4f &min, const Vec4f &max) const;

    /**
     * Clamp Vec4f within minimum and maximum bounds, given by other
     * Vec4f values.
     * Destructive.
     * @param min Vec4f minimum bound
     * @param max Vec4f maximum bound
     */
    void ClampSelf (const Vec4f &min, const Vec4f &max);

    float Dot (const Vec4f &rhs) const;

    /** Swizzling */
    Vec3f xyz () const;

    Vec2f xy () const;

    Vec2f xz () const;

    Vec2f yz () const;

    /**
     * Compare this Vec4f against another Vec4f exactly.
     *
     * @return true if this Vec4f exactly equals the other, false otherwise
     */
    bool Compare (const Vec4f &other) const;

    /**
     * Compare this Vec4f against another Vec4f within a given tolerance.
     *
     * @param threshold Tolerance within which Vec4f are considered equal
     * @return true if this Vec4f equals the other within given
     *         tolerance, false otherwise
     */
    bool Compare (const Vec4f &other, const float threshold) const;

    /**
     * Compare this Vec4f against another Vec4f exactly.
     * @return true if this Vec4f exactly equals the other, false otherwise
     */
    bool operator== (const Vec4f &other) const;

    /**
     * Compare this Vec4f against another Vec4f exactly.
     * @return true if this Vec4f does not equal the other, false otherwise
     */
    bool operator!= (const Vec4f &other) const;
};

// --------------------------------------------------------------------------

inline float Vec4f::operator[] (const std::size_t index) const {
    return (&x)[index];
}

inline float &Vec4f::operator[] (const std::size_t index) {
    return (&x)[index];
}

inline void Vec4f::Set (const float xx, const float yy, const float zz, const float ww) {
    x = xx;
    y = yy;
    z = zz;
    w = ww;
}

inline void Vec4f::Zero () {
    x = y = z = w = 0.0f;
}

//==========================
// Vec4f Operators
//==========================

/** Negate. */
inline Vec4f operator- (const Vec4f &v) {
    return Vec4f(-v.x, -v.y, -v.z, -v.w);
}

/** Multiply by scalar. */
inline Vec4f operator* (const Vec4f &v, const float a) {
    return Vec4f(a * v.x, a * v.y, a * v.z, a * v.w);
}

/** Multiply by scalar. */
inline Vec4f operator* (const float a, const Vec4f &v) {
    return Vec4f(a * v.x, a * v.y, a * v.z, a * v.w);
}

/** Piecewise multiplication. */
inline Vec4f operator* (const Vec4f &a, const Vec4f &b) {
    return Vec4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

/** Addition. */
inline Vec4f operator+ (const Vec4f &a, const Vec4f &b) {
    return Vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

/** Subtraction. */
inline Vec4f operator- (const Vec4f &a, const Vec4f &b) {
    return Vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

/** Division. */
inline Vec4f operator/ (const Vec4f &v, const float a) {
    float inva = 1.0f / a;
    return Vec4f(v.x * inva, v.y * inva, v.z * inva, v.w * inva);
}

/** Multiply by scalar in place. */
inline Vec4f& operator*= (Vec4f &v, const float a) {
    v.x *= a;
    v.y *= a;
    v.z *= a;
    v.w *= a;

    return v;
}

/** Piecewise multiplication in place. */
inline Vec4f& operator*= (Vec4f &a, const Vec4f &b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;

    return a;
}

/** Addition in place. */
inline Vec4f& operator+= (Vec4f &a, const Vec4f &b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;

    return a;
}

/** Subtraction in place. */
inline Vec4f& operator-= (Vec4f &a, const Vec4f &b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;

    return a;
}

/** Division in place. */
inline Vec4f& operator/= (Vec4f &v, const float a) {
    float inva = 1.0f / a;
    v.x *= inva;
    v.y *= inva;
    v.z *= inva;
    v.w *= inva;

    return v;
}

/** Piecewise division in place. */
inline Vec4f& operator/= (Vec4f &a, const Vec4f &b) {
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;

    return a;
}

//==========================
// Vec4f Length Operators
//==========================

inline float Vec4f::LengthSqr () const {
    return x * x + y * y + z * z + w * w;
}

inline float Vec4f::Length () const {
    return sqrt(x * x + y * y + z * z + w * w);
}

inline Vec4f Vec4f::SetLength (const float length) const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return Vec4f(*this);
    } else {
        return *this * (length / currMag);
    }
}

inline void Vec4f::SetLengthSelf (const float length) {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this *= (length / currMag);
    }

}

inline Vec4f Vec4f::Normalize () const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return Vec4f(*this);
    } else {
        return *this / currMag;
    }
}

inline void Vec4f::NormalizeSelf () {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this /= currMag;
    }
}

inline Vec4f Vec4f::ClampLength (const float max) const {
    if (LengthSqr() > (max * max)) {
        return SetLength(max);
    }

    return Vec4f(*this);
}

inline Vec4f Vec4f::ClampLength (const float min, const float max) const {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        return SetLength(min);
    }

    if (ls > (max * max)) {
        return SetLength(max);
    }

    return Vec4f(*this);
}

inline void Vec4f::ClampLengthSelf (const float max) {
    if (LengthSqr() > (max * max)) {
        SetLengthSelf(max);
    }
}

inline void Vec4f::ClampLengthSelf (const float min, const float max) {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        SetLengthSelf(min);
    }

    if (ls > (max * max)) {
        SetLengthSelf(max);
    }
}

inline Vec4f Vec4f::Clamp (const Vec4f &min, const Vec4f &max) const {
    return Vec4f(FMath::ClampFloat(x, min.x, max.x),
                 FMath::ClampFloat(y, min.y, max.y),
                 FMath::ClampFloat(z, min.z, max.z),
                 FMath::ClampFloat(w, min.w, max.w));
}

inline void Vec4f::ClampSelf (const Vec4f &min, const Vec4f &max) {
    x = FMath::ClampFloat(x, min.x, max.x);
    y = FMath::ClampFloat(y, min.y, max.y);
    z = FMath::ClampFloat(z, min.z, max.z);
    w = FMath::ClampFloat(w, min.w, max.w);
}

// Dot product.
inline float Vec4f::Dot (const Vec4f &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

inline Vec3f Vec4f::xyz () const {
    return Vec3f(x, y, z);
}

inline Vec2f Vec4f::xy () const {
    return Vec2f(x, y);
}

inline Vec2f Vec4f::xz () const {
    return Vec2f(x, z);
}

inline Vec2f Vec4f::yz () const {
    return Vec2f(y, z);
}

//==========================
// Vec4f Comparison
//==========================

// This comparison may be inaccurate, prefer Compare(val, threshold)
// where possible.
inline bool Vec4f::Compare (const Vec4f &other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

inline bool Vec4f::Compare (const Vec4f &other, const float threshold) const {
    return fabsf(x - other.x) <= threshold &&
           fabsf(y - other.y) <= threshold &&
           fabsf(z - other.z) <= threshold &&
           fabsf(w - other.w) <= threshold;
}

inline bool Vec4f::operator== (const Vec4f &other) const {
    return Compare(other);
}

inline bool Vec4f::operator!= (const Vec4f &other) const {
    return !Compare(other);
}

#endif /* __SGE_VECTOR4_H */
