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

    GLSLShader(const std::string &filename);

    GLuint Compile();

    bool IsCompiled() const;

    void Delete ();

private:
    GLuint m_id = 0; // 0 == error/uninitialized
    GLenum m_type;
    std::string m_filename;
};

// --------------------------------------------------------------------------

inline bool GLSLShader::IsCompiled() const {
    return m_id > 0;
}

} /* namespace sge */

#endif /* __SGE_GLSLSHADER_H */
