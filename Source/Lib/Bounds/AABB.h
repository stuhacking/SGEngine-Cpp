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
    bool Contains (const Vec3f &point) const;

    /** Test if rectangle entirely contains other rectangle. */
    bool Contains (const AABB &other) const;

    /** Test if rectangle partially (or fully) intersects other rectangle. */
    bool Intersects (const AABB &other) const;

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

INLINE void AABB::Clear () {
    min.x = min.y = min.z = FMath::INFTY;
    max.x = max.y = max.z = -FMath::INFTY;
}

INLINE void AABB::Maximize () {
    min.x = min.y = min.z = -FMath::INFTY;
    max.x = max.y = max.z = FMath::INFTY;
}

INLINE Vec3f AABB::Center () const {
    return (min + max) * 0.5f;
}

INLINE float AABB::Volume () const {
    return fabsf((max.x - min.x) * (max.y - min.y) * (max.z - min.z));
}

INLINE AABB AABB::Expand (const float val) const {
    return AABB(min.x - val, min.y - val, min.z - val,
                max.x + val, max.y + val, max.z + val);
}

INLINE void AABB::ExpandSelf (const float val) {
    min.x -= val;
    min.y -= val;
    min.z -= val;
    max.x += val;
    max.y += val;
    max.z += val;
}

INLINE bool AABB::Contains (const Vec3f &point) const {
    return point.x >= min.x && point.x <= max.x &&
        point.y >= min.y && point.y <= max.y &&
        point.z >= min.z && point.z <= max.z;
}

INLINE bool AABB::Contains (const AABB &other) const {
    return Contains(other.min) && Contains(other.max);
}

INLINE bool AABB::Intersects (const AABB &other) const {
    return (other.max.x >= min.x && other.max.y >= min.y && other.max.z >= min.z &&
            other.min.x <= max.x && other.min.y <= max.y && other.min.z <= max.z);
}

//=================
// AABB Comparison
//=================

INLINE bool AABB::Compare (const AABB &other) const {
    return min == other.min && max == other.max;
}

INLINE bool AABB::Compare (const AABB &other, const float threshold) const {
    return min.Compare(other.min, threshold) && max.Compare(other.max, threshold);
}

INLINE bool AABB::operator== (const AABB &other) const {
    return Compare(other);
}

INLINE bool AABB::operator!= (const AABB &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGE_AABB_H */
