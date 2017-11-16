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
    /** Default Constructor */
    Mat4f ()
          : mat{Vec4f{0, 0, 0, 0}, Vec4f{0, 0, 0, 0}, Vec4f{0, 0, 0, 0}, Vec4f{0, 0, 0, 0}} { }

    /** Fill Constructor */
    explicit Mat4f (const float f)
          : mat{Vec4f{f, f, f, f}, Vec4f{f, f, f, f}, Vec4f{f, f, f, f}, Vec4f{f, f, f, f}} { }

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
     * Set all values of this Mat4f to zero.
     * Destructive.
     */
    void zero ();

    /**
     * Set the values of this Mat4f using float values.
     * Destructive.
     */
    void set (const float aa, const float ab, const float ac, const float ad,
              const float ba, const float bb, const float bc, const float bd,
              const float ca, const float cb, const float cc, const float cd,
              const float da, const float db, const float dc, const float dd);

    /**
     * Set the columns of this Mat4f using Vec4fs.
     * Destructive.
     */
    void set (const Vec4f &col1, const Vec4f &col2, const Vec4f &col3,
              const Vec4f &col4);

    /**
     * Set the values of this Mat4f using a 1D float array.
     * Destructive.
     */
    void set (const float *data);

    /**
     * Set the values of this Mat4f using a 2D float array.
     * Destructive.
     */
    void set (const float **data);

    /**
     * Test if this Mat4f is the identity Matrix.
     */
    bool isIdentity () const;

    const Vec4f &operator[] (const std::size_t index) const { return mat[index]; }

    Vec4f &operator[] (const std::size_t index) { return mat[index]; }

    float determinant () const;

    bool hasInverse () const;

    Mat4f inverse () const;

    bool inverseSelf ();

    Mat4f transpose () const;

    Mat4f& transposeSelf ();

    /** Comarisons. */
    bool compare (const Mat4f &other) const;

    bool compare (const Mat4f &other, const float threshold) const;

public:
    Vec4f mat[4];
};

extern const Mat4f Mat4f_Zero;
extern const Mat4f Mat4f_One;
extern const Mat4f Mat4f_Identity;

// --------------------------------------------------------------------------

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

inline void Mat4f::set (const float aa, const float ab, const float ac,
                        const float ad,
                        const float ba, const float bb, const float bc,
                        const float bd,
                        const float ca, const float cb, const float cc,
                        const float cd,
                        const float da, const float db, const float dc,
                        const float dd) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac; mat[0].w = ad;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc; mat[1].w = bd;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc; mat[2].w = cd;
    mat[3].x = da; mat[3].y = db; mat[3].z = dc; mat[3].w = dd;
}

inline void Mat4f::set (const Vec4f &col1, const Vec4f &col2,
                        const Vec4f &col3, const Vec4f &col4) {
    mat[0].x = col1.x; mat[0].y = col1.y; mat[0].z = col1.z; mat[0].w = col1.w;
    mat[1].x = col2.x; mat[1].y = col2.y; mat[1].z = col2.z; mat[1].w = col2.w;
    mat[2].x = col3.x; mat[2].y = col3.y; mat[2].z = col3.z; mat[2].w = col3.w;
    mat[3].x = col4.x; mat[3].y = col4.y; mat[3].z = col4.z; mat[3].w = col4.w;
}

inline void Mat4f::set (const float *data) {
    std::memcpy(mat, data, 16 * sizeof(float));
}

inline void Mat4f::set (const float **data) {
    std::memcpy(mat, data, 4 * 4 * sizeof(float));
}

inline void Mat4f::zero () {
    mat[0].zero();
    mat[1].zero();
    mat[2].zero();
    mat[3].zero();
}

inline bool Mat4f::isIdentity () const {
    return compare(Mat4f_Identity);
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
    Mat4f tmp = a.transpose();

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
    Mat4f tmp = a.transpose();

    a.set(tmp[0].Dot(b[0]), tmp[1].Dot(b[0]), tmp[2].Dot(b[0]),
          tmp[3].Dot(b[0]),
          tmp[0].Dot(b[1]), tmp[1].Dot(b[1]), tmp[2].Dot(b[1]),
          tmp[3].Dot(b[1]),
          tmp[0].Dot(b[2]), tmp[1].Dot(b[2]), tmp[2].Dot(b[2]),
          tmp[3].Dot(b[2]),
          tmp[0].Dot(b[3]), tmp[1].Dot(b[3]), tmp[2].Dot(b[3]),
          tmp[3].Dot(b[3]));

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

inline float Mat4f::determinant () const {
    float a, b, c, d;

    a = Mat3f(mat[1].y, mat[2].y, mat[3].y, mat[1].z, mat[2].z, mat[3].z,
              mat[1].w, mat[2].w, mat[3].w)
          .determinant();
    b = Mat3f(mat[1].x, mat[2].x, mat[3].x, mat[1].z, mat[2].z, mat[3].z,
              mat[1].w, mat[2].w, mat[3].w)
          .determinant();
    c = Mat3f(mat[1].x, mat[2].x, mat[3].x, mat[1].y, mat[2].y, mat[3].y,
              mat[1].w, mat[2].w, mat[3].w)
          .determinant();
    d = Mat3f(mat[1].x, mat[2].x, mat[3].x, mat[1].y, mat[2].y, mat[3].y,
              mat[1].z, mat[2].z, mat[3].z)
          .determinant();

    return mat[0].x * a - mat[0].y * b + mat[0].z * c - mat[0].w * d;
}

inline bool Mat4f::hasInverse () const {
    return 0 != determinant();
}

inline Mat4f Mat4f::transpose () const {
    return Mat4f(mat[0].x, mat[1].x, mat[2].x, mat[3].x,
                     mat[0].y, mat[1].y, mat[2].y, mat[3].y,
                     mat[0].z, mat[1].z, mat[2].z, mat[3].z,
                     mat[0].w, mat[1].w, mat[2].w, mat[3].w);
}

inline Mat4f &Mat4f::transposeSelf () {

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

inline bool Mat4f::compare (const Mat4f &other) const {
    return mat[0].compare(other.mat[0]) &&
           mat[1].compare(other.mat[1]) &&
           mat[2].compare(other.mat[2]) &&
           mat[3].compare(other.mat[3]);
}

inline bool Mat4f::compare (const Mat4f &other, const float threshold) const {
    return mat[0].compare(other.mat[0], threshold) &&
           mat[1].compare(other.mat[1], threshold) &&
           mat[2].compare(other.mat[2], threshold) &&
           mat[3].compare(other.mat[3], threshold);
}

inline bool operator== (const Mat4f &a, const Mat4f &b) {
    return a.compare(b);
}

inline bool operator!= (const Mat4f &a, const Mat4f &b) {
    return !a.compare(b);
}

#endif /* __SGE_MATRIX4_H */
