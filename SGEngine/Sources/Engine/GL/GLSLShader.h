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
#ifndef __SHENGINE_GLSLSHADER_H_
#define __SHENGINE_GLSLSHADER_H_

#include <string>

using std::string;

namespace sge {

class GLSLShader {
public:
    friend class GLSLProgram;

    GLSLShader(const string &filename);

    int Compile();

    bool IsCompiled() const;

    void Delete ();

private:
    GLuint m_id; // May be <0 if error or uninitialized.
    GLenum m_type;
    string m_filename;
};

inline bool GLSLShader::IsCompiled() const {
    return m_id > 0;
}

} /* namespace sge */

#endif /* __SHENGINE_GLSLSHADER_H_ */
