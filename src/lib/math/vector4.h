/*---  Vector4.h - 4D Vector Header  -------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a low level Vec4 type.
 */
#ifndef __SGE_VECTOR4_H
#define __SGE_VECTOR4_H

/**
 * 4D Vector. Implement math operations for 4D geometry vectors.
 */
class Vec4f {
public:
    float x = 0.0f; /**< x coordinate. */
    float y = 0.0f; /**< y coordinate. */
    float z = 0.0f; /**< z coordinate. */
    float w = 0.0f; /**< w coordinate. */

public:
    /** Default Constructor. */
    Vec4f () = default;

    /** Fill Constructor. */
    explicit Vec4f (const float f) : x(f), y(f), z(f), w(f) { }

    /** Construct a Vec4f using x, y, z, w coordinates. */
    explicit Vec4f (const float xx, const float yy, const float zz, const float ww)
        : x(xx), y(yy), z(zz), w(ww) { }

    /** Construct a Vec4f using the x,y,z components of a Vec3f. */
    Vec4f (const Vec3f &vec, const float ww) : x(vec.x), y(vec.y), z(vec.z), w(ww) { }

    /** Value access using an index. */
    float operator[] (const std::size_t index) const { return (&x)[index]; }

    /** Reference access using an index. */
    float &operator[] (const std::size_t index) { return (&x)[index]; }

    /**
     * Set the values of x, y, z, and w to 0.0f.
     * Destructive.
     */
    void zero () { x = y = z = w = 0; }

    /**
     * Set the values of x, y, z, and w.
     * Destructive.
     *
     * @param xx The X component
     * @param yy The Y component
     * @param zz The Z component
     * @param ww The W component
     */
    void set (const float xx, const float yy, const float zz, const float ww);

    /**
     * Get the squared magnitude of this Vec4f.
     * @return The Vector's Length squared
     */
    float magSq () const;

    /**
     * Get the magnitude of this Vec4f.
     * @return The Vector's magnitude
     */
    float mag () const;

    /**
     * Set the magnitude of a Vec4f, maintaining direction. If the
     * magnitude is currently 0.0f then we don't attempt to guess. Returns
     * a new Vec4f.
     *
     * @param pMag The desired new magnitude
     * @return New Vec4f with adjusted magnitude
     */
    Vec4f setMag (const float pMag) const;

    /**
     * Set the magnitude of this Vec4f, maintaining direction. If the
     * magnitude is currently 0.0f then we don't attempt to guess.
     * Destructive.
     *
     * @param pMag The desired new magnitude
     */
    void setMagSelf (const float pMag);

    /**
     * Set the magnitude of a Vec4f to 1.0f, maintaining direction. If
     * the current magnitude is 0.0f then we don't attempt to guess. Returns
     * a new Vec4f.
     * @param vec Original Vec4f
     * @return New normalized Vec4f
     */
    Vec4f normalize () const;

    /**
     * Set the magnitude of this Vec4f to 1.0f, maintaining direction. If
     * the current magnitude is 0.0f then we don't attempt to guess.
     * Destructive.
     */
    void normalizeSelf ();

    /**
     * Return a new Vec4f which has been truncated if its magnitude
     * exceeds the limit.
     * @param max Maximum magnitude of Vec4f
     * @return New (possibly truncated) Vec4f
     */
    Vec4f clampMag (const float max) const;

    /**
     * Return a new Vec4f which has been extended or truncated
     * if its magnitude is outside the limits.
     * @param min Minimum magnitude of Vec4f
     * @param max Maximum magnitude of Vec4f
     * @return New (possibly truncated) Vec4f
     */
    Vec4f clampMag (const float min, const float max) const;

    /**
     * Truncate this Vec4f if its magnitude exceeds the limit.
     * Destructive.
     * @param max Maximum magnitude of Vec4f
     */
    void clampMagSelf (const float max);

    /**
     * Truncate or extend this Vec4f if its magnitude is outside
     * the limits.
     * Destructive.
     * @param min Minimum magnitude of Vec4f
     * @param max Maximum magnitude of Vec4f
     */
    void clampMagSelf (const float min, const float max);

    /**
     * Clamp Vec4f within minimum and maximum bounds, given by other
     * Vec4f values.
     *
     * @param min Vec4f minimum bound
     * @param max Vec4f maximum bound
     */
    Vec4f clamp (const Vec4f &min, const Vec4f &max) const;

    /**
     * Clamp Vec4f within minimum and maximum bounds, given by other
     * Vec4f values.
     * Destructive.
     * @param min Vec4f minimum bound
     * @param max Vec4f maximum bound
     */
    void clampSelf (const Vec4f &min, const Vec4f &max);

    float Dot (const Vec4f &rhs) const;

    /** Swizzling */
    Vec3f xyz () const { return Vec3f(x, y, z); }
    Vec2f  xy () const { return Vec2f(x, y); }
    Vec2f  xz () const { return Vec2f(x, z); }
    Vec2f  yz () const { return Vec2f(y, z); }

    /**
     * Compare this Vec4f against another Vec4f exactly.
     *
     * @return true if this Vec4f exactly equals the other, false otherwise
     */
    bool compare (const Vec4f &other) const;

    /**
     * Compare this Vec4f against another Vec4f within a given tolerance.
     *
     * @param threshold Tolerance within which Vec4f are considered equal
     * @return true if this Vec4f equals the other within given
     *         tolerance, false otherwise
     */
    bool compare (const Vec4f &other, const float threshold) const;
};

extern const Vec4f Vec4f_Zero;
extern const Vec4f Vec4f_One;
extern const Vec4f Vec4f_X;
extern const Vec4f Vec4f_Y;
extern const Vec4f Vec4f_Z;
extern const Vec4f Vec4f_W;

