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
#ifndef __SGE_MATRIX3_H
#define __SGE_MATRIX3_H

#include <utility> // std::swap
#include <cstring> // std::memcpy

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
    /** Default Constructor */
    Mat3f () : mat{Vec3f{0, 0, 0}, Vec3f{0, 0, 0}, Vec3f{0, 0, 0}} { }

    /** Fill Constructor */
    explicit Mat3f (const float f)
          : mat{Vec3f{f, f, f}, Vec3f{f, f, f}, Vec3f{f, f, f}} { }

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
     * Set all values of this Mat3f to zero.
     * Destructive.
     */
    void zero ();

    /**
     * Set the values of this Mat3f using Ts.
     * Destructive.
     */
    void set (const float aa, const float ab, const float ac,
              const float ba, const float bb, const float bc,
              const float ca, const float cb, const float cc);

    /**
     * Set the values of this Mat3f using Vec3f columns.
     * Destructive.
     */
    void set (const Vec3f &col1, const Vec3f &col2, const Vec3f &col3);

    /**
     * Set the values of this Mat3f using a 1D array.
     * Destructive.
     */
    void set (const float *data);

    /**
     * Set the values of this Mat3f using a 2D array.
     * Destructive.
     */
    void set (const float **data);

    bool isIdentity () const;

    const Vec3f& operator[] (const std::size_t index) const { return mat[index]; }

    Vec3f& operator[] (const std::size_t index) { return mat[index]; }

    /**
     * Get the determinant of this Mat3f.
     */
    float determinant () const;

    /**
     * Determine if this Mat3f has an inverse.
     */
    bool hasInverse () const;

    /**
     * Get the inverse of this Mat3f.
     */
    Mat3f inverse () const;

    /**
     * Set this Mat3f to be its inverse.
     * Destructive.
     * @return false if Mat3f has no inverse, true if success.
     */
    bool inverseSelf ();

    Mat3f transpose () const;

    Mat3f& transposeSelf ();

    /**
     * Test if this Mat3f is equivalent to another Mat3f.
     */
    bool compare (const Mat3f &other) const;

    /**
     * Test if this Mat3f is similar to another Mat3f
     * within a given tolerance.
     */
    bool compare (const Mat3f &other, const float threshold) const;

private:
    Vec3f mat[3];
};

extern const Mat3f Mat3f_Zero;
extern const Mat3f Mat3f_One;
extern const Mat3f Mat3f_Identity;

// --------------------------------------------------------------------------

inline Mat3f::Mat3f (const float aa, const float ab, const float ac,
                     const float ba, const float bb, const float bc,
                     const float ca, const float cb, const float cc) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc;
}

inline Mat3f::Mat3f (const Vec3f &col1, const Vec3f &col2, const Vec3f &col3) {
    mat[0].x = col1.x; mat[0].y = col1.y; mat[0].z = col1.z;
    mat[1].x = col2.x; mat[1].y = col2.y; mat[1].z = col2.z;
    mat[2].x = col3.x; mat[2].y = col3.y; mat[2].z = col3.z;
}

inline Mat3f::Mat3f (const float data[9]) {
    std::memcpy(mat, data, 9 * sizeof(float));
}

inline Mat3f::Mat3f (const float data[3][3]) {
    std::memcpy(mat, data, 3 * 3 * sizeof(float));
}

inline void Mat3f::zero () {
    mat[0].zero();
    mat[1].zero();
    mat[2].zero();
}

inline void Mat3f::set (const float aa, const float ab, const float ac,
                        const float ba, const float bb, const float bc,
                        const float ca, const float cb, const float cc) {
    mat[0].x = aa; mat[0].y = ab; mat[0].z = ac;
    mat[1].x = ba; mat[1].y = bb; mat[1].z = bc;
    mat[2].x = ca; mat[2].y = cb; mat[2].z = cc;
}

inline void Mat3f::set (const Vec3f &col1, const Vec3f &col2, const Vec3f &col3) {
    mat[0] = col1;
    mat[1] = col2;
    mat[2] = col3;
}

inline void Mat3f::set (const float *data) {
    std::memcpy(mat, data, 9 * sizeof(float));
}

inline void Mat3f::set (const float **data) {
    std::memcpy(mat, data, 3 * 3 * sizeof(float));
}

inline bool Mat3f::isIdentity () const {
    return compare(Mat3f_Identity);
}

