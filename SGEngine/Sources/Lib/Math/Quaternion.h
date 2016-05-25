/*---  Quaternion.h - Quaternion Header  ---------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level Quat4_T type.
 */
#ifndef __SGENGINE_QUATERNION_H_
#define __SGENGINE_QUATERNION_H_

namespace sge {

/**
 * Quat4_T. Implements math operators and Quat->Vect
 * multiplication/rotation
 */
template <typename T>
class Quat4_T {
public:
    /* Quat4_T Imaginary (i,j,k) components */
    T i, j, k;

    /* Quat4_T real component */
    T w;

public:
    /** Default Constructor */
    Quat4_T () : i(0.0f), j(0.0f), k(0.0f), w(0.0f) { }

    /** Value Constructor */
    explicit Quat4_T (const T ii, const T jj, const T kk, const T ww)
        : i(ii), j(jj), k(kk), w(ww) { }

    /**
     * Create a Quat4_T from an Axis/Angle rotation.
     * @param axis about which to rotate.
     * @param angle Angle of rotation in radians.
     */
    static Quat4_T AxisAngle (const Vec3_T<T> &axis, const T angle);

    /**
     * Read access to this Quat4_T's components using
     *subscript notation.
     */
    T operator[] (const u32 index) const;

    /**
     * Reference/write access to this Quat4_T's components using
     * subscript notation.
     */
    T &operator[] (const u32 index);

    void Zero ();

    T LengthSqr () const;

    T Length () const;

    bool IsIdentity () const;

    bool IsUnit () const;

    Quat4_T Normalize () const;

    void NormalizeSelf ();

    Quat4_T Conjugate () const;

    T Dot (const Quat4_T &rhs) const;

    Quat4_T Cross (const Quat4_T &rhs) const;

    /**
     * Scale quaternion.
     */
    Quat4_T operator* (const T a) const;

    /**
     * Scale quaternion, reversed operands.
     */
    template <typename U>
    friend Quat4_T<U> operator* (const U a, const Quat4_T<U> &rhs);

    /**
     * Quat4_T multiplication.
     */
    Quat4_T operator* (const Quat4_T &rhs) const;

    /**
     * Quat4_T x Vector multiplication.
     */
    Quat4_T operator* (const Vec3_T<T> &rhs) const;

    /**
     * Quat4_T Addition.
     */
    Quat4_T operator+ (const Quat4_T &rhs) const;

    /**
     * Quat4_T subraction.
     */
    Quat4_T operator- (const Quat4_T &rhs) const;

    /**
     * Quat4_T division.
     */
    Quat4_T operator/ (const T a) const;

    Quat4_T &operator*= (const T a);

    Quat4_T &operator*= (const Quat4_T &rhs);

    Quat4_T &operator+= (const Quat4_T &rhs);

    Quat4_T &operator-= (const Quat4_T &rhs);

    Quat4_T &operator/= (const T a);

    Quat4_T &operator/= (const Quat4_T &rhs);

    /**
     * Apply the rotation in this quaternion to a Vec3_T<T>.
     */
    Vec3_T<T> Rotate (const Vec3_T<T> &vec) const;

    /**
     * Test if two Quat4_Ts are equivalent.
     */
    bool Compare (const Quat4_T &rhs) const;

    /**
     * Test if two Quat4_Ts are similar within a
     * given tolerance.
     */
    bool Compare (const Quat4_T &rhs, const T threshold) const;

    /**
     * Test if two Quat4_Ts are equivalent.
     */
    bool operator== (const Quat4_T &rhs) const;

