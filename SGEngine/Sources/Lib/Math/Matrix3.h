/*---  Matrix3.h - 3x3 Matrix Header  ------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level Mat3 type.
 */
#ifndef __SGENGINE_MATRIX3_H_
#define __SGENGINE_MATRIX3_H_

#include <utility> // std::swap
#include <cstring> // std::memcpy

namespace sge {

/**
 * 3x3 Matrix. Implements math operations for 3x3 Matrices stored in
 * Column Major form.
 *
 * <pre>
 *     0 1 2
 *   +------
 *  x| 0 3 6
 *  y| 1 4 7
 *  z| 2 5 8
 * </pre>
 */
template <typename T>
class Mat3_T {
public:
    /** Default Constructor */
    Mat3_T () { }

    /** Fill Constructor */
    explicit Mat3_T (const T f);

    /** Value Constructor */
    explicit Mat3_T (const T aa, const T ab, const T ac,
                     const T ba, const T bb, const T bc,
                     const T ca, const T cb, const T cc);

    /** Vec3_T<T> Column Constructor */
    explicit Mat3_T (const Vec3_T<T> &col1, const Vec3_T<T> &col2, const Vec3_T<T> &col3);

    /** 1D Array Constructor */
    explicit Mat3_T (const T data[9]);

    /** 2D Array Constructor */
    explicit Mat3_T (const T data[3][3]);

    /**
     * Set the values of this Mat3_T using Ts.
     * Destructive.
     */
    void Set (const T aa, const T ab, const T ac,
              const T ba, const T bb, const T bc,
              const T ca, const T cb, const T cc);

    /**
     * Set the values of this Mat3_T using Vec3_T<T> columns.
     * Destructive.
     */
    void Set (const Vec3_T<T> &col1, const Vec3_T<T> &col2, const Vec3_T<T> &col3);

    /**
     * Set the values of this Mat3_T using a 1D array.
     * Destructive.
     */
    void Set (const T data[9]);

    /**
     * Set the values of this Mat3_T using a 2D array.
     * Destructive.
     */
    void Set (const T data[3][3]);

    /**
     * Set all values of this Mat3_T to zero.
     * Destructive.
     */
    void Zero ();

    bool IsIdentity () const;

    const Vec3_T<T> &operator[] (const u32 index) const;

    Vec3_T<T> &operator[] (const u32 index);

    /**
     * Mat3_T Scale.
     */
    Mat3_T operator* (const T a) const;

    /**
     * Mat3_T Scale, reversed operands.
     */
    template <typename U>
    friend Mat3_T<U> operator* (const U a, const Mat3_T<U> &rhs);

    /**
     * Mat3_T Multiplication.
     */
    Mat3_T operator* (const Mat3_T &rhs) const;

    /**
     * Mat3_T x Vec3_T<T> multiplication.
     */
    Vec3_T<T> operator* (const Vec3_T<T> &rhs) const;

    /**
     * Vec3_T<T> x Mat3_T multiplication.
     */
    template <typename U>
    friend Vec3_T<U> operator* (const Vec3_T<U> &lhs, const Mat3_T<U> &rhs);

    /**
     * Mat3_T Addition.
     */
    Mat3_T operator+ (const Mat3_T &rhs) const;

    /**
     * Mat3_T Subtraction.
     */
    Mat3_T operator- (const Mat3_T &rhs) const;

    /**
     * Mat3_T Scale in place.
     * Destructive.
     */
    Mat3_T &operator*= (const T a);

    /**
     * Mat3_T Multiplication in place.
     * Destructive.
     */
    Mat3_T &operator*= (const Mat3_T &rhs);

    /**
     * Mat3_T Addition in place.
     */
    Mat3_T &operator+= (const Mat3_T &rhs);

    /**
     * Mat3_T Subtraction in place.
     */
    Mat3_T &operator-= (const Mat3_T &rhs);

    /**
     * Get the determinant of this Mat3_T.
     */
    T Determinant () const;

    /**
     * Determine if this Mat3_T has an inverse.
     */
    bool HasInverse () const;

    /**
     * Get the inverse of this Mat3_T.
     */
    Mat3_T Inverse () const;

    /**
     * Set this Mat3_T to be its inverse.
     * Destructive.
     * @return false if Mat3_T has no inverse, true if success.
     */
    bool InverseSelf ();

    Mat3_T Transpose () const;

    Mat3_T &TransposeSelf ();

    /**
     * Test if this Mat3_T is equivalent to another Mat3_T.
     */
    bool Compare (const Mat3_T &other) const;

