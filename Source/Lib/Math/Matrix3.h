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
class Mat3f {
public:
    static const Mat3f ZERO;
    static const Mat3f ONE;
    static const Mat3f IDENTITY;

public:
    /** Default Constructor */
    Mat3f () = default;

    /** Fill Constructor */
    explicit Mat3f (const float f);

    /** Value Constructor */
    explicit Mat3f (const float aa, const float ab, const float ac,
                     const float ba, const float bb, const float bc,
                     const float ca, const float cb, const float cc);

    /** Vec3f Column Constructor */
    explicit Mat3f (const Vec3f &col1, const Vec3f &col2, const Vec3f &col3);

    /** 1D Array Constructor */
    explicit Mat3f (const float data[9]);

    /** 2D Array Constructor */
    explicit Mat3f (const float data[3][3]);

    /**
     * Set the values of this Mat3f using Ts.
     * Destructive.
     */
    void Set (const float aa, const float ab, const float ac,
              const float ba, const float bb, const float bc,
              const float ca, const float cb, const float cc);

    /**
     * Set the values of this Mat3f using Vec3f columns.
     * Destructive.
     */
    void Set (const Vec3f &col1, const Vec3f &col2, const Vec3f &col3);

    /**
     * Set the values of this Mat3f using a 1D array.
     * Destructive.
     */
    void Set (const float data[9]);

    /**
     * Set the values of this Mat3f using a 2D array.
     * Destructive.
     */
    void Set (const float data[3][3]);

    /**
     * Set all values of this Mat3f to zero.
     * Destructive.
     */
    void Zero ();

    bool IsIdentity () const;

    const Vec3f &operator[] (const u32 index) const;

    Vec3f &operator[] (const u32 index);

    /**
     * Mat3f Scale.
     */
    Mat3f operator* (const float a) const;

    /**
     * Mat3f Scale, reversed operands.
     */
    friend Mat3f operator* (const float a, const Mat3f &rhs);

    /**
     * Mat3f Multiplication.
     */
    Mat3f operator* (const Mat3f &rhs) const;

    /**
     * Mat3f x Vec3f multiplication.
     */
    Vec3f operator* (const Vec3f &rhs) const;

    /**
     * Vec3f x Mat3f multiplication.
     */
    friend Vec3f operator* (const Vec3f &lhs, const Mat3f &rhs);

    /**
     * Mat3f Addition.
     */
    Mat3f operator+ (const Mat3f &rhs) const;

    /**
     * Mat3f Subtraction.
     */
    Mat3f operator- (const Mat3f &rhs) const;

    /**
     * Mat3f Scale in place.
     * Destructive.
     */
    Mat3f &operator*= (const float a);

    /**
     * Mat3f Multiplication in place.
     * Destructive.
     */
    Mat3f &operator*= (const Mat3f &rhs);

    /**
     * Mat3f Addition in place.
     */
    Mat3f &operator+= (const Mat3f &rhs);

    /**
     * Mat3f Subtraction in place.
     */
    Mat3f &operator-= (const Mat3f &rhs);

    /**
     * Get the determinant of this Mat3f.
     */
    float Determinant () const;

    /**
     * Determine if this Mat3f has an inverse.
     */
    bool HasInverse () const;

    /**
     * Get the inverse of this Mat3f.
     */
    Mat3f Inverse () const;

    /**
     * Set this Mat3f to be its inverse.
     * Destructive.
     * @return false if Mat3f has no inverse, true if success.
     */
    bool InverseSelf ();

    Mat3f Transpose () const;

    Mat3f &TransposeSelf ();

    /**
     * Test if this Mat3f is equivalent to another Mat3f.
     */
    bool Compare (const Mat3f &other) const;

    /**
     * Test if this Mat3f is similar to another Mat3f
     * within a given tolerance.
     */
    bool Compare (const Mat3f &other, const float threshold) const;

    /**
     * Test if this Mat3f is equivalent to another Mat3f.
     */
    bool operator== (const Mat3f &other) const;

    /**
     * Test if this Mat3f is not equivalent to another Mat3f.
     */
    bool operator!= (const Mat3f &other) const;

private:
    Vec3f mat[3];
};

// --------------------------------------------------------------------------

INLINE Mat3f::Mat3f (const float f) {
    mat[0].x = mat[0].y = mat[0].z = f;
    mat[1].x = mat[1].y = mat[1].z = f;
    mat[2].x = mat[2].y = mat[2].z = f;
}

INLINE Mat3f::Mat3f (const float aa, const float ab, const float ac,
                          const float ba, const float bb, const float bc,
                          const float ca, const float cb, const float cc) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc;
}

INLINE Mat3f::Mat3f (const Vec3f &col1, const Vec3f &col2, const Vec3f &col3) {
    mat[0].x = col1.x; mat[0].y = col1.y; mat[0].z = col1.z;
    mat[1].x = col2.x; mat[1].y = col2.y; mat[1].z = col2.z;
    mat[2].x = col3.x; mat[2].y = col3.y; mat[2].z = col3.z;
}

INLINE Mat3f::Mat3f (const float data[9]) {
    std::memcpy(mat, data, 9 * sizeof(float));
}

INLINE Mat3f::Mat3f (const float data[3][3]) {
    std::memcpy(mat, data, 3 * 3 * sizeof(float));
}

INLINE void Mat3f::Set (const float aa, const float ab, const float ac,
                            const float ba, const float bb, const float bc,
                            const float ca, const float cb, const float cc) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc;
}

INLINE void Mat3f::Set (const Vec3f &col1, const Vec3f &col2, const Vec3f &col3) {
    mat[0] = col1;
    mat[1] = col2;
    mat[2] = col3;
}

