/**--  Vector2.h - 2D Vector Header  -------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level 2D Vector type.
 */
#ifndef __SGE_VECTOR2I_H
#define __SGE_VECTOR2I_H

/**
 * 2D Vector. Implement math operations for 2D geometry vectors.
 */
class Vec2i {
public:
    int x = 0; /**< x coordinate. */
    int y = 0; /**< y coordinate. */

public:
    /** Default Constructor. */
    Vec2i () = default;

    /** Fill Constructor. */
    explicit Vec2i (const int f) : x(f), y(f) { }

    /** Construct a Vec2i using x, y coordinates. */
    explicit Vec2i (const int xx, const int yy) : x(xx), y(yy) { }

    /** Value access by index. */
    int operator[] (const std::size_t index) const;

    /** Reference access by index. */
    int &operator[] (const std::size_t index);

    /**
     * Set the values of x and y to 0.0f.
     * Destructive.
     */
    void zero () { x = y = 0; }

    /**
     * Set the values of x and y.
     * Destructive.
     *
     * @param xx The X component
     * @param yy The Y component
     */
    void set (const int xx, const int yy);


    /**
     * Compare this Vec2i against another Vec2i.
     *
     * @return true if this Vec2i equals the other within given
     *         tolerance, false otherwise
     */
    bool compare (const Vec2i &other) const;
};

extern const Vec2i Vec2i_Zero;
extern const Vec2i Vec2i_One;
extern const Vec2i Vec2i_X;
extern const Vec2i Vec2i_Y;

// --------------------------------------------------------------------------

inline int Vec2i::operator[] (const std::size_t index) const {
    return (&x)[index];
}

inline int &Vec2i::operator[] (const std::size_t index) {
    return (&x)[index];
}

inline void Vec2i::set (const int xx, const int yy) {
    x = xx;
    y = yy;
}

//==========================
// Vec2i Operators
//==========================

/** Negate. */
inline Vec2i operator- (const Vec2i &v) {
    return Vec2i(-v.x, -v.y);
}

/** Multiply by scalar. */
inline Vec2i operator* (const Vec2i &v, const int a) {
    return Vec2i(a * v.x, a * v.y);
}

/** Multiply by scalar. */
inline Vec2i operator* (const int a, const Vec2i &v) {
    return Vec2i(a * v.x, a * v.y);
}

/** Piecewise multiplication. */
inline Vec2i operator* (const Vec2i &a, const Vec2i &b) {
    return Vec2i(a.x * b.x, a.y * b.y);
}

/** Addition. */
inline Vec2i operator+ (const Vec2i &a, const Vec2i &b) {
    return Vec2i(a.x + b.x, a.y + b.y);
}

/** Subtraction. */
inline Vec2i operator- (const Vec2i &a, const Vec2i &b) {
    return Vec2i(a.x - b.x, a.y - b.y);
}

/** Division. */
inline Vec2i operator/ (const Vec2i &v, const int a) {
    return Vec2i(v.x / a, v.y / a);
}

/** Multiply by scalar in place. */
inline Vec2i& operator*= (Vec2i &v, const float a) {
    v.x *= a;
    v.y *= a;

    return v;
}

/** Piecewise multiplication in place. */
inline Vec2i& operator*= (Vec2i &a, const Vec2i &b) {
    a.x *= b.x;
    a.y *= b.y;

    return a;
}

/** Addition in place. */
inline Vec2i& operator+= (Vec2i &a, const Vec2i &b) {
    a.x += b.x;
    a.y += b.y;

    return a;
}

/** Subtraction in place. */
inline Vec2i& operator-= (Vec2i &a, const Vec2i &b) {
    a.x -= b.x;
    a.y -= b.y;

    return a;
}

/** Division in place. */
inline Vec2i& operator/= (Vec2i &v, const int a) {
    v.x /= a;
    v.y /= a;

    return v;
}

/** Piecewise division in place. */
inline Vec2i& operator/= (Vec2i &a, const Vec2i &b) {
    a.x /= b.x;
    a.y /= b.y;

    return a;
}

//==========================
// Vec2i Comparisons
//==========================

inline bool Vec2i::compare (const Vec2i &other) const {
    return x == other.x && y == other.y;
}

inline bool operator== (const Vec2i &a, const Vec2i &b) {
    return a.compare(b);
}

inline bool operator!= (const Vec2i &a, const Vec2i &b) {
    return !a.compare(b);
}

inline bool operator< (const Vec2i &a, const Vec2i &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

#endif /* __SGE_VECTOR2I_H */
