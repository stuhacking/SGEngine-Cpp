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
    explicit Ray3D (const Vec3f &p_start, const Vec3f &p_end)
        : start(p_start), end(p_end) { }

    /**
     * Get the length of this Line Section.
     */
    float Length () const;

    /**
     * Test if this Ray3D intersects another Ray3D.
     */
    friend bool Intersects (const Ray3D &a, const Ray3D &b);

    /**
     * Return the point at which this Ray3D intersects
     * another Ray3D, or extend the Input line to
     * INFINITY if no intersection exists.
     */
    Vec3f Intersection (const Ray3D &rhs) const;

    /**
     * Find the point along this Line that occurs at time t.
     * If time is between 0..1 then this point will lie on the
     * line.
     */
    Vec3f Extrapolate (const float t) const;

    bool Compare (const Ray3D &other) const;

    bool Compare (const Ray3D &other, const float threshold) const;

    bool operator== (const Ray3D &other) const;

    bool operator!= (const Ray3D &other) const;
};

// --------------------------------------------------------------------------

inline float Ray3D::Length () const {
    return (end - start).Length();
}

inline Vec3f Ray3D::Extrapolate (const float t) const {
    return start + (end - start) * t;
}

inline bool Ray3D::Compare (const Ray3D &other) const {
    return start == other.start && end == other.end;
}

inline bool Ray3D::Compare (const Ray3D &other, const float threshold) const {
    return start.Compare(other.start, threshold) &&
        end.Compare(other.end, threshold);
}

inline bool Ray3D::operator== (const Ray3D &other) const {
    return Compare(other);
}

inline bool Ray3D::operator!= (const Ray3D &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGE_RAY_H */
