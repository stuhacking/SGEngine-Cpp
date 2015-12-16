/*---  Vector2.h - 2D Vector Header  -------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 * 
 * @brief Defines a low level Vector2 type.
 */
#ifndef __SHLIB_VECTOR2_H_
#define __SHLIB_VECTOR2_H_

#include <cmath>

namespace sge {

/**
 * 2D Vector. Implement math operations for 2D geometry vectors.
 */
class Vector2 {
public:
    /** Vector2 X component. */
    float x;
    /** Vector2 Y component. */
    float y;

public:
    static const Vector2 ZERO;
    static const Vector2 ONE;

public:
    /** Construct a default Vector2 at 0,0. */
    Vector2 () : x(0.0f), y(0.0f) { }

    /** Fill Constructor. */
    Vector2 (const float f) : x(f), y(f) { }

    /** Construct a Vector2 using x, y coordinates. */
    Vector2 (const float xx, const float yy) : x(xx), y(yy) { }

    /** Value access by index. */
    float operator[] (const s32 index) const;

    /** Reference access by index. */
    float &operator[] (const s32 index);
    
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
     * Get the squared length of this Vector2.
     * @return The Vector's Length squared
     */
    float LengthSqr () const;

    /**
     * Get the length of this Vector2.
     * @return The Vector's length
     */
    float Length () const;

    /**
     * Set the length of this Vector2, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess.
     * Destructive.
     * @param length The desired new length
     */
    void SetLengthSelf (const float length);

    /**
     * Set the length of a Vector2, maintaining direction. If the
     * length is currently 0.0f then we don't attempt to guess. Returns
     * a new Vector2.
     * @param length The desired new length
     * @return New Vector2 with adjusted length
     */
    Vector2 SetLength (const float length) const;

    /**
     * Set the length of a Vector2 to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess. Returns
     * a new Vector2.
     * @return New normalized Vector2
     */
    Vector2 Normalize () const;
    
    /**
     * Set the length of this Vector2 to 1.0f, maintaining direction. If
     * the current length is 0.0f then we don't attempt to guess.
     * Destructive.
     */
    void NormalizeSelf ();

    /**
     * Return a new Vector2 which has been truncated if its length
     * exceeds the limit.
     * @param max Maximum length of Vector2
     * @return New clamped Vector2
     */
    Vector2 ClampLength (const float max) const;

    /**
     * Return a new Vector2 which has been extended or truncated
     * if its length falls outside the limits.
     * @param min Minimum length of Vector2
     * @param max Maximum length of Vector2
     * @return New clamped Vector2
     */
    Vector2 ClampLength (const float min, const float max) const;
    
    /**
     * Truncate this Vector2 if its length exceeds the limit.
     * Destructive.
     * @param max Maximum length of Vector2
     */
    void ClampLengthSelf (const float max);
    
    /**
     * Truncate or extend this Vector2 if its length is outside
     * the limits.
     * Destructive.
     * @param min Minimum length of Vector2
     * @param max Maximum length of Vector2
     */
    void ClampLengthSelf (const float min, const float max);
    
    /**
     * Clamp Vector2 within minimum and maximum bounds, given by other
     * Vector2 values.
     * Destructive.
     * @param min Vector2 minimum bound
     * @param max Vector2 maximum bound
     */
    void Clamp (const Vector2 &min, const Vector2 &max);

    /**
     * Return a copy of this Vector2 with the components negated.
     */
    Vector2 operator- () const;

    /**
     * Return a scaled copy of this Vector2.
     * @param a Scale factor
     */
    Vector2 operator* (const float a) const;

    /**
     * Return a scaled copy of a Vector2, reversed operands.
     * @param a Scale Factor
     * @param rhs Vector2 to be scaled
     */
    friend Vector2 operator* (const float a, const Vector2 &rhs);

    /**
     * Multiply this Vector2 by another Vector2 componentwise.
     * @return Result of Vector2 multiplication
     */
    Vector2 operator* (const Vector2 &rhs) const;

    /**
     * Add this Vector2 to another Vector2.
     * @return Result of Vector2 addition
     */
    Vector2 operator+ (const Vector2 &rhs) const;

