/*---  Matrix4.h - 4x4 Matrix Header  ------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level Mat4 type.
 */
#ifndef __SGENGINE_MATRIX4_H_
#define __SGENGINE_MATRIX4_H_

#include <utility> // std::swap
#include <cstring> // std::memcpy

namespace sge {

/**
 * 4x4 Matrix. Implements math operations for 4x4 Matrices stored in
 * column major form.
 *
 * <pre>
 *     0 1 2 3
 *   +--------
 *  x| 0 4 8 C
 *  y| 1 5 9 D
 *  z| 2 6 A E
 *  w| 3 7 B F
 * </pre>
 */
template <typename T>
class Mat4_T {
public:
    /** Default Constructor */
    Mat4_T () { }

    /** Fill Constructor */
    explicit Mat4_T (const T f);

    /** Value Constructor */
    explicit Mat4_T (const T aa, const T ab, const T ac, const T ad,
                     const T ba, const T bb, const T bc, const T bd,
                     const T ca, const T cb, const T cc, const T cd,
                     const T da, const T db, const T dc, const T dd);

    /** Vec4_T<T> Column Constructor */
    explicit Mat4_T (const Vec4_T<T> &col1, const Vec4_T<T> &col2,
                     const Vec4_T<T> &col3, const Vec4_T<T> &col4);

    /** 1D Array Constructor */
    explicit Mat4_T (const T data[16]);

    /** 2D Array Constructor */
    explicit Mat4_T (const T data[4][4]);

    /**
     * Set the values of this Mat4_T using T values.
     * Destructive.
     */
    void Set (const T aa, const T ab, const T ac, const T ad,
              const T ba, const T bb, const T bc, const T bd,
              const T ca, const T cb, const T cc, const T cd,
              const T da, const T db, const T dc, const T dd);

    /**
     * Set the columns of this Mat4_T using Vec4_T<T>s.
     * Destructive.
     */
    void Set (const Vec4_T<T> &col1, const Vec4_T<T> &col2, const Vec4_T<T> &col3, const Vec4_T<T> &col4);

    /**
     * Set the values of this Mat4_T using a 1D T array.
     * Destructive.
     */
    void Set (const T data[16]);

    /**
     * Set the values of this Mat4_T using a 2D T array.
     * Destructive.
     */
    void Set (const T data[4][4]);

    /**
     * Set all values of this Mat4_T to zero.
     * Destructive.
     */
    void Zero ();

    /**
     * Test if this Mat4_T is the identity Matrix.
     */
    bool IsIdentity () const;

    const Vec4_T<T> &operator[] (const u32 index) const;

    Vec4_T<T> &operator[] (const u32 index);

    /** Mat4_T operations. */
    Mat4_T operator* (const T a) const;

    template <typename U>
    friend Mat4_T<U> operator* (const U a, const Mat4_T<U> &rhs);

    Mat4_T operator* (const Mat4_T &rhs) const;

    Vec4_T<T> operator* (const Vec4_T<T> &rhs) const;

    template <typename U>
    friend Vec4_T<U> operator* (const Vec4_T<U> &lhs, const Mat4_T<U> &rhs);

    Mat4_T operator+ (const Mat4_T &rhs) const;

    Mat4_T operator- (const Mat4_T &rhs) const;

    Mat4_T &operator*= (const T a);

    Mat4_T &operator*= (const Mat4_T &rhs);

    Mat4_T &operator+= (const Mat4_T &rhs);

    Mat4_T &operator-= (const Mat4_T &rhs);

    T Determinant () const;

    bool HasInverse () const;

    Mat4_T Inverse () const;

    bool InverseSelf ();

    Mat4_T Transpose () const;

    Mat4_T &TransposeSelf ();

    /** Comarisons. */
    bool Compare (const Mat4_T &other) const;

    bool Compare (const Mat4_T &other, const T threshold) const;

    bool operator== (const Mat4_T &other) const;

