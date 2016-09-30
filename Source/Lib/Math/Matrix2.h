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
#ifndef __SGE_MATRIX2_H
#define __SGE_MATRIX2_H

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
class Mat2f {
public:
    static const Mat2f ZERO;
    static const Mat2f ONE;
    static const Mat2f IDENTITY;

public:
    /** Construct a default (All 0.0f) Mat2f. */
    Mat2f () = default;

    /** Fill Constructor */
    explicit Mat2f (const float f);

    /** Construct a Mat2f with float values. */
    explicit Mat2f (const float aa, const float ab, const float ba, const float bb);

    /** Construct a Mat2f using Vec2f columns. */
    explicit Mat2f (const Vec2f &col1, const Vec2f &col2);

    /** 1D Array Constructor */
    explicit Mat2f (const float data[4]);

    /** 2D Array Constructor */
    explicit Mat2f (const float data[2][2]);

    /**
     * Write the data from the columns of this Mat2f into
     * Vec2fs.
     */
    void Columns (Vec2f &col1, Vec2f &col2) const;

    /**
     * Set the values of this Mat2f using Ts.
     * Destructive.
     */
    void Set (const float aa, const float ab, const float ba, const float bb);

    /**
     * Set the values of this Mat2f using Vec2f columns.
     * Destructive.
     */
    void Set (const Vec2f &col1, const Vec2f &col2);

    /**
     * Set the values of this Mat2f using a 1D array.
     * Destructive.
     */
    void Set (const float data[4]);

    /**
     * Set the values of this Mat2f using a 2D array.
     * Destructive.
     */
    void Set (const float data[2][2]);

    /**
     * Set all the values of this Mat2f to 0.0f.
     * Destructive.
     */
    void Zero ();

    /**
     * Return true if this Mat2f is the identity Matrix.
     * @return true if identity, false otherwise
     */
    bool IsIdentity () const;

    /**
     * Read access to the matrix columns using subscript notation.
     */
    const Vec2f &operator[] (const u32 index) const;

    /**
     * Reference/Write access to the matrix columns using subscript notation.
     */
    Vec2f &operator[] (const u32 index);

    // Mat2f operators

    /**
     * Mat2f Uniform Scale.
     */
    Mat2f operator* (const float a) const;

    /**
     * Mat2f Uniform Scale.
     * Reversed operands.
     */
    friend Mat2f operator* (const float a, const Mat2f &rhs);

    /**
     * Mat2f Multiplication.
     */
    Mat2f operator* (const Mat2f &rhs) const;

    /**
     * Mat2f Addition.
     */
    Mat2f operator+ (const Mat2f &rhs) const;

    /**
     * Mat2f Subtraction.
     */
    Mat2f operator- (const Mat2f &rhs) const;

    /**
     * Mat2f Uniform Scale in place.
     * Destructive.
     */
    Mat2f &operator*= (const float a);

    /**
     * Mat2f Multiplication in place.
     * Destructive.
     */
    Mat2f &operator*= (const Mat2f &rhs);

    /**
     * Mat2f Addition in place.
     * Destructive.
     */
    Mat2f &operator+= (const Mat2f &rhs);

    /**
     * Mat2f Subtraction in place.
     * Destructive.
     */
    Mat2f &operator-= (const Mat2f &rhs);

    /**
     * Get the determinant of this Mat2f
     */
    float Determinant () const;

    /**
     * Determine whether this Mat2f has an inverse.
     */
    bool HasInverse () const;

    /**
     * Mirror the cells of this Matrix about the line x==y.
     */
    Mat2f Transpose () const;

    /**
     * Mirror the cells of this Matrix about the line x==y in place.
     * Destructive.
     */
    Mat2f &TransposeSelf ();

    /**
     * Test if this Mat2f is equivalent to another Mat2f.
     */
    bool Compare (const Mat2f &other) const;

    /**
     * Test if this Mat2f is similar to another Mat2f
     * within a given tolerance.
     */
    bool Compare (const Mat2f &other, const float threshold) const;

    /**
     * Test if this Mat2f is equivalent to another Mat2f.
     */
    bool operator== (const Mat2f &other) const;

    /**
     * Test if this Mat2f is not equivalent to another Mat2f.
     */
    bool operator!= (const Mat2f &other) const;

private:
    Vec2f mat[2];
};

// --------------------------------------------------------------------------

INLINE Mat2f::Mat2f (const float f) {
    mat[0].x = mat[0].y = mat[1].x = mat[1].y = f;
}

INLINE Mat2f::Mat2f (const float aa, const float ab, const float ba, const float bb) {
    mat[0].x = aa; mat[0].y = ab;
    mat[1].x = ba; mat[1].y = bb;
}

INLINE Mat2f::Mat2f (const Vec2f &col1, const Vec2f &col2) {
    mat[0].x = col1.x; mat[0].y = col1.y;
    mat[1].x = col2.x; mat[1].y = col2.y;
}

