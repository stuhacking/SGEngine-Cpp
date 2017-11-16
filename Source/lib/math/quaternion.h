/** @file Quaternion.h - Quaternion Header  ------------------------*- C++ -*---
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
 * Quaternion 4D (w<sub>r</sub> + {i, j, k}<sub>i</sub>).
 *
 * Implements math operators and Quat->Vec3 multiplication/rotation.
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
    /** Default Constructor */
    Quat4f () = default;

    /** Value Constructor */
    explicit Quat4f (const float ii, const float jj, const float kk, const float ww)
        : i(ii), j(jj), k(kk), w(ww) { }

    /**
     * Create a Quat4f from an Axis/Angle rotation.
     *
     * @param angle Angle of rotation in radians.
     * @param axis about which to rotate.
     */
    explicit Quat4f (const float angle, const Vec3f &axis);

    /**
     * Read access to this Quat4f's components using
     *subscript notation.
     */
    float operator[] (const std::size_t index) const { return (&i)[index]; }

    /**
     * Reference/write access to this Quat4f's components using
     * subscript notation.
     */
    float &operator[] (const std::size_t index) { return (&i)[index]; }

    void Zero () { i = j = k = w = 0; }

    float magSq () const;

    float mag () const;

    bool isIdentity () const;

    bool isUnit () const;

    Quat4f normalize () const;

    void normalizeSelf ();

    Quat4f conjugate () const;

    float dot (const Quat4f &rhs) const;

    Quat4f cross (const Quat4f &rhs) const;

    /**
     * Apply the rotation in this quaternion to a Vec3f.
     */
    Vec3f rotate (const Vec3f &vec) const;

    /**
     * Test if two Quat4fs are equivalent.
     */
    bool compare (const Quat4f &rhs) const;

    /**
     * Test if two Quat4fs are similar within a
     * given tolerance.
     */
    bool compare (const Quat4f &rhs, const float threshold) const;
};

extern const Quat4f Quat4f_Identity;

// --------------------------------------------------------------------------

inline Quat4f::Quat4f (const float angle, const Vec3f &axis) {
    float sinHalf, cosHalf;
    math::sinCos(angle * 0.5f, sinHalf, cosHalf);

    i = axis.x * sinHalf;
    j = axis.y * sinHalf;
    k = axis.z * sinHalf;
    w = cosHalf;
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

inline float Quat4f::magSq () const {
    return i * i + j * j + k * k + w * w;
}

inline float Quat4f::mag () const {
    return sqrt(i * i + j * j + k * k + w * w);
}

inline Quat4f Quat4f::normalize () const {
    float length = mag();
    if (length == 0) {
        return Quat4f(*this);
    } else {
        return *this / length;
    }
}

inline void Quat4f::normalizeSelf () {
    float length = mag();
    if (length != 0.0f) {
        *this /= length;
    }
}

inline bool Quat4f::isIdentity () const {
    return compare(Quat4f_Identity);
}

inline bool Quat4f::isUnit () const {
    return 1.0f == magSq();
}

inline Quat4f Quat4f::conjugate () const {
    return Quat4f(-i, -j, -k, w);
}

inline float Quat4f::dot (const Quat4f &rhs) const {
    return i * rhs.i + j * rhs.j + k * rhs.k;
}

inline Quat4f Quat4f::cross (const Quat4f &rhs) const {
    return Quat4f(j * rhs.k - k * rhs.j,
                      k * rhs.i - i * rhs.k,
                      i * rhs.j - j * rhs.i,
                      w);
}


//=======================
// Quat4f Comparison
//=======================

inline bool Quat4f::compare (const Quat4f &rhs) const {
    return i == rhs.i && j == rhs.j && k == rhs.k && w == rhs.w;
}

inline bool Quat4f::compare (const Quat4f &rhs, const float threshold) const {
    return (fabsf(i - rhs.i) <= threshold) &&
           (fabsf(j - rhs.j) <= threshold) &&
           (fabsf(k - rhs.k) <= threshold) &&
           (fabsf(w - rhs.w) <= threshold);
}

inline bool operator== (const Quat4f &a, const Quat4f &b) {
    return a.compare(b);
}

inline bool operator!= (const Quat4f &a, const Quat4f &b) {
    return !a.compare(b);
}

#endif /* __SGE_QUATERNION_H */
