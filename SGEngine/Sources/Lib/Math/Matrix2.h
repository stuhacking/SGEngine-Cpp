/*---  Matrix2.h - 2x2 Matrix Header  ------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level Mat2 type.
 */
#ifndef __SGENGINE_MATRIX2_H_
#define __SGENGINE_MATRIX2_H_

#include <utility> // std::swap
#include <cstring> // std::memcpy

namespace sge {

/**
 * 2x2 Matrix. Implements math operations for 2x2 Matrices stored in
 * Column Major.
 *
 * <pre>
 *     0 1
 *   +----
 *  x| 0 2
 *  y| 1 3
 * </pre>
 */
template <typename T>
class Mat2_T {
public:
    static const Mat2_T ZERO;
    static const Mat2_T ONE;
    static const Mat2_T IDENTITY;

public:
    /** Construct a default (All 0.0f) Mat2_T. */
    Mat2_T () { }

    /** Fill Constructor */
    explicit Mat2_T (const T f);

    /** Construct a Mat2_T with T values. */
    explicit Mat2_T (const T aa, const T ab, const T ba, const T bb);

    /** Construct a Mat2_T using Vec2_T<T> columns. */
    explicit Mat2_T (const Vec2_T<T> &col1, const Vec2_T<T> &col2);

    /** 1D Array Constructor */
    explicit Mat2_T (const T data[4]);

    /** 2D Array Constructor */
    explicit Mat2_T (const T data[2][2]);

    /**
     * Write the data from the columns of this Mat2_T into
     * Vec2_T<T>s.
     */
    void Columns (Vec2_T<T> &col1, Vec2_T<T> &col2) const;

    /**
     * Set the values of this Mat2_T using Ts.
     * Destructive.
     */
    void Set (const T aa, const T ab, const T ba, const T bb);

    /**
     * Set the values of this Mat2_T using Vec2_T<T> columns.
     * Destructive.
     */
    void Set (const Vec2_T<T> &col1, const Vec2_T<T> &col2);

    /**
     * Set the values of this Mat2_T using a 1D array.
     * Destructive.
     */
    void Set (const T data[4]);

    /**
     * Set the values of this Mat2_T using a 2D array.
     * Destructive.
     */
    void Set (const T data[2][2]);

    /**
     * Set all the values of this Mat2_T to 0.0f.
     * Destructive.
     */
    void Zero ();

    /**
     * Return true if this Mat2_T is the identity Matrix.
     * @return true if identity, false otherwise
     */
    bool IsIdentity () const;

    /**
     * Read access to the matrix columns using subscript notation.
     */
    const Vec2_T<T> &operator[] (const u32 index) const;

    /**
     * Reference/Write access to the matrix columns using subscript notation.
     */
    Vec2_T<T> &operator[] (const u32 index);

    // Mat2_T operators

    /**
     * Mat2_T Uniform Scale.
     */
    Mat2_T operator* (const T a) const;

    /**
     * Mat2_T Uniform Scale.
     * Reversed operands.
     */
    template <typename U>
    friend Mat2_T<U> operator* (const U a, const Mat2_T<U> &rhs);

    /**
     * Mat2_T Multiplication.
     */
    Mat2_T operator* (const Mat2_T &rhs) const;

    /**
     * Mat2_T Addition.
     */
    Mat2_T operator+ (const Mat2_T &rhs) const;

    /**
     * Mat2_T Subtraction.
     */
    Mat2_T operator- (const Mat2_T &rhs) const;

    /**
     * Mat2_T Uniform Scale in place.
     * Destructive.
     */
    Mat2_T &operator*= (const T a);

    /**
     * Mat2_T Multiplication in place.
     * Destructive.
     */
    Mat2_T &operator*= (const Mat2_T &rhs);

    /**
     * Mat2_T Addition in place.
     * Destructive.
     */
    Mat2_T &operator+= (const Mat2_T &rhs);

