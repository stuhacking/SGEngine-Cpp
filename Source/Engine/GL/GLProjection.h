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
#ifndef __SGE_GLPROJECTION_H
#define __SGE_GLPROJECTION_H

namespace sge {

class GLProjection {
public:
    float near;
    float far;
    float fov;

    GLProjection(const float p_near, const float p_far, const float p_fov = 50.0f)
        : near(p_near), far(p_far), fov(p_fov) { }

    Mat4f GetPerspectiveProjection(const u32 w, const u32 h) const;

    Mat4f GetOrthographicProjection(const u32 w, const u32 h) const;
};

} /* namespace sge */

#endif /* __SGE_GLPROJECTION_H  */
