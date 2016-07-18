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
#ifndef __SGENGINE_ICOSPHERE_H_
#define __SGENGINE_ICOSPHERE_H_

namespace sge {

class ICOSphere {
public:
    ICOSphere (const Vec3f &p_center, const float p_size)
        : center(p_center) {
        hSize = Vec3f(p_size * 0.5f);
    }
    
    ICOSphere (const Vec3f &p_center, const Vec3f &p_size)
        : center(p_center) {
        hSize = p_size * 0.5f;
    }

    Mesh ToMesh () const;
    
private:
    Vec3f center;
    Vec3f hSize;
};
    
} /* namespace sge */

#endif /* __SGENGINE_ICOSPHERE_H_ */