    bool operator!= (const Mat4_T &other) const;

public:
    Vec4_T<T> mat[4];
};

// Common Mat4 types
typedef Mat4_T<float> Mat4f;

// Constants
extern const Mat4f MAT4F_ZERO;
extern const Mat4f MAT4F_ONE;
extern const Mat4f MAT4F_IDENTITY;

// --------------------------------------------------------------------------

template <typename T>
INLINE Mat4_T<T>::Mat4_T (const T f) {
    mat[0].x = f; mat[0].y = f; mat[0].z = f; mat[0].w = f;
    mat[1].x = f; mat[1].y = f; mat[1].z = f; mat[1].w = f;
    mat[2].x = f; mat[2].y = f; mat[2].z = f; mat[2].w = f;
    mat[3].x = f; mat[3].y = f; mat[3].z = f; mat[3].w = f;
}

template <typename T>
INLINE Mat4_T<T>::Mat4_T (const T aa, const T ab, const T ac, const T ad,
                          const T ba, const T bb, const T bc, const T bd,
                          const T ca, const T cb, const T cc, const T cd,
                          const T da, const T db, const T dc, const T dd) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac; mat[0].w = ad;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc; mat[1].w = bd;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc; mat[2].w = cd;
    mat[3].x = da; mat[3].y = db; mat[3].z = dc; mat[3].w = dd;
}

template <typename T>
INLINE Mat4_T<T>::Mat4_T (const Vec4_T<T> &col1, const Vec4_T<T> &col2,
                          const Vec4_T<T> &col3, const Vec4_T<T> &col4) {
    mat[0].x = col1.x; mat[0].y = col1.y; mat[0].z = col1.z; mat[0].w = col1.w;
    mat[1].x = col2.x; mat[1].y = col2.y; mat[1].z = col2.z; mat[1].w = col2.w;
    mat[2].x = col3.x; mat[2].y = col3.y; mat[2].z = col3.z; mat[2].w = col3.w;
    mat[3].x = col4.x; mat[3].y = col4.y; mat[3].z = col4.z; mat[3].w = col4.w;
}

template <typename T>
INLINE Mat4_T<T>::Mat4_T (const T data[16]) {
    std::memcpy(mat, data, 16 * sizeof(T));
}

template <typename T>
INLINE Mat4_T<T>::Mat4_T (const T data[4][4]) {
    std::memcpy(mat, data, 4 * 4 * sizeof(T));
}

template <typename T>
INLINE void Mat4_T<T>::Set (const T aa, const T ab, const T ac, const T ad,
                            const T ba, const T bb, const T bc, const T bd,
                            const T ca, const T cb, const T cc, const T cd,
                            const T da, const T db, const T dc, const T dd) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac; mat[0].w = ad;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc; mat[1].w = bd;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc; mat[2].w = cd;
    mat[3].x = da; mat[3].y = db; mat[3].z = dc; mat[3].w = dd;
}

template <typename T>
INLINE void Mat4_T<T>::Set (const Vec4_T<T> &col1, const Vec4_T<T> &col2,
                            const Vec4_T<T> &col3, const Vec4_T<T> &col4) {
    mat[0].x = col1.x; mat[0].y = col1.y; mat[0].z = col1.z; mat[0].w = col1.w;
    mat[1].x = col2.x; mat[1].y = col2.y; mat[1].z = col2.z; mat[1].w = col2.w;
    mat[2].x = col3.x; mat[2].y = col3.y; mat[2].z = col3.z; mat[2].w = col3.w;
    mat[3].x = col4.x; mat[3].y = col4.y; mat[3].z = col4.z; mat[3].w = col4.w;
}

template <typename T>
INLINE void Mat4_T<T>::Set (const T data[16]) {
    std::memcpy(mat, data, 16 * sizeof(T));
}

template <typename T>
INLINE void Mat4_T<T>::Set (const T data[4][4]) {
    std::memcpy(mat, data, 4 * 4 * sizeof(T));
}

template <typename T>
INLINE void Mat4_T<T>::Zero () {
    mat[0].Zero();
    mat[1].Zero();
    mat[2].Zero();
    mat[3].Zero();
}

