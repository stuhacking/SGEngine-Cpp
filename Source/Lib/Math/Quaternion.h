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

namespace sge {

/**
 * Quat4f. Implements math operators and Quat->Vect
 * multiplication/rotation
 */
class Quat4f {
public:
    /* Quat4f Imaginary (i,j,k) components */
    float i = 0.0f;
    float j = 0.0f;
    float k = 0.0f;

    /* Quat4f real component */
    float w = 0.0f;

public:
    static const Quat4f IDENTITY;

public:
    /** Default Constructor */
    Quat4f () = default;

    /** Value Constructor */
    explicit Quat4f (const float ii, const float jj, const float kk, const float ww)
        : i(ii), j(jj), k(kk), w(ww) { }

    /**
     * Create a Quat4f from an Axis/Angle rotation.
     * @param axis about which to rotate.
     * @param angle Angle of rotation in radians.
     */
    static Quat4f AxisAngle (const Vec3f &axis, const float angle);

    /**
     * Read access to this Quat4f's components using
     *subscript notation.
     */
    float operator[] (const u32 index) const;

    /**
     * Reference/write access to this Quat4f's components using
     * subscript notation.
     */
    float &operator[] (const u32 index);

    void Zero ();

    float LengthSqr () const;

    float Length () const;

    bool IsIdentity () const;

    bool IsUnit () const;

    Quat4f Normalize () const;

    void NormalizeSelf ();

    Quat4f Conjugate () const;

    float Dot (const Quat4f &rhs) const;

    Quat4f Cross (const Quat4f &rhs) const;

    /**
     * Scale quaternion.
     */
    Quat4f operator* (const float a) const;

    /**
     * Scale quaternion, reversed operands.
     */
    friend Quat4f operator* (const float a, const Quat4f &rhs);

    /**
     * Quat4f multiplication.
     */
    Quat4f operator* (const Quat4f &rhs) const;

    /**
     * Quat4f x Vector multiplication.
     */
    Quat4f operator* (const Vec3f &rhs) const;

    /**
     * Quat4f Addition.
     */
    Quat4f operator+ (const Quat4f &rhs) const;

    /**
     * Quat4f subraction.
     */
    Quat4f operator- (const Quat4f &rhs) const;

    /**
     * Quat4f division.
     */
    Quat4f operator/ (const float a) const;

    Quat4f &operator*= (const float a);

    Quat4f &operator*= (const Quat4f &rhs);

    Quat4f &operator+= (const Quat4f &rhs);

    Quat4f &operator-= (const Quat4f &rhs);

    Quat4f &operator/= (const float a);

    Quat4f &operator/= (const Quat4f &rhs);

    /**
     * Apply the rotation in this quaternion to a Vec3f.
     */
    Vec3f Rotate (const Vec3f &vec) const;

    /**
     * Test if two Quat4fs are equivalent.
     */
    bool Compare (const Quat4f &rhs) const;

    /**
     * Test if two Quat4fs are similar within a
     * given tolerance.
     */
    bool Compare (const Quat4f &rhs, const float threshold) const;

    /**
     * Test if two Quat4fs are equivalent.
     */
    bool operator== (const Quat4f &rhs) const;

