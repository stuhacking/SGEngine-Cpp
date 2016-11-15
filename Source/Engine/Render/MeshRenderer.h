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
#ifndef __SGE_MESHRENDERER_H
#define __SGE_MESHRENDERER_H

namespace sge {

class MeshRenderer {
public:

    /**
     * Create a Renderable object for mesh data using an input Mesh.
     *
     * @param p_mesh
     * @return
     */
    explicit MeshRenderer(const Mesh &p_mesh)
            : m_glVaoId(0), m_buffers{0, 0}, mesh(p_mesh) { }

    /**
     * @return true if mesh has been compiled and has valid bound GPU buffers.
     */
    bool IsCompiled() const;

    /**
     * Request storage on the GPU and buffer mesh data.
     */
    void Compile();

    /**
     * Draw mesh data.
     */
    void Render() const;

private:
    GLuint m_glVaoId;
    GLuint m_buffers[2];
    Mesh mesh;
};

// --------------------------------------------------------------------------

INLINE bool MeshRenderer::IsCompiled() const {
    return (m_glVaoId > 0 && m_buffers[0] > 0 && m_buffers[1] > 0);
}

} /* namespace sge */

#endif /* __SGE_MESHRENDERER_H */
