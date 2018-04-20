/*---  Cube.h - Primitive Cube Header  -----------------------------*- C++ -*---
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
#ifndef __SGE_CUBE_H
#define __SGE_CUBE_H

namespace sge {

class Cube {
public:
    Cube (const Vec3f &pCenter, const float pSize)
        : mCenter(pCenter) {
        mHalfSize = Vec3f(pSize * 0.5f);
    }

    Cube (const Vec3f &pCenter, const Vec3f &pSize)
        : mCenter(pCenter) {
        mHalfSize = pSize * 0.5f;
    }

    Mesh toMesh () const;

private:
    Vec3f mCenter;
    Vec3f mHalfSize;
};

} /* namespace sge */

#endif /* __SGE_CUBE_H */