template <typename T>
INLINE bool Mat4_T<T>::IsIdentity () const {
    return Compare(MAT4F_IDENTITY);
}

template <typename T>
INLINE const Vec4_T<T> &Mat4_T<T>::operator[] (const u32 index) const {
    return mat[index];
}

template <typename T>
INLINE Vec4_T<T> &Mat4_T<T>::operator[] (const u32 index) {
    return mat[index];
}

//=======================
// Mat4_T<T> Operations
//=======================

template <typename T>
INLINE Mat4_T<T> Mat4_T<T>::operator* (const T a) const {
    return Mat4_T<T>(mat[0] * a, mat[1] * a, mat[2] * a, mat[3] * a);
}

template <typename T>
INLINE Mat4_T<T> operator* (const T a, const Mat4_T<T> &rhs) {
    return rhs * a;
}

template <typename T>
INLINE Mat4_T<T> Mat4_T<T>::operator* (const Mat4_T<T> &rhs) const {
    Mat4_T<T> lhs = Transpose();

    return Mat4_T<T>(lhs[0].Dot(rhs[0]), lhs[1].Dot(rhs[0]), lhs[2].Dot(rhs[0]), lhs[3].Dot(rhs[0]),
                     lhs[0].Dot(rhs[1]), lhs[1].Dot(rhs[1]), lhs[2].Dot(rhs[1]), lhs[3].Dot(rhs[1]),
                     lhs[0].Dot(rhs[2]), lhs[1].Dot(rhs[2]), lhs[2].Dot(rhs[2]), lhs[3].Dot(rhs[2]),
                     lhs[0].Dot(rhs[3]), lhs[1].Dot(rhs[3]), lhs[2].Dot(rhs[3]), lhs[3].Dot(rhs[3]));
}

template <typename T>
INLINE Vec4_T<T> Mat4_T<T>::operator* (const Vec4_T<T> &rhs) const {
    return Vec4_T<T>(mat[0].x * rhs.x + mat[1].x * rhs.y + mat[2].x * rhs.z + mat[3].x * rhs.w,
                     mat[0].y * rhs.x + mat[1].y * rhs.y + mat[2].y * rhs.z + mat[3].y * rhs.w,
                     mat[0].z * rhs.x + mat[1].z * rhs.y + mat[2].z * rhs.z + mat[3].z * rhs.w,
                     mat[0].w * rhs.x + mat[1].w * rhs.y + mat[2].w * rhs.z + mat[3].w * rhs.w);
}

