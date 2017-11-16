//
// GLSL Shader Implementation
//
#include "../Engine.h"

#include <iostream>
#include <sstream>
#include <fstream>

namespace sge {

static
void printShaderInfoLog (const GLuint glslID) {
    GLsizei maxLength = 0;
    glGetShaderiv(glslID, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(glslID, maxLength, &maxLength, &errorLog[0]);

    std::copy(std::begin(errorLog), std::end(errorLog), std::ostream_iterator<char>(std::cout, ""));
}

static
bool checkCompileStatus(const GLuint glslID) {
    GLint success = 0;
    glGetShaderiv(glslID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        printShaderInfoLog(glslID);
        return false;
    }

    return true;
}

static
bool checkLinkStatus(const GLuint glslID) {
    GLint success = 0;
    glGetProgramiv(glslID, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        printShaderInfoLog(glslID);
        return false;
    }

    return true;
}

static
bool checkValidateStatus(const GLuint glslID) {
    GLint success = 0;
    glGetProgramiv(glslID, GL_VALIDATE_STATUS, &success);
    if (success == GL_FALSE) {
        printShaderInfoLog(glslID);
        return false;
    }

    return true;
}

/**
 * Attempt to detect the type of GLSL Shader based on file extension.
 */
static
GLuint DetectShaderType (const std::string &filename) {
    std::string ext = str::fileExt(filename);

    if ("vs" == ext || "vert" == ext) {
        return GL_VERTEX_SHADER;
    } else if ("gs" == ext || "geom" == ext) {
        return GL_GEOMETRY_SHADER;
    } else if ("fs" == ext || "frag" == ext) {
        return GL_FRAGMENT_SHADER;
    } else {
        console.Errorf("Unrecognized shader extension -- %s. Defaulting to vertex shader.\n", filename.c_str());
        return GL_VERTEX_SHADER;
    }
}

/**
 * Return a print friendly string for GL shader types.
 */
static
const char *ShaderTypeString (const GLenum shaderType) {
    switch (shaderType) {
    case GL_VERTEX_SHADER:
        return "vertex";
    case GL_FRAGMENT_SHADER:
        return "fragment";
    case GL_GEOMETRY_SHADER:
        return "geometry";
    default:
        return "unknown";
    }
}

static
std::string ReadShaderFile(const std::string &filename) {
    std::ifstream input(filename);
    if (!input) {
        console.Errorf("Unable to find source file: ", filename.c_str());
        return "";
    }

    std::stringstream src;
    std::string line;
    while (std::getline(input, line)) {
        src << line << "\n";
    }

    return src.str();
}

// --------------------------------------------------------------------------

//======================
// GLSLProgram
//======================

bool GLSLProgram::Compile () {
    GLuint newId = 0;

    if (IsCompiled()) {
        IF_DEBUG( console.Errorf("Recompiling GLSL Program %u\n", m_id); );
        newId = m_id;
    } else {
        newId = glCreateProgram();
    }

    if (0 == newId) {
        console.Error("Unable to assign GLSL Program ID.\n");
        return false;
    }

    console.Debugf("Compiling Program Sources (%d)\n", newId);

    for (auto &shader : m_shaders) {
        bool compiled = shader.Compile();

        if (!compiled) {
            console.Errorf("Error compiling shader: %s\n", shader.m_filename.c_str());
            Delete();
            glDeleteProgram(newId);
            return false;
        }

        glAttachShader(newId, shader.m_id);
    }

    glLinkProgram(newId);

    if (!checkLinkStatus(newId)) {
        console.Error("Failed to Link Shader.\n");
        Delete();
        glDeleteProgram(newId);
        return false;
    }

    m_id = newId;

    return true;
}

bool GLSLProgram::Validate () const {
    glValidateProgram(m_id);

    if (!checkValidateStatus(m_id))
    {
        console.Errorf("Failed to Validate Shader Program (%u)\n", m_id);
        return false;
    }

    return true;
}

void GLSLProgram::Bind () {
    if (!IsCompiled()) {
        console.Debugf("Warning: Attempted to use an uncompiled shader: %u\n", m_id);
        Compile();
    }

    glUseProgram(m_id);
}

void GLSLProgram::Delete () {
    for (auto &shader : m_shaders) {
        shader.Delete();
    }

    if (IsCompiled()) {
        glDeleteProgram(m_id);
        m_id = 0;
    }
}

GLint GLSLProgram::GetUniform (const std::string &name) {

    if (m_uniforms[name]) {
        return m_uniforms[name];
    }

    GLint uniformLocation = glGetUniformLocation(m_id, name.c_str());

    if (uniformLocation < 0) {
        console.Errorf("Uniform location does not exist: %s\n", name.c_str());
    } else {
        m_uniforms[name] = uniformLocation;
    }

    return uniformLocation;
}

void GLSLProgram::SetUniform (const std::string &name, const u32 value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniform1ui(u, value);
    }
}

void GLSLProgram::SetUniform (const std::string &name, const float value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniform1f(u, value);
    }
}

