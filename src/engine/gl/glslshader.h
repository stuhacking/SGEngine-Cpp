/*---  GLSLShader.h - GLSL Shader Header  --------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a GLSL shader type which is part of a GLSLProgram.
 */
#ifndef __SGE_GLSLSHADER_H
#define __SGE_GLSLSHADER_H

#include <string>

namespace sge {

class GLSLShader {
public:
    friend class GLSLProgram;

    /**
     * GLSLShader is an individual component of a complete shader.
     */
    GLSLShader (const std::string &pFilename);

    bool compile ();

    bool isCompiled () const { return mId > 0; }

    /**
     * Clean up assigned IDs.
     */
    void destroy ();

private:
    GLuint mId = 0;          /**< GL shader Id. 0 == error/uninitialized. */
    GLenum mType;            /**< Shader type. */
    std::string mFilename;   /**< Path to shader source. */
};

} /* namespace sge */

#endif /* __SGE_GLSLSHADER_H */