template <typename T>
INLINE Vec4_T<T> operator* (const Vec4_T<T> &lhs, const Mat4_T<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
INLINE Mat4_T<T> Mat4_T<T>::operator+ (const Mat4_T<T> &rhs) const {
    return Mat4_T<T>(mat[0] + rhs[0], mat[1] + rhs[1], mat[2] + rhs[2], mat[3] + rhs[3]);
}

template <typename T>
INLINE Mat4_T<T> Mat4_T<T>::operator- (const Mat4_T<T> &rhs) const {
    return Mat4_T<T>(mat[0] - rhs[0], mat[1] - rhs[1], mat[2] - rhs[2], mat[3] - rhs[3]);
}

template <typename T>
INLINE Mat4_T<T> &Mat4_T<T>::operator*= (const T a) {
    mat[0] *= a;
    mat[1] *= a;
    mat[2] *= a;
    mat[3] *= a;

    return *this;
}

template <typename T>
INLINE Mat4_T<T> &Mat4_T<T>::operator*= (const Mat4_T<T> &rhs) {
    Mat4_T<T> lhs = Transpose();

    Set(lhs[0].Dot(rhs[0]), lhs[1].Dot(rhs[0]), lhs[2].Dot(rhs[0]), lhs[3].Dot(rhs[0]),
        lhs[0].Dot(rhs[1]), lhs[1].Dot(rhs[1]), lhs[2].Dot(rhs[1]), lhs[3].Dot(rhs[1]),
        lhs[0].Dot(rhs[2]), lhs[1].Dot(rhs[2]), lhs[2].Dot(rhs[2]), lhs[3].Dot(rhs[2]),
        lhs[0].Dot(rhs[3]), lhs[1].Dot(rhs[3]), lhs[2].Dot(rhs[3]), lhs[3].Dot(rhs[3]));

    return *this;
}

template <typename T>
INLINE Mat4_T<T> &Mat4_T<T>::operator+= (const Mat4_T<T> &rhs) {
    mat[0] += rhs[0];
    mat[1] += rhs[1];
    mat[2] += rhs[2];
    mat[3] += rhs[3];

    return *this;
}

template <typename T>
INLINE Mat4_T<T> &Mat4_T<T>::operator-= (const Mat4_T<T> &rhs) {
    mat[0] -= rhs[0];
    mat[1] -= rhs[1];
    mat[2] -= rhs[2];
    mat[3] -= rhs[3];

    return *this;
}

template <typename T>
INLINE T Mat4_T<T>::Determinant () const {
    T a, b, c, d;

    a = Mat3f(mat[1].y, mat[2].y, mat[3].y, mat[1].z, mat[2].z, mat[3].z, mat[1].w, mat[2].w, mat[3].w)
        .Determinant();
    b = Mat3f(mat[1].x, mat[2].x, mat[3].x, mat[1].z, mat[2].z, mat[3].z, mat[1].w, mat[2].w, mat[3].w)
        .Determinant();
    c = Mat3f(mat[1].x, mat[2].x, mat[3].x, mat[1].y, mat[2].y, mat[3].y, mat[1].w, mat[2].w, mat[3].w)
        .Determinant();
    d = Mat3f(mat[1].x, mat[2].x, mat[3].x, mat[1].y, mat[2].y, mat[3].y, mat[1].z, mat[2].z, mat[3].z)
        .Determinant();

    return mat[0].x * a - mat[0].y * b + mat[0].z * c - mat[0].w * d;
}

template <typename T>
INLINE bool Mat4_T<T>::HasInverse () const {
    return 0 != Determinant();
}

template <typename T>
INLINE Mat4_T<T> Mat4_T<T>::Transpose () const {
    return Mat4_T<T>(mat[0].x, mat[1].x, mat[2].x, mat[3].x,
                     mat[0].y, mat[1].y, mat[2].y, mat[3].y,
                     mat[0].z, mat[1].z, mat[2].z, mat[3].z,
                     mat[0].w, mat[1].w, mat[2].w, mat[3].w);
}

template <typename T>
INLINE Mat4_T<T> &Mat4_T<T>::TransposeSelf () {

    std::swap(mat[0].y, mat[1].x);
    std::swap(mat[0].z, mat[2].x);
    std::swap(mat[0].w, mat[3].x);
    std::swap(mat[1].z, mat[2].y);
    std::swap(mat[1].w, mat[3].y);
    std::swap(mat[2].w, mat[3].z);

    return *this;
}

//=======================
// Mat4_T<T> Comparisons
//=======================

template <typename T>
INLINE bool Mat4_T<T>::Compare (const Mat4_T<T> &other) const {
    return mat[0].Compare(other.mat[0]) && mat[1].Compare(other.mat[1]) && mat[2].Compare(other.mat[2]) &&
        mat[3].Compare(other.mat[3]);
}

template <typename T>
INLINE bool Mat4_T<T>::Compare (const Mat4_T<T> &other, const T threshold) const {
    return mat[0].Compare(other.mat[0], threshold) &&
        mat[1].Compare(other.mat[1], threshold) &&
        mat[2].Compare(other.mat[2], threshold) &&
        mat[3].Compare(other.mat[3], threshold);
}

template <typename T>
INLINE bool Mat4_T<T>::operator== (const Mat4_T<T> &other) const {
    return Compare(other);
}

template <typename T>
INLINE bool Mat4_T<T>::operator!= (const Mat4_T<T> &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_MATRIX4_H_ */