    /**
     * Test if two Quat4_Ts are not equivalent.
     */
    bool operator!= (const Quat4_T &rhs) const;
};

// Common Quat4 types
typedef Quat4_T<float> Quat4f;

// Constants
extern const Quat4f QUAT4F_IDENTITY;

// --------------------------------------------------------------------------

template <typename T>
INLINE T Quat4_T<T>::operator[] (const u32 index) const {
    return (&i)[index];
}

template <typename T>
INLINE T &Quat4_T<T>::operator[] (const u32 index) {
    return (&i)[index];
}

template <typename T>
INLINE void Quat4_T<T>::Zero () {
    i = j = k = w = 0.0f;
}

template <typename T>
INLINE T Quat4_T<T>::LengthSqr () const {
    return i * i + j * j + k * k + w * w;
}

template <typename T>
INLINE T Quat4_T<T>::Length () const {
    return sqrt(i * i + j * j + k * k + w * w);
}

template <typename T>
INLINE Quat4_T<T> Quat4_T<T>::Normalize () const {
    T length = Length();
    if (length == 0) {
        return Quat4_T<T>(*this);
    } else {
        return *this / length;
    }
}

template <typename T>
INLINE void Quat4_T<T>::NormalizeSelf () {
    T length = Length();
    if (length != 0.0f) {
        *this /= length;
    }
}

template <typename T>
INLINE bool Quat4_T<T>::IsIdentity () const {
    return *this == QUAT4F_IDENTITY;
}

template <typename T>
INLINE bool Quat4_T<T>::IsUnit () const {
    return 1 == LengthSqr();
}

template <typename T>
INLINE Quat4_T<T> Quat4_T<T>::Conjugate () const {
    return Quat4_T<T>(-i, -j, -k, w);
}

template <typename T>
INLINE T Quat4_T<T>::Dot (const Quat4_T<T> &rhs) const {
    return i * rhs.i + j * rhs.j + k * rhs.k;
}

template <typename T>
INLINE Quat4_T<T> Quat4_T<T>::Cross (const Quat4_T<T> &rhs) const {
    return Quat4_T<T>(j * rhs.k - k * rhs.j,
                      k * rhs.i - i * rhs.k,
                      i * rhs.j - j * rhs.i,
                      w);
}

//======================
// Quat4_T<T> Operators
//======================

template <typename T>
INLINE Quat4_T<T> Quat4_T<T>::operator* (const T a) const {
    return Quat4_T<T>(i * a, j * a, k * a, w * a);
}

template <typename T>
INLINE Quat4_T<T> operator* (const T a, const Quat4_T<T> &rhs) {
    return Quat4_T<T>(a * rhs.i, a * rhs.j, a * rhs.k, a * rhs.w);
}

template <typename T>
INLINE Quat4_T<T> Quat4_T<T>::operator* (const Quat4_T<T> &rhs) const {
    return Quat4_T<T>(i * rhs.w + w * rhs.i + j * rhs.k - k * rhs.j,
                      j * rhs.w + w * rhs.j + k * rhs.i - i * rhs.k,
                      k * rhs.w + w * rhs.k + i * rhs.j - j * rhs.i,
                      w * rhs.w - i * rhs.i - j * rhs.j - k * rhs.k);
}

template <typename T>
INLINE Quat4_T<T> Quat4_T<T>::operator* (const Vec3_T<T> &rhs) const {
    return Quat4_T<T>(w * rhs.x + j * rhs.z - k * rhs.y,
                      w * rhs.y + k * rhs.x - i * rhs.z,
                      w * rhs.z + i * rhs.y - j * rhs.x,
                      -i * rhs.x - j * rhs.y - k * rhs.z);
}

template <typename T>
INLINE Quat4_T<T> Quat4_T<T>::operator+ (const Quat4_T<T> &rhs) const {
    return Quat4_T<T>(i + rhs.i, j + rhs.j, k + rhs.k, w + rhs.w);
}

template <typename T>
INLINE Quat4_T<T> Quat4_T<T>::operator- (const Quat4_T<T> &rhs) const {
    return Quat4_T<T>(i - rhs.i, j - rhs.j, k - rhs.k, w - rhs.w);
}

template <typename T>
INLINE Quat4_T<T> Quat4_T<T>::operator/ (const T a) const {
    T inva = 1.0f / a;
    return Quat4_T<T>(i * inva, j * inva, k * inva, w * inva);
}

template <typename T>
INLINE Quat4_T<T> &Quat4_T<T>::operator*= (const T a) {
    i *= a;
    j *= a;
    k *= a;
    w *= a;

    return *this;
}

template <typename T>
INLINE Quat4_T<T> &Quat4_T<T>::operator*= (const Quat4_T<T> &rhs) {
    i = i * rhs.w + w * rhs.i + j * rhs.k - k * rhs.j;
    j = j * rhs.w + w * rhs.j + k * rhs.i - i * rhs.k;
    k = k * rhs.w + w * rhs.k + i * rhs.j - j * rhs.i;
    w = w * rhs.w - i * rhs.i - j * rhs.j - k * rhs.k;

    return *this;
}

template <typename T>
INLINE Quat4_T<T> &Quat4_T<T>::operator+= (const Quat4_T<T> &rhs) {
    i += rhs.i;
    j += rhs.j;
    k += rhs.k;
    w += rhs.w;

    return *this;
}

template <typename T>
INLINE Quat4_T<T> &Quat4_T<T>::operator-= (const Quat4_T<T> &rhs) {
    i -= rhs.i;
    j -= rhs.j;
    k -= rhs.k;
    w -= rhs.w;

    return *this;
}

template <typename T>
INLINE Quat4_T<T> &Quat4_T<T>::operator/= (const T a) {
    T inva = 1.0f / a;

    i *= inva;
    j *= inva;
    k *= inva;
    w *= inva;

    return *this;
}

//=======================
// Quat4_T<T> Comparison
//=======================

template <typename T>
INLINE bool Quat4_T<T>::Compare (const Quat4_T<T> &rhs) const {
    return i == rhs.i && j == rhs.j && k == rhs.k && w == rhs.w;
}

template <typename T>
INLINE bool Quat4_T<T>::Compare (const Quat4_T<T> &rhs, const T threshold) const {
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

template <typename T>
INLINE bool Quat4_T<T>::operator== (const Quat4_T<T> &rhs) const {
    return Compare(rhs);
}

template <typename T>
INLINE bool Quat4_T<T>::operator!= (const Quat4_T<T> &rhs) const {
    return !Compare(rhs);
}

} /* namespace sge */

#endif /* __SGENGINE_QUATERNION_H_ */