    /**
     * Subtract another Vector2 from this Vector2.
     * @return Result of Vector2 subtraction
     */
    Vector2 operator- (const Vector2 &rhs) const;

    /**
     * Divide this Vector2 by a scalar value.
     * @param a Divisor
     * @return Result of Vector2 division
     */
    Vector2 operator/ (const float a) const;

    /**
     * Divide this Vector2 componenetwise by another Vector2.
     * @param rhs Divisor
     * @return Result of Vector2 division
     */
    Vector2 operator/ (const Vector2 &rhs) const;

    /**
     * Multiply and mutate this Vector2 with a scalar value.
     * Destructive.
     * @param Scale Factor
     */
    Vector2 &operator*= (const float a);

    /**
     * Multiply and mutate this Vector2 componentwise with another Vector2.
     * Destructive.
     */
    Vector2 &operator*= (const Vector2 &rhs);

    /**
     * Add and mutate this Vector2 with another Vector2.
     * Destructive.
     */
    Vector2 &operator+= (const Vector2 &rhs);

    /**
     * Subtract and mutate this Vector2 with another Vector2.
     * Destructive.
     */
    Vector2 &operator-= (const Vector2 &rhs);

    /**
     * Divide and mutate this Vector2 by a scalar value.
     * Destructive.
     */
    Vector2 &operator/= (const float a);

    /**
     * Divide and mutate this Vector2 componentwise with another Vector2.
     * Destructive.
     */
    Vector2 &operator/= (const Vector2 &rhs);

    /**
     * Return the dot product of this Vector2 and another Vector2.
     * @return Vector2 Dot Product
     */
    float Dot (const Vector2 &rhs) const;

    /**
     * Return the cross product of this Vector2 and another Vector2.
     * @return Vector2 Cross Product
     */
    float Cross (const Vector2 &rhs) const;

    /**
     * Return the mirror of this Vector2 about an arbitrary axis.
     * @param axis The axis of symmetry
     * @return Result of mirroring this Vector2 about axis
     */
    Vector2 Mirror (const Vector2 &axis) const;

    /**
     * Compare this Vector2 against another Vector2 exactly.
     * @return true if this Vector2 exactly equals the other, false otherwise
     */
    bool Compare (const Vector2 &other) const;

    /**
     * Compare this Vector2 against another Vector2 within a given tolerance.
     * @param threshold Tolerance within which Vector2 are considered equal
     * @return true if this Vector2 equals the other within given
     *         tolerance, false otherwise
     */
    bool Compare (const Vector2 &other, const float threshold) const;

    /**
     * Compare this Vector2 against another Vector2 exactly.
     * @return true if this Vector2 exactly equals the other, false otherwise
     */
    bool operator== (const Vector2 &other) const;

    /**
     * Compare this Vector2 against another Vector2 exactly.
     * @return true if this Vector2 does not equal the other, false otherwise
     */
    bool operator!= (const Vector2 &other) const;
};

// --------------------------------------------------------------------------

inline float Vector2::operator[] (const s32 index) const {
    return (&x)[index];
}

inline float &Vector2::operator[] (const s32 index) {
    return (&x)[index];
}

inline void Vector2::Set (const float xx, const float yy) {
    x = xx;
    y = yy;
}

inline void Vector2::Zero () {
    x = y = 0.0f;
}

//==========================
// Vector2 Length Operators
//==========================

inline float Vector2::LengthSqr () const {
    return x * x + y * y;
}

inline float Vector2::Length () const {
    return sqrt(x * x + y * y);
}

inline Vector2 Vector2::SetLength (float length) const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return Vector2(*this);
    } else {
        return *this * (length / currMag);
    }
}

inline void Vector2::SetLengthSelf (const float length) {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this *= (length / currMag);
    }
}

inline Vector2 Vector2::Normalize () const {
    float currMag = Length();
    if (currMag == 0.0f) {
        return Vector2(*this);
    } else {
        return *this / currMag;
    }
}