void GLSLProgram::SetUniform (const std::string &name, const Vec2f &value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniform2f(u, value.x, value.y);
    }
}

void GLSLProgram::SetUniform (const std::string &name, const Vec3f &value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniform3f(u, value.x, value.y, value.z);
    }
}

void GLSLProgram::SetUniform (const std::string &name, const Vec4f &value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniform4f(u, value.x, value.y, value.z, value.w);
    }
}

void GLSLProgram::SetUniform (const std::string &name, const Mat2f &value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniformMatrix2fv(u, 1, false, reinterpret_cast<const GLfloat*>(&value));
    }
}

void GLSLProgram::SetUniform (const std::string &name, const Mat3f &value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniformMatrix3fv(u, 1, false, reinterpret_cast<const GLfloat*>(&value));
    }
}

void GLSLProgram::SetUniform (const std::string &name, const Mat4f &value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniformMatrix4fv(u, 1, false, reinterpret_cast<const GLfloat*>(&value));
    }
}

void GLSLProgram::BindUniformBuffer (const std::string &name, const GLuint buffer, const GLuint bindingPoint) {
    GLuint blockIdx = glGetUniformBlockIndex(m_id, name.c_str());
    if (GL_INVALID_INDEX == blockIdx) {
        std::cerr << "Invalid Uniform Buffer Block: " << name << "\n";
        return;
    }

    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer);
    glUniformBlockBinding(m_id, blockIdx, bindingPoint);
}

//======================
// GLSLShader
//======================

GLSLShader::GLSLShader(const std::string &filename) {
    m_type = DetectShaderType(filename);
    m_filename = filename;
}

//======================================================================
// Compile a shader source file
// return the shader id if successful, or 0 if errors were encountered.
//======================================================================

GLuint GLSLShader::Compile() {
    GLuint newId = 0;

    std::string source = ReadShaderFile(m_filename);
    if (source.empty()) {
        console.Errorf(" Shader source is empty: %s\n", m_filename.c_str());
        return 0;
    }

    if (IsCompiled()) {
        newId = m_id;
    } else {
        newId = glCreateShader(m_type);
    }

    if (newId <= 0) {
        console.Errorf(" Unable to assign new Shader ID: %s\n", m_filename.c_str());
        return 0;
    }

    console.Debugf(" Compiling %s shader (%u): %s\n",
                   ShaderTypeString(m_type), newId, m_filename.c_str());

    const char *src = source.c_str();
    glShaderSource(newId, 1, &src, nullptr);
    glCompileShader(newId);

    if (!checkCompileStatus(newId)) {
        console.Errorf(" Failed to compile shader: %s\n", m_filename.c_str());
        glDeleteShader(newId);
        return 0;
    }

    m_id = newId;

    return m_id;
}

void GLSLShader::Delete () {
    if (IsCompiled()) {
        glDeleteShader(m_id);
        m_id = 0;
    }
}

} /* namespace sge */
