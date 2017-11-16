/*---  Circle.h - Bounding Circle Header  --------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a 2D bounding circle type.
 */
#ifndef __SGE_CIRCLE_H
#define __SGE_CIRCLE_H

#include <cmath> // fabsf

namespace sge {

/**
 * 2D Circle. Implements intersection and envelopment tests for
 * 2D shapes.
 */
class Circle {
public:
    Vec2f center;
    float radius;

public:
    /** Default Constructor. */
    Circle()
        : center(Vec2f_Zero), radius(-math::Infinity) { }

    /** Construct a circle centered at p_center, with radius p_radius. */
    explicit Circle(const Vec2f &p_center, const float p_radius = -math::Infinity)
        : center(p_center), radius(p_radius) { }

    /**
     * Clear all points from this Circle.
     * Destructive.
     */
    void reset ();

    /**
     * Expand this circle to cover an infinite area.
     * Destructive.
     */
    void maximize ();

    /**
     * Get the area of this circle.
     */
    float area () const;

    /**
     * Test if this Circle contains point.
     */
    friend bool contains (const Circle &circle, const Vec2f &point);

    /**
     * Test if this Circle fully encloses another
     * Circle.
     */
    friend bool contains (const Circle &a, const Circle &b);

    /**
     * Test if this Circle intersects another
     * Circle.
     */
    friend bool intersects (const Circle &a, const Circle &b);

    /**
     * Test if two Circles are equivalent.
     */
    bool compare (const Circle &other) const;

    /**
     * Test if two Circles are similar within a given
     * tolerance.
     */
    bool compare (const Circle &other, const float threshold) const;
};

// --------------------------------------------------------------------------

inline void Circle::reset () {
    radius = -math::Infinity;
    center = Vec2f(0.0f, 0.0f);
}

inline void Circle::maximize () {
    radius = math::Infinity;
    center.x = center.y = 0.0f;
}

inline float Circle::area () const {
    return radius * radius * math::Pi;
}

//===================
// Circle Comparison
//===================

inline bool Circle::compare (const Circle &other) const {
    return radius == other.radius && center == other.center;
}

inline bool Circle::compare (const Circle &other, const float threshold) const {

    return (fabsf(radius - other.radius) <= threshold) &&
           center.compare(other.center, threshold);
}

inline bool operator== (const Circle &a, const Circle &b) {
    return a.compare(b);
}

inline bool operator!= (const Circle &a, const Circle &b) {
    return !a.compare(b);
}

} /* namespace sge */

#endif /* __SGE_CIRCLE_H */
