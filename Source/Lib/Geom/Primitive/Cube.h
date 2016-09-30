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
    Cube (const Vec3f &p_center, const float p_size)
        : center(p_center) {
        hSize = Vec3f(p_size * 0.5f);
    }
    
    Cube (const Vec3f &p_center, const Vec3f &p_size)
        : center(p_center) {
        hSize = p_size * 0.5f;
    }

    Mesh ToMesh () const;
    
private:
    Vec3f center;
    Vec3f hSize;
};
    
} /* namespace sge */

#endif /* __SGE_CUBE_H */
