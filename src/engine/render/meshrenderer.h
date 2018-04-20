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
     * @param pMesh Geometry mesh data
     * @return
     */
    explicit MeshRenderer(const Mesh &pMesh)
            : mGlVaoId{0}, mBuffers{0, 0}, mesh{pMesh} { }

    /**
     * @return true if mesh has been compiled and has valid bound GPU buffers.
     */
    bool isCompiled () const;

    /**
     * Request storage on the GPU and buffer mesh data.
     */
    void compile ();

    /**
     * Draw mesh data.
     */
    void render () const;

private:
    GLuint mGlVaoId;
    GLuint mBuffers[2];
    Mesh mesh;
};

// --------------------------------------------------------------------------

inline bool MeshRenderer::isCompiled () const {
    return (mGlVaoId > 0 && mBuffers[0] > 0 && mBuffers[1] > 0);
}

} /* namespace sge */

#endif /* __SGE_MESHRENDERER_H */
