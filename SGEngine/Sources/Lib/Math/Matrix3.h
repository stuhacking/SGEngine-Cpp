/*---  Matrix3.h - 3x3 Matrix Header  ------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level Matrix3 type.
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
class Matrix3 {
public:
    static const Matrix3 ZERO;
    static const Matrix3 ONE;
    static const Matrix3 IDENTITY;

public:
    /** Default Constructor */
    Matrix3 () { }

    /** Fill Constructor */
    Matrix3 (const float f);

    /** Value Constructor */
    Matrix3 (const float aa, const float ab, const float ac,
             const float ba, const float bb, const float bc,
             const float ca, const float cb, const float cc);

    /** Vec3f Column Constructor */
    Matrix3 (const Vec3f &col1, const Vec3f &col2, const Vec3f &col3);

    /** 1D Array Constructor */
    Matrix3 (const float data[9]);

    /** 2D Array Constructor */
    Matrix3 (const float data[3][3]);

    /**
     * Set the values of this Matrix3 using floats.
     * Destructive.
     */
    void Set (const float aa, const float ab, const float ac,
              const float ba, const float bb, const float bc,
              const float ca, const float cb, const float cc);

    /**
     * Set the values of this Matrix3 using Vec3f columns.
     * Destructive.
     */
    void Set (const Vec3f &col1, const Vec3f &col2, const Vec3f &col3);

    /**
     * Set the values of this Matrix3 using a 1D array.
     * Destructive.
     */
    void Set (const float data[9]);

    /**
     * Set the values of this Matrix3 using a 2D array.
     * Destructive.
     */
    void Set (const float data[3][3]);

    /**
     * Set all values of this Matrix3 to zero.
     * Destructive.
     */
    void Zero ();

    bool IsIdentity () const;

    const Vec3f &operator[] (const u32 index) const;

    Vec3f &operator[] (const u32 index);

    /**
     * Matrix3 Scale.
     */
    Matrix3 operator* (const float a) const;

    /**
     * Matrix3 Scale, reversed operands.
     */
    friend Matrix3 operator* (const float a, const Matrix3 &rhs);

    /**
     * Matrix3 Multiplication.
     */
    Matrix3 operator* (const Matrix3 &rhs) const;

    /**
     * Matrix3 x Vec3f multiplication.
     */
    Vec3f operator* (const Vec3f &rhs) const;

    /**
     * Vec3f x Matrix3 multiplication.
     */
    friend Vec3f operator* (const Vec3f &lhs, const Matrix3 &rhs);

    /**
     * Matrix3 Addition.
     */
    Matrix3 operator+ (const Matrix3 &rhs) const;

    /**
     * Matrix3 Subtraction.
     */
    Matrix3 operator- (const Matrix3 &rhs) const;

    /**
     * Matrix3 Scale in place.
     * Destructive.
     */
    Matrix3 &operator*= (const float a);

    /**
     * Matrix3 Multiplication in place.
     * Destructive.
     */
    Matrix3 &operator*= (const Matrix3 &rhs);

    /**
     * Matrix3 Addition in place.
     */
    Matrix3 &operator+= (const Matrix3 &rhs);

    /**
     * Matrix3 Subtraction in place.
     */
    Matrix3 &operator-= (const Matrix3 &rhs);

    /**
     * Get the determinant of this Matrix3.
     */
    float Determinant () const;

    /**
     * Determine if this Matrix3 has an inverse.
     */
    bool HasInverse () const;

    /**
     * Get the inverse of this Matrix3.
     */
    Matrix3 Inverse () const;

    /**
     * Set this Matrix3 to be its inverse.
     * Destructive.
     * @return false if Matrix3 has no inverse, true if success.
     */
    bool InverseSelf ();

    Matrix3 Transpose () const;

    Matrix3 &TransposeSelf ();

    /**
     * Test if this Matrix3 is equivalent to another Matrix3.
     */
    bool Compare (const Matrix3 &other) const;

    /**
     * Test if this Matrix3 is similar to another Matrix3
     * within a given tolerance.
     */
    bool Compare (const Matrix3 &other, const float threshold) const;

    /**
     * Test if this Matrix3 is equivalent to another Matrix3.
     */
    bool operator== (const Matrix3 &other) const;

    /**
     * Test if this Matrix3 is not equivalent to another Matrix3.
     */
    bool operator!= (const Matrix3 &other) const;

private:
    Vec3f mat[3];
};

// --------------------------------------------------------------------------

INLINE Matrix3::Matrix3 (const float f) {
    mat[0].x = mat[0].y = mat[0].z = f;
    mat[1].x = mat[1].y = mat[1].z = f;
    mat[2].x = mat[2].y = mat[2].z = f;
}

INLINE Matrix3::Matrix3 (const float aa, const float ab, const float ac,
                         const float ba, const float bb, const float bc,
                         const float ca, const float cb, const float cc) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc;
}

INLINE Matrix3::Matrix3 (const Vec3f &col1, const Vec3f &col2, const Vec3f &col3) {
    mat[0].x = col1.x; mat[0].y = col1.y; mat[0].z = col1.z;
    mat[1].x = col2.x; mat[1].y = col2.y; mat[1].z = col2.z;
    mat[2].x = col3.x; mat[2].y = col3.y; mat[2].z = col3.z;
}

INLINE Matrix3::Matrix3 (const float data[9]) {
    std::memcpy(mat, data, 9 * sizeof(float));
}

INLINE Matrix3::Matrix3 (const float data[3][3]) {
    std::memcpy(mat, data, 3 * 3 * sizeof(float));
}

INLINE void Matrix3::Set (const float aa, const float ab, const float ac,
                          const float ba, const float bb, const float bc,
                          const float ca, const float cb, const float cc) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc;
}

