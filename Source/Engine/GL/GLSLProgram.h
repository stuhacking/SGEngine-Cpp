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
#ifndef __SGE_GLSLPROGRAM_H
#define __SGE_GLSLPROGRAM_H

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
     * Set the value of a uniform using an unsigned int.
     * (Might update uniform cache.)
     */
    void SetUniform (const std::string &name, const u32 value);

    /**
     * Set the value of a uniform using a float.
     * (Might update uniform cache.)
     */
    void SetUniform (const std::string &name, const float value);

    /**
     * Set the value of a uniform using data from a Vec2f.
     * (Might update uniform cache.)
     */
    void SetUniform (const std::string &name, const Vec2f &value);

    /**
     * Set the value of a uniform using data from a Vec3f.
     * (Might update uniform cache.)
     */
    void SetUniform (const std::string &name, const Vec3f &value);

    /**
     * Set the value of a uniform using data from a Vec4f.
     * (Might update uniform cache.)
     */
    void SetUniform (const std::string &name, const Vec4f &value);

    /**
     * Set the value of a uniform using data from a 2x2 Matrix.
     * (Might update uniform cache.)
     */
    void SetUniform (const std::string &name, const Mat2f &value);

    /**
     * Set the value of a uniform using data from a 3x3 Matrix.
     * (Might update uniform cache.)
     */
    void SetUniform (const std::string &name, const Mat3f &value);

    /**
     * Set the value of a uniform using data from a 4x4 Matrix.
     * (Might update uniform cache.)
     */
    void SetUniform (const std::string &name, const Mat4f &value);

private:
    GLuint m_id; // 0 == error/uninitialized
    std::vector<GLSLShader> m_shaders;
    std::unordered_map<std::string, GLint> m_uniforms;
};

// --------------------------------------------------------------------------

INLINE GLSLProgram &GLSLProgram::AddSource (const std::string &filename) {
    m_shaders.emplace_back(filename);

    return *this;
}

INLINE bool GLSLProgram::IsCompiled() const {
    return m_id > 0;
}

} /* namespace sge */

#endif /* __SGE_GLSLPROGRAM_H */
