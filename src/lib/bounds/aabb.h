/*---  AABB.h - Axis-Aligned Bounding Box Header  ------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a 3D axis-aligned bounding box type.
 */
#ifndef __SGE_AABB_H
#define __SGE_AABB_H

#include <cmath> // fabsf

namespace sge {

/**
 * Axis-aligned Bounding Box. Implements intersection and containment
 * tests for 3D volumes.
 */
class Aabb {
public:
    Vec3f min;
    Vec3f max;

public:
    /** Default Constructor */
    Aabb ()
        : min{math::kInfty, math::kInfty, math::kInfty},
          max{-math::kInfty, -math::kInfty, -math::kInfty} { }

    /** Point Constructor */
    explicit Aabb (const Vec3f &point)
        : min{point}, max{point} { }

    /**
     * Construct a AABB with min and max bounds as Vec3f.
     */
    explicit Aabb (const Vec3f &pMin, const Vec3f &pMax)
        : min{pMin}, max{pMax} { }

    /**
     * Construct a AABB with min and max bounds as values.
     */
    explicit Aabb (const float xMin, const float yMin, const float zMin,
                   const float xMax, const float yMax, const float zMax)
        : min{xMin, yMin, zMin}, max{xMax, yMax, zMax} { }

    /**
     * Clear the contents of this AABB.
     */
    void reset ();

    /**
     * Expand this AABB to maximum size.
     */
    void maximize ();

    /**
     * Get the center of this AABB as a Vec3f.
     */
    Vec3f center () const;

    /**
     * Get the area of this AABB.
     */
    float volume () const;

    /**
     * Return a new AABB expanded by val in each direction,
     * which shares the same center as this AABB.
     */
    Aabb expand (const float val) const;

    /**
     * Expand the bounds of this AABB by val in each direction.
     * Destructive.
     */
    void expandSelf (const float val);

    /** Test if rectangle contains point. */
    friend bool contains (const Aabb &aabb, const Vec3f &point);

    /** Test if rectangle entirely contains other rectangle. */
    friend bool contains (const Aabb &a, const Aabb &b);

    /** Test if rectangle partially (or fully) intersects other rectangle. */
    friend bool intersects (const Aabb &a, const Aabb &b);

    /**
     * Test whether two AABBs are equivalent.
     */
    bool compare (const Aabb &other) const;

    /**
     * Test whether two AABBs are the same within a given
     * tolerance.
     */
    bool compare (const Aabb &other, const float threshold) const;
};

// --------------------------------------------------------------------------

inline void Aabb::reset () {
    min.x = min.y = min.z = math::kInfty;
    max.x = max.y = max.z = -math::kInfty;
}

inline void Aabb::maximize () {
    min.x = min.y = min.z = -math::kInfty;
    max.x = max.y = max.z = math::kInfty;
}

inline Vec3f Aabb::center () const {
    return (min + max) * 0.5f;
}

inline float Aabb::volume () const {
    return fabsf((max.x - min.x) * (max.y - min.y) * (max.z - min.z));
}

inline Aabb Aabb::expand (const float val) const {
    return Aabb(min.x - val, min.y - val, min.z - val,
                max.x + val, max.y + val, max.z + val);
}

inline void Aabb::expandSelf (const float val) {
    min.x -= val;
    min.y -= val;
    min.z -= val;
    max.x += val;
    max.y += val;
    max.z += val;
}

//=================
// Aabb Comparison
//=================

inline bool Aabb::compare (const Aabb &other) const {
    return min == other.min && max == other.max;
}

inline bool Aabb::compare (const Aabb &other, const float threshold) const {
    return min.compare(other.min, threshold) &&
          max.compare(other.max, threshold);
}

inline bool operator== (const Aabb &a, const Aabb &b) {
    return a.compare(b);
}

inline bool operator!= (const Aabb &a, const Aabb &b) {
    return !a.compare(b);
}

} /* namespace sge */

#endif /* __SGE_AABB_H */
