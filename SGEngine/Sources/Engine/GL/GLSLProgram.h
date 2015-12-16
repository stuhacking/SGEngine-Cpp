/*---  GLSLProgram.h - OpenGL Shader Program Header  ---------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a class for loading and binding shader resources.
 */
#ifndef __SHENGINE_GLSLPROGRAM_H_
#define __SHENGINE_GLSLPROGRAM_H_

#include <string>
#include <vector>
#include <unordered_map>

class GLSLShader;

namespace sge {

/**
 * GLSL Program type. Implement loading and compiling shader source
 * provided as separate shader files. Tracks assigned GL IDs.
 *
 * Note: GLSL programs are currently composed of a vertex shader and a
 * fragment shader.
 *
 * TODO Support linking already compiled shaders?
 * TODO Better error detection
 */
class GLSLProgram {
public:
    GLSLProgram() : m_id(0) { }

    GLSLProgram &AddSource (const std::string &filename);

    bool Compile();

    bool Validate () const;

    void Bind();

    bool IsCompiled() const;

    void Delete ();

    /**
     * Lookup the address of a shader uniform variable.
     * (Might update a cache.)
     */
    GLint GetUniform (const std::string &name);

    /**
     * Set the value of a uniform using data from a 4x4 Matrix.
     * (Might update a cache.)
     */
    void SetUniform (const std::string &name, float value);

    /**
     * Set the value of a uniform using data from a 4x4 Matrix.
     * (Might update a cache.)
     */
    void SetUniform (const std::string &name, const Vector2 &value);

    /**
     * Set the value of a uniform using data from a 4x4 Matrix.
     * (Might update a cache.)
     */
    void SetUniform (const std::string &name, const Vector3 &value);

    /**
     * Set the value of a uniform using data from a 4x4 Matrix.
     * (Might update a cache.)
     */
    void SetUniform (const std::string &name, const Vector4 &value);

    /**
     * Set the value of a uniform using data from a 4x4 Matrix.
     * (Might update a cache.)
     */
    void SetUniform (const std::string &name, const Matrix2 &value);

    /**
     * Set the value of a uniform using data from a 4x4 Matrix.
     * (Might update a cache.)
     */
    void SetUniform (const std::string &name, const Matrix3 &value);

    /**
     * Set the value of a uniform using data from a 4x4 Matrix.
     * (Might update a cache.)
     */
    void SetUniform (const std::string &name, const Matrix4 &value);

private:
    GLuint m_id; // 0 == error/uninitialized
    std::vector<GLSLShader> m_shaders;
    std::unordered_map<std::string, GLint> m_uniforms;
};

// --------------------------------------------------------------------------

inline GLSLProgram &GLSLProgram::AddSource (const std::string &filename) {
    m_shaders.emplace_back(filename);

    return *this;
}

inline bool GLSLProgram::IsCompiled() const {
    return m_id > 0;
}

} /* namespace sge */

#endif /* __SHENGINE_GLSLPROGRAM_H_ */