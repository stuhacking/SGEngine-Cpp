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
    GLSLProgram() : mId(0) { }

    GLSLProgram &AddSource (const std::string &filename);

    /**
     * Allocate a shader program ID for this program, and compile child shaders.
     * Release all IDs if any component shader fails.
     *
     * @return true if compilation was successful, otherwise false.
     */
    bool compile ();

    bool validate () const;

    /**
     * Make this the active shader program.
     */
    void bind ();

    /**
     * Check if this shader program is compiled.
     *
     * @return true if shader is compiled, otherwise false.
     */
    bool isCompiled () const;

    void destroy ();

    /**
     * Lookup the address of a shader uniform variable.
     * (Might update a cache.)
     */
    GLint uniform (const std::string &pName);

    /**
     * Set the value of a uniform using an unsigned int.
     * (Might update uniform cache.)
     */
    void setUniform (const std::string &pName, const u32 pVal);

    /**
     * Set the value of a uniform using a float.
     * (Might update uniform cache.)
     */
    void setUniform (const std::string &pName, const float pVal);

    /**
     * Set the value of a uniform using data from a Vec2f.
     * (Might update uniform cache.)
     */
    void setUniform (const std::string &pName, const Vec2f &pVal);

    /**
     * Set the value of a uniform using data from a Vec3f.
     * (Might update uniform cache.)
     */
    void setUniform (const std::string &pName, const Vec3f &pVal);

    /**
     * Set the value of a uniform using data from a Vec4f.
     * (Might update uniform cache.)
     */
    void setUniform (const std::string &pName, const Vec4f &pVal);

    /**
     * Set the value of a uniform using data from a 2x2 Matrix.
     * (Might update uniform cache.)
     */
    void setUniform (const std::string &pName, const Mat2f &pVal);

    /**
     * Set the value of a uniform using data from a 3x3 Matrix.
     * (Might update uniform cache.)
     */
    void setUniform (const std::string &pName, const Mat3f &pVal);

    /**
     * Set the value of a uniform using data from a 4x4 Matrix.
     * (Might update uniform cache.)
     */
    void setUniform (const std::string &pName, const Mat4f &pVal);

    /**
     * Bind a Uniform Buffer Object as data for this shader.
     * @param pName Name of the Interface Block in the shader source.
     * @param pBuffer ID of the buffer object to bind.
     * @param pBindPoint Slot to store the interface and buffer binding.
     */
    void bindUniformBuffer (const std::string &pName, const GLuint pBuffer,
                            const GLuint pBindPoint = 1);

private:
    GLuint mId; // 0 == error/uninitialized
    std::vector<GLSLShader> mShaders;
    std::unordered_map<std::string, GLint> mUniforms;
};

// --------------------------------------------------------------------------

inline GLSLProgram &GLSLProgram::AddSource (const std::string &filename) {
    mShaders.emplace_back(filename);

    return *this;
}

inline bool GLSLProgram::isCompiled () const {
    return mId > 0;
}

} /* namespace sge */

#endif /* __SGE_GLSLPROGRAM_H */
