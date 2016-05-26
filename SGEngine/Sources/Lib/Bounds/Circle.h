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
#ifndef __SGENGINE_CIRCLE_H_
#define __SGENGINE_CIRCLE_H_

#include <cfloat> // fabsf

namespace sge {

/**
 * 2D Circle. Implements intersection and envelopment tests for
 * 2D shapes.
 */
class Circle {
public:
    Circle()
        : origin(Vec2f::ZERO), radius(-FMath::INFTY) { }

    Circle(const Vec2f &p_origin, const float p_radius = -FMath::INFTY)
        : origin(p_origin), radius(p_radius) { }

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
     * Get the center of this circle.
     */
    Vec2f Center() const;

    /**
     * Get the area of this circle.
     */
    float Area() const;

    bool Contains(const Vec2f &point) const;

    bool Contains(const Circle &other) const;

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

private:
    Vec2f origin;
    float radius;
};

// --------------------------------------------------------------------------

INLINE void Circle::Clear() {
    radius = -FMath::INFTY;
    origin = Vec2f(0.0f, 0.0f);
}

INLINE void Circle::Maximize() {
    radius = FMath::INFTY;
    origin.x = origin.y = 0.0f;
}

INLINE Vec2f Circle::Center() const {
    return origin;
}

INLINE float Circle::Area() const {
    return radius * radius * FMath::PI;
}

INLINE bool Circle::Contains(const Vec2f &point) const {
    Vec2f relPoint = point - origin;
    return (radius * radius) >= relPoint.LengthSqr();
}

INLINE bool Circle::Contains(const Circle &other) const {
    Vec2f relPoint = other.origin - origin;
    float distance = relPoint.Length() + other.radius;
    return radius > distance;
}

INLINE bool Circle::Intersects(const Circle &other) const {
    Vec2f relPoint = other.origin - origin;
    float distance = relPoint.Length() - other.radius;
    return radius >= distance;
}

//===================
// Circle Comparison
//===================

INLINE bool Circle::Compare (const Circle &other) const {
    return radius == radius && origin == origin;
}

INLINE bool Circle::Compare (const Circle &other, const float threshold) const {
    if (fabsf(radius - other.radius) > threshold) {
        return false;
    }

    return origin.Compare(other.origin, threshold);
}

INLINE bool Circle::operator== (const Circle &other) const {
    return Compare(other);
}

INLINE bool Circle::operator!= (const Circle &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_CIRCLE_H_ */
