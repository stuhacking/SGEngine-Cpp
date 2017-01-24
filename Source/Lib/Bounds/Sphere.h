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
        : center(Vec3f::ZERO), radius(-FMath::INFTY) { }

    /** Construct a sphere centered at p_center, with radius p_radius. */
    explicit Sphere (const Vec3f &p_center, const float p_radius = -FMath::INFTY)
        : center(p_center), radius(p_radius) { }

    /**
     * Clear all points from this Sphere.
     * Destructive.
     */
    void Clear ();

    /**
     * Expand this sphere to cover an infinite area.
     * Destructive.
     */
    void Maximize ();

    /**
     * Get the area of this sphere.
     */
    float Volume () const;

    /**
     * Test if this Sphere contains point.
     */
    friend bool Contains (const Sphere &sphere, const Vec3f &point);

    /**
     * Test if this Sphere fully encloses another
     * Sphere.
     */
    friend bool Contains (const Sphere &a, const Sphere &b);

    /**
     * Test if this Sphere intersects another
     * Sphere.
     */
    friend bool Intersects (const Sphere &a, const Sphere &b);

    /**
     * Test if two Spheres are equivalent.
     */
    bool Compare (const Sphere &other) const;

    /**
     * Test if two Spheres are similar within a given
     * tolerance.
     */
    bool Compare (const Sphere &other, const float threshold) const;

    /**
     * Test if two Spheres are equivalent.
     */
    bool operator== (const Sphere &other) const;

    /**
     * Test if two Spheres are not equivalent.
     */
    bool operator!= (const Sphere &other) const;
};

// --------------------------------------------------------------------------

inline void Sphere::Clear () {
    radius = -FMath::INFTY;
    center = Vec3f(0.0f);
}

inline void Sphere::Maximize () {
    radius = FMath::INFTY;
    center.x = center.y = 0.0f;
}

inline float Sphere::Volume () const {
    return 4.0f / 3.0f * FMath::PI * (radius * radius * radius);
}

//===================
// Sphere Comparison
//===================

inline bool Sphere::Compare (const Sphere &other) const {
    return radius == radius && center == center;
}

inline bool Sphere::Compare (const Sphere &other, const float threshold) const {
    if (fabsf(radius - other.radius) > threshold) {
        return false;
    }

    return center.Compare(other.center, threshold);
}

inline bool Sphere::operator== (const Sphere &other) const {
    return Compare(other);
}

inline bool Sphere::operator!= (const Sphere &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGE_SPHERE_H */
