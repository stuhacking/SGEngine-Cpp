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
    float operator[] (const u32 index) const;

    /** Reference access using an index. */
    float &operator[] (const u32 index);

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
    Vec4f Clamp (const Vec4f &min, const Vec4f &max);

    /**
     * Clamp Vec4f within minimum and maximum bounds, given by other
     * Vec4f values.
     * Destructive.
     * @param min Vec4f minimum bound
     * @param max Vec4f maximum bound
     */
    void ClampSelf (const Vec4f &min, const Vec4f &max);

    /**
     * Return a copy of this Vec4f with the components negated.
     */
    Vec4f operator- () const;

    /**
     * Return a scaled copy of this Vec4f.
     * @param a Scale factor
     */
    Vec4f operator* (const float a) const;

    /**
     * Return a scaled copy of a Vec4f, reversed operands.
     * @param a Scale Factor
     * @param rhs Vec4f to be scaled
     */
    friend Vec4f operator* (const float a, const Vec4f &rhs);

    /**
     * Multiply this Vec4f by another Vec4f componentwise.
     * @return Result of Vec4f multiplication
     */
    Vec4f operator* (const Vec4f &rhs) const;

    /**
     * Add this Vec4f to another Vec4f.
     * @return Result of Vec4f addition
     */
    Vec4f operator+ (const Vec4f &rhs) const;

    /**
     * Subtract another Vec4f from this Vec4f.
     * @return Result of Vec4f subtraction
     */
    Vec4f operator- (const Vec4f &rhs) const;

    /**
     * Divide this Vec4f by a scalar value.
     * @param a Divisor
     * @return Result of Vec4f division
     */
    Vec4f operator/ (const float a) const;

    /**
     * Multiply and mutate this Vec4f with a scalar value.
     * Destructive.
     * @param Scale Factor
     */
    Vec4f &operator*= (const float a);

    /**
     * Multiply and mutate this Vec4f componentwise with another Vec4f.
     * Destructive.
     */
    Vec4f &operator*= (const Vec4f &rhs);

    /**
     * Add and mutate this Vec4f with another Vec4f.
     * Destructive.
     */
    Vec4f &operator+= (const Vec4f &rhs);

    /**
     * Subtract and mutate this Vec4f with another Vec4f.
     * Destructive.
     */
    Vec4f &operator-= (const Vec4f &rhs);

    /**
     * Divide and mutate this Vec4f by a scalar value.
     * Destructive.
     */
    Vec4f &operator/= (const float a);

    /**
     * Divide and mutate this Vec4f componentwise with another Vec4f.
     * Destructive.
     */
    Vec4f &operator/= (const Vec4f &rhs);

    float Dot (const Vec4f &rhs) const;

    /** Swizzling */
    Vec3f xyz () const;

    Vec2f xy () const;

    Vec2f xz () const;

    Vec2f yz () const;

    /**
     * Compare this Vec4f against another Vec4f exactly.
     * @return true if this Vec4f exactly equals the other, false otherwise
     */
    bool Compare (const Vec4f &other) const;

    /**
     * Compare this Vec4f against another Vec4f within a given tolerance.
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

INLINE float Vec4f::operator[] (const u32 index) const {
    return (&x)[index];
}

INLINE float &Vec4f::operator[] (const u32 index) {
    return (&x)[index];
}

INLINE void Vec4f::Set (const float xx, const float yy, const float zz, const float ww) {
    x = xx;
    y = yy;
    z = zz;
    w = ww;
}

INLINE void Vec4f::Zero () {
    x = y = z = w = 0.0f;
}

//==========================
// Vec4f Length Operators
//==========================

INLINE float Vec4f::LengthSqr () const {
    return x * x + y * y + z * z + w * w;
}

INLINE float Vec4f::Length () const {
    return sqrt(x * x + y * y + z * z + w * w);
}

INLINE Vec4f Vec4f::SetLength (const float length) const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return Vec4f(*this);
    } else {
        return *this * (length / currMag);
    }
}

INLINE void Vec4f::SetLengthSelf (const float length) {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this *= (length / currMag);
    }

}

INLINE Vec4f Vec4f::Normalize () const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return Vec4f(*this);
    } else {
        return *this / currMag;
    }
}

INLINE void Vec4f::NormalizeSelf () {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this /= currMag;
    }
}

INLINE Vec4f Vec4f::ClampLength (const float max) const {
    if (LengthSqr() > (max * max)) {
        return SetLength(max);
    }

    return Vec4f(*this);
}

INLINE Vec4f Vec4f::ClampLength (const float min, const float max) const {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        return SetLength(min);
    }

    if (ls > (max * max)) {
        return SetLength(max);
    }

    return Vec4f(*this);
}

INLINE void Vec4f::ClampLengthSelf (const float max) {
    if (LengthSqr() > (max * max)) {
        SetLengthSelf(max);
    }
}

INLINE void Vec4f::ClampLengthSelf (const float min, const float max) {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        SetLengthSelf(min);
    }

    if (ls > (max * max)) {
        SetLengthSelf(max);
    }
}

INLINE Vec4f Vec4f::Clamp (const Vec4f &min, const Vec4f &max) {
    return Vec4f(FMath::ClampFloat(x, min.x, max.x),
                 FMath::ClampFloat(y, min.y, max.y),
                 FMath::ClampFloat(z, min.z, max.z),
                 FMath::ClampFloat(w, min.w, max.w));
}

INLINE void Vec4f::ClampSelf (const Vec4f &min, const Vec4f &max) {
    x = FMath::ClampFloat(x, min.x, max.x);
    y = FMath::ClampFloat(y, min.y, max.y);
    z = FMath::ClampFloat(z, min.z, max.z);
    w = FMath::ClampFloat(w, min.w, max.w);
}

INLINE Vec4f Vec4f::operator- () const {
    return Vec4f(-x, -y, -z, -w);
}

//==========================
// Vec4f Operators
//==========================

INLINE Vec4f Vec4f::operator* (const float rhs) const {
    return Vec4f(x * rhs, y * rhs, z * rhs, w * rhs);
}

INLINE Vec4f operator* (const float a, const Vec4f &rhs) {
    return Vec4f(a * rhs.x, a * rhs.y, a * rhs.z, a * rhs.w);
}

INLINE Vec4f Vec4f::operator* (const Vec4f &rhs) const {
    return Vec4f(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

INLINE Vec4f Vec4f::operator+ (const Vec4f &rhs) const {
    return Vec4f(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

INLINE Vec4f Vec4f::operator- (const Vec4f &rhs) const {
    return Vec4f(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

INLINE Vec4f Vec4f::operator/ (const float a) const {
    float inva = 1.0f / a;
    return Vec4f(x * inva, y * inva, z * inva, w * inva);
}

INLINE Vec4f &Vec4f::operator*= (const float a) {
    x *= a;
    y *= a;
    z *= a;
    w *= a;

    return *this;
}

INLINE Vec4f &Vec4f::operator*= (const Vec4f &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;

    return *this;
}

INLINE Vec4f &Vec4f::operator+= (const Vec4f &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;

    return *this;
}

INLINE Vec4f &Vec4f::operator-= (const Vec4f &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;

    return *this;
}

INLINE Vec4f &Vec4f::operator/= (const float a) {
    float inva = 1.0f / a;
    x *= inva;
    y *= inva;
    z *= inva;
    w *= inva;

    return *this;
}

INLINE Vec4f &Vec4f::operator/= (const Vec4f &rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;

    return *this;
}

// Dot product.
INLINE float Vec4f::Dot (const Vec4f &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

INLINE Vec3f Vec4f::xyz () const {
    return Vec3f(x, y, z);
}

INLINE Vec2f Vec4f::xy () const {
    return Vec2f(x, y);
}

INLINE Vec2f Vec4f::xz () const {
    return Vec2f(x, z);
}

INLINE Vec2f Vec4f::yz () const {
    return Vec2f(y, z);
}

//==========================
// Vec4f Comparison
//==========================

// This comparison may be inaccurate, prefer Compare(val, threshold)
// where possible.
INLINE bool Vec4f::Compare (const Vec4f &other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

INLINE bool Vec4f::Compare (const Vec4f &other, const float threshold) const {
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

INLINE bool Vec4f::operator== (const Vec4f &other) const {
    return Compare(other);
}

INLINE bool Vec4f::operator!= (const Vec4f &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_VECTOR4_H_ */
