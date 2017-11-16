/*---  Sphere.h - Bounding Sphere Header  --------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a 3D bounding sphere type.
 */
#ifndef __SGE_SPHERE_H
#define __SGE_SPHERE_H

#include <cmath> // fabsf

namespace sge {

/**
 * 3D Sphere. Implements intersection and envelopment tests for
 * 3D shapes.
 */
class Sphere {
public:
    Vec3f center;
    float radius;

public:
    /** Default Constructor. */
    Sphere ()
        : center(Vec3f_Zero), radius(-math::Infinity) { }

    /** Construct a sphere centered at p_center, with radius p_radius. */
    explicit Sphere (const Vec3f &p_center, const float p_radius = -math::Infinity)
        : center(p_center), radius(p_radius) { }

    /**
     * Clear all points from this Sphere.
     * Destructive.
     */
    void reset ();

    /**
     * Expand this sphere to cover an infinite area.
     * Destructive.
     */
    void maximize ();

    /**
     * Get the area of this sphere.
     */
    float volume () const;

    /**
     * Test if this Sphere contains point.
     */
    friend bool contains (const Sphere &sphere, const Vec3f &point);

    /**
     * Test if this Sphere fully encloses another
     * Sphere.
     */
    friend bool contains (const Sphere &a, const Sphere &b);

    /**
     * Test if this Sphere intersects another
     * Sphere.
     */
    friend bool intersects (const Sphere &a, const Sphere &b);

    /**
     * Test if two Spheres are equivalent.
     */
    bool compare (const Sphere &other) const;

    /**
     * Test if two Spheres are similar within a given
     * tolerance.
     */
    bool compare (const Sphere &other, const float threshold) const;
};

// --------------------------------------------------------------------------

inline void Sphere::reset () {
    radius = -math::Infinity;
    center = Vec3f(0.0f);
}

inline void Sphere::maximize () {
    radius = math::Infinity;
    center.x = center.y = 0.0f;
}

inline float Sphere::volume () const {
    return 4.0f / 3.0f * math::Pi * (radius * radius * radius);
}

//===================
// Sphere Comparison
//===================

inline bool Sphere::compare (const Sphere &other) const {
    return radius == other.radius && center == other.center;
}

inline bool Sphere::compare (const Sphere &other, const float threshold) const {

    return (fabsf(radius - other.radius) <= threshold) &&
           center.compare(other.center, threshold);
}

inline bool operator== (const Sphere &a, const Sphere &b) {
    return a.compare(b);
}

inline bool operator!= (const Sphere &a, const Sphere &b) {
    return !a.compare(b);
}

} /* namespace sge */

#endif /* __SGE_SPHERE_H */
