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
    /** Construct a default (All 0.0f) Mat2f. */
    Mat2f () : mat{Vec2f{0, 0}, Vec2f{0, 0}} { }

    /** Fill Constructor */
    explicit Mat2f (const float f)
          : mat{Vec2f{f, f}, Vec2f{f, f}} { }

    /** Construct a Mat2f with float values. */
    explicit Mat2f (const float aa, const float ab, const float ba, const float bb);

    /** Construct a Mat2f using Vec2f columns. */
    explicit Mat2f (const Vec2f &col1, const Vec2f &col2);

    /** 1D Array Constructor */
    explicit Mat2f (const float data[4]);

    /** 2D Array Constructor */
    explicit Mat2f (const float data[2][2]);

    /**
     * Read access to the matrix columns using subscript notation.
     */
    const Vec2f& operator[] (const std::size_t index) const { return mat[index]; }

    /**
     * Reference/Write access to the matrix columns using subscript notation.
     */
    Vec2f& operator[] (const std::size_t index) { return mat[index]; }

    /**
     * Write the data from the columns of this Mat2f into
     * Vec2fs.
     */
    void columns (Vec2f &col1, Vec2f &col2) const;

    /**
     * Set the values of this Mat2f using Ts.
     * Destructive.
     */
    void set (const float aa, const float ab, const float ba, const float bb);

    /**
     * Set the values of this Mat2f using Vec2f columns.
     * Destructive.
     */
    void set (const Vec2f &col1, const Vec2f &col2);

    /**
     * Set the values of this Mat2f using a 1D array.
     * Destructive.
     */
    void set (const float *data);

    /**
     * Set the values of this Mat2f using a 2D array.
     * Destructive.
     */
    void set (const float **data);

    /**
     * Set all the values of this Mat2f to 0.0f.
     * Destructive.
     */
    void zero ();

    /**
     * Return true if this Mat2f is the identity Matrix.
     * @return true if identity, false otherwise
     */
    bool isIdentity () const;

    /**
     * Get the determinant of this Mat2f
     */
    float determinant () const;

    /**
     * Determine whether this Mat2f has an inverse.
     */
    bool hasInverse () const;

    /**
     * Mirror the cells of this Matrix about the line x==y.
     */
    Mat2f transpose () const;

    /**
     * Mirror the cells of this Matrix about the line x==y in place.
     * Destructive.
     */
    Mat2f& transposeSelf ();

    /**
     * Test if this Mat2f is equivalent to another Mat2f.
     */
    bool compare (const Mat2f &other) const;

    /**
     * Test if this Mat2f is similar to another Mat2f
     * within a given tolerance.
     */
    bool compare (const Mat2f &other, const float threshold) const;


private:
    Vec2f mat[2];
};

extern const Mat2f Mat2f_Zero;
extern const Mat2f Mat2f_One;
extern const Mat2f Mat2f_Identity;

// --------------------------------------------------------------------------

inline Mat2f::Mat2f (const float aa, const float ab,
                     const float ba, const float bb) {
    mat[0].x = aa; mat[0].y = ab;
    mat[1].x = ba; mat[1].y = bb;
}

inline Mat2f::Mat2f (const Vec2f &col1, const Vec2f &col2) {
    mat[0].x = col1.x; mat[0].y = col1.y;
    mat[1].x = col2.x; mat[1].y = col2.y;
}

inline Mat2f::Mat2f (const float data[4]) {
    std::memcpy(mat, data, 4 * sizeof(float));
}

inline Mat2f::Mat2f (const float data[2][2]) {
    std::memcpy(mat, data, 2 * 2 * sizeof(float));
}

inline void Mat2f::columns (Vec2f &col1, Vec2f &col2) const {
    col1 = mat[0];
    col2 = mat[1];
}

inline void Mat2f::set (const float aa, const float ab,
                        const float ba, const float bb) {
    mat[0].x = aa; mat[0].y = ab;
    mat[1].x = ba; mat[1].y = bb;
}

inline void Mat2f::set (const Vec2f &col1, const Vec2f &col2) {
    mat[0] = col1;
    mat[1] = col2;
}

inline void Mat2f::set (const float *data) {
    std::memcpy(mat, data, 4 * sizeof(float));
}

inline void Mat2f::set (const float **data) {
    std::memcpy(mat, data, 2 * 2 * sizeof(float));
}

inline void Mat2f::zero () {
    mat[0].zero();
    mat[1].zero();
}

inline bool Mat2f::isIdentity () const {
    return compare(Mat2f_Identity);
}

//=======================
// Mat2f Operators
//=======================

inline Mat2f operator* (const Mat2f &m, const float a) {
    return Mat2f(m[0] * a, m[1] * a);
}

inline Mat2f operator* (const float a, const Mat2f &m) {
    return Mat2f(m[0] * a, m[1] * a);
}

inline Mat2f operator* (const Mat2f &a, const Mat2f &b) {
    return Mat2f(a[0].x * b[0].x + a[0].y * b[1].x,
                 a[0].x * b[0].y + a[0].y * b[1].y,

                 a[1].x * b[0].x + a[1].y * b[1].x,
                 a[1].x * b[0].y + a[1].y * b[1].y);
}

inline Mat2f operator+ (const Mat2f &a, const Mat2f &b) {
    return Mat2f(a[0] + b[0], a[1] + b[1]);
}

inline Mat2f operator- (const Mat2f &a, const Mat2f &b) {
    return Mat2f(a[0] - b[0], a[1] - b[1]);
}

inline Mat2f& operator*= (Mat2f &m, const float a) {
    m[0] *= a;
    m[1] *= a;

    return m;
}

inline Mat2f& operator*= (Mat2f &a, const Mat2f &b) {
    float tmp[4];

    tmp[0] = a[0].x * b[0].x + a[0].y * b[1].x;
    tmp[1] = a[0].x * b[0].y + a[0].y * b[1].y;
    tmp[2] = a[1].x * b[0].x + a[1].y * b[1].x;
    tmp[3] = a[1].x * b[0].y + a[1].y * b[1].y;

    a[0].x = tmp[0]; a[0].y = tmp[1];
    a[1].x = tmp[2]; a[1].y = tmp[3];

    return a;
}

inline Mat2f& operator+= (Mat2f &a, const Mat2f &b) {
    a[0] += b[0];
    a[1] += b[1];

    return a;
}

inline Mat2f& operator-= (Mat2f &a, const Mat2f &b) {
    a[0] -= b[0];
    a[1] -= b[1];

    return a;
}

// --------------------------------------------------------------------------

inline float Mat2f::determinant () const {
    return mat[0].x * mat[1].y - mat[0].y * mat[1].x;
}

inline bool Mat2f::hasInverse () const {
    return 0 != determinant();
}

inline Mat2f Mat2f::transpose () const {
    return Mat2f(mat[0].x, mat[1].x, mat[0].y, mat[1].y);
}

inline Mat2f& Mat2f::transposeSelf () {
    std::swap(mat[0].y, mat[1].x);

    return *this;
}

//=======================
// Mat2f Comparisons
//=======================

inline bool Mat2f::compare (const Mat2f &other) const {
    return mat[0] == other.mat[0] && mat[1] == other.mat[1];
}

inline bool Mat2f::compare (const Mat2f &other, const float threshold) const {
    return mat[0].compare(other.mat[0], threshold) &&
           mat[1].compare(other.mat[1], threshold);
}

inline bool operator== (const Mat2f &a, const Mat2f &b) {
    return a.compare(b);
}

inline bool operator!= (const Mat2f &a, const Mat2f &b) {
    return !a.compare(b);
}

#endif /* __SGE_MATRIX2_H */