INLINE Mat2f::Mat2f (const float data[4]) {
    std::memcpy(mat, data, 4 * sizeof(float));
}

INLINE Mat2f::Mat2f (const float data[2][2]) {
    std::memcpy(mat, data, 2 * 2 * sizeof(float));
}

INLINE void Mat2f::Columns (Vec2f &col1, Vec2f &col2) const {
    col1 = mat[0];
    col2 = mat[1];
}

INLINE void Mat2f::Set (const float aa, const float ab, const float ba, const float bb) {
    mat[0].x = aa; mat[0].y = ab;
    mat[1].x = ba; mat[1].y = bb;
}

INLINE void Mat2f::Set (const Vec2f &col1, const Vec2f &col2) {
    mat[0] = col1;
    mat[1] = col2;
}

INLINE void Mat2f::Set (const float data[4]) {
    std::memcpy(mat, data, 4 * sizeof(float));
}

INLINE void Mat2f::Set (const float data[2][2]) {
    std::memcpy(mat, data, 2 * 2 * sizeof(float));
}

INLINE void Mat2f::Zero () {
    mat[0].Zero();
    mat[1].Zero();
}

INLINE bool Mat2f::IsIdentity () const {
    return Compare(Mat2f::IDENTITY);
}

INLINE const Vec2f &Mat2f::operator[] (const u32 index) const {
    return mat[index];
}

INLINE Vec2f &Mat2f::operator[] (const u32 index) {
    return mat[index];
}

//=======================
// Mat2f Operators
//=======================

INLINE Mat2f Mat2f::operator* (const float a) const {
    return Mat2f(mat[0] * a, mat[1] * a);
}

INLINE Mat2f operator* (const float a, const Mat2f &rhs) {
    return rhs * a;
}

INLINE Mat2f Mat2f::operator* (const Mat2f &rhs) const {
    return Mat2f(mat[0].x * rhs[0].x + mat[0].y * rhs[1].x,
                     mat[0].x * rhs[0].y + mat[0].y * rhs[1].y,

                     mat[1].x * rhs[0].x + mat[1].y * rhs[1].x,
                     mat[1].x * rhs[0].y + mat[1].y * rhs[1].y);
}

INLINE Mat2f Mat2f::operator+ (const Mat2f &rhs) const {
    return Mat2f(mat[0] + rhs[0], mat[1] + rhs[1]);
}

INLINE Mat2f Mat2f::operator- (const Mat2f &rhs) const {
    return Mat2f(mat[0] - rhs[0], mat[1] - rhs[1]);
}

INLINE Mat2f &Mat2f::operator*= (const float a) {
    mat[0] *= a;
    mat[1] *= a;

    return *this;
}

INLINE Mat2f &Mat2f::operator*= (const Mat2f &rhs) {
    float aa, ab, ba, bb;
    aa = mat[0].x * rhs[0].x + mat[0].y * rhs[1].x;
    ab = mat[0].x * rhs[0].y + mat[0].y * rhs[1].y;
    ba = mat[1].x * rhs[0].x + mat[1].y * rhs[1].x;
    bb = mat[1].x * rhs[0].y + mat[1].y * rhs[1].y;

    mat[0].x = aa; mat[0].y = ab;
    mat[1].x = ba; mat[1].y = bb;

    return *this;
}

INLINE Mat2f &Mat2f::operator+= (const Mat2f &rhs) {
    mat[0] += rhs[0];
    mat[1] += rhs[1];

    return *this;
}

INLINE Mat2f &Mat2f::operator-= (const Mat2f &rhs) {
    mat[0] -= rhs[0];
    mat[1] -= rhs[1];

    return *this;
}

INLINE float Mat2f::Determinant () const {
    return mat[0].x * mat[1].y - mat[0].y * mat[1].x;
}

INLINE bool Mat2f::HasInverse () const {
    return 0 != Determinant();
}

INLINE Mat2f Mat2f::Transpose () const {
    return Mat2f(mat[0].x, mat[1].x, mat[0].y, mat[1].y);
}

INLINE Mat2f &Mat2f::TransposeSelf () {
    std::swap(mat[0].y, mat[1].x);

    return *this;
}

//=======================
// Mat2f Comparisons
//=======================

INLINE bool Mat2f::Compare (const Mat2f &other) const {
    return mat[0].Compare(other.mat[0]) &&
        mat[1].Compare(other.mat[1]);
}

INLINE bool Mat2f::Compare (const Mat2f &other, const float threshold) const {
    return mat[0].Compare(other.mat[0], threshold) &&
        mat[1].Compare(other.mat[1], threshold);
}

INLINE bool Mat2f::operator== (const Mat2f &other) const {
    return Compare(other);
}

INLINE bool Mat2f::operator!= (const Mat2f &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGE_MATRIX2_H */
