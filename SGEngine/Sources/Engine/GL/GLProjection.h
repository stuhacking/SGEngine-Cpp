/*---  GLProjection.h - GL Project Matrix Header  ------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 * 
 * @brief Implements Perspective and Orthographic projections.
 */
#ifndef __SGENGINE_GLPROJECTION_H_
#define __SGENGINE_GLPROJECTION_H_

namespace sge {

class Matrix4;

class GLProjection {
public:
    float near;
    float far;
    float fov;

    GLProjection(const float p_near, const float p_far, const float p_fov = 50.0f)
        : near(p_near), far(p_far), fov(p_fov) { }

    Matrix4 GetPerspectiveProjection(const u32 w, const u32 h) const;

    Matrix4 GetOrthographicProjection(const u32 w, const u32 h) const;
};

} /* namespace sge */

#endif /* __SGENGINE_GLPROJECTION_H_  */
