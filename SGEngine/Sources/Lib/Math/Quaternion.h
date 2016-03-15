/*---  Quaternion.h - Quaternion Header  ---------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level Quaternion type.
 */
#ifndef __SGENGINE_QUATERNION_H_
#define __SGENGINE_QUATERNION_H_

#include <cmath> // sqrt, fabsf

namespace sge {

/**
 * Quaternion. Implements math operators and Quat->Vect
 * multiplication/rotation
 */
class Quaternion {
public:
    /* Quaternion Imaginary i component */
    float i;
    /* Quaternion Imaginary j component */
    float j;
    /* Quaternion Imaginary k component */
    float k;
    /* Quaternion Real w component */
    float w;

public:
    static const Quaternion IDENTITY;

public:
    /** Default Constructor */
    Quaternion () : i(0.0f), j(0.0f), k(0.0f), w(0.0f) { }

    /** Value Constructor */
    Quaternion (const float ii, const float jj, const float kk, const float ww)
        : i(ii), j(jj), k(kk), w(ww) { }

    /**
     * Create a Quaternion from an Axis/Angle rotation.
     * @param axis about which to rotate.
     * @param angle Angle of rotation in radians.
     */
    static Quaternion AxisAngle (const Vector3 &axis, const float angle);

    /**
     * Read access to this Quaternion's components using
     *subscript notation.
     */
    float operator[] (const u32 index) const;

    /**
     * Reference/write access to this Quaternion's components using
     * subscript notation.
     */
    float &operator[] (const u32 index);

    void Zero ();

    float LengthSqr () const;

    float Length () const;

    bool IsIdentity () const;

    bool IsUnit () const;

    Quaternion Normalize () const;

    void NormalizeSelf ();

    Quaternion Conjugate () const;

    float Dot (const Quaternion &rhs) const;

    Quaternion Cross (const Quaternion &rhs) const;

    /**
     * Scale quaternion.
     */
    Quaternion operator* (const float a) const;

    /**
     * Scale quaternion, reversed operands.
     */
    friend Quaternion operator* (const float a, const Quaternion &rhs);

    /**
     * Quaternion multiplication.
     */
    Quaternion operator* (const Quaternion &rhs) const;

    /**
     * Quaternion x Vector multiplication.
     */
    Quaternion operator* (const Vector3 &rhs) const;

    /**
     * Quaternion Addition.
     */
    Quaternion operator+ (const Quaternion &rhs) const;

    /**
     * Quaternion subraction.
     */
    Quaternion operator- (const Quaternion &rhs) const;

    /**
     * Quaternion division.
     */
    Quaternion operator/ (const float a) const;

    Quaternion &operator*= (const float a);

    Quaternion &operator*= (const Quaternion &rhs);

    Quaternion &operator+= (const Quaternion &rhs);

    Quaternion &operator-= (const Quaternion &rhs);

    Quaternion &operator/= (const float a);

    Quaternion &operator/= (const Quaternion &rhs);

    /**
     * Apply the rotation in this quaternion to a Vector3.
     */
    Vector3 Rotate (const Vector3 &vec) const;

    /**
     * Test if two Quaternions are equivalent.
     */
    bool Compare (const Quaternion &rhs) const;

    /**
     * Test if two Quaternions are similar within a
     * given tolerance.
     */
    bool Compare (const Quaternion &rhs, const float threshold) const;

    /**
     * Test if two Quaternions are equivalent.
     */
    bool operator== (const Quaternion &rhs) const;

