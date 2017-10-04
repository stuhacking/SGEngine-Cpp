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
#ifndef __SGE_MATRIX4_H
#define __SGE_MATRIX4_H

#include <utility> // std::swap
#include <cstring> // std::memcpy

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
class Mat4f {
public:
    static const Mat4f ZERO;
    static const Mat4f ONE;
    static const Mat4f IDENTITY;

public:
    /** Default Constructor */
    Mat4f () = default;

    /** Fill Constructor */
    explicit Mat4f (const float f);

    /** Value Constructor */
    explicit Mat4f (const float aa, const float ab, const float ac, const float ad,
                     const float ba, const float bb, const float bc, const float bd,
                     const float ca, const float cb, const float cc, const float cd,
                     const float da, const float db, const float dc, const float dd);

    /** Vec4f Column Constructor */
    explicit Mat4f (const Vec4f &col1, const Vec4f &col2,
                     const Vec4f &col3, const Vec4f &col4);

    /** 1D Array Constructor */
    explicit Mat4f (const float data[16]);

    /** 2D Array Constructor */
    explicit Mat4f (const float data[4][4]);

    /**
     * Set the values of this Mat4f using float values.
     * Destructive.
     */
    void Set (const float aa, const float ab, const float ac, const float ad,
              const float ba, const float bb, const float bc, const float bd,
              const float ca, const float cb, const float cc, const float cd,
              const float da, const float db, const float dc, const float dd);

    /**
     * Set the columns of this Mat4f using Vec4fs.
     * Destructive.
     */
    void Set (const Vec4f &col1, const Vec4f &col2, const Vec4f &col3, const Vec4f &col4);

    /**
     * Set the values of this Mat4f using a 1D float array.
     * Destructive.
     */
    void Set (const float data[16]);

    /**
     * Set the values of this Mat4f using a 2D float array.
     * Destructive.
     */
    void Set (const float data[4][4]);

    /**
     * Set all values of this Mat4f to zero.
     * Destructive.
     */
    void Zero ();

    /**
     * Test if this Mat4f is the identity Matrix.
     */
    bool IsIdentity () const;

    const Vec4f &operator[] (const std::size_t index) const;

    Vec4f &operator[] (const std::size_t index);

    float Determinant () const;

    bool HasInverse () const;

    Mat4f Inverse () const;

    bool InverseSelf ();

    Mat4f Transpose () const;

    Mat4f &TransposeSelf ();

    /** Comarisons. */
    bool Compare (const Mat4f &other) const;

    bool Compare (const Mat4f &other, const float threshold) const;

    bool operator== (const Mat4f &other) const;

    bool operator!= (const Mat4f &other) const;

public:
    Vec4f mat[4];
};

// --------------------------------------------------------------------------

inline Mat4f::Mat4f (const float f) {
    mat[0].x = f; mat[0].y = f; mat[0].z = f; mat[0].w = f;
    mat[1].x = f; mat[1].y = f; mat[1].z = f; mat[1].w = f;
    mat[2].x = f; mat[2].y = f; mat[2].z = f; mat[2].w = f;
    mat[3].x = f; mat[3].y = f; mat[3].z = f; mat[3].w = f;
}

inline Mat4f::Mat4f (const float aa, const float ab, const float ac, const float ad,
                          const float ba, const float bb, const float bc, const float bd,
                          const float ca, const float cb, const float cc, const float cd,
                          const float da, const float db, const float dc, const float dd) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac; mat[0].w = ad;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc; mat[1].w = bd;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc; mat[2].w = cd;
    mat[3].x = da; mat[3].y = db; mat[3].z = dc; mat[3].w = dd;
}

inline Mat4f::Mat4f (const Vec4f &col1, const Vec4f &col2,
                          const Vec4f &col3, const Vec4f &col4) {
    mat[0].x = col1.x; mat[0].y = col1.y; mat[0].z = col1.z; mat[0].w = col1.w;
    mat[1].x = col2.x; mat[1].y = col2.y; mat[1].z = col2.z; mat[1].w = col2.w;
    mat[2].x = col3.x; mat[2].y = col3.y; mat[2].z = col3.z; mat[2].w = col3.w;
    mat[3].x = col4.x; mat[3].y = col4.y; mat[3].z = col4.z; mat[3].w = col4.w;
}

inline Mat4f::Mat4f (const float data[16]) {
    std::memcpy(mat, data, 16 * sizeof(float));
}

inline Mat4f::Mat4f (const float data[4][4]) {
    std::memcpy(mat, data, 4 * 4 * sizeof(float));
}

inline void Mat4f::Set (const float aa, const float ab, const float ac, const float ad,
                            const float ba, const float bb, const float bc, const float bd,
                            const float ca, const float cb, const float cc, const float cd,
                            const float da, const float db, const float dc, const float dd) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac; mat[0].w = ad;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc; mat[1].w = bd;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc; mat[2].w = cd;
    mat[3].x = da; mat[3].y = db; mat[3].z = dc; mat[3].w = dd;
}

inline void Mat4f::Set (const Vec4f &col1, const Vec4f &col2,
                            const Vec4f &col3, const Vec4f &col4) {
    mat[0].x = col1.x; mat[0].y = col1.y; mat[0].z = col1.z; mat[0].w = col1.w;
    mat[1].x = col2.x; mat[1].y = col2.y; mat[1].z = col2.z; mat[1].w = col2.w;
    mat[2].x = col3.x; mat[2].y = col3.y; mat[2].z = col3.z; mat[2].w = col3.w;
    mat[3].x = col4.x; mat[3].y = col4.y; mat[3].z = col4.z; mat[3].w = col4.w;
}

inline void Mat4f::Set (const float data[16]) {
    std::memcpy(mat, data, 16 * sizeof(float));
}

