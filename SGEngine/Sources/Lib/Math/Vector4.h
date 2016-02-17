/*---  Vector4.h - 4D Vector Header  -------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 * 
 * @brief Defines a low level Vector4 type.
 */
#ifndef __SGENGINE_VECTOR4_H_
#define __SGENGINE_VECTOR4_H_

#include <cmath>

namespace sge {

/**
 * 4D Vector. Implement math operations for 4D geometry vectors.
 */
class Vector4 {
public:
    /** Vector4 X component. */
    float x;
    /** Vector4 Y component. */
    float y;
    /** Vector4 Z component. */
    float z;
    /** Vector4 W component. */
    float w;

public:
    static const Vector4 ZERO;
    static const Vector4 ONE;
    static const Vector4 X;
    static const Vector4 Y;
    static const Vector4 Z;
    static const Vector4 W;

public:
    /** Construct a default Vector4 at origin. */
    Vector4 () : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }

    /** Fill Constructor. */
    Vector4 (const float f) : x(f), y(f), z(f), w(f) { }

    /** Construct a Vector4 using x, y, z, w coordinates. */
    Vector4 (const float xx, const float yy, const float zz, const float ww)
        : x(xx), y(yy), z(zz), w(ww) { }

    /** Construct a Vector4 using the x,y,z components of a Vector3. */
    Vector4 (const Vector3 &vec, const float ww) : x(vec.x), y(vec.y), z(vec.z), w(ww) { }

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
     * Get the squared length of this Vector4.
     * @return The Vector's Length squared
     */
    float LengthSqr () const;

    /**
     * Get the length of this Vector4.
     * @return The Vector's length
     */
    float Length () const;

    /**
     * Set the length of a Vector4, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess. Returns
     * a new Vector4.
     * @param vec Original Vector4
     * @param length The desired new length
     * @return New Vector4 with adjusted length
     */
    Vector4 SetLength (const float length) const;

    /**
     * Set the length of this Vector4, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess.
     * Destructive.
     * @param length The desired new length
     */
    void SetLengthSelf (const float length);

    /**
     * Set the length of a Vector4 to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess. Returns
     * a new Vector4.
     * @param vec Original Vector4
     * @return New normalized Vector4
     */
    Vector4 Normalize () const;

    /**
     * Set the length of this Vector4 to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess.
     * Destructive.
     */
    void NormalizeSelf ();

    /**
     * Return a new Vector4 which has been truncated if its length
     * exceeds the limit.
     * @param max Maximum length of Vector4
     * @return New (possibly truncated) Vector4
     */
    Vector4 ClampLength (const float max) const;

    /**
     * Return a new Vector4 which has been extended or truncated 
     * if its length is outside the limits.
     * @param min Minimum length of Vector4
     * @param max Maximum length of Vector4
     * @return New (possibly truncated) Vector4
     */
    Vector4 ClampLength (const float min, const float max) const;

    /**
     * Truncate this Vector4 if its length exceeds the limit.
     * Destructive.
     * @param max Maximum length of Vector4
     */
    void ClampLengthSelf (const float max);

    /**
     * Truncate or extend this Vector4 if its length is outside
     * the limits.
     * Destructive.
     * @param min Minimum length of Vector4
     * @param max Maximum length of Vector4
     */
    void ClampLengthSelf (const float min, const float max);

    /**
     * Clamp Vector4 within minimum and maximum bounds, given by other
     * Vector4 values.
     * Destructive.
     * @param min Vector4 minimum bound
     * @param max Vector4 maximum bound
     */
    void Clamp (const Vector4 &min, const Vector4 &max);

    /**
     * Return a copy of this Vector4 with the components negated.
     */
    Vector4 operator- () const;

    /**
     * Return a scaled copy of this Vector4.
     * @param a Scale factor
     */
    Vector4 operator* (const float a) const;

    /**
     * Return a scaled copy of a Vector4, reversed operands.
     * @param a Scale Factor
     * @param rhs Vector4 to be scaled
     */
    friend Vector4 operator* (const float a, const Vector4 &rhs);

    /**
     * Multiply this Vector4 by another Vector4 componentwise.
     * @return Result of Vector4 multiplication
     */
    Vector4 operator* (const Vector4 &rhs) const;

    /**
     * Add this Vector4 to another Vector4.
     * @return Result of Vector4 addition
     */
    Vector4 operator+ (const Vector4 &rhs) const;

    /**
     * Subtract another Vector4 from this Vector4.
     * @return Result of Vector4 subtraction
     */
    Vector4 operator- (const Vector4 &rhs) const;

    /**
     * Divide this Vector4 by a scalar value.
     * @param a Divisor
     * @return Result of Vector4 division
     */
    Vector4 operator/ (const float a) const;

    /**
     * Multiply and mutate this Vector4 with a scalar value.
     * Destructive.
     * @param Scale Factor
     */
    Vector4 &operator*= (const float a);

    /**
     * Multiply and mutate this Vector4 componentwise with another Vector4.
     * Destructive.
     */
    Vector4 &operator*= (const Vector4 &rhs);

    /**
     * Add and mutate this Vector4 with another Vector4.
     * Destructive.
     */
    Vector4 &operator+= (const Vector4 &rhs);

    /**
     * Subtract and mutate this Vector4 with another Vector4.
     * Destructive.
     */
    Vector4 &operator-= (const Vector4 &rhs);

    /**
     * Divide and mutate this Vector4 by a scalar value.
     * Destructive.
     */
    Vector4 &operator/= (const float a);

    /**
     * Divide and mutate this Vector4 componentwise with another Vector4.
     * Destructive.
     */
    Vector4 &operator/= (const Vector4 &rhs);

    float Dot (const Vector4 &rhs) const;

    Vector4 Cross (const Vector4 &rhs) const;

    /** Swizzling */
    Vector3 xyz () const;

    Vector2 xy () const;

    Vector2 xz () const;

    Vector2 yz () const;

    /**
     * Compare this Vector4 against another Vector4 exactly.
     * @return true if this Vector4 exactly equals the other, false otherwise
     */
    bool Compare (const Vector4 &other) const;

    /**
     * Compare this Vector4 against another Vector4 within a given tolerance.
     * @param threshold Tolerance within which Vector4 are considered equal
     * @return true if this Vector4 equals the other within given
     *         tolerance, false otherwise
     */
    bool Compare (const Vector4 &other, const float threshold) const;

    /**
     * Compare this Vector4 against another Vector4 exactly.
     * @return true if this Vector4 exactly equals the other, false otherwise
     */
    bool operator== (const Vector4 &other) const;

    /**
     * Compare this Vector4 against another Vector4 exactly.
     * @return true if this Vector4 does not equal the other, false otherwise
     */
    bool operator!= (const Vector4 &other) const;
};

// --------------------------------------------------------------------------

inline float Vector4::operator[] (const u32 index) const {
    return (&x)[index];
}

inline float &Vector4::operator[] (const u32 index) {
    return (&x)[index];
}

inline void Vector4::Set (const float xx, const float yy, const float zz, const float ww) {
    x = xx;
    y = yy;
    z = zz;
    w = ww;
}

inline void Vector4::Zero () {
    x = y = z = w = 0.0f;
}

//==========================
// Vector4 Length Operators
//==========================

inline float Vector4::LengthSqr () const {
    return x * x + y * y + z * z + w * w;
}

inline float Vector4::Length () const {
    return sqrt(x * x + y * y + z * z + w * w);
}

inline Vector4 Vector4::SetLength (float length) const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return Vector4(*this);
    } else {
        return *this * (length / currMag);
    }
}

inline void Vector4::SetLengthSelf (const float length) {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this *= (length / currMag);
    }

}

inline Vector4 Vector4::Normalize () const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return Vector4(*this);
    } else {
        return *this / currMag;
    }
}

inline void Vector4::NormalizeSelf () {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this /= currMag;
    }
}

inline Vector4 Vector4::ClampLength (const float max) const {
    if (LengthSqr() > (max * max)) {
        return SetLength(max);
    }
    
    return Vector4(*this);
}

inline Vector4 Vector4::ClampLength (const float min, const float max) const {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        return SetLength(min);
    }
    
    if (ls > (max * max)) {
        return SetLength(max);
    }
    
    return Vector4(*this);
}

inline void Vector4::ClampLengthSelf (const float max) {
    if (LengthSqr() > (max * max)) {
        SetLengthSelf(max);
    }
}

inline void Vector4::ClampLengthSelf (const float min, const float max) {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        SetLengthSelf(min);
    }
    
    if (ls > (max * max)) {
        SetLengthSelf(max);
    }
}

inline void Vector4::Clamp (const Vector4 &min, const Vector4 &max) {
    x = FMath::ClampFloat(x, min.x, max.x);
    y = FMath::ClampFloat(y, min.y, max.y);
    z = FMath::ClampFloat(z, min.z, max.z);
    w = FMath::ClampFloat(w, min.w, max.w);
}

inline Vector4 Vector4::operator- () const {
    return Vector4(-x, -y, -z, -w);
}

//==========================
// Vector4 Operators
//==========================

inline Vector4 Vector4::operator* (const float rhs) const {
    return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
}

inline Vector4 operator* (const float a, const Vector4 &rhs) {
    return Vector4(a * rhs.x, a * rhs.y, a * rhs.z, a * rhs.w);
}

inline Vector4 Vector4::operator* (const Vector4 &rhs) const {
    return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

inline Vector4 Vector4::operator+ (const Vector4 &rhs) const {
    return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

inline Vector4 Vector4::operator- (const Vector4 &rhs) const {
    return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

inline Vector4 Vector4::operator/ (const float a) const {
    float inva = 1.0f / a;
    return Vector4(x * inva, y * inva, z * inva, w * inva);
}

inline Vector4 &Vector4::operator*= (const float a) {
    x *= a;
    y *= a;
    z *= a;
    w *= a;

    return *this;
}

inline Vector4 &Vector4::operator*= (const Vector4 &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;

    return *this;
}

inline Vector4 &Vector4::operator+= (const Vector4 &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;

    return *this;
}

inline Vector4 &Vector4::operator-= (const Vector4 &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;

    return *this;
}

inline Vector4 &Vector4::operator/= (const float a) {
    float inva = 1.0f / a;
    x *= inva;
    y *= inva;
    z *= inva;
    w *= inva;

    return *this;
}

inline Vector4 &Vector4::operator/= (const Vector4 &rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;

    return *this;
}

// Dot product.
inline float Vector4::Dot (const Vector4 &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

inline Vector3 Vector4::xyz () const {
    return Vector3(x, y, z);
}

inline Vector2 Vector4::xy () const {
    return Vector2(x, y);
}

inline Vector2 Vector4::xz () const {
    return Vector2(x, z);
}

inline Vector2 Vector4::yz () const {
    return Vector2(y, z);
}

//==========================
// Vector4 Comparison
//==========================

// This comparison may be inaccurate, prefer Compare(val, threshold)
// where possible.
inline bool Vector4::Compare (const Vector4 &other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

inline bool Vector4::Compare (const Vector4 &other, const float threshold) const {
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

inline bool Vector4::operator== (const Vector4 &other) const {
    return Compare(other);
}

inline bool Vector4::operator!= (const Vector4 &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_VECTOR4_H_ */
