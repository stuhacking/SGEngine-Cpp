/*---  Matrix2.h - 2x2 Matrix Header  ------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level Matrix2 type.
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
class Matrix2 {
public:
    static const Matrix2 ZERO;
    static const Matrix2 ONE;
    static const Matrix2 IDENTITY;

public:
    /** Construct a default (All 0.0f) Matrix2. */
    Matrix2 () { }

    /** Fill Constructor */
    Matrix2 (const float f);

    /** Construct a Matrix2 with float values. */
    Matrix2 (const float aa, const float ab, const float ba, const float bb);

    /** Construct a Matrix2 using Vec2f columns. */
    Matrix2 (const Vec2f &col1, const Vec2f &col2);

    /** 1D Array Constructor */
    Matrix2 (const float data[4]);

    /** 2D Array Constructor */
    Matrix2 (const float data[2][2]);

    /**
     * Write the data from the columns of this Matrix2 into
     * Vec2fs.
     */
    void Columns (Vec2f &col1, Vec2f &col2) const;

    /**
     * Set the values of this Matrix2 using floats.
     * Destructive.
     */
    void Set (const float aa, const float ab, const float ba, const float bb);

    /**
     * Set the values of this Matrix2 using Vec2f columns.
     * Destructive.
     */
    void Set (const Vec2f &col1, const Vec2f &col2);

    /**
     * Set the values of this Matrix2 using a 1D array.
     * Destructive.
     */
    void Set (const float data[4]);

    /**
     * Set the values of this Matrix2 using a 2D array.
     * Destructive.
     */
    void Set (const float data[2][2]);

    /**
     * Set all the values of this Matrix2 to 0.0f.
     * Destructive.
     */
    void Zero ();

    /**
     * Return true if this Matrix2 is the identity Matrix.
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

    // Matrix2 operators

    /**
     * Matrix2 Uniform Scale.
     */
    Matrix2 operator* (const float a) const;

    /**
     * Matrix2 Uniform Scale.
     * Reversed operands.
     */
    friend Matrix2 operator* (const float a, const Matrix2 &rhs);

    /**
     * Matrix2 Multiplication.
     */
    Matrix2 operator* (const Matrix2 &rhs) const;

    /**
     * Matrix2 Addition.
     */
    Matrix2 operator+ (const Matrix2 &rhs) const;

    /**
     * Matrix2 Subtraction.
     */
    Matrix2 operator- (const Matrix2 &rhs) const;

    /**
     * Matrix2 Uniform Scale in place.
     * Destructive.
     */
    Matrix2 &operator*= (const float a);

    /**
     * Matrix2 Multiplication in place.
     * Destructive.
     */
    Matrix2 &operator*= (const Matrix2 &rhs);

    /**
     * Matrix2 Addition in place.
     * Destructive.
     */
    Matrix2 &operator+= (const Matrix2 &rhs);

    /**
     * Matrix2 Subtraction in place.
     * Destructive.
     */
    Matrix2 &operator-= (const Matrix2 &rhs);

    /**
     * Get the determinant of this Matrix2
     */
    float Determinant () const;

    /**
     * Determine whether this Matrix2 has an inverse.
     */
    bool HasInverse () const;

    /**
     * Mirror the cells of this Matrix about the line x==y.
     */
    Matrix2 Transpose () const;

    /**
     * Mirror the cells of this Matrix about the line x==y in place.
     * Destructive.
     */
    Matrix2 &TransposeSelf ();

    /**
     * Test if this Matrix2 is equivalent to another Matrix2.
     */
    bool Compare (const Matrix2 &other) const;

    /**
     * Test if this Matrix2 is similar to another Matrix2
     * within a given tolerance.
     */
    bool Compare (const Matrix2 &other, const float threshold) const;

    /**
     * Test if this Matrix2 is equivalent to another Matrix2.
     */
    bool operator== (const Matrix2 &other) const;

    /**
     * Test if this Matrix2 is not equivalent to another Matrix2.
     */
    bool operator!= (const Matrix2 &other) const;

private:
    Vec2f mat[2];
};

// --------------------------------------------------------------------------

INLINE Matrix2::Matrix2 (const float f) {
    mat[0].x = mat[0].y = mat[1].x = mat[1].y = f;
}

INLINE Matrix2::Matrix2 (const float aa, const float ab, const float ba, const float bb) {
    mat[0].x = aa; mat[0].y = ab;
    mat[1].x = ba; mat[1].y = bb;
}

INLINE Matrix2::Matrix2 (const Vec2f &col1, const Vec2f &col2) {
    mat[0].x = col1.x; mat[0].y = col1.y;
    mat[1].x = col2.x; mat[1].y = col2.y;
}

INLINE Matrix2::Matrix2 (const float data[4]) {
    std::memcpy(mat, data, 4 * sizeof(float));
}

