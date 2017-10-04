/*---  Vector2.h - 2D Vector Header  -------------------------------*- C++ -*---
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
    static const Vec2i ZERO;
    static const Vec2i ONE;
    static const Vec2i X;
    static const Vec2i Y;

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
     * Set the values of x and y.
     * Destructive.
     *
     * @param xx The X component
     * @param yy The Y component
     */
    void Set (const int xx, const int yy);

    /**
     * Set the values of x and y to 0.0f.
     * Destructive.
     */
    void Zero ();

    /**
     * Compare this Vec2i against another Vec2i.
     *
     * @return true if this Vec2i equals the other within given
     *         tolerance, false otherwise
     */
    bool Compare (const Vec2i &other) const;

    /**
     * Compare this Vec2i against another Vec2i exactly.
     *
     * @return true if this Vec2i exactly equals the other, false otherwise
     */
    bool operator== (const Vec2i &other) const;

    /**
     * Compare this Vec2i against another Vec2i exactly.
     *
     * @return true if this Vec2i does not equal the other, false otherwise
     */
    bool operator!= (const Vec2i &other) const;

    bool operator<  (const Vec2i &rhs) const;
};

// --------------------------------------------------------------------------

inline int Vec2i::operator[] (const std::size_t index) const {
    return (&x)[index];
}

inline int &Vec2i::operator[] (const std::size_t index) {
    return (&x)[index];
}

inline void Vec2i::Set (const int xx, const int yy) {
    x = xx;
    y = yy;
}

inline void Vec2i::Zero () {
    x = y = 0;
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

inline bool Vec2i::Compare (const Vec2i &other) const {
    return x == other.x && y == other.y;
}

inline bool Vec2i::operator== (const Vec2i &other) const {
    return Compare(other);
}

inline bool Vec2i::operator!= (const Vec2i &other) const {
    return !Compare(other);
}

inline bool Vec2i::operator< (const Vec2i &rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
}

#endif /* __SGE_VECTOR2I_H */