// --------------------------------------------------------------------------

inline void Vec4f::set (const float xx, const float yy, const float zz,
                        const float ww) {
    x = xx;
    y = yy;
    z = zz;
    w = ww;
}

//==========================
// Vec4f Operators
//==========================

/** Negate. */
inline Vec4f operator- (const Vec4f &v) {
    return Vec4f(-v.x, -v.y, -v.z, -v.w);
}

/** Multiply by scalar. */
inline Vec4f operator* (const Vec4f &v, const float a) {
    return Vec4f(a * v.x, a * v.y, a * v.z, a * v.w);
}

/** Multiply by scalar. */
inline Vec4f operator* (const float a, const Vec4f &v) {
    return Vec4f(a * v.x, a * v.y, a * v.z, a * v.w);
}

/** Piecewise multiplication. */
inline Vec4f operator* (const Vec4f &a, const Vec4f &b) {
    return Vec4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

/** Addition. */
inline Vec4f operator+ (const Vec4f &a, const Vec4f &b) {
    return Vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

/** Subtraction. */
inline Vec4f operator- (const Vec4f &a, const Vec4f &b) {
    return Vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

/** Division. */
inline Vec4f operator/ (const Vec4f &v, const float a) {
    float inva = 1.0f / a;
    return Vec4f(v.x * inva, v.y * inva, v.z * inva, v.w * inva);
}

/** Multiply by scalar in place. */
inline Vec4f& operator*= (Vec4f &v, const float a) {
    v.x *= a;
    v.y *= a;
    v.z *= a;
    v.w *= a;

    return v;
}

/** Piecewise multiplication in place. */
inline Vec4f& operator*= (Vec4f &a, const Vec4f &b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;

    return a;
}

/** Addition in place. */
inline Vec4f& operator+= (Vec4f &a, const Vec4f &b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;

    return a;
}

/** Subtraction in place. */
inline Vec4f& operator-= (Vec4f &a, const Vec4f &b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;

    return a;
}

/** Division in place. */
inline Vec4f& operator/= (Vec4f &v, const float a) {
    float inva = 1.0f / a;
    v.x *= inva;
    v.y *= inva;
    v.z *= inva;
    v.w *= inva;

    return v;
}

/** Piecewise division in place. */
inline Vec4f& operator/= (Vec4f &a, const Vec4f &b) {
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;

    return a;
}

//==========================
// Vec4f Length Operators
//==========================

inline float Vec4f::magSq () const {
    return x * x + y * y + z * z + w * w;
}

inline float Vec4f::mag () const {
    return sqrt(x * x + y * y + z * z + w * w);
}

inline Vec4f Vec4f::setMag (const float pMag) const {
    float currMag = mag();
    if (currMag == 0.0f) {
        return Vec4f(*this);
    } else {
        return *this * (pMag / currMag);
    }
}

inline void Vec4f::setMagSelf (const float pMag) {
    float currMag = mag();
    if (currMag != 0.0f) {
        *this *= (pMag / currMag);
    }

}

inline Vec4f Vec4f::normalize () const {
    float currMag = mag();
    if (currMag == 0.0f) {
        return Vec4f(*this);
    } else {
        return *this / currMag;
    }
}

inline void Vec4f::normalizeSelf () {
    float currMag = mag();
    if (currMag != 0.0f) {
        *this /= currMag;
    }
}

inline Vec4f Vec4f::clampMag (const float max) const {
    if (magSq() > (max * max)) {
        return setMag(max);
    }

    return Vec4f(*this);
}

inline Vec4f Vec4f::clampMag (const float min, const float max) const {
    float ls = magSq();

    if (ls < (min * min)) {
        return setMag(min);
    }

    if (ls > (max * max)) {
        return setMag(max);
    }

    return Vec4f(*this);
}

inline void Vec4f::clampMagSelf (const float max) {
    if (magSq() > (max * max)) {
        setMagSelf(max);
    }
}

inline void Vec4f::clampMagSelf (const float min, const float max) {
    float ls = magSq();

    if (ls < (min * min)) {
        setMagSelf(min);
    }

    if (ls > (max * max)) {
        setMagSelf(max);
    }
}

inline Vec4f Vec4f::clamp (const Vec4f &min, const Vec4f &max) const {
    return Vec4f(math::clamp(x, min.x, max.x),
                 math::clamp(y, min.y, max.y),
                 math::clamp(z, min.z, max.z),
                 math::clamp(w, min.w, max.w));
}

inline void Vec4f::clampSelf (const Vec4f &min, const Vec4f &max) {
    x = math::clamp(x, min.x, max.x);
    y = math::clamp(y, min.y, max.y);
    z = math::clamp(z, min.z, max.z);
    w = math::clamp(w, min.w, max.w);
}

// Dot product.
inline float Vec4f::Dot (const Vec4f &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

//==========================
// Vec4f Comparison
//==========================

// This comparison may be inaccurate, prefer Compare(val, threshold)
// where possible.
inline bool Vec4f::compare (const Vec4f &other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

inline bool Vec4f::compare (const Vec4f &other, const float threshold) const {
    return fabsf(x - other.x) <= threshold &&
           fabsf(y - other.y) <= threshold &&
           fabsf(z - other.z) <= threshold &&
           fabsf(w - other.w) <= threshold;
}

inline bool operator== (const Vec4f &a, const Vec4f &b) {
    return a.compare(b);
}

inline bool operator!= (const Vec4f &a, const Vec4f &b) {
    return !a.compare(b);
}

#endif /* __SGE_VECTOR4_H */