INLINE Matrix2::Matrix2 (const float data[2][2]) {
    std::memcpy(mat, data, 2 * 2 * sizeof(float));
}

INLINE void Matrix2::Columns (Vec2f &col1, Vec2f &col2) const {
    col1 = mat[0];
    col2 = mat[1];
}

INLINE void Matrix2::Set (const float aa, const float ab, const float ba, const float bb) {
    mat[0].x = aa; mat[0].y = ab;
    mat[1].x = ba; mat[1].y = bb;
}

INLINE void Matrix2::Set (const Vec2f &col1, const Vec2f &col2) {
    mat[0] = col1;
    mat[1] = col2;
}

INLINE void Matrix2::Set (const float data[4]) {
    std::memcpy(mat, data, 4 * sizeof(float));
}

INLINE void Matrix2::Set (const float data[2][2]) {
    std::memcpy(mat, data, 2 * 2 * sizeof(float));
}

INLINE void Matrix2::Zero () {
    mat[0].Zero();
    mat[1].Zero();
}

INLINE bool Matrix2::IsIdentity () const {
    return Compare(Matrix2::IDENTITY);
}

INLINE const Vec2f &Matrix2::operator[] (const u32 index) const {
    return mat[index];
}

INLINE Vec2f &Matrix2::operator[] (const u32 index) {
    return mat[index];
}

//=======================
// Matrix2 Operators
//=======================

INLINE Matrix2 Matrix2::operator* (const float a) const {
    return Matrix2(mat[0] * a, mat[1] * a);
}

INLINE Matrix2 operator* (const float a, const Matrix2 &rhs) {
    return rhs * a;
}

INLINE Matrix2 Matrix2::operator* (const Matrix2 &rhs) const {
    return Matrix2(mat[0].x * rhs[0].x + mat[0].y * rhs[1].x,
                   mat[0].x * rhs[0].y + mat[0].y * rhs[1].y,

                   mat[1].x * rhs[0].x + mat[1].y * rhs[1].x,
                   mat[1].x * rhs[0].y + mat[1].y * rhs[1].y);
}

INLINE Matrix2 Matrix2::operator+ (const Matrix2 &rhs) const {
    return Matrix2(mat[0] + rhs[0], mat[1] + rhs[1]);
}

INLINE Matrix2 Matrix2::operator- (const Matrix2 &rhs) const {
    return Matrix2(mat[0] - rhs[0], mat[1] - rhs[1]);
}

INLINE Matrix2 &Matrix2::operator*= (const float a) {
    mat[0] *= a;
    mat[1] *= a;

    return *this;
}

INLINE Matrix2 &Matrix2::operator*= (const Matrix2 &rhs) {
    float aa, ab, ba, bb;
    aa = mat[0].x * rhs[0].x + mat[0].y * rhs[1].x;
    ab = mat[0].x * rhs[0].y + mat[0].y * rhs[1].y;
    ba = mat[1].x * rhs[0].x + mat[1].y * rhs[1].x;
    bb = mat[1].x * rhs[0].y + mat[1].y * rhs[1].y;

    mat[0].x = aa; mat[0].y = ab;
    mat[1].x = ba; mat[1].y = bb;

    return *this;
}

INLINE Matrix2 &Matrix2::operator+= (const Matrix2 &rhs) {
    mat[0] += rhs[0];
    mat[1] += rhs[1];

    return *this;
}

INLINE Matrix2 &Matrix2::operator-= (const Matrix2 &rhs) {
    mat[0] -= rhs[0];
    mat[1] -= rhs[1];

    return *this;
}

INLINE float Matrix2::Determinant () const {
    return mat[0].x * mat[1].y - mat[0].y * mat[1].x;
}

INLINE bool Matrix2::HasInverse () const {
    return 0 != Determinant();
}

INLINE Matrix2 Matrix2::Transpose () const {
    return Matrix2(mat[0].x, mat[1].x, mat[0].y, mat[1].y);
}

INLINE Matrix2 &Matrix2::TransposeSelf () {
    std::swap(mat[0].y, mat[1].x);

    return *this;
}

//=======================
// Matrix2 Comparisons
//=======================

INLINE bool Matrix2::Compare (const Matrix2 &other) const {
    return mat[0].Compare(other.mat[0]) &&
        mat[1].Compare(other.mat[1]);
}

INLINE bool Matrix2::Compare (const Matrix2 &other, const float threshold) const {
    return mat[0].Compare(other.mat[0], threshold) &&
        mat[1].Compare(other.mat[1], threshold);
}

INLINE bool Matrix2::operator== (const Matrix2 &other) const {
    return Compare(other);
}

INLINE bool Matrix2::operator!= (const Matrix2 &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_MATRIX2_H_ */
