/*---  GLProjection.h - gl Project Matrix Header  ------------------*- C++ -*---
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

    GLProjection(const float pNear, const float pFar, const float pFov = 50.0f)
        : near(pNear), far(pFar), fov(pFov) { }

    Mat4f perspectiveProjection (const u32 w, const u32 h) const;

    Mat4f orthographicProjection (const u32 w, const u32 h) const;
};

} /* namespace sge */

#endif /* __SGE_GLPROJECTION_H  */
