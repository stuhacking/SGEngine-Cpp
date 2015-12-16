/*---  MeshRenderer.h - OpenGL Mesh Rendering Header  --------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 * 
 * @brief Define class for sending mesh data to OpenGL.
 */
#ifndef __SHENGINE_MESHRENDERER_H_
#define __SHENGINE_MESHRENDERER_H_

namespace sge {

class MeshRenderer {
public:
    MeshRenderer(const Mesh &p_mesh)
        : m_glVaoId(0), m_buffers{0, 0}, mesh(p_mesh) { }

    bool IsCompiled() const;

    void Compile();

    void Render() const;

private:
    GLuint m_glVaoId;
    GLuint m_buffers[2];
    Mesh mesh;
};

// --------------------------------------------------------------------------

inline bool MeshRenderer::IsCompiled() const {
    return (m_glVaoId > 0 && m_buffers[0] > 0 && m_buffers[1] > 0);
}

} /* namespace sge */

#endif /* __SHENGINE_MESHRENDERER_H_ */