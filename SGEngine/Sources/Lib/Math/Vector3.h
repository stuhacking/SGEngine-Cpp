/*---  Vector3.h - 3D Vector Header  -------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 * 
 * @brief Defines a low level Vector3 type.
 */
#ifndef __SHLIB_VECTOR3_H_
#define __SHLIB_VECTOR3_H_

#include <cmath> // fabs

namespace sge {

/**
 * 3D Vector. Implements math operations for 3D geometry vectors.
 */
class Vector3 {
public:
    /** Vector3 X component. */
    float x;

    /** Vector3 Y component. */
    float y;

    /** Vector3 Z component. */
    float z;

public:
    static const Vector3 ZERO;
    static const Vector3 ONE;
    static const Vector3 X;
    static const Vector3 Y;
    static const Vector3 Z;

public:
    /** Construct a default Vector3 at origin. */
    Vector3 () : x(0.0f), y(0.0f), z(0.0f) { }

    /** Fill Constructor. */
    Vector3 (const float f) : x(f), y(f), z(f) { }

    /** Construct a Vector3 using x, y, z coordinates. */
    Vector3 (const float xx, const float yy, const float zz)
        : x(xx), y(yy), z(zz) { }

    /** Value access using an index. */
    float operator[] (const s32 index) const;

    /** Reference access using an index. */
    float &operator[] (const s32 index);
    
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
     * Get the squared length of this Vector3.
     * @return The Vector's Length squared
     */
    float LengthSqr () const;

    /**
     * Get the length of this Vector3.
     * @return The Vector's length
     */
    float Length () const;

    /**
     * Set the length of a Vector3, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess.
     * @param length The desired new length
     * @return New Vector3 with adjusted length
     */
    Vector3 SetLength (const float length) const;
    
    /**
     * Set the length of this Vector3, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess.
     * Destructive.
     * @param length The desired new length
     */
    void SetLengthSelf (const float length);

    /**
     * Set the length of a Vector3 to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess.
     * @return New normalized Vector3
     */
    Vector3 Normalize () const;
    
    /**
     * Set the length of this Vector3 to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess.
     * Destructive.
     */
    void NormalizeSelf ();

    /**
     * Return a new Vector3 which has been truncated if its length
     * exceeds the limit.
     * @param max Maximum length of Vector3
     * @return New clamped Vector3
     */
    Vector3 ClampLength (const float max) const;

    /**
     * Return a new Vector3 which has been truncated if its length
     * exceeds the limit.
     * @param min Minimum length of Vector3
     * @param max Maximum length of Vector3
     * @return New clamped Vector3
     */
    Vector3 ClampLength (const float min, const float max) const;
    
    /**
     * Truncate this Vector3 if its length exceeds the limit.
     * Destructive.
     * @param max Maximum length of Vector3
     */
    void ClampLengthSelf (const float max);
    
    /**
     * Truncate this Vector3 if its length exceeds the limit.
     * Destructive.
     * @param min Minimum length of Vector3
     * @param max Maximum length of Vector3
     */
    void ClampLengthSelf (const float min, const float max);

    /**
     * Clamp Vector3 within minimum and maximum bounds, given by other
     * Vector3 values.
     * Destructive.
     * @param min Vector3 minimum bound
     * @param max Vector3 maximum bound
     */
    void Clamp (const Vector3 &min, const Vector3 &max);

    /**
     * Return a copy of this Vector3 with the components negated.
     */
    Vector3 operator- () const;

    /**
     * Return a scaled copy of this Vector3.
     * @param a Scale factor
     */
    Vector3 operator* (const float a) const;

    /**
     * Return a scaled copy of a Vector3, reversed operands.
     * @param a Scale Factor
     * @param rhs Vector3 to be scaled
     */
    friend Vector3 operator* (const float a, const Vector3 &rhs);

    /**
     * Multiply this Vector3 by another Vector3 componentwise.
     * @return Result of Vector3 multiplication
     */
    Vector3 operator* (const Vector3 &rhs) const;

    /**
     * Add this Vector3 to another Vector3.
     * @return Result of Vector3 addition
     */
    Vector3 operator+ (const Vector3 &rhs) const;