    /**
     * Mat2_T Subtraction in place.
     * Destructive.
     */
    Mat2_T &operator-= (const Mat2_T &rhs);

    /**
     * Get the determinant of this Mat2_T
     */
    T Determinant () const;

    /**
     * Determine whether this Mat2_T has an inverse.
     */
    bool HasInverse () const;

    /**
     * Mirror the cells of this Matrix about the line x==y.
     */
    Mat2_T Transpose () const;

    /**
     * Mirror the cells of this Matrix about the line x==y in place.
     * Destructive.
     */
    Mat2_T &TransposeSelf ();

    /**
     * Test if this Mat2_T is equivalent to another Mat2_T.
     */
    bool Compare (const Mat2_T &other) const;

    /**
     * Test if this Mat2_T is similar to another Mat2_T
     * within a given tolerance.
     */
    bool Compare (const Mat2_T &other, const T threshold) const;

    /**
     * Test if this Mat2_T is equivalent to another Mat2_T.
     */
    bool operator== (const Mat2_T &other) const;

    /**
     * Test if this Mat2_T is not equivalent to another Mat2_T.
     */
    bool operator!= (const Mat2_T &other) const;

private:
    Vec2_T<T> mat[2];
};

// Common Mat2 types.
typedef Mat2_T<float> Mat2f;

// --------------------------------------------------------------------------

template <typename T>
INLINE Mat2_T<T>::Mat2_T (const T f) {
    mat[0].x = mat[0].y = mat[1].x = mat[1].y = f;
}

template <typename T>
INLINE Mat2_T<T>::Mat2_T (const T aa, const T ab, const T ba, const T bb) {
    mat[0].x = aa; mat[0].y = ab;
    mat[1].x = ba; mat[1].y = bb;
}

template <typename T>
INLINE Mat2_T<T>::Mat2_T (const Vec2_T<T> &col1, const Vec2_T<T> &col2) {
    mat[0].x = col1.x; mat[0].y = col1.y;
    mat[1].x = col2.x; mat[1].y = col2.y;
}

template <typename T>
INLINE Mat2_T<T>::Mat2_T (const T data[4]) {
    std::memcpy(mat, data, 4 * sizeof(T));
}

template <typename T>
INLINE Mat2_T<T>::Mat2_T (const T data[2][2]) {
    std::memcpy(mat, data, 2 * 2 * sizeof(T));
}

template <typename T>
INLINE void Mat2_T<T>::Columns (Vec2_T<T> &col1, Vec2_T<T> &col2) const {
    col1 = mat[0];
    col2 = mat[1];
}

template <typename T>
INLINE void Mat2_T<T>::Set (const T aa, const T ab, const T ba, const T bb) {
    mat[0].x = aa; mat[0].y = ab;
    mat[1].x = ba; mat[1].y = bb;
}

template <typename T>
INLINE void Mat2_T<T>::Set (const Vec2_T<T> &col1, const Vec2_T<T> &col2) {
    mat[0] = col1;
    mat[1] = col2;
}

template <typename T>
INLINE void Mat2_T<T>::Set (const T data[4]) {
    std::memcpy(mat, data, 4 * sizeof(T));
}

template <typename T>
INLINE void Mat2_T<T>::Set (const T data[2][2]) {
    std::memcpy(mat, data, 2 * 2 * sizeof(T));
}

template <typename T>
INLINE void Mat2_T<T>::Zero () {
    mat[0].Zero();
    mat[1].Zero();
}

template <typename T>
INLINE bool Mat2_T<T>::IsIdentity () const {
    return Compare(Mat2_T<T>::IDENTITY);
}

template <typename T>
INLINE const Vec2_T<T> &Mat2_T<T>::operator[] (const u32 index) const {
    return mat[index];
}

template <typename T>
INLINE Vec2_T<T> &Mat2_T<T>::operator[] (const u32 index) {
    return mat[index];
}

//=======================
// Mat2_T<T> Operators
//=======================

template <typename T>
INLINE Mat2_T<T> Mat2_T<T>::operator* (const T a) const {
    return Mat2_T<T>(mat[0] * a, mat[1] * a);
}

template <typename T>
INLINE Mat2_T<T> operator* (const T a, const Mat2_T<T> &rhs) {
    return rhs * a;
}

template <typename T>
INLINE Mat2_T<T> Mat2_T<T>::operator* (const Mat2_T<T> &rhs) const {
    return Mat2_T<T>(mat[0].x * rhs[0].x + mat[0].y * rhs[1].x,
                     mat[0].x * rhs[0].y + mat[0].y * rhs[1].y,

                     mat[1].x * rhs[0].x + mat[1].y * rhs[1].x,
                     mat[1].x * rhs[0].y + mat[1].y * rhs[1].y);
}

template <typename T>
INLINE Mat2_T<T> Mat2_T<T>::operator+ (const Mat2_T<T> &rhs) const {
    return Mat2_T<T>(mat[0] + rhs[0], mat[1] + rhs[1]);
}

template <typename T>
INLINE Mat2_T<T> Mat2_T<T>::operator- (const Mat2_T<T> &rhs) const {
    return Mat2_T<T>(mat[0] - rhs[0], mat[1] - rhs[1]);
}

template <typename T>
INLINE Mat2_T<T> &Mat2_T<T>::operator*= (const T a) {
    mat[0] *= a;
    mat[1] *= a;

    return *this;
}

template <typename T>
INLINE Mat2_T<T> &Mat2_T<T>::operator*= (const Mat2_T<T> &rhs) {
    T aa, ab, ba, bb;
    aa = mat[0].x * rhs[0].x + mat[0].y * rhs[1].x;
    ab = mat[0].x * rhs[0].y + mat[0].y * rhs[1].y;
    ba = mat[1].x * rhs[0].x + mat[1].y * rhs[1].x;
    bb = mat[1].x * rhs[0].y + mat[1].y * rhs[1].y;

    mat[0].x = aa; mat[0].y = ab;
    mat[1].x = ba; mat[1].y = bb;

    return *this;
}

template <typename T>
INLINE Mat2_T<T> &Mat2_T<T>::operator+= (const Mat2_T<T> &rhs) {
    mat[0] += rhs[0];
    mat[1] += rhs[1];

    return *this;
}

template <typename T>
INLINE Mat2_T<T> &Mat2_T<T>::operator-= (const Mat2_T<T> &rhs) {
    mat[0] -= rhs[0];
    mat[1] -= rhs[1];

    return *this;
}

template <typename T>
INLINE T Mat2_T<T>::Determinant () const {
    return mat[0].x * mat[1].y - mat[0].y * mat[1].x;
}

template <typename T>
INLINE bool Mat2_T<T>::HasInverse () const {
    return 0 != Determinant();
}

template <typename T>
INLINE Mat2_T<T> Mat2_T<T>::Transpose () const {
    return Mat2_T<T>(mat[0].x, mat[1].x, mat[0].y, mat[1].y);
}

template <typename T>
INLINE Mat2_T<T> &Mat2_T<T>::TransposeSelf () {
    std::swap(mat[0].y, mat[1].x);

    return *this;
}

//=======================
// Mat2_T<T> Comparisons
//=======================

template <typename T>
INLINE bool Mat2_T<T>::Compare (const Mat2_T<T> &other) const {
    return mat[0].Compare(other.mat[0]) &&
        mat[1].Compare(other.mat[1]);
}

template <typename T>
INLINE bool Mat2_T<T>::Compare (const Mat2_T<T> &other, const T threshold) const {
    return mat[0].Compare(other.mat[0], threshold) &&
        mat[1].Compare(other.mat[1], threshold);
}

template <typename T>
INLINE bool Mat2_T<T>::operator== (const Mat2_T<T> &other) const {
    return Compare(other);
}

template <typename T>
INLINE bool Mat2_T<T>::operator!= (const Mat2_T<T> &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_MATRIX2_H_ */
