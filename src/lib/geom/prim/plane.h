/*---  Plane.h - Primitive Plane Header  ---------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a primitive plane mesh generator.
 */
#ifndef __SGE_PLANE_H
#define __SGE_PLANE_H

namespace sge {

class Plane {
public:
    Plane (const Vec3f &pCenter, const float pSize)
        : mCenter(pCenter) {
        mHalfSize = Vec2f(pSize * 0.5f);
    }

    Plane (const Vec3f &pCenter, const Vec2f &pSize)
        : mCenter(pCenter) {
        mHalfSize = pSize * 0.5f;
    }

    Mesh toMesh () const;

private:
    Vec3f mCenter;
    Vec2f mHalfSize;
};

} /* namespace sge */

#endif /* __SGE_PLANE_H */
