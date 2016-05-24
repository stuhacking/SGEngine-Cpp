/*---  Matrix4.h - 4x4 Matrix Header  ------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level Matrix4 type.
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
class Matrix4 {
public:
    static const Matrix4 ZERO;
    static const Matrix4 ONE;
    static const Matrix4 IDENTITY;

public:
    /** Default Constructor */
    Matrix4 () { }

    /** Fill Constructor */
    Matrix4 (const float f);

    /** Value Constructor */
    Matrix4 (const float aa, const float ab, const float ac, const float ad,
             const float ba, const float bb, const float bc, const float bd,
             const float ca, const float cb, const float cc, const float cd,
             const float da, const float db, const float dc, const float dd);

    /** Vec4f Column Constructor */
    Matrix4 (const Vec4f &col1, const Vec4f &col2,
             const Vec4f &col3, const Vec4f &col4);

    /** 1D Array Constructor */
    Matrix4 (const float data[16]);

    /** 2D Array Constructor */
    Matrix4 (const float data[4][4]);

    /**
     * Set the values of this Matrix4 using float values.
     * Destructive.
     */
    void Set (const float aa, const float ab, const float ac, const float ad,
              const float ba, const float bb, const float bc, const float bd,
              const float ca, const float cb, const float cc, const float cd,
              const float da, const float db, const float dc, const float dd);

    /**
     * Set the columns of this Matrix4 using Vec4fs.
     * Destructive.
     */
    void Set (const Vec4f &col1, const Vec4f &col2, const Vec4f &col3, const Vec4f &col4);

    /**
     * Set the values of this Matrix4 using a 1D float array.
     * Destructive.
     */
    void Set (const float data[16]);

    /**
     * Set the values of this Matrix4 using a 2D float array.
     * Destructive.
     */
    void Set (const float data[4][4]);

    /**
     * Set all values of this Matrix4 to zero.
     * Destructive.
     */
    void Zero ();

    /**
     * Test if this Matrix4 is the identity Matrix.
     */
    bool IsIdentity () const;

    const Vec4f &operator[] (const u32 index) const;

    Vec4f &operator[] (const u32 index);

    /** Matrix4 operations. */
    Matrix4 operator* (const float a) const;

    friend Matrix4 operator* (const float a, const Matrix4 &rhs);

    Matrix4 operator* (const Matrix4 &rhs) const;

    Vec4f operator* (const Vec4f &rhs) const;

    friend Vec4f operator* (const Vec4f &lhs, const Matrix4 &rhs);

    Matrix4 operator+ (const Matrix4 &rhs) const;

    Matrix4 operator- (const Matrix4 &rhs) const;

    Matrix4 &operator*= (const float a);

    Matrix4 &operator*= (const Matrix4 &rhs);

    Matrix4 &operator+= (const Matrix4 &rhs);

    Matrix4 &operator-= (const Matrix4 &rhs);

    float Determinant () const;

    bool HasInverse () const;

    Matrix4 Inverse () const;

    bool InverseSelf ();

    Matrix4 Transpose () const;

    Matrix4 &TransposeSelf ();

    /** Comarisons. */
    bool Compare (const Matrix4 &other) const;

    bool Compare (const Matrix4 &other, const float threshold) const;

    bool operator== (const Matrix4 &other) const;

    bool operator!= (const Matrix4 &other) const;

public:
    Vec4f mat[4];
};

// --------------------------------------------------------------------------

INLINE Matrix4::Matrix4 (const float f) {
    mat[0].x = f; mat[0].y = f; mat[0].z = f; mat[0].w = f;
    mat[1].x = f; mat[1].y = f; mat[1].z = f; mat[1].w = f;
    mat[2].x = f; mat[2].y = f; mat[2].z = f; mat[2].w = f;
    mat[3].x = f; mat[3].y = f; mat[3].z = f; mat[3].w = f;
}

INLINE Matrix4::Matrix4 (const float aa, const float ab, const float ac, const float ad,
                         const float ba, const float bb, const float bc, const float bd,
                         const float ca, const float cb, const float cc, const float cd,
                         const float da, const float db, const float dc, const float dd) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac; mat[0].w = ad;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc; mat[1].w = bd;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc; mat[2].w = cd;
    mat[3].x = da; mat[3].y = db; mat[3].z = dc; mat[3].w = dd;
}

