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
class AABB {
public:
    Vec3f min;
    Vec3f max;

public:
    /** Default Constructor */
    AABB ()
        : min{FMath::INFTY, FMath::INFTY, FMath::INFTY},
          max{-FMath::INFTY, -FMath::INFTY, -FMath::INFTY} { }

    /** Point Constructor */
    explicit AABB (const Vec3f &point)
        : min{point}, max{point} { }

    /**
     * Construct a AABB with min and max bounds as Vec3f.
     */
    explicit AABB (const Vec3f &p_min, const Vec3f &p_max)
        : min{p_min}, max{p_max} { }

    /**
     * Construct a AABB with min and max bounds as values.
     */
    explicit AABB (const float xMin, const float yMin, const float zMin,
                   const float xMax, const float yMax, const float zMax)
        : min{xMin, yMin, zMin}, max{xMax, yMax, zMax} { }

    /**
     * Clear the contents of this AABB.
     */
    void Clear ();

    /**
     * Expand this AABB to maximum size.
     */
    void Maximize ();

    /**
     * Get the center of this AABB as a Vec3f.
     */
    Vec3f Center () const;

    /**
     * Get the area of this AABB.
     */
    float Volume () const;

    /**
     * Return a new AABB expanded by val in each direction,
     * which shares the same center as this AABB.
     */
    AABB Expand (const float val) const;

    /**
     * Expand the bounds of this AABB by val in each direction.
     * Destructive.
     */
    void ExpandSelf (const float val);

    /** Test if rectangle contains point. */
    friend bool Contains (const AABB &aabb, const Vec3f &point);

    /** Test if rectangle entirely contains other rectangle. */
    friend bool Contains (const AABB &a, const AABB &b);

    /** Test if rectangle partially (or fully) intersects other rectangle. */
    friend bool Intersects (const AABB &a, const AABB &b);

    /**
     * Test whether two AABBs are equivalent.
     */
    bool Compare (const AABB &other) const;

    /**
     * Test whether two AABBs are the same within a given
     * tolerance.
     */
    bool Compare (const AABB &other, const float threshold) const;

    /**
     * Test whether to AABBs are equivalent.
     */
    bool operator== (const AABB &other) const;

    /**
     * Test whether two AABBs are not equivalent.
     */
    bool operator!= (const AABB &other) const;
};

// --------------------------------------------------------------------------

inline void AABB::Clear () {
    min.x = min.y = min.z = FMath::INFTY;
    max.x = max.y = max.z = -FMath::INFTY;
}

inline void AABB::Maximize () {
    min.x = min.y = min.z = -FMath::INFTY;
    max.x = max.y = max.z = FMath::INFTY;
}

inline Vec3f AABB::Center () const {
    return (min + max) * 0.5f;
}

inline float AABB::Volume () const {
    return fabsf((max.x - min.x) * (max.y - min.y) * (max.z - min.z));
}

inline AABB AABB::Expand (const float val) const {
    return AABB(min.x - val, min.y - val, min.z - val,
                max.x + val, max.y + val, max.z + val);
}

inline void AABB::ExpandSelf (const float val) {
    min.x -= val;
    min.y -= val;
    min.z -= val;
    max.x += val;
    max.y += val;
    max.z += val;
}

//=================
// AABB Comparison
//=================

inline bool AABB::Compare (const AABB &other) const {
    return min == other.min && max == other.max;
}

inline bool AABB::Compare (const AABB &other, const float threshold) const {
    return min.Compare(other.min, threshold) && max.Compare(other.max, threshold);
}

inline bool AABB::operator== (const AABB &other) const {
    return Compare(other);
}

inline bool AABB::operator!= (const AABB &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGE_AABB_H */