INLINE void Mat3f::Set (const float data[9]) {
    std::memcpy(mat, data, 9 * sizeof(float));
}

INLINE void Mat3f::Set (const float data[3][3]) {
    std::memcpy(mat, data, 3 * 3 * sizeof(float));
}

INLINE void Mat3f::Zero () {
    mat[0].Zero();
    mat[1].Zero();
    mat[2].Zero();
}

INLINE bool Mat3f::IsIdentity () const {
    return Compare(Mat3f::IDENTITY);
}

INLINE const Vec3f &Mat3f::operator[] (const u32 index) const {
    return mat[index];
}

INLINE Vec3f &Mat3f::operator[] (const u32 index) {
    return mat[index];
}

//=======================
// Mat3f Operations
//=======================

INLINE Mat3f Mat3f::operator* (const float a) const {
    return Mat3f(mat[0] * a, mat[1] * a, mat[2] * a);
}

INLINE Mat3f operator* (const float a, const Mat3f &rhs) {
    return rhs * a;
}

INLINE Mat3f Mat3f::operator* (const Mat3f &rhs) const {
    Mat3f lhs = Transpose();

    return Mat3f(lhs[0].Dot(rhs[0]), lhs[1].Dot(rhs[0]), lhs[2].Dot(rhs[0]),
                     lhs[0].Dot(rhs[1]), lhs[1].Dot(rhs[1]), lhs[2].Dot(rhs[1]),
                     lhs[0].Dot(rhs[2]), lhs[1].Dot(rhs[2]), lhs[2].Dot(rhs[2]));
}

INLINE Vec3f Mat3f::operator* (const Vec3f &rhs) const {
    return Vec3f(mat[0].x * rhs.x + mat[1].x * rhs.y + mat[2].x * rhs.z,
                     mat[0].y * rhs.x + mat[1].y * rhs.y + mat[2].y * rhs.z,
                     mat[0].z * rhs.x + mat[1].z * rhs.y + mat[2].z * rhs.z);
}

INLINE Vec3f operator* (const Vec3f &lhs, const Mat3f &rhs) {
    return rhs * lhs;
}

INLINE Mat3f Mat3f::operator+ (const Mat3f &rhs) const {
    return Mat3f(mat[0] + rhs[0], mat[1] + rhs[1], mat[2] + rhs[2]);
}

INLINE Mat3f Mat3f::operator- (const Mat3f &rhs) const {
    return Mat3f(mat[0] - rhs[0], mat[1] - rhs[1], mat[2] - rhs[2]);
}

INLINE Mat3f &Mat3f::operator*= (const float a) {
    mat[0] *= a;
    mat[1] *= a;
    mat[2] *= a;

    return *this;
}

INLINE Mat3f &Mat3f::operator*= (const Mat3f &rhs) {
    Mat3f lhs = Transpose();

    Set(lhs[0].Dot(rhs[0]), lhs[1].Dot(rhs[0]), lhs[2].Dot(rhs[0]),
        lhs[0].Dot(rhs[1]), lhs[1].Dot(rhs[1]), lhs[2].Dot(rhs[1]),
        lhs[0].Dot(rhs[2]), lhs[1].Dot(rhs[2]), lhs[2].Dot(rhs[2]));

    return *this;
}

INLINE Mat3f &Mat3f::operator+= (const Mat3f &rhs) {
    mat[0] += rhs[0];
    mat[1] += rhs[1];
    mat[2] += rhs[2];

    return *this;
}

INLINE Mat3f &Mat3f::operator-= (const Mat3f &rhs) {
    mat[0] -= rhs[0];
    mat[1] -= rhs[1];
    mat[2] -= rhs[2];

    return *this;
}

INLINE float Mat3f::Determinant () const {
    // Laplace Expansion Determinant
    //    0 1 2
    // x |0 3 6|
    // y |1 4 7|
    // z |2 5 8|
    return mat[0].x * (mat[1].y * mat[2].z - mat[2].y * mat[1].z) -
        mat[0].y * (mat[1].x * mat[2].z - mat[2].x * mat[1].z) +
        mat[0].z * (mat[1].x * mat[2].y - mat[2].x * mat[1].y);
}

INLINE bool Mat3f::HasInverse () const {
    return 0 != Determinant();
}

INLINE Mat3f Mat3f::Transpose () const {
    return Mat3f(mat[0].x, mat[1].x, mat[2].x,
                     mat[0].y, mat[1].y, mat[2].y,
                     mat[0].z, mat[1].z, mat[2].z);
}

INLINE Mat3f &Mat3f::TransposeSelf () {
    std::swap(mat[0].y, mat[1].x);
    std::swap(mat[0].z, mat[2].x);
    std::swap(mat[1].z, mat[2].y);

    return *this;
}

//=======================
// Mat3f Comparisons
//=======================

INLINE bool Mat3f::Compare (const Mat3f &other) const {
    return mat[0].Compare(other.mat[0]) &&
        mat[1].Compare(other.mat[1]) &&
        mat[2].Compare(other.mat[2]);
}

INLINE bool Mat3f::Compare (const Mat3f &other, const float threshold) const {
    return mat[0].Compare(other.mat[0], threshold) &&
        mat[1].Compare(other.mat[1], threshold) &&
        mat[2].Compare(other.mat[2], threshold);
}

INLINE bool Mat3f::operator== (const Mat3f &other) const {
    return Compare(other);
}

INLINE bool Mat3f::operator!= (const Mat3f &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_MATRIX3_H_ */