    /**
     * Test if this Mat3_T is similar to another Mat3_T
     * within a given tolerance.
     */
    bool Compare (const Mat3_T &other, const T threshold) const;

    /**
     * Test if this Mat3_T is equivalent to another Mat3_T.
     */
    bool operator== (const Mat3_T &other) const;

    /**
     * Test if this Mat3_T is not equivalent to another Mat3_T.
     */
    bool operator!= (const Mat3_T &other) const;

private:
    Vec3_T<T> mat[3];
};

// Common Mat3 types.
typedef Mat3_T<float> Mat3f;

// Constants
extern const Mat3f MAT3F_ZERO;
extern const Mat3f MAT3F_ONE;
extern const Mat3f MAT3F_IDENTITY;

// --------------------------------------------------------------------------

template <typename T>
INLINE Mat3_T<T>::Mat3_T (const T f) {
    mat[0].x = mat[0].y = mat[0].z = f;
    mat[1].x = mat[1].y = mat[1].z = f;
    mat[2].x = mat[2].y = mat[2].z = f;
}

template <typename T>
INLINE Mat3_T<T>::Mat3_T (const T aa, const T ab, const T ac,
                          const T ba, const T bb, const T bc,
                          const T ca, const T cb, const T cc) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc;
}

template <typename T>
INLINE Mat3_T<T>::Mat3_T (const Vec3_T<T> &col1, const Vec3_T<T> &col2, const Vec3_T<T> &col3) {
    mat[0].x = col1.x; mat[0].y = col1.y; mat[0].z = col1.z;
    mat[1].x = col2.x; mat[1].y = col2.y; mat[1].z = col2.z;
    mat[2].x = col3.x; mat[2].y = col3.y; mat[2].z = col3.z;
}

template <typename T>
INLINE Mat3_T<T>::Mat3_T (const T data[9]) {
    std::memcpy(mat, data, 9 * sizeof(T));
}

template <typename T>
INLINE Mat3_T<T>::Mat3_T (const T data[3][3]) {
    std::memcpy(mat, data, 3 * 3 * sizeof(T));
}

template <typename T>
INLINE void Mat3_T<T>::Set (const T aa, const T ab, const T ac,
                            const T ba, const T bb, const T bc,
                            const T ca, const T cb, const T cc) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc;
}

template <typename T>
INLINE void Mat3_T<T>::Set (const Vec3_T<T> &col1, const Vec3_T<T> &col2, const Vec3_T<T> &col3) {
    mat[0] = col1;
    mat[1] = col2;
    mat[2] = col3;
}

template <typename T>
INLINE void Mat3_T<T>::Set (const T data[9]) {
    std::memcpy(mat, data, 9 * sizeof(T));
}

template <typename T>
INLINE void Mat3_T<T>::Set (const T data[3][3]) {
    std::memcpy(mat, data, 3 * 3 * sizeof(T));
}

template <typename T>
INLINE void Mat3_T<T>::Zero () {
    mat[0].Zero();
    mat[1].Zero();
    mat[2].Zero();
}

template <typename T>
INLINE bool Mat3_T<T>::IsIdentity () const {
    return Compare(MAT3F_IDENTITY);
}

template <typename T>
INLINE const Vec3_T<T> &Mat3_T<T>::operator[] (const u32 index) const {
    return mat[index];
}

template <typename T>
INLINE Vec3_T<T> &Mat3_T<T>::operator[] (const u32 index) {
    return mat[index];
}

//=======================
// Mat3_T<T> Operations
//=======================

template <typename T>
INLINE Mat3_T<T> Mat3_T<T>::operator* (const T a) const {
    return Mat3_T<T>(mat[0] * a, mat[1] * a, mat[2] * a);
}

template <typename T>
INLINE Mat3_T<T> operator* (const T a, const Mat3_T<T> &rhs) {
    return rhs * a;
}

template <typename T>
INLINE Mat3_T<T> Mat3_T<T>::operator* (const Mat3_T<T> &rhs) const {
    Mat3_T<T> lhs = Transpose();

    return Mat3_T<T>(lhs[0].Dot(rhs[0]), lhs[1].Dot(rhs[0]), lhs[2].Dot(rhs[0]),
                     lhs[0].Dot(rhs[1]), lhs[1].Dot(rhs[1]), lhs[2].Dot(rhs[1]),
                     lhs[0].Dot(rhs[2]), lhs[1].Dot(rhs[2]), lhs[2].Dot(rhs[2]));
}

