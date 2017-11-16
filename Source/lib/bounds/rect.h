/*---  Rectangle.h - Bounding Rectangle Header  --------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a 2D axis aligned bounding rectangle type.
 */
#ifndef __SGE_RECTANGLE_H
#define __SGE_RECTANGLE_H

#include <cmath> // fabsf

namespace sge {

/**
 * 2D Bounding Rectangle. Test for intersections and envelopment
 * between 2D shapes.
 */
class Rect {
public:
    Vec2f min;
    Vec2f max;

public:
    /** Default Constructor */
    Rect ()
        : min{math::Infinity, math::Infinity}, max{-math::Infinity, -math::Infinity} { }

    /** Point Constructor */
    explicit Rect (const Vec2f &point)
        : min(point), max(point) { }

    /**
     * Construct a Rectangle with min and max bounds as Vec2f.
     */
    explicit Rect (const Vec2f &p_min, const Vec2f &p_max)
        : min(p_min), max(p_max) { }

    /**
     * Construct a Rectangle with min and max bounds as values.
     */
    explicit Rect (const float xMin, const float yMin,
                        const float xMax, const float yMax)
        : min{xMin, yMin}, max{xMax, yMax} { }

    /**
     * Clear the contents of this Rectangle.
     */
    void reset ();

    /**
     * Expand this Rectangle to maximum size.
     */
    void maximize ();

    /**
     * Get the center of this Rectangle as a Vec2f.
     */
    Vec2f center () const;

    /**
     * Get the area of this Rectangle.
     */
    float area () const;

    /**
     * Return a new Rectangle expanded by val in each direction,
     * which shares the same center as this Rectangle.
     */
    Rect expand (const float val) const;

    /**
     * Expand the bounds of this Rectangle by val in each direction.
     * Destructive.
     */
    void expandSelf (const float val);

    /** Test if rectangle contains point. */
    friend bool contains (const Rect &rect, const Vec2f &point);

    /** Test if rectangle entirely contains other rectangle. */
    friend bool contains (const Rect &a, const Rect &b);

    /**
     * Test if this Rectangle partially (or fully) intersects
     * another Rectangle.
     */
    friend bool intersects (const Rect &a, const Rect &b);

    /**
     * Test whether two Rectangles are equivalent.
     */
    bool compare (const Rect &other) const;

    /**
     * Test whether two Rectangles are the same within a given
     * tolerance.
     */
    bool compare (const Rect &other, const float threshold) const;
};

// --------------------------------------------------------------------------

inline void Rect::reset () {
    min.x = min.y = math::Infinity;
    max.x = max.y = -math::Infinity;
}

inline void Rect::maximize () {
    min.x = min.y = -math::Infinity;
    max.x = max.y = math::Infinity;
}

inline Vec2f Rect::center () const {
    return (min + max) * 0.5f;
}

inline float Rect::area () const {
    return fabsf((max.x - min.x) * (max.y - min.y));
}

inline Rect Rect::expand (const float val) const {
    return Rect(min.x - val, min.y - val, max.x + val, max.y + val);
}

inline void Rect::expandSelf (const float val) {
    min.x -= val;
    min.y -= val;
    max.x += val;
    max.y += val;
}


inline bool Rect::compare (const Rect &other) const {
    return min == other.min && max == other.max;
}

//======================
// rectangle Comparison
//======================

inline bool Rect::compare (const Rect &other, const float threshold) const {
    return min.compare(other.min, threshold) &&
           max.compare(other.max, threshold);
}

inline bool operator== (const Rect &a, const Rect &b) {
    return a.compare(b);
}

inline bool operator!= (const Rect &a, const Rect &b) {
    return !a.compare(b);
}

} /* namespace sge */

#endif /* __SGE_RECTANGLE_H */
