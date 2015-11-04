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
#ifndef __SHLIB_ICOSPHERE_H_
#define __SHLIB_ICOSPHERE_H_

namespace sge {

class ICOSphere {
public:
    ICOSphere (const Vector3 &p_center, const float p_size)
        : center(p_center) {
        hSize = Vector3(p_size * 0.5f);
    }
    
    ICOSphere (const Vector3 &p_center, const Vector3 &p_size)
        : center(p_center) {
        hSize = p_size * 0.5f;
    }

    Mesh ToMesh () const;
    
private:
    Vector3 center;
    Vector3 hSize;
};
    
} /* namespace sge */

#endif /* __SHLIB_ICOSPHERE_H_ */
