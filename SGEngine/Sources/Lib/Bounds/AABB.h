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
#ifndef __SGENGINE_AABB_H_
#define __SGENGINE_AABB_H_

#include <cmath> // fabsf

namespace sge {

/**
 * Axis-aligned Bounding Box. Implements intersection and envelopment
 * tests for 3D volumes.
 */
class AABB {
public:
    /** Default Constructor */
    AABB ();

    /** Point Constructor */
    AABB (const Vector3 &point);

    /**
     * Construct a AABB with min and max bounds as Vector3.
     */
    AABB (const Vector3 &p_min, const Vector3 &p_max);

    /**
     * Construct a AABB with min and max bounds as values.
     */
    AABB (const float xMin, const float yMin, const float zMin,
          const float xMax, const float yMax, const float zMax);

    /**
     * Clear the contents of this AABB.
     */
    void Clear ();

    /**
     * Expand this AABB to maximum size.
     */
    void Maximize ();

    /**
     * Get the center of this AABB as a Vector3.
     */
    Vector3 Center () const;

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
    bool Contains (const Vector3 &point) const;

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

private:
    Vector3 min;
    Vector3 max;
};

// --------------------------------------------------------------------------

inline AABB::AABB () {
    min.x = min.y = min.z = FMath::INFTY;
    max.x = max.y = max.z = -FMath::INFTY;
}

inline AABB::AABB (const Vector3 &point) {
    min = max = point;
}

inline AABB::AABB (const Vector3 &p_min, const Vector3 &p_max) {
    min = p_min;
    max = p_max;
}

inline AABB::AABB (const float xMin, const float yMin, const float zMin,
                   const float xMax, const float yMax, const float zMax) {
    min = Vector3(xMin, yMin, zMin);
    max = Vector3(xMax, yMax, zMax);
}

inline void AABB::Clear () {
    min.x = min.y = min.z = FMath::INFTY;
    max.x = max.y = max.z = -FMath::INFTY;
}

inline void AABB::Maximize () {
    min.x = min.y = min.z = -FMath::INFTY;
    max.x = max.y = max.z = FMath::INFTY;
}

inline Vector3 AABB::Center () const {
    return (min + max) / 2.0f;
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

inline bool AABB::Contains (const Vector3 &point) const {
    return point.x >= min.x && point.x <= max.x &&
        point.y >= min.y && point.y <= max.y &&
        point.z >= min.z && point.z <= max.z;
}

inline bool AABB::Contains (const AABB &other) const {
    return Contains(other.min) && Contains(other.max);
}

inline bool AABB::Intersects (const AABB &other) const {
    if (other.max.x < min.x || other.max.y < min.y || other.max.z < min.z ||
        other.min.x > max.x || other.min.y > max.y || other.min.z > max.z) {
        return false;
    }
    
    return true;
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

#endif /* __SGENGINE_AABB_H_ */