INLINE void Matrix3::Set (const Vec3f &col1, const Vec3f &col2, const Vec3f &col3) {
    mat[0] = col1;
    mat[1] = col2;
    mat[2] = col3;
}

INLINE void Matrix3::Set (const float data[9]) {
    std::memcpy(mat, data, 9 * sizeof(float));
}

INLINE void Matrix3::Set (const float data[3][3]) {
    std::memcpy(mat, data, 3 * 3 * sizeof(float));
}

INLINE void Matrix3::Zero () {
    mat[0].Zero();
    mat[1].Zero();
    mat[2].Zero();
}

INLINE bool Matrix3::IsIdentity () const {
    return Compare(Matrix3::IDENTITY);
}

INLINE const Vec3f &Matrix3::operator[] (const u32 index) const {
    return mat[index];
}

INLINE Vec3f &Matrix3::operator[] (const u32 index) {
    return mat[index];
}

//=======================
// Matrix3 Operations
//=======================

INLINE Matrix3 Matrix3::operator* (const float a) const {
    return Matrix3(mat[0] * a, mat[1] * a, mat[2] * a);
}

INLINE Matrix3 operator* (const float a, const Matrix3 &rhs) {
    return rhs * a;
}

INLINE Matrix3 Matrix3::operator* (const Matrix3 &rhs) const {
    Matrix3 lhs = Transpose();

    return Matrix3(lhs[0].Dot(rhs[0]), lhs[1].Dot(rhs[0]), lhs[2].Dot(rhs[0]),
                   lhs[0].Dot(rhs[1]), lhs[1].Dot(rhs[1]), lhs[2].Dot(rhs[1]),
                   lhs[0].Dot(rhs[2]), lhs[1].Dot(rhs[2]), lhs[2].Dot(rhs[2]));
}

INLINE Vec3f Matrix3::operator* (const Vec3f &rhs) const {
    return Vec3f(mat[0].x * rhs.x + mat[1].x * rhs.y + mat[2].x * rhs.z,
                   mat[0].y * rhs.x + mat[1].y * rhs.y + mat[2].y * rhs.z,
                   mat[0].z * rhs.x + mat[1].z * rhs.y + mat[2].z * rhs.z);
}

INLINE Vec3f operator* (const Vec3f &lhs, const Matrix3 &rhs) {
    return rhs * lhs;
}

INLINE Matrix3 Matrix3::operator+ (const Matrix3 &rhs) const {
    return Matrix3(mat[0] + rhs[0], mat[1] + rhs[1], mat[2] + rhs[2]);
}

INLINE Matrix3 Matrix3::operator- (const Matrix3 &rhs) const {
    return Matrix3(mat[0] - rhs[0], mat[1] - rhs[1], mat[2] - rhs[2]);
}

INLINE Matrix3 &Matrix3::operator*= (const float a) {
    mat[0] *= a;
    mat[1] *= a;
    mat[2] *= a;

    return *this;
}

INLINE Matrix3 &Matrix3::operator*= (const Matrix3 &rhs) {
    Matrix3 lhs = Transpose();

    Set(lhs[0].Dot(rhs[0]), lhs[1].Dot(rhs[0]), lhs[2].Dot(rhs[0]),
        lhs[0].Dot(rhs[1]), lhs[1].Dot(rhs[1]), lhs[2].Dot(rhs[1]),
        lhs[0].Dot(rhs[2]), lhs[1].Dot(rhs[2]), lhs[2].Dot(rhs[2]));

    return *this;
}

INLINE Matrix3 &Matrix3::operator+= (const Matrix3 &rhs) {
    mat[0] += rhs[0];
    mat[1] += rhs[1];
    mat[2] += rhs[2];

    return *this;
}

INLINE Matrix3 &Matrix3::operator-= (const Matrix3 &rhs) {
    mat[0] -= rhs[0];
    mat[1] -= rhs[1];
    mat[2] -= rhs[2];

    return *this;
}

INLINE float Matrix3::Determinant () const {
    // Laplace Expansion Determinant
    //    0 1 2
    // x |0 3 6|
    // y |1 4 7|
    // z |2 5 8|
    return mat[0].x * (mat[1].y * mat[2].z - mat[2].y * mat[1].z) -
           mat[0].y * (mat[1].x * mat[2].z - mat[2].x * mat[1].z) +
           mat[0].z * (mat[1].x * mat[2].y - mat[2].x * mat[1].y);
}

INLINE bool Matrix3::HasInverse () const {
    return 0 != Determinant();
}

INLINE Matrix3 Matrix3::Transpose () const {
    return Matrix3(mat[0].x, mat[1].x, mat[2].x,
                   mat[0].y, mat[1].y, mat[2].y,
                   mat[0].z, mat[1].z, mat[2].z);
}

INLINE Matrix3 &Matrix3::TransposeSelf () {
    std::swap(mat[0].y, mat[1].x);
    std::swap(mat[0].z, mat[2].x);
    std::swap(mat[1].z, mat[2].y);

    return *this;
}

//=======================
// Matrix3 Comparisons
//=======================

INLINE bool Matrix3::Compare (const Matrix3 &other) const {
    return mat[0].Compare(other.mat[0]) &&
        mat[1].Compare(other.mat[1]) &&
        mat[2].Compare(other.mat[2]);
}

INLINE bool Matrix3::Compare (const Matrix3 &other, const float threshold) const {
    return mat[0].Compare(other.mat[0], threshold) &&
        mat[1].Compare(other.mat[1], threshold) &&
        mat[2].Compare(other.mat[2], threshold);
}

INLINE bool Matrix3::operator== (const Matrix3 &other) const {
    return Compare(other);
}

INLINE bool Matrix3::operator!= (const Matrix3 &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_MATRIX3_H_ */