    /**
     * Test if two Quaternions are not equivalent.
     */
    bool operator!= (const Quaternion &rhs) const;
};

// --------------------------------------------------------------------------

inline float Quaternion::operator[] (const u32 index) const {
    return (&i)[index];
}

inline float &Quaternion::operator[] (const u32 index) {
    return (&i)[index];
}

inline void Quaternion::Zero () {
    i = j = k = w = 0.0f;
}

inline float Quaternion::LengthSqr () const {
    return i * i + j * j + k * k + w * w;
}

inline float Quaternion::Length () const {
    return sqrt(i * i + j * j + k * k + w * w);
}

inline Quaternion Quaternion::Normalize () const {
    float length = Length();
    if (length == 0) {
        return Quaternion(*this);
    } else {
        return *this / length;
    }
}

inline void Quaternion::NormalizeSelf () {
    float length = Length();
    if (length != 0.0f) {
        *this /= length;
    }
}

inline bool Quaternion::IsIdentity () const {
    return *this == Quaternion::IDENTITY;
}

inline bool Quaternion::IsUnit () const {
    return 1 == LengthSqr();
}

inline Quaternion Quaternion::Conjugate () const {
    return Quaternion(-i, -j, -k, w);
}

inline float Quaternion::Dot (const Quaternion &rhs) const {
    return i * rhs.i + j * rhs.j + k * rhs.k;
}

inline Quaternion Quaternion::Cross (const Quaternion &rhs) const {
    return Quaternion(j * rhs.k - k * rhs.j,
                      k * rhs.i - i * rhs.k,
                      i * rhs.j - j * rhs.i,
                      w);
}

//======================
// Quaternion Operators
//======================

inline Quaternion Quaternion::operator* (const float a) const {
    return Quaternion(i * a, j * a, k * a, w * a);
}

inline Quaternion operator* (const float a, const Quaternion &rhs) {
    return Quaternion(a * rhs.i, a * rhs.j, a * rhs.k, a * rhs.w);
}

inline Quaternion Quaternion::operator* (const Quaternion &rhs) const {
    return Quaternion(i * rhs.w + w * rhs.i + j * rhs.k - k * rhs.j,
                      j * rhs.w + w * rhs.j + k * rhs.i - i * rhs.k,
                      k * rhs.w + w * rhs.k + i * rhs.j - j * rhs.i,
                      w * rhs.w - i * rhs.i - j * rhs.j - k * rhs.k);
}

inline Quaternion Quaternion::operator* (const Vector3 &rhs) const {
    return Quaternion(w * rhs.x + j * rhs.z - k * rhs.y,
                      w * rhs.y + k * rhs.x - i * rhs.z,
                      w * rhs.z + i * rhs.y - j * rhs.x,
                      -i * rhs.x - j * rhs.y - k * rhs.z);
}

inline Quaternion Quaternion::operator+ (const Quaternion &rhs) const {
    return Quaternion(i + rhs.i, j + rhs.j, k + rhs.k, w + rhs.w);
}

inline Quaternion Quaternion::operator- (const Quaternion &rhs) const {
    return Quaternion(i - rhs.i, j - rhs.j, k - rhs.k, w - rhs.w);
}

inline Quaternion Quaternion::operator/ (const float a) const {
    float inva = 1.0f / a;
    return Quaternion(i * inva, j * inva, k * inva, w * inva);
}

inline Quaternion &Quaternion::operator*= (const float a) {
    i *= a;
    j *= a;
    k *= a;
    w *= a;

    return *this;
}

inline Quaternion &Quaternion::operator*= (const Quaternion &rhs) {
    i = i * rhs.w + w * rhs.i + j * rhs.k - k * rhs.j;
    j = j * rhs.w + w * rhs.j + k * rhs.i - i * rhs.k;
    k = k * rhs.w + w * rhs.k + i * rhs.j - j * rhs.i;
    w = w * rhs.w - i * rhs.i - j * rhs.j - k * rhs.k;

    return *this;
}

inline Quaternion &Quaternion::operator+= (const Quaternion &rhs) {
    i += rhs.i;
    j += rhs.j;
    k += rhs.k;
    w += rhs.w;

    return *this;
}

inline Quaternion &Quaternion::operator-= (const Quaternion &rhs) {
    i -= rhs.i;
    j -= rhs.j;
    k -= rhs.k;
    w -= rhs.w;

    return *this;
}

inline Quaternion &Quaternion::operator/= (const float a) {
    float inva = 1.0f / a;

    i *= inva;
    j *= inva;
    k *= inva;
    w *= inva;

    return *this;
}

//=======================
// Quaternion Comparison
//=======================

inline bool Quaternion::Compare (const Quaternion &rhs) const {
    return i == rhs.i && j == rhs.j && k == rhs.k && w == rhs.w;
}

inline bool Quaternion::Compare (const Quaternion &rhs, const float threshold) const {
    if (fabsf(i - rhs.i) > threshold)
        return false;
    if (fabsf(j - rhs.j) > threshold)
        return false;
    if (fabsf(k - rhs.k) > threshold)
        return false;
    if (fabsf(w - rhs.w) > threshold)
        return false;
    return true;
}

inline bool Quaternion::operator== (const Quaternion &rhs) const {
    return Compare(rhs);
}

inline bool Quaternion::operator!= (const Quaternion &rhs) const {
    return !Compare(rhs);
}

} /* namespace sge */

#endif /* __SGENGINE_QUATERNION_H_ */
