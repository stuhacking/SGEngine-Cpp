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
#ifndef __SHLIB_CIRCLE_H_
#define __SHLIB_CIRCLE_H_

#include <cfloat> // fabsf

namespace sge {

/**
 * 2D Circle. Implements intersection and envelopment tests for
 * 2D shapes.
 */
class Circle {
public:
    Circle()
        : origin(Vector2::ZERO), radius(-FMath::INFTY) { }

    Circle(const Vector2 &p_origin, const float p_radius = -FMath::INFTY)
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
    Vector2 Center() const;

    /**
     * Get the area of this circle.
     */
    float Area() const;

    bool Contains(const Vector2 &point) const;

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
    Vector2 origin;
    float radius;
};

// --------------------------------------------------------------------------

inline void Circle::Clear() {
    radius = -FMath::INFTY;
    origin = Vector2(0.0f, 0.0f);
}

inline void Circle::Maximize() {
    radius = FMath::INFTY;
    origin.x = origin.y = 0.0f;
}

inline Vector2 Circle::Center() const {
    return origin;
}

inline float Circle::Area() const {
    return radius * radius * FMath::PI;
}

inline bool Circle::Contains(const Vector2 &point) const {
    Vector2 relPoint = point - origin;
    return (radius * radius) >= relPoint.LengthSqr();
}

inline bool Circle::Contains(const Circle &other) const {
    Vector2 relPoint = other.origin - origin;
    float distance = relPoint.Length() + other.radius;
    return radius > distance;
}

inline bool Circle::Intersects(const Circle &other) const {
    Vector2 relPoint = other.origin - origin;
    float distance = relPoint.Length() - other.radius;
    return radius >= distance;
}

//===================
// Circle Comparison
//===================

inline bool Circle::Compare (const Circle &other) const {
    return radius == radius && origin == origin;
}

inline bool Circle::Compare (const Circle &other, const float threshold) const {
    if (fabsf(radius - other.radius) > threshold) {
        return false;
    }

    return origin.Compare(other.origin, threshold);
}

inline bool Circle::operator== (const Circle &other) const {
    return Compare(other);
}

inline bool Circle::operator!= (const Circle &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SHLIB_CIRCLE_H_ */
