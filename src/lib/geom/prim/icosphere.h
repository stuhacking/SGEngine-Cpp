/*---  ICOSphere.h - Primitive ICOSphere Header  -------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a primitive ico sphere mesh generator.
 */
#ifndef __SGE_ICOSPHERE_H
#define __SGE_ICOSPHERE_H

namespace sge {

class ICOSphere {
public:
    ICOSphere (const Vec3f &pCenter, const float pSize)
        : mCenter(pCenter) {
        mHalfSize = Vec3f(pSize * 0.5f);
    }

    ICOSphere (const Vec3f &pCenter, const Vec3f &pSize)
        : mCenter(pCenter) {
        mHalfSize = pSize * 0.5f;
    }

    Mesh toMesh () const;

private:
    Vec3f mCenter;
    Vec3f mHalfSize;
};

} /* namespace sge */

#endif /* __SGE_ICOSPHERE_H */