INLINE Matrix4::Matrix4 (const Vec4f &col1, const Vec4f &col2,
                         const Vec4f &col3, const Vec4f &col4) {
    mat[0].x = col1.x; mat[0].y = col1.y; mat[0].z = col1.z; mat[0].w = col1.w;
    mat[1].x = col2.x; mat[1].y = col2.y; mat[1].z = col2.z; mat[1].w = col2.w;
    mat[2].x = col3.x; mat[2].y = col3.y; mat[2].z = col3.z; mat[2].w = col3.w;
    mat[3].x = col4.x; mat[3].y = col4.y; mat[3].z = col4.z; mat[3].w = col4.w;
}

INLINE Matrix4::Matrix4 (const float data[16]) {
    std::memcpy(mat, data, 16 * sizeof(float));
}

INLINE Matrix4::Matrix4 (const float data[4][4]) {
    std::memcpy(mat, data, 4 * 4 * sizeof(float));
}

INLINE void Matrix4::Set (const float aa, const float ab, const float ac, const float ad,
                          const float ba, const float bb, const float bc, const float bd,
                          const float ca, const float cb, const float cc, const float cd,
                          const float da, const float db, const float dc, const float dd) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac; mat[0].w = ad;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc; mat[1].w = bd;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc; mat[2].w = cd;
    mat[3].x = da; mat[3].y = db; mat[3].z = dc; mat[3].w = dd;
}

INLINE void Matrix4::Set (const Vec4f &col1, const Vec4f &col2,
                          const Vec4f &col3, const Vec4f &col4) {
    mat[0].x = col1.x; mat[0].y = col1.y; mat[0].z = col1.z; mat[0].w = col1.w;
    mat[1].x = col2.x; mat[1].y = col2.y; mat[1].z = col2.z; mat[1].w = col2.w;
    mat[2].x = col3.x; mat[2].y = col3.y; mat[2].z = col3.z; mat[2].w = col3.w;
    mat[3].x = col4.x; mat[3].y = col4.y; mat[3].z = col4.z; mat[3].w = col4.w;
}

INLINE void Matrix4::Set (const float data[16]) {
    std::memcpy(mat, data, 16 * sizeof(float));
}

INLINE void Matrix4::Set (const float data[4][4]) {
    std::memcpy(mat, data, 4 * 4 * sizeof(float));
}

INLINE void Matrix4::Zero () {
    mat[0].Zero();
    mat[1].Zero();
    mat[2].Zero();
    mat[3].Zero();
}

INLINE bool Matrix4::IsIdentity () const {
    return Compare(Matrix4::IDENTITY);
}

INLINE const Vec4f &Matrix4::operator[] (const u32 index) const {
    return mat[index];
}

INLINE Vec4f &Matrix4::operator[] (const u32 index) {
    return mat[index];
}

//=======================
// Matrix4 Operations
//=======================

INLINE Matrix4 Matrix4::operator* (const float a) const {
    return Matrix4(mat[0] * a, mat[1] * a, mat[2] * a, mat[3] * a);
}

INLINE Matrix4 operator* (const float a, const Matrix4 &rhs) {
    return rhs * a;
}

INLINE Matrix4 Matrix4::operator* (const Matrix4 &rhs) const {
    Matrix4 lhs = Transpose();

    return Matrix4(lhs[0].Dot(rhs[0]), lhs[1].Dot(rhs[0]), lhs[2].Dot(rhs[0]), lhs[3].Dot(rhs[0]),
                   lhs[0].Dot(rhs[1]), lhs[1].Dot(rhs[1]), lhs[2].Dot(rhs[1]), lhs[3].Dot(rhs[1]),
                   lhs[0].Dot(rhs[2]), lhs[1].Dot(rhs[2]), lhs[2].Dot(rhs[2]), lhs[3].Dot(rhs[2]),
                   lhs[0].Dot(rhs[3]), lhs[1].Dot(rhs[3]), lhs[2].Dot(rhs[3]), lhs[3].Dot(rhs[3]));
}

INLINE Vec4f Matrix4::operator* (const Vec4f &rhs) const {
    return Vec4f(mat[0].x * rhs.x + mat[1].x * rhs.y + mat[2].x * rhs.z + mat[3].x * rhs.w,
                   mat[0].y * rhs.x + mat[1].y * rhs.y + mat[2].y * rhs.z + mat[3].y * rhs.w,
                   mat[0].z * rhs.x + mat[1].z * rhs.y + mat[2].z * rhs.z + mat[3].z * rhs.w,
                   mat[0].w * rhs.x + mat[1].w * rhs.y + mat[2].w * rhs.z + mat[3].w * rhs.w);
}

INLINE Vec4f operator* (const Vec4f &lhs, const Matrix4 &rhs) {
    return rhs * lhs;
}

INLINE Matrix4 Matrix4::operator+ (const Matrix4 &rhs) const {
    return Matrix4(mat[0] + rhs[0], mat[1] + rhs[1], mat[2] + rhs[2], mat[3] + rhs[3]);
}

