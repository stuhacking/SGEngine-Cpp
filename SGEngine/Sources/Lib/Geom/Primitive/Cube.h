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
#ifndef __SHLIB_CUBE_H_
#define __SHLIB_CUBE_H_

namespace sge {

class Cube {
public:
    Cube (const Vector3 &p_center, const float p_size)
        : center(p_center) {
        hSize = Vector3(p_size * 0.5f);
    }
    
    Cube (const Vector3 &p_center, const Vector3 &p_size)
        : center(p_center) {
        hSize = p_size * 0.5f;
    }

    Mesh ToMesh () const;
    
private:
    Vector3 center;
    Vector3 hSize;
};
    
} /* namespace sge */

#endif /* __SHLIB_CUBE_H_ */