//=======================
// Mat3f Operations
//=======================

inline Mat3f operator* (const Mat3f &m, const float a) {
    return Mat3f(m[0] * a, m[1] * a, m[2] * a);
}

inline Mat3f operator* (const float a, const Mat3f &rhs) {
    return rhs * a;
}

inline Mat3f operator* (const Mat3f &a, const Mat3f &b) {
    Mat3f tmp = a.transpose();

    return Mat3f(tmp[0].dot(b[0]), tmp[1].dot(b[0]), tmp[2].dot(b[0]),
                 tmp[0].dot(b[1]), tmp[1].dot(b[1]), tmp[2].dot(b[1]),
                 tmp[0].dot(b[2]), tmp[1].dot(b[2]), tmp[2].dot(b[2]));
}

inline Vec3f operator* (const Mat3f &m, const Vec3f &v) {
    return Vec3f(m[0].x * v.x + m[1].x * v.y + m[2].x * v.z,
                 m[0].y * v.x + m[1].y * v.y + m[2].y * v.z,
                 m[0].z * v.x + m[1].z * v.y + m[2].z * v.z);
}

inline Vec3f operator* (const Vec3f &lhs, const Mat3f &rhs) {
    return rhs * lhs;
}

inline Mat3f operator+ (const Mat3f &a, const Mat3f &b) {
    return Mat3f(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

inline Mat3f operator- (const Mat3f &a, const Mat3f &b) {
    return Mat3f(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

inline Mat3f& operator*= (Mat3f &m, const float a) {
    m[0] *= a;
    m[1] *= a;
    m[2] *= a;

    return m;
}

inline Mat3f& operator*= (Mat3f &a, const Mat3f &b) {
    Mat3f tmp = a.transpose();

    a.set(tmp[0].dot(b[0]), tmp[1].dot(b[0]), tmp[2].dot(b[0]),
          tmp[0].dot(b[1]), tmp[1].dot(b[1]), tmp[2].dot(b[1]),
          tmp[0].dot(b[2]), tmp[1].dot(b[2]), tmp[2].dot(b[2]));

    return a;
}

inline Mat3f& operator+= (Mat3f &a, const Mat3f &b) {
    a[0] += b[0];
    a[1] += b[1];
    a[2] += b[2];

    return a;
}

inline Mat3f& operator-= (Mat3f &a, const Mat3f &b) {
    a[0] -= b[0];
    a[1] -= b[1];
    a[2] -= b[2];

    return a;
}

inline float Mat3f::determinant () const {
    // Laplace Expansion Determinant
    //    0 1 2
    // x |0 3 6|
    // y |1 4 7|
    // z |2 5 8|
    return mat[0].x * (mat[1].y * mat[2].z - mat[2].y * mat[1].z) -
           mat[0].y * (mat[1].x * mat[2].z - mat[2].x * mat[1].z) +
           mat[0].z * (mat[1].x * mat[2].y - mat[2].x * mat[1].y);
}

inline bool Mat3f::hasInverse () const {
    return 0 != determinant();
}

inline Mat3f Mat3f::transpose () const {
    return Mat3f(mat[0].x, mat[1].x, mat[2].x,
                 mat[0].y, mat[1].y, mat[2].y,
                 mat[0].z, mat[1].z, mat[2].z);
}

inline Mat3f &Mat3f::transposeSelf () {
    std::swap(mat[0].y, mat[1].x);
    std::swap(mat[0].z, mat[2].x);
    std::swap(mat[1].z, mat[2].y);

    return *this;
}

//=======================
// Mat3f Comparisons
//=======================

inline bool Mat3f::compare (const Mat3f &other) const {
    return mat[0] == other.mat[0] &&
           mat[1] == other.mat[1] &&
           mat[2] == other.mat[2];
}

inline bool Mat3f::compare (const Mat3f &other, const float threshold) const {
    return mat[0].compare(other.mat[0], threshold) &&
           mat[1].compare(other.mat[1], threshold) &&
           mat[2].compare(other.mat[2], threshold);
}

inline bool operator== (const Mat3f &a, const Mat3f &b) {
    return a.compare(b);
}

inline bool operator!= (const Mat3f &a, const Mat3f &b) {
    return !a.compare(b);
}

#endif /* __SGE_MATRIX3_H */