    /**
     * Subtract another Vector3 from this Vector3.
     * @return Result of Vector3 subtraction
     */
    Vector3 operator- (const Vector3 &rhs) const;

    /**
     * Divide this Vector3 by a scalar value.
     * @param a Divisor
     * @return Result of Vector3 division
     */
    Vector3 operator/ (const float a) const;

    /**
     * Multiply and mutate this Vector3 with a scalar value.
     * Destructive.
     * @param Scale Factor
     */
    Vector3 &operator*= (const float a);

    /**
     * Multiply and mutate this Vector3 componentwise with another Vector3.
     * Destructive.
     */
    Vector3 &operator*= (const Vector3 &rhs);

    /**
     * Add and mutate this Vector3 with another Vector3.
     * Destructive.
     */
    Vector3 &operator+= (const Vector3 &rhs);

    /**
     * Subtract and mutate this Vector3 with another Vector3.
     * Destructive.
     */
    Vector3 &operator-= (const Vector3 &rhs);

    /**
     * Divide and mutate this Vector3 by a scalar value.
     * Destructive.
     */
    Vector3 &operator/= (const float a);

    /**
     * Divide and mutate this Vector3 componentwise with another Vector3.
     * Destructive.
     */
    Vector3 &operator/= (const Vector3 &rhs);

    /**
     * Return the dot product of this Vector3 and another Vector3.
     * @return Vector3 Dot Product
     */
    float Dot (const Vector3 &rhs) const;

    /**
     * Return the cross product of this Vector3 and another Vector3. The
     * resulting Vector3 is perpendicular to A and B.
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
     * @return Vector2 Cross Product
     */
    Vector3 Cross (const Vector3 &rhs) const;

    /**
     * Return the mirror of this Vector3 about an arbitrary axis.
     * @param axis The axis of symmetry
     * @return Result of mirroring this Vector3 about axis
     */
    Vector3 Mirror (const Vector3 &axis) const;

    /**
     * Return the result of rotation this Vector3 by an angle around an
     * axis of rotation.
     * @param angle Angle of rotation in degrees
     * @param axis Axis of rotation as a Unit Vector3
     * @return New rotated Vector3
     */
    Vector3 Rotate (const float angle, const Vector3 &axis) const;

    /**
     * Return the result of rotation this Vector3 by an angle around an
     * axis of rotation.
     * Destructive.
     * @param angle Angle of rotation in degrees
     * @param axis Axis of rotation as a Unit Vector3
     */
    void RotateSelf (const float angle, const Vector3 &axis);

    /** Swizzling */
    Vector2 xy () const;

    Vector2 xz () const;

    Vector2 yz () const;

    /**
     * Compare this Vector3 against another Vector3 exactly.
     * @return true if this Vector3 exactly equals the other, false otherwise
     */
    bool Compare (const Vector3 &other) const;

    /**
     * Compare this Vector3 against another Vector3 within a given tolerance.
     * @param threshold Tolerance within which Vector3 are considered equal
     * @return true if this Vector3 equals the other within given
     *         tolerance, false otherwise
     */
    bool Compare (const Vector3 &other, const float threshold) const;

    /**
     * Compare this Vector3 against another Vector3 exactly.
     * @return true if this Vector3 exactly equals the other, false otherwise
     */
    bool operator== (const Vector3 &other) const;

    /**
     * Compare this Vector3 against another Vector3 exactly.
     * @return true if this Vector3 does not equal the other, false otherwise
     */
    bool operator!= (const Vector3 &other) const;
};

// --------------------------------------------------------------------------

inline float Vector3::operator[] (const s32 index) const {
    return (&x)[index];
}

inline float &Vector3::operator[] (const s32 index) {
    return (&x)[index];
}

inline void Vector3::Set (const float xx, const float yy, const float zz) {
    x = xx;
    y = yy;
    z = zz;
}

inline void Vector3::Zero () {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

//==========================
// Vector3 Length Operators
//==========================

inline float Vector3::LengthSqr () const {
    return x * x + y * y + z * z;
}

inline float Vector3::Length () const {
    return sqrt(x * x + y * y + z * z);
}

inline Vector3 Vector3::SetLength (float length) const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return Vector3(*this);
    } else {
        return *this * (length / currMag);
    }
}

