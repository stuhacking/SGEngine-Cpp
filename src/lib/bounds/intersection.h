/*---  Intersection.h - test intersections between shapes  --------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Define functions to test intersections and containment tests
 *   between 2D and 3D volumes where each function makes sense...
 *   (e.g. Testing if a point contains a Rectangle makes no sense.)
 */
#ifndef __SGE_INTERSECTION_H
#define __SGE_INTERSECTION_H

namespace sge {

/** Intersection between 2D Lines. */
inline bool intersects (const Line2D &a, const Line2D &b) {
    Vec2f l1 = a.m_end - a.m_start;
    Vec2f l2 = b.m_end - b.m_start;

    // Not intersecting if parallel
    float cross = l1.cross(l2);
    if (cross == 0) {
        return false;
    }

    Vec2f distance = b.m_start - a.m_start;
    float m = distance.cross(l1) / cross;
    float n = distance.cross(l2) / cross;

    return (0.0f < m) && (m < 1.0f) && (0.0f < n) && (n < 1.0f);
}

/** Intersection between 2D Rectangles. */
inline bool intersects (const Rect &a, const Rect &b) {
    return (b.max.x >= a.min.x && b.max.y >= a.min.y &&
            b.min.x <= a.max.x && b.min.y <= a.max.y);
}

/** Intersection between 2D Circles. */
inline bool intersects (const Circle &a, const Circle &b) {
    Vec2f relPoint = b.center - a.center;
    float distance = relPoint.mag() - b.radius;
    return a.radius >= distance;
}

inline bool intersects (const Rect &rect, const Circle &circle) {
    Vec2f nearest = circle.center.clamp(rect.min, rect.max);
    nearest = nearest - circle.center;

    return nearest.magSq() <= (circle.radius * circle.radius);
}

inline bool intersects (const Circle &circle, const Rect &rect) {
    return intersects(rect, circle);
}

/** Intersection between 3D Rays. */
inline bool intersects (const Ray3D &a, const Ray3D &b) {
    Vec3f l1 = a.end - a.start;
    Vec3f l2 = b.end - b.start;

    // Not intersecting if parallel
    float cross = l1.cross(l2).mag();
    if (cross == 0) {
        return false;
    }

    Vec3f distance = b.start - a.start;
    float m = distance.cross(l1).mag() / cross;
    float n = distance.cross(l2).mag() / cross;

    return (0.0f < m) && (m < 1.0f) && (0.0f < n) && (n < 1.0f);
}

/** Intersection between Axis-aligned boxes. */
inline bool intersects (const Aabb &a, const Aabb &b) {
    return (b.max.x >= a.min.x && b.max.y >= a.min.y && b.max.z >= a.min.z &&
            b.min.x <= a.max.x && b.min.y <= a.max.y && b.min.z <= a.max.z);
}

/** Intersection between Spheres. */
inline bool intersects (const Sphere &a, const Sphere &b) {
    Vec3f relPoint = b.center - a.center;
    float distance = relPoint.mag() - b.radius;
    return a.radius >= distance;
}

inline bool intersects (const Aabb &aabb, const Sphere &sphere) {
    Vec3f nearest = sphere.center.clamp(aabb.min, aabb.max);
    nearest = nearest - sphere.center;

    return nearest.magSq() <= (sphere.radius * sphere.radius);
}

inline bool Intersects (const Sphere &sphere, const Aabb &aabb) {
    return intersects(aabb, sphere);
}

// Shapes containing points

inline bool contains (const Rect &rect, const Vec2f &point) {
    return point.x >= rect.min.x && point.x <= rect.max.x &&
           point.y >= rect.min.y && point.y <= rect.max.y;
}

inline bool contains (const Circle &circle, const Vec2f &point) {
    Vec2f relPoint = point - circle.center;
    return (circle.radius * circle.radius) >= relPoint.magSq();
}

// Volumes containing points

inline bool contains (const Aabb &aabb, const Vec3f &point) {
    return point.x >= aabb.min.x && point.x <= aabb.max.x &&
           point.y >= aabb.min.y && point.y <= aabb.max.y &&
           point.z >= aabb.min.z && point.z <= aabb.max.z;
}

inline bool contains (const Sphere &sphere, const Vec3f &point) {
    Vec3f relPoint = point - sphere.center;
    return (sphere.radius * sphere.radius) >= relPoint.magSq();
}

// Shapes containing shapes

inline bool contains (const Rect &a, const Rect &b) {
    return contains(a, b.min) && contains(a, b.max);
}

inline bool contains (const Circle &a, const Circle &b) {
    Vec2f relPoint = b.center - a.center;
    float distance = relPoint.mag() + b.radius;
    return a.radius > distance;
}

// Volumes containing volumes

inline bool contains (const Aabb &a, const Aabb &b) {
    return contains(a, b.min) && contains(a, b.max);
}

inline bool contains (const Sphere &a, const Sphere &b) {
    Vec3f relPoint = b.center - a.center;
    float distance = relPoint.mag() + b.radius;

    return a.radius > distance;
}

} /* namespace sge */

#endif /* __SGE_INTERSECTION_H */