    /**
     * Test if two Quat4fs are not equivalent.
     */
    bool operator!= (const Quat4f &rhs) const;
};

// --------------------------------------------------------------------------

INLINE float Quat4f::operator[] (const u32 index) const {
    return (&i)[index];
}

INLINE float &Quat4f::operator[] (const u32 index) {
    return (&i)[index];
}

INLINE void Quat4f::Zero () {
    i = j = k = w = 0.0f;
}

INLINE float Quat4f::LengthSqr () const {
    return i * i + j * j + k * k + w * w;
}

INLINE float Quat4f::Length () const {
    return sqrt(i * i + j * j + k * k + w * w);
}

INLINE Quat4f Quat4f::Normalize () const {
    float length = Length();
    if (length == 0) {
        return Quat4f(*this);
    } else {
        return *this / length;
    }
}

INLINE void Quat4f::NormalizeSelf () {
    float length = Length();
    if (length != 0.0f) {
        *this /= length;
    }
}

INLINE bool Quat4f::IsIdentity () const {
    return *this == Quat4f::IDENTITY;
}

INLINE bool Quat4f::IsUnit () const {
    return 1 == LengthSqr();
}

INLINE Quat4f Quat4f::Conjugate () const {
    return Quat4f(-i, -j, -k, w);
}

INLINE float Quat4f::Dot (const Quat4f &rhs) const {
    return i * rhs.i + j * rhs.j + k * rhs.k;
}

INLINE Quat4f Quat4f::Cross (const Quat4f &rhs) const {
    return Quat4f(j * rhs.k - k * rhs.j,
                      k * rhs.i - i * rhs.k,
                      i * rhs.j - j * rhs.i,
                      w);
}

//======================
// Quat4f Operators
//======================

INLINE Quat4f Quat4f::operator* (const float a) const {
    return Quat4f(i * a, j * a, k * a, w * a);
}

INLINE Quat4f operator* (const float a, const Quat4f &rhs) {
    return Quat4f(a * rhs.i, a * rhs.j, a * rhs.k, a * rhs.w);
}

INLINE Quat4f Quat4f::operator* (const Quat4f &rhs) const {
    return Quat4f(i * rhs.w + w * rhs.i + j * rhs.k - k * rhs.j,
                      j * rhs.w + w * rhs.j + k * rhs.i - i * rhs.k,
                      k * rhs.w + w * rhs.k + i * rhs.j - j * rhs.i,
                      w * rhs.w - i * rhs.i - j * rhs.j - k * rhs.k);
}

INLINE Quat4f Quat4f::operator* (const Vec3f &rhs) const {
    return Quat4f(w * rhs.x + j * rhs.z - k * rhs.y,
                      w * rhs.y + k * rhs.x - i * rhs.z,
                      w * rhs.z + i * rhs.y - j * rhs.x,
                      -i * rhs.x - j * rhs.y - k * rhs.z);
}

INLINE Quat4f Quat4f::operator+ (const Quat4f &rhs) const {
    return Quat4f(i + rhs.i, j + rhs.j, k + rhs.k, w + rhs.w);
}

INLINE Quat4f Quat4f::operator- (const Quat4f &rhs) const {
    return Quat4f(i - rhs.i, j - rhs.j, k - rhs.k, w - rhs.w);
}

INLINE Quat4f Quat4f::operator/ (const float a) const {
    float inva = 1.0f / a;
    return Quat4f(i * inva, j * inva, k * inva, w * inva);
}

INLINE Quat4f &Quat4f::operator*= (const float a) {
    i *= a;
    j *= a;
    k *= a;
    w *= a;

    return *this;
}

INLINE Quat4f &Quat4f::operator*= (const Quat4f &rhs) {
    i = i * rhs.w + w * rhs.i + j * rhs.k - k * rhs.j;
    j = j * rhs.w + w * rhs.j + k * rhs.i - i * rhs.k;
    k = k * rhs.w + w * rhs.k + i * rhs.j - j * rhs.i;
    w = w * rhs.w - i * rhs.i - j * rhs.j - k * rhs.k;

    return *this;
}

INLINE Quat4f &Quat4f::operator+= (const Quat4f &rhs) {
    i += rhs.i;
    j += rhs.j;
    k += rhs.k;
    w += rhs.w;

    return *this;
}

INLINE Quat4f &Quat4f::operator-= (const Quat4f &rhs) {
    i -= rhs.i;
    j -= rhs.j;
    k -= rhs.k;
    w -= rhs.w;

    return *this;
}

INLINE Quat4f &Quat4f::operator/= (const float a) {
    float inva = 1.0f / a;

    i *= inva;
    j *= inva;
    k *= inva;
    w *= inva;

    return *this;
}

//=======================
// Quat4f Comparison
//=======================

INLINE bool Quat4f::Compare (const Quat4f &rhs) const {
    return i == rhs.i && j == rhs.j && k == rhs.k && w == rhs.w;
}

INLINE bool Quat4f::Compare (const Quat4f &rhs, const float threshold) const {
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

INLINE bool Quat4f::operator== (const Quat4f &rhs) const {
    return Compare(rhs);
}

INLINE bool Quat4f::operator!= (const Quat4f &rhs) const {
    return !Compare(rhs);
}

} /* namespace sge */

#endif /* __SGENGINE_QUATERNION_H_ */
