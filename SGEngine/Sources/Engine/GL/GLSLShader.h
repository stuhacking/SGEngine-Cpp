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
#ifndef __SGENGINE_GLSLSHADER_H_
#define __SGENGINE_GLSLSHADER_H_

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
    GLuint m_id; // 0 == error/uninitialized
    GLenum m_type;
    std::string m_filename;
};

inline bool GLSLShader::IsCompiled() const {
    return m_id > 0;
}

} /* namespace sge */

#endif /* __SGENGINE_GLSLSHADER_H_ */
