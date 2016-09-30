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
        : center(Vec2f::ZERO), radius(-FMath::INFTY) { }

    /** Construct a circle centered at p_center, with radius p_radius. */
    explicit Circle(const Vec2f &p_center, const float p_radius = -FMath::INFTY)
        : center(p_center), radius(p_radius) { }

    /**
     * Clear all points from this Circle.
     * Destructive.
     */
    void Clear();

    /**
     * Expand this circle to cover an infinite area.
     * Destructive.
     */
    void Maximize();

    /**
     * Get the area of this circle.
     */
    float Area() const;

    /**
     * Test if this Circle contains point.
     */
    bool Contains(const Vec2f &point) const;

    /**
     * Test if this Circle fully encloses another
     * Circle.
     */
    bool Contains(const Circle &other) const;

    /**
     * Test if this Circle intersects another
     * Circle.
     */
    bool Intersects(const Circle &other) const;

    /**
     * Test if two Circles are equivalent.
     */
    bool Compare (const Circle &other) const;

    /**
     * Test if two Circles are similar within a given
     * tolerance.
     */
    bool Compare (const Circle &other, const float threshold) const;

    /**
     * Test if two Circles are equivalent.
     */
    bool operator== (const Circle &other) const;

    /**
     * Test if two Circles are not equivalent.
     */
    bool operator!= (const Circle &other) const;
};

// --------------------------------------------------------------------------

INLINE void Circle::Clear() {
    radius = -FMath::INFTY;
    center = Vec2f(0.0f, 0.0f);
}

INLINE void Circle::Maximize() {
    radius = FMath::INFTY;
    center.x = center.y = 0.0f;
}

INLINE float Circle::Area() const {
    return radius * radius * FMath::PI;
}

INLINE bool Circle::Contains(const Vec2f &point) const {
    Vec2f relPoint = point - center;
    return (radius * radius) >= relPoint.LengthSqr();
}

INLINE bool Circle::Contains(const Circle &other) const {
    Vec2f relPoint = other.center - center;
    float distance = relPoint.Length() + other.radius;
    return radius > distance;
}

INLINE bool Circle::Intersects(const Circle &other) const {
    Vec2f relPoint = other.center - center;
    float distance = relPoint.Length() - other.radius;
    return radius >= distance;
}

//===================
// Circle Comparison
//===================

INLINE bool Circle::Compare (const Circle &other) const {
    return radius == radius && center == center;
}

INLINE bool Circle::Compare (const Circle &other, const float threshold) const {
    if (fabsf(radius - other.radius) > threshold) {
        return false;
    }

    return center.Compare(other.center, threshold);
}

INLINE bool Circle::operator== (const Circle &other) const {
    return Compare(other);
}

INLINE bool Circle::operator!= (const Circle &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGE_CIRCLE_H */
