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
#ifndef __SGE_QUATERNION_H
#define __SGE_QUATERNION_H

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
    float operator[] (const std::size_t index) const;

    /**
     * Reference/write access to this Quat4f's components using
     * subscript notation.
     */
    float &operator[] (const std::size_t index);

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

inline float Quat4f::operator[] (const std::size_t index) const {
    return (&i)[index];
}

inline float &Quat4f::operator[] (const std::size_t index) {
    return (&i)[index];
}

inline void Quat4f::Zero () {
    i = j = k = w = 0.0f;
}

//======================
// Quat4f Operators
//======================

/** Multiply by scalar. */
inline Quat4f operator* (const Quat4f &q, const float a) {
    return Quat4f(a * q.i, a * q.j, a * q.k, a * q.w);
}

/** Multiply by scalar. */
inline Quat4f operator* (const float a, const Quat4f &q) {
    return Quat4f(a * q.i, a * q.j, a * q.k, a * q.w);
}

/** Multiply by quaternion. */
inline Quat4f operator* (const Quat4f &a, const Quat4f &b) {
    return Quat4f(a.i * b.w + a.w * b.i + a.j * b.k - a.k * b.j,
                  a.j * b.w + a.w * b.j + a.k * b.i - a.i * b.k,
                  a.k * b.w + a.w * b.k + a.i * b.j - a.j * b.i,
                  a.w * b.w - a.i * b.i - a.j * b.j - a.k * b.k);
}

/** Multiply by Vector3. */
inline Quat4f operator* (const Quat4f &a, const Vec3f &b) {
    return Quat4f(a.w * b.x + a.j * b.z - a.k * b.y,
                  a.w * b.y + a.k * b.x - a.i * b.z,
                  a.w * b.z + a.i * b.y - a.j * b.x,
                  -a.i * b.x - a.j * b.y - a.k * b.z);
}

/** Addition. */
inline Quat4f operator+ (const Quat4f &a, const Quat4f &b) {
    return Quat4f(a.i + b.i, a.j + b.j, a.k + b.k, a.w + b.w);
}

/** Subtraction. */
inline Quat4f operator- (const Quat4f &a, const Quat4f &b) {
    return Quat4f(a.i - b.i, a.j - b.j, a.k - b.k, a.w - b.w);
}

/** Division */
inline Quat4f operator/ (const Quat4f &q, const float a) {
    float inva = 1.0f / a;
    return Quat4f(q.i * inva, q.j * inva, q.k * inva, q.w * inva);
}

/** Multiply by scalar in place. */
inline Quat4f& operator*= (Quat4f &q, const float a) {
    q.i *= a;
    q.j *= a;
    q.k *= a;
    q.w *= a;

    return q;
}

/** Multiply by quaternion in place. */
inline Quat4f& operator*= (Quat4f &a, const Quat4f &b) {
    a.i = a.i * b.w + a.w * b.i + a.j * b.k - a.k * b.j;
    a.j = a.j * b.w + a.w * b.j + a.k * b.i - a.i * b.k;
    a.k = a.k * b.w + a.w * b.k + a.i * b.j - a.j * b.i;
    a.w = a.w * b.w - a.i * b.i - a.j * b.j - a.k * b.k;

    return a;
}

/** Multiply by Vector3 in place. */
inline Quat4f& operator* (Quat4f &a, const Vec3f &b) {
    a.i = a.w * b.x + a.j * b.z - a.k * b.y;
    a.j = a.w * b.y + a.k * b.x - a.i * b.z;
    a.k = a.w * b.z + a.i * b.y - a.j * b.x;
    a.w = -a.i * b.x - a.j * b.y - a.k * b.z;

    return a;
}

/** Addition in place. */
inline Quat4f& operator+= (Quat4f &a, const Quat4f &b) {
    a.i += b.i;
    a.j += b.j;
    a.k += b.k;
    a.w += b.w;

    return a;
}

/** Subtraction in place. */
inline Quat4f& operator-= (Quat4f &a, const Quat4f &b) {
    a.i -= b.i;
    a.j -= b.j;
    a.k -= b.k;
    a.w -= b.w;

    return a;
}

/** Division in place. */
inline Quat4f& operator/= (Quat4f &q, const float a) {
    float inva = 1.0f / a;

    q.i *= inva;
    q.j *= inva;
    q.k *= inva;
    q.w *= inva;

    return q;
}

inline float Quat4f::LengthSqr () const {
    return i * i + j * j + k * k + w * w;
}

inline float Quat4f::Length () const {
    return sqrt(i * i + j * j + k * k + w * w);
}

inline Quat4f Quat4f::Normalize () const {
    float length = Length();
    if (length == 0) {
        return Quat4f(*this);
    } else {
        return *this / length;
    }
}

inline void Quat4f::NormalizeSelf () {
    float length = Length();
    if (length != 0.0f) {
        *this /= length;
    }
}

inline bool Quat4f::IsIdentity () const {
    return *this == Quat4f::IDENTITY;
}

inline bool Quat4f::IsUnit () const {
    return 1 == LengthSqr();
}

inline Quat4f Quat4f::Conjugate () const {
    return Quat4f(-i, -j, -k, w);
}

inline float Quat4f::Dot (const Quat4f &rhs) const {
    return i * rhs.i + j * rhs.j + k * rhs.k;
}

inline Quat4f Quat4f::Cross (const Quat4f &rhs) const {
    return Quat4f(j * rhs.k - k * rhs.j,
                      k * rhs.i - i * rhs.k,
                      i * rhs.j - j * rhs.i,
                      w);
}


//=======================
// Quat4f Comparison
//=======================

inline bool Quat4f::Compare (const Quat4f &rhs) const {
    return i == rhs.i && j == rhs.j && k == rhs.k && w == rhs.w;
}

inline bool Quat4f::Compare (const Quat4f &rhs, const float threshold) const {
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

inline bool Quat4f::operator== (const Quat4f &rhs) const {
    return Compare(rhs);
}

inline bool Quat4f::operator!= (const Quat4f &rhs) const {
    return !Compare(rhs);
}

#endif /* __SGE_QUATERNION_H */
