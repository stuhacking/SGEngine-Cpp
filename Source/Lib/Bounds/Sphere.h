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
#ifndef __SGENGINE_SPHERE_H_
#define __SGENGINE_SPHERE_H_

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
    bool Contains (const Vec3f &point) const;

    /**
     * Test if this Sphere fully encloses another
     * Sphere.
     */
    bool Contains (const Sphere &other) const;

    /**
     * Test if this Sphere intersects another
     * Sphere.
     */
    bool Intersects (const Sphere &other) const;

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

INLINE void Sphere::Clear () {
    radius = -FMath::INFTY;
    center = Vec3f(0.0f);
}

INLINE void Sphere::Maximize () {
    radius = FMath::INFTY;
    center.x = center.y = 0.0f;
}

INLINE float Sphere::Volume () const {
    return 4.0f / 3.0f * FMath::PI * (radius * radius * radius);
}

INLINE bool Sphere::Contains (const Vec3f &point) const {
    Vec3f relPoint = point - center;
    return (radius * radius) >= relPoint.LengthSqr();
}

INLINE bool Sphere::Contains (const Sphere &other) const {
    Vec3f relPoint = other.center - center;
    float distance = relPoint.Length() + other.radius;
    return radius > distance;
}

INLINE bool Sphere::Intersects (const Sphere &other) const {
    Vec3f relPoint = other.center - center;
    float distance = relPoint.Length() - other.radius;
    return radius >= distance;
}

//===================
// Sphere Comparison
//===================

INLINE bool Sphere::Compare (const Sphere &other) const {
    return radius == radius && center == center;
}

INLINE bool Sphere::Compare (const Sphere &other, const float threshold) const {
    if (fabsf(radius - other.radius) > threshold) {
        return false;
    }

    return center.Compare(other.center, threshold);
}

INLINE bool Sphere::operator== (const Sphere &other) const {
    return Compare(other);
}

INLINE bool Sphere::operator!= (const Sphere &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_SPHERE_H_ */
