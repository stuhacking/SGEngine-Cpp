/*---  Intersection.h - Test intersections between shapes  --------*- C++ -*---
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
#ifndef __SGENGINE_INTERSECTION_H
#define __SGENGINE_INTERSECTION_H

namespace sge {

/** Intersection between 2D Lines. */
inline bool Intersects (const  Line2D &a, const Line2D &b) {
    Vec2f l1 = a.m_end - a.m_start;
    Vec2f l2 = b.m_end - b.m_start;

    // Not intersecting if parallel
    float cross = l1.Cross(l2);
    if (cross == 0) {
        return false;
    }

    Vec2f distance = b.m_start - a.m_start;
    float m = distance.Cross(l1) / cross;
    float n = distance.Cross(l2) / cross;

    return (0.0f < m) && (m < 1.0f) && (0.0f < n) && (n < 1.0f);
}

/** Intersection between 2D Rectangles. */
inline bool Intersects (const Rectangle &a, const Rectangle &b) {
    return (b.max.x >= a.min.x && b.max.y >= a.min.y &&
            b.min.x <= a.max.x && b.min.y <= a.max.y);
}

/** Intersection between 2D Circles. */
inline bool Intersects (const Circle &a, const Circle &b) {
    Vec2f relPoint = b.center - a.center;
    float distance = relPoint.Length() - b.radius;
    return a.radius >= distance;
}

inline bool Intersects (const Rectangle &rect, const Circle &circle) {
    Vec2f nearest = circle.center.Clamp(rect.min, rect.max);
    nearest = nearest - circle.center;

    return nearest.LengthSqr() <= (circle.radius * circle.radius);
}

inline bool Intersects (const Circle &circle, const Rectangle &rect) {
    return Intersects(rect, circle);
}

/** Intersection between 3D Rays. */
inline bool Intersects (const Ray3D &a, const Ray3D &b) {
    Vec3f l1 = a.end - a.start;
    Vec3f l2 = b.end - b.start;

    // Not intersecting if parallel
    float cross = l1.Cross(l2).Length();
    if (cross == 0) {
        return false;
    }

    Vec3f distance = b.start - a.start;
    float m = distance.Cross(l1).Length() / cross;
    float n = distance.Cross(l2).Length() / cross;

    return (0.0f < m) && (m < 1.0f) && (0.0f < n) && (n < 1.0f);
}

/** Intersection between Axis-aligned boxes. */
inline bool Intersects (const AABB &a, const AABB &b) {
    return (b.max.x >= a.min.x && b.max.y >= a.min.y && b.max.z >= a.min.z &&
            b.min.x <= a.max.x && b.min.y <= a.max.y && b.min.z <= a.max.z);
}

/** Intersection between Spheres. */
inline bool Intersects (const Sphere &a, const Sphere &b) {
    Vec3f relPoint = b.center - a.center;
    float distance = relPoint.Length() - b.radius;
    return a.radius >= distance;
}

inline bool Intersects (const AABB &aabb, const Sphere &sphere) {
    Vec3f nearest = sphere.center.Clamp(aabb.min, aabb.max);
    nearest = nearest - sphere.center;

    return nearest.LengthSqr() <= (sphere.radius * sphere.radius);
}

inline bool Intersects (const Sphere &sphere, const AABB &aabb) {
    return Intersects(aabb, sphere);
}

// Shapes containing points

inline bool Contains (const Rectangle &rect, const Vec2f &point) {
    return point.x >= rect.min.x && point.x <= rect.max.x &&
           point.y >= rect.min.y && point.y <= rect.max.y;
}

inline bool Contains(const Circle &circle, const Vec2f &point) {
    Vec2f relPoint = point - circle.center;
    return (circle.radius * circle.radius) >= relPoint.LengthSqr();
}

// Volumes containing points

inline bool Contains (const AABB &aabb, const Vec3f &point) {
    return point.x >= aabb.min.x && point.x <= aabb.max.x &&
           point.y >= aabb.min.y && point.y <= aabb.max.y &&
           point.z >= aabb.min.z && point.z <= aabb.max.z;
}

inline bool Contains (const Sphere &sphere, const Vec3f &point) {
    Vec3f relPoint = point - sphere.center;
    return (sphere.radius * sphere.radius) >= relPoint.LengthSqr();
}

// Shapes containing shapes

inline bool Contains (const Rectangle &a, const Rectangle &b) {
    return Contains(a, b.min) && Contains(a, b.max);
}

inline bool Contains(const Circle &a, const Circle &b) {
    Vec2f relPoint = b.center - a.center;
    float distance = relPoint.Length() + b.radius;
    return a.radius > distance;
}

// Volumes containing volumes

inline bool Contains (const AABB &a, const AABB &b) {
    return Contains(a, b.min) && Contains(a, b.max);
}

inline bool Contains (const Sphere &a, const Sphere &b) {
    Vec3f relPoint = b.center - a.center;
    float distance = relPoint.Length() + b.radius;
    return a.radius > distance;
}

} /* namespace sge */

#endif /* __SGENGINE_INTERSECTION_H */
