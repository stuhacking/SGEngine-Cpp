//
// GLSL Shader Implementation
//
#include "../Engine.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace sge {

static
void printShaderInfoLog (const GLuint glslID) {
    GLint maxLength = 0;
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
    std::string ext = String::FileExtension(filename);

    if ("vs" == ext || "vert" == ext) {
        return GL_VERTEX_SHADER;
    } else if ("gs" == ext || "geom" == ext) {
        return GL_GEOMETRY_SHADER;
    } else if ("fs" == ext || "frag" == ext) {
        return GL_FRAGMENT_SHADER;
    } else {
        std::cerr << "GLSL Error: Unrecognized shader extension -- "
                  << filename << "\nDefaulting to Vertex Shader.\n";
        return GL_VERTEX_SHADER;
    }
}

static
std::string ShaderTypeString (const GLenum shaderType) {
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
        std::cerr << "Unable to find source file: " << filename << "\n";
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
    int a_id = 0;

    if (IsCompiled()) {
#ifndef NDEBUG
        std::cerr << "Recompiling GLSL Program " << a_id << "\n";
#endif
    } else {
        a_id = glCreateProgram();
    }

    if (0 == a_id) {
        std::cerr << "Unable to assign GLSL Program ID.\n";
        return false;
    }

    DEBUG( std::cout << "Compiling Program Sources (" << a_id << ")\n"; );

    for (auto &shader : m_shaders) {
        bool compiled = shader.Compile();

        if (!compiled) {
            std::cerr << "Error compiling shader: " << shader.m_filename << "\n";
            Delete();
            glDeleteProgram(a_id);
            return false;
        }

        glAttachShader(a_id, shader.m_id);
    }

    glLinkProgram(a_id);

    if (!checkLinkStatus(a_id)) {
        std::cerr << "Failed to Link Shader.\n";
        Delete();
        glDeleteProgram(a_id);
        a_id = 0;
        return false;
    }

    m_id = a_id;

    return true;
}

bool GLSLProgram::Validate () const {
    glValidateProgram(m_id);

    if (!checkValidateStatus(m_id))
    {
    	std::cerr << "Failed to Validate Shader Program (" << m_id << ")\n";
        return false;
    }

    return true;
}

void GLSLProgram::Bind () {
    if (!IsCompiled()) {
        std::cerr << "Warning: Attempted to use an uncompiled shader: " << m_id << "\n";
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

    int uniformLocation = glGetUniformLocation(m_id, name.c_str());

    if (uniformLocation < 0) {
        std::cerr << "Uniform location does not exist: " << name << "\n";
    } else {
        m_uniforms[name] = uniformLocation;
    }

    return uniformLocation;
}

void GLSLProgram::SetUniform (const std::string &name, const float value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniform1f(u, value);
    }
}

void GLSLProgram::SetUniform (const std::string &name, const Vector2 &value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniform2f(u, value.x, value.y);
    }
}

void GLSLProgram::SetUniform (const std::string &name, const Vector3 &value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniform3f(u, value.x, value.y, value.z);
    }
}

void GLSLProgram::SetUniform (const std::string &name, const Vector4 &value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniform4f(u, value.x, value.y, value.z, value.w);
    }
}

void GLSLProgram::SetUniform (const std::string &name, const Matrix2 &value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniformMatrix2fv(u, 1, false, reinterpret_cast<const GLfloat*>(&value));
    }
}

void GLSLProgram::SetUniform (const std::string &name, const Matrix3 &value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniformMatrix3fv(u, 1, false, reinterpret_cast<const GLfloat*>(&value));
    }
}

void GLSLProgram::SetUniform (const std::string &name, const Matrix4 &value) {
    GLint u = GetUniform(name);

    if (u >= 0) {
        glUniformMatrix4fv(u, 1, false, reinterpret_cast<const GLfloat*>(&value));
    }
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

int GLSLShader::Compile() {
    int a_id = 0;

    std::string source = ReadShaderFile(m_filename);
    if (source.empty()) {
        std::cerr << " Shader source is empty: " << m_filename << "\n";
        return 0;
    }

    a_id = glCreateShader(m_type);

    if (a_id <= 0) {
        std::cerr << " Unable to assign new Shader ID: " << m_filename << "\n";
        return 0;
    }

    std::cout << " Compiling " << ShaderTypeString(m_type) << " Shader ("
              << a_id << "): " << m_filename << "\n";

    const char *src = source.c_str();
    glShaderSource(a_id, 1, &src, nullptr);
    glCompileShader(a_id);

    if (!checkCompileStatus(a_id)) {
        std::cerr << " Failed to compile shader: " << m_filename << "\n";
        glDeleteShader(a_id);
        return 0;
    }

    m_id = a_id;

    return m_id;
}

void GLSLShader::Delete () {
    if (IsCompiled()) {
        glDeleteShader(m_id);
        m_id = 0;
    }
}

} /* namespace sge */
