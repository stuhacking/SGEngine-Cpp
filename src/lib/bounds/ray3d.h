/*---  Ray3D.h - 2D Line Section Header  ---------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a 2D Line Section for intersection tests.
 */
#ifndef __SGE_RAY3D_H
#define __SGE_RAY3D_H

namespace sge {

/**
 * 3D Ray. Implements intersection tests against
 * other rays and 3D volumes.
 */
class Ray3D {
public:
    Vec3f start;
    Vec3f end;

public:

    /**
     * Create a Ray3D with (x1, y1)..(x2, y2) values.
     */
    explicit Ray3D (const float x1, const float y1, const float z1,
                    const float x2, const float y2, const float z2)
        : start{x1, y1, z1}, end{x2, y2, z2} { }

    /**
     * Create a Ray3D with start and end points.
     */
    explicit Ray3D (const Vec3f &pStart, const Vec3f &pEnd)
        : start(pStart), end(pEnd) { }

    /**
     * Get the length of this Line Section.
     */
    float length () const;

    /**
     * Test if this Ray3D intersects another Ray3D.
     */
    friend bool intersects (const Ray3D &a, const Ray3D &b);

    /**
     * Return the point at which this Ray3D intersects
     * another Ray3D, or extend the Input line to
     * INFINITY if no intersection exists.
     */
    Vec3f intersection (const Ray3D &rhs) const;

    /**
     * Find the point along this Line that occurs at time t.
     * If time is between 0..1 then this point will lie on the
     * line.
     */
    Vec3f extrapolate (const float t) const;

    bool compare (const Ray3D &other) const;

    bool compare (const Ray3D &other, const float threshold) const;
};

// --------------------------------------------------------------------------

inline float Ray3D::length () const {
    return (end - start).mag();
}

inline Vec3f Ray3D::extrapolate (const float t) const {
    return start + (end - start) * t;
}

inline bool Ray3D::compare (const Ray3D &other) const {
    return start == other.start && end == other.end;
}

inline bool Ray3D::compare (const Ray3D &other, const float threshold) const {
    return start.compare(other.start, threshold) &&
          end.compare(other.end, threshold);
}

inline bool operator== (const Ray3D &a, const Ray3D &b) {
    return a.compare(b);
}

inline bool operator!= (const Ray3D &a, const Ray3D &b) {
    return !a.compare(b);
}

} /* namespace sge */

#endif /* __SGE_RAY_H */