inline void Mat4f::Set (const float data[4][4]) {
    std::memcpy(mat, data, 4 * 4 * sizeof(float));
}

inline void Mat4f::Zero () {
    mat[0].Zero();
    mat[1].Zero();
    mat[2].Zero();
    mat[3].Zero();
}

inline bool Mat4f::IsIdentity () const {
    return Compare(Mat4f::IDENTITY);
}

inline const Vec4f &Mat4f::operator[] (const std::size_t index) const {
    return mat[index];
}

inline Vec4f &Mat4f::operator[] (const std::size_t index) {
    return mat[index];
}

//=======================
// Mat4f Operations
//=======================

inline Mat4f operator* (const Mat4f &m, const float a) {
    return Mat4f(m[0] * a, m[1] * a, m[2] * a, m[3] * a);
}

inline Mat4f operator* (const float a, const Mat4f &rhs) {
    return rhs * a;
}

inline Mat4f operator* (const Mat4f &a, const Mat4f &b) {
    Mat4f tmp = a.Transpose();

    return Mat4f(tmp[0].Dot(b[0]), tmp[1].Dot(b[0]), tmp[2].Dot(b[0]), tmp[3].Dot(b[0]),
                 tmp[0].Dot(b[1]), tmp[1].Dot(b[1]), tmp[2].Dot(b[1]), tmp[3].Dot(b[1]),
                 tmp[0].Dot(b[2]), tmp[1].Dot(b[2]), tmp[2].Dot(b[2]), tmp[3].Dot(b[2]),
                 tmp[0].Dot(b[3]), tmp[1].Dot(b[3]), tmp[2].Dot(b[3]), tmp[3].Dot(b[3]));
}

inline Vec4f operator* (const Mat4f &m, const Vec4f &v) {
    return Vec4f(m[0].x * v.x + m[1].x * v.y + m[2].x * v.z + m[3].x * v.w,
                 m[0].y * v.x + m[1].y * v.y + m[2].y * v.z + m[3].y * v.w,
                 m[0].z * v.x + m[1].z * v.y + m[2].z * v.z + m[3].z * v.w,
                 m[0].w * v.x + m[1].w * v.y + m[2].w * v.z + m[3].w * v.w);
}

inline Vec4f operator* (const Vec4f &lhs, const Mat4f &rhs) {
    return rhs * lhs;
}

inline Mat4f operator+ (const Mat4f &a, const Mat4f &b) {
    return Mat4f(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
}

inline Mat4f operator- (const Mat4f &a, const Mat4f &b) {
    return Mat4f(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]);
}

inline Mat4f& operator*= (Mat4f &m, const float a) {
    m[0] *= a;
    m[1] *= a;
    m[2] *= a;
    m[3] *= a;

    return m;
}

inline Mat4f& operator*= (Mat4f &a, const Mat4f &b) {
    Mat4f tmp = a.Transpose();

    a.Set(tmp[0].Dot(b[0]), tmp[1].Dot(b[0]), tmp[2].Dot(b[0]), tmp[3].Dot(b[0]),
          tmp[0].Dot(b[1]), tmp[1].Dot(b[1]), tmp[2].Dot(b[1]), tmp[3].Dot(b[1]),
          tmp[0].Dot(b[2]), tmp[1].Dot(b[2]), tmp[2].Dot(b[2]), tmp[3].Dot(b[2]),
          tmp[0].Dot(b[3]), tmp[1].Dot(b[3]), tmp[2].Dot(b[3]), tmp[3].Dot(b[3]));

    return a;
}

inline Mat4f& operator+= (Mat4f &a, const Mat4f &b) {
    a[0] += b[0];
    a[1] += b[1];
    a[2] += b[2];
    a[3] += b[3];

    return a;
}

inline Mat4f& operator-= (Mat4f &a, const Mat4f &b) {
    a[0] -= b[0];
    a[1] -= b[1];
    a[2] -= b[2];
    a[3] -= b[3];

    return a;
}

inline float Mat4f::Determinant () const {
    float a, b, c, d;

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

inline bool Mat4f::HasInverse () const {
    return 0 != Determinant();
}

inline Mat4f Mat4f::Transpose () const {
    return Mat4f(mat[0].x, mat[1].x, mat[2].x, mat[3].x,
                     mat[0].y, mat[1].y, mat[2].y, mat[3].y,
                     mat[0].z, mat[1].z, mat[2].z, mat[3].z,
                     mat[0].w, mat[1].w, mat[2].w, mat[3].w);
}

inline Mat4f &Mat4f::TransposeSelf () {

    std::swap(mat[0].y, mat[1].x);
    std::swap(mat[0].z, mat[2].x);
    std::swap(mat[0].w, mat[3].x);
    std::swap(mat[1].z, mat[2].y);
    std::swap(mat[1].w, mat[3].y);
    std::swap(mat[2].w, mat[3].z);

    return *this;
}

//=======================
// Mat4f Comparisons
//=======================

inline bool Mat4f::Compare (const Mat4f &other) const {
    return mat[0].Compare(other.mat[0]) && mat[1].Compare(other.mat[1]) && mat[2].Compare(other.mat[2]) &&
           mat[3].Compare(other.mat[3]);
}

inline bool Mat4f::Compare (const Mat4f &other, const float threshold) const {
    return mat[0].Compare(other.mat[0], threshold) &&
           mat[1].Compare(other.mat[1], threshold) &&
           mat[2].Compare(other.mat[2], threshold) &&
           mat[3].Compare(other.mat[3], threshold);
}

inline bool Mat4f::operator== (const Mat4f &other) const {
    return Compare(other);
}

inline bool Mat4f::operator!= (const Mat4f &other) const {
    return !Compare(other);
}

#endif /* __SGE_MATRIX4_H */