template <typename T>
INLINE Vec3_T<T> Mat3_T<T>::operator* (const Vec3_T<T> &rhs) const {
    return Vec3_T<T>(mat[0].x * rhs.x + mat[1].x * rhs.y + mat[2].x * rhs.z,
                     mat[0].y * rhs.x + mat[1].y * rhs.y + mat[2].y * rhs.z,
                     mat[0].z * rhs.x + mat[1].z * rhs.y + mat[2].z * rhs.z);
}

template <typename T>
INLINE Vec3_T<T> operator* (const Vec3_T<T> &lhs, const Mat3_T<T> &rhs) {
    return rhs * lhs;
}

template <typename T>
INLINE Mat3_T<T> Mat3_T<T>::operator+ (const Mat3_T<T> &rhs) const {
    return Mat3_T<T>(mat[0] + rhs[0], mat[1] + rhs[1], mat[2] + rhs[2]);
}

template <typename T>
INLINE Mat3_T<T> Mat3_T<T>::operator- (const Mat3_T<T> &rhs) const {
    return Mat3_T<T>(mat[0] - rhs[0], mat[1] - rhs[1], mat[2] - rhs[2]);
}

template <typename T>
INLINE Mat3_T<T> &Mat3_T<T>::operator*= (const T a) {
    mat[0] *= a;
    mat[1] *= a;
    mat[2] *= a;

    return *this;
}

template <typename T>
INLINE Mat3_T<T> &Mat3_T<T>::operator*= (const Mat3_T<T> &rhs) {
    Mat3_T<T> lhs = Transpose();

    Set(lhs[0].Dot(rhs[0]), lhs[1].Dot(rhs[0]), lhs[2].Dot(rhs[0]),
        lhs[0].Dot(rhs[1]), lhs[1].Dot(rhs[1]), lhs[2].Dot(rhs[1]),
        lhs[0].Dot(rhs[2]), lhs[1].Dot(rhs[2]), lhs[2].Dot(rhs[2]));

    return *this;
}

template <typename T>
INLINE Mat3_T<T> &Mat3_T<T>::operator+= (const Mat3_T<T> &rhs) {
    mat[0] += rhs[0];
    mat[1] += rhs[1];
    mat[2] += rhs[2];

    return *this;
}

template <typename T>
INLINE Mat3_T<T> &Mat3_T<T>::operator-= (const Mat3_T<T> &rhs) {
    mat[0] -= rhs[0];
    mat[1] -= rhs[1];
    mat[2] -= rhs[2];

    return *this;
}

template <typename T>
INLINE T Mat3_T<T>::Determinant () const {
    // Laplace Expansion Determinant
    //    0 1 2
    // x |0 3 6|
    // y |1 4 7|
    // z |2 5 8|
    return mat[0].x * (mat[1].y * mat[2].z - mat[2].y * mat[1].z) -
        mat[0].y * (mat[1].x * mat[2].z - mat[2].x * mat[1].z) +
        mat[0].z * (mat[1].x * mat[2].y - mat[2].x * mat[1].y);
}

template <typename T>
INLINE bool Mat3_T<T>::HasInverse () const {
    return 0 != Determinant();
}

template <typename T>
INLINE Mat3_T<T> Mat3_T<T>::Transpose () const {
    return Mat3_T<T>(mat[0].x, mat[1].x, mat[2].x,
                     mat[0].y, mat[1].y, mat[2].y,
                     mat[0].z, mat[1].z, mat[2].z);
}

template <typename T>
INLINE Mat3_T<T> &Mat3_T<T>::TransposeSelf () {
    std::swap(mat[0].y, mat[1].x);
    std::swap(mat[0].z, mat[2].x);
    std::swap(mat[1].z, mat[2].y);

    return *this;
}

//=======================
// Mat3_T<T> Comparisons
//=======================

template <typename T>
INLINE bool Mat3_T<T>::Compare (const Mat3_T<T> &other) const {
    return mat[0].Compare(other.mat[0]) &&
        mat[1].Compare(other.mat[1]) &&
        mat[2].Compare(other.mat[2]);
}

template <typename T>
INLINE bool Mat3_T<T>::Compare (const Mat3_T<T> &other, const T threshold) const {
    return mat[0].Compare(other.mat[0], threshold) &&
        mat[1].Compare(other.mat[1], threshold) &&
        mat[2].Compare(other.mat[2], threshold);
}

template <typename T>
INLINE bool Mat3_T<T>::operator== (const Mat3_T<T> &other) const {
    return Compare(other);
}

template <typename T>
INLINE bool Mat3_T<T>::operator!= (const Mat3_T<T> &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_MATRIX3_H_ */