inline void Vector3::SetLengthSelf (const float length) {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this *= (length / currMag);
    }

}

inline Vector3 Vector3::Normalize () const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return Vector3(*this);
    } else {
        return *this / currMag;
    }
}

inline void Vector3::NormalizeSelf () {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this /= currMag;
    }
}

inline Vector3 Vector3::ClampLength (const float max) const {
    if (LengthSqr() > (max * max)) {
        return SetLength(max);
    }
    
    return Vector3(*this);
}

inline Vector3 Vector3::ClampLength (const float min, const float max) const {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        return SetLength(min);
    }
    
    if (ls > (max * max)) {
        return SetLength(max);
    }
    
    return Vector3(*this);
}

inline void Vector3::ClampLengthSelf (const float max) {
    if (LengthSqr() > (max * max)) {
        SetLengthSelf(max);
    }
}

inline void Vector3::ClampLengthSelf (const float min, const float max) {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        SetLengthSelf(min);
    }
    
    if (ls > (max * max)) {
        SetLengthSelf(max);
    }
}

inline void Vector3::Clamp (const Vector3 &min, const Vector3 &max) {
    x = FMath::ClampFloat(x, min.x, max.x);
    y = FMath::ClampFloat(y, min.y, max.y);
    z = FMath::ClampFloat(z, min.z, max.z);
}

//==========================
// Vector3 Operators
//==========================

inline Vector3 Vector3::operator- () const {
    return Vector3(-x, -y, -z);
}

inline Vector3 Vector3::operator* (const float rhs) const {
    return Vector3(x * rhs, y * rhs, z * rhs);
}

inline Vector3 operator* (const float a, const Vector3 &rhs) {
    return Vector3(a * rhs.x, a * rhs.y, a * rhs.z);
}

inline Vector3 Vector3::operator* (const Vector3 &rhs) const {
    return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

inline Vector3 Vector3::operator+ (const Vector3 &rhs) const {
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

inline Vector3 Vector3::operator- (const Vector3 &rhs) const {
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

inline Vector3 Vector3::operator/ (const float a) const {
    float inva = 1.0f / a;
    return Vector3(x * inva, y * inva, z * inva);
}

inline Vector3 &Vector3::operator*= (const float a) {
    x *= a;
    y *= a;
    z *= a;

    return *this;
}

inline Vector3 &Vector3::operator*= (const Vector3 &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;

    return *this;
}

inline Vector3 &Vector3::operator+= (const Vector3 &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
}

inline Vector3 &Vector3::operator-= (const Vector3 &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;

    return *this;
}

inline Vector3 &Vector3::operator/= (const float a) {
    float inva = 1.0f / a;
    x *= inva;
    y *= inva;
    z *= inva;

    return *this;
}

inline Vector3 &Vector3::operator/= (const Vector3 &rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;

    return *this;
}

// Dot product.
inline float Vector3::Dot (const Vector3 &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

// Vector3 Cross Product.
inline Vector3 Vector3::Cross (const Vector3 &rhs) const {
    return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

inline Vector3 Vector3::Mirror (const Vector3 &axis) const {
    return 2.0f * this->Dot(axis) * axis - *this;
}

inline Vector2 Vector3::xy () const {
    return Vector2(x, y);
}

inline Vector2 Vector3::xz () const {
    return Vector2(x, z);
}

inline Vector2 Vector3::yz () const {
    return Vector2(y, z);
}

//==========================
// Vector3 Comparison
//==========================

// This comparison may be inaccurate, prefer Compare(val, threshold)
// where possible.
inline bool Vector3::Compare (const Vector3 &other) const {
    return x == other.x && y == other.y && z == other.z;
}

inline bool Vector3::Compare (const Vector3 &other, const float threshold) const {
    if (fabs(x - other.x) > threshold)
        return false;
    if (fabs(y - other.y) > threshold)
        return false;
    if (fabs(z - other.z) > threshold)
        return false;

    return true;
}

inline bool Vector3::operator== (const Vector3 &other) const {
    return Compare(other);
}

inline bool Vector3::operator!= (const Vector3 &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SHLIB_VECTOR3_H_ */
