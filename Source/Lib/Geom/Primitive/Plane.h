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
#ifndef __SGENGINE_PLANE_H_
#define __SGENGINE_PLANE_H_

namespace sge {

class Plane {
public:
    Plane (const Vec3f &p_center, const float p_size)
        : center(p_center) {
        hSize = Vec2f(p_size * 0.5f);
    }
    
    Plane (const Vec3f &p_center, const Vec2f &p_size)
        : center(p_center) {
        hSize = p_size * 0.5f;
    }

    Mesh ToMesh () const;
    
private:
    Vec3f center;
    Vec2f hSize;
};
    
} /* namespace sge */

#endif /* __SGENGINE_PLANE_H_ */