inline void Vector2::NormalizeSelf () {
    float currMag = Length();
    if (currMag != 0.0f) {
        *this /= currMag;
    }
}

inline Vector2 Vector2::ClampLength (const float max) const {
    if (LengthSqr() > (max * max)) {
        return SetLength(max);
    }
    
    return Vector2(*this);
}

inline Vector2 Vector2::ClampLength (const float min, const float max) const {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        return SetLength(min);
    }
    
    if (ls > (max * max)) {
        return SetLength(max);
    }
    
    return Vector2(*this);
}

inline void Vector2::ClampLengthSelf (const float max) {
    if (LengthSqr() > (max * max)) {
        SetLengthSelf(max);
    }
}

inline void Vector2::ClampLengthSelf (const float min, const float max) {
    float ls = LengthSqr();

    if (ls < (min * min)) {
        SetLengthSelf(min);
    }
    
    if (ls > (max * max)) {
        SetLengthSelf(max);
    }
}

inline void Vector2::Clamp (const Vector2 &min, const Vector2 &max) {
    x = FMath::ClampFloat(x, min.x, max.x);
    y = FMath::ClampFloat(y, min.y, max.y);
}

//==========================
// Vector2 Operators
//==========================

inline Vector2 Vector2::operator- () const {
    return Vector2(-x, -y);
}

inline Vector2 Vector2::operator* (const float rhs) const {
    return Vector2(x * rhs, y * rhs);
}

inline Vector2 operator* (const float a, const Vector2 &rhs) {
    return Vector2(a * rhs.x, a * rhs.y);
}

inline Vector2 Vector2::operator* (const Vector2 &rhs) const {
    return Vector2(x * rhs.x, y * rhs.y);
}

inline Vector2 Vector2::operator+ (const Vector2 &rhs) const {
    return Vector2(x + rhs.x, y + rhs.y);
}

inline Vector2 Vector2::operator- (const Vector2 &rhs) const {
    return Vector2(x - rhs.x, y - rhs.y);
}

inline Vector2 Vector2::operator/ (const float a) const {
    float inva = 1.0f / a;
    return Vector2(x * inva, y * inva);
}

inline Vector2 Vector2::operator/ (const Vector2 &rhs) const {
    return Vector2(x / rhs.x, y / rhs.y);
}

inline Vector2 &Vector2::operator*= (const float a) {
    x *= a;
    y *= a;

    return *this;
}

inline Vector2 &Vector2::operator*= (const Vector2 &rhs) {
    x *= rhs.x;
    y *= rhs.y;

    return *this;
}

inline Vector2 &Vector2::operator+= (const Vector2 &rhs) {
    x += rhs.x;
    y += rhs.y;

    return *this;
}

inline Vector2 &Vector2::operator-= (const Vector2 &rhs) {
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

inline Vector2 &Vector2::operator/= (const float a) {
    float inva = 1.0f / a;
    x *= inva;
    y *= inva;

    return *this;
}

inline Vector2 &Vector2::operator/= (const Vector2 &rhs) {
    x /= rhs.x;
    y /= rhs.y;

    return *this;
}

inline float Vector2::Dot (const Vector2 &rhs) const {
    return x * rhs.x + y * rhs.y;
}

inline float Vector2::Cross (const Vector2 &rhs) const {
    return x * rhs.y - y * rhs.x;
}

inline Vector2 Vector2::Mirror (const Vector2 &axis) const {
    return 2.0f * this->Dot(axis) * axis - *this;
}

//==========================
// Vector2 Comparisons
//==========================

// This comparison may be inaccurate, prefer Compare(val, threshold)
// where possible.
inline bool Vector2::Compare (const Vector2 &other) const {
    return x == other.x && y == other.y;
}

inline bool Vector2::Compare (const Vector2 &other, const float threshold) const {
    if (fabsf(x - other.x) > threshold)
        return false;
    if (fabsf(y - other.y) > threshold)
        return false;

    return true;
}

inline bool Vector2::operator== (const Vector2 &other) const {
    return Compare(other);
}

inline bool Vector2::operator!= (const Vector2 &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SHLIB_VECTOR2_H_ */