INLINE Matrix4 Matrix4::operator- (const Matrix4 &rhs) const {
    return Matrix4(mat[0] - rhs[0], mat[1] - rhs[1], mat[2] - rhs[2], mat[3] - rhs[3]);
}

INLINE Matrix4 &Matrix4::operator*= (const float a) {
    mat[0] *= a;
    mat[1] *= a;
    mat[2] *= a;
    mat[3] *= a;

    return *this;
}

INLINE Matrix4 &Matrix4::operator*= (const Matrix4 &rhs) {
    Matrix4 lhs = Transpose();

    Set(lhs[0].Dot(rhs[0]), lhs[1].Dot(rhs[0]), lhs[2].Dot(rhs[0]), lhs[3].Dot(rhs[0]),
        lhs[0].Dot(rhs[1]), lhs[1].Dot(rhs[1]), lhs[2].Dot(rhs[1]), lhs[3].Dot(rhs[1]),
        lhs[0].Dot(rhs[2]), lhs[1].Dot(rhs[2]), lhs[2].Dot(rhs[2]), lhs[3].Dot(rhs[2]),
        lhs[0].Dot(rhs[3]), lhs[1].Dot(rhs[3]), lhs[2].Dot(rhs[3]), lhs[3].Dot(rhs[3]));

    return *this;
}

INLINE Matrix4 &Matrix4::operator+= (const Matrix4 &rhs) {
    mat[0] += rhs[0];
    mat[1] += rhs[1];
    mat[2] += rhs[2];
    mat[3] += rhs[3];

    return *this;
}

INLINE Matrix4 &Matrix4::operator-= (const Matrix4 &rhs) {
    mat[0] -= rhs[0];
    mat[1] -= rhs[1];
    mat[2] -= rhs[2];
    mat[3] -= rhs[3];

    return *this;
}

INLINE float Matrix4::Determinant () const {
    float a, b, c, d;

    a = Matrix3(mat[1].y, mat[2].y, mat[3].y, mat[1].z, mat[2].z, mat[3].z, mat[1].w, mat[2].w, mat[3].w)
        .Determinant();
    b = Matrix3(mat[1].x, mat[2].x, mat[3].x, mat[1].z, mat[2].z, mat[3].z, mat[1].w, mat[2].w, mat[3].w)
        .Determinant();
    c = Matrix3(mat[1].x, mat[2].x, mat[3].x, mat[1].y, mat[2].y, mat[3].y, mat[1].w, mat[2].w, mat[3].w)
        .Determinant();
    d = Matrix3(mat[1].x, mat[2].x, mat[3].x, mat[1].y, mat[2].y, mat[3].y, mat[1].z, mat[2].z, mat[3].z)
        .Determinant();

    return mat[0].x * a - mat[0].y * b + mat[0].z * c - mat[0].w * d;
}

INLINE bool Matrix4::HasInverse () const {
    return 0 != Determinant();
}

INLINE Matrix4 Matrix4::Transpose () const {
    return Matrix4(mat[0].x, mat[1].x, mat[2].x, mat[3].x,
                   mat[0].y, mat[1].y, mat[2].y, mat[3].y,
                   mat[0].z, mat[1].z, mat[2].z, mat[3].z,
                   mat[0].w, mat[1].w, mat[2].w, mat[3].w);
}

INLINE Matrix4 &Matrix4::TransposeSelf () {

    std::swap(mat[0].y, mat[1].x);
    std::swap(mat[0].z, mat[2].x);
    std::swap(mat[0].w, mat[3].x);
    std::swap(mat[1].z, mat[2].y);
    std::swap(mat[1].w, mat[3].y);
    std::swap(mat[2].w, mat[3].z);

    return *this;
}

//=======================
// Matrix4 Comparisons
//=======================

INLINE bool Matrix4::Compare (const Matrix4 &other) const {
    return mat[0].Compare(other.mat[0]) && mat[1].Compare(other.mat[1]) && mat[2].Compare(other.mat[2]) &&
           mat[3].Compare(other.mat[3]);
}

INLINE bool Matrix4::Compare (const Matrix4 &other, const float threshold) const {
    return mat[0].Compare(other.mat[0], threshold) &&
        mat[1].Compare(other.mat[1], threshold) &&
        mat[2].Compare(other.mat[2], threshold) &&
        mat[3].Compare(other.mat[3], threshold);
}

INLINE bool Matrix4::operator== (const Matrix4 &other) const {
    return Compare(other);
}

INLINE bool Matrix4::operator!= (const Matrix4 &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_MATRIX4_H_ */
