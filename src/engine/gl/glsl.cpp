//
// GLSL Shader Implementation
//
#include "../engine.h"

#include <cstdio>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>

namespace sge {

static
void printShaderInfoLog (const GLuint pId) {
    GLsizei bufLen = 0;
    glGetShaderiv(pId, GL_INFO_LOG_LENGTH, &bufLen);

    // The maxLength includes the NULL character
    std::unique_ptr<char[]> buf = std::make_unique<char[]>(bufLen);
    glGetShaderInfoLog(pId, bufLen, &bufLen, buf.get());

    fprintf(stderr, "Shader compile error:\n%s\n", buf.get());
}

static
bool checkCompileStatus(const GLuint pId) {
    GLint success = 0;
    glGetShaderiv(pId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        return false;
    }

    return true;
}

static
bool checkLinkStatus(const GLuint pId) {
    GLint success = 0;
    glGetProgramiv(pId, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        return false;
    }

    return true;
}

static
bool checkValidateStatus(const GLuint pId) {
    GLint success = 0;
    glGetProgramiv(pId, GL_VALIDATE_STATUS, &success);
    if (success == GL_FALSE) {
        return false;
    }

    return true;
}

/**
 * Attempt to detect the type of GLSL Shader based on file extension.
 */
static
GLuint detectShaderType (const std::string &pFilename) {
    std::string ext = str::fileExt(pFilename);

    if ("vs" == ext || "vert" == ext) {
        return GL_VERTEX_SHADER;
    } else if ("gs" == ext || "geom" == ext) {
        return GL_GEOMETRY_SHADER;
    } else if ("fs" == ext || "frag" == ext) {
        return GL_FRAGMENT_SHADER;
    } else {
        gConsole.errorf(
                "Unrecognized shader extension -- %s. Defaulting to vertex shader.\n",
                pFilename.c_str());
        return GL_VERTEX_SHADER;
    }
}

/**
 * Return a print friendly string for GL shader types.
 */
static
const char* shaderTypeString (const GLenum pShaderType) {
    switch (pShaderType) {
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
std::string readShaderFile (const std::string &filepName) {
    std::ifstream input(filepName);
    if (!input) {
        gConsole.errorf("Unable to find source file: ", filepName.c_str());
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

bool GLSLProgram::compile () {
    GLuint newId = 0;

    if (isCompiled()) {
        IF_DEBUG(gConsole.errorf("Recompiling GLSL Program %u\n", mId); );
        newId = mId;
    } else {
        newId = glCreateProgram();
    }

    if (0 == newId) {
        gConsole.error("Unable to assign GLSL Program ID.\n");
        return false;
    }

    gConsole.debugf("Compiling Program Sources (%d)\n", newId);

    for (auto &shader : mShaders) {
        bool compiled = shader.compile();

        if (!compiled) {
            gConsole.errorf("Error compiling shader: %s\n",
                           shader.mFilename.c_str());
            destroy();
            glDeleteProgram(newId);
            return false;
        }

        glAttachShader(newId, shader.mId);
    }

    glLinkProgram(newId);

    if (!checkLinkStatus(newId)) {
        gConsole.error("Failed to Link Shader.\n");
        printShaderInfoLog(newId);
        destroy();
        glDeleteProgram(newId);
        return false;
    }

    mId = newId;

    return true;
}

bool GLSLProgram::validate () const {
    glValidateProgram(mId);

    if (!checkValidateStatus(mId))
    {
        gConsole.errorf("Failed to Validate Shader Program (%u)\n", mId);
        return false;
    }

    return true;
}

void GLSLProgram::bind () {
    if (!isCompiled()) {
        gConsole.debugf("Warning: Attempted to use an uncompiled shader: %u\n",
                       mId);
        compile();
    }

    glUseProgram(mId);
}

void GLSLProgram::destroy () {
    for (auto &shader : mShaders) {
        shader.destroy();
    }

    if (isCompiled()) {
        glDeleteProgram(mId);
        mId = 0;
    }
}

GLint GLSLProgram::uniform (const std::string &pName) {

    if (mUniforms[pName]) {
        return mUniforms[pName];
    }

    GLint uniformLocation = glGetUniformLocation(mId, pName.c_str());

    if (uniformLocation < 0) {
        gConsole.errorf("Uniform location does not exist: %s\n", pName.c_str());
    } else {
        mUniforms[pName] = uniformLocation;
    }

    return uniformLocation;
}

void GLSLProgram::setUniform (const std::string &pName, const u32 pVal) {
    GLint u = uniform(pName);

    if (u >= 0) {
        glUniform1ui(u, pVal);
    }
}

void GLSLProgram::setUniform (const std::string &pName, const float pVal) {
    GLint u = uniform(pName);

    if (u >= 0) {
        glUniform1f(u, pVal);
    }
}

void GLSLProgram::setUniform (const std::string &pName, const Vec2f &pVal) {
    GLint u = uniform(pName);

    if (u >= 0) {
        glUniform2f(u, pVal.x, pVal.y);
    }
}

void GLSLProgram::setUniform (const std::string &pName, const Vec3f &pVal) {
    GLint u = uniform(pName);

    if (u >= 0) {
        glUniform3f(u, pVal.x, pVal.y, pVal.z);
    }
}

void GLSLProgram::setUniform (const std::string &pName, const Vec4f &pVal) {
    GLint u = uniform(pName);

    if (u >= 0) {
        glUniform4f(u, pVal.x, pVal.y, pVal.z, pVal.w);
    }
}

void GLSLProgram::setUniform (const std::string &pName, const Mat2f &pVal) {
    GLint u = uniform(pName);

    if (u >= 0) {
        glUniformMatrix2fv(u, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&pVal));
    }
}

void GLSLProgram::setUniform (const std::string &pName, const Mat3f &pVal) {
    GLint u = uniform(pName);

    if (u >= 0) {
        glUniformMatrix3fv(u, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&pVal));
    }
}

void GLSLProgram::setUniform (const std::string &pName, const Mat4f &pVal) {
    GLint u = uniform(pName);

    if (u >= 0) {
        glUniformMatrix4fv(u, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&pVal));
    }
}

void GLSLProgram::bindUniformBuffer (const std::string &pName,
                                     const GLuint pBuffer,
                                     const GLuint pBindPoint) {
    GLuint blockIdx = glGetUniformBlockIndex(mId, pName.c_str());
    if (GL_INVALID_INDEX == blockIdx) {
        std::cerr << "Invalid Uniform Buffer Block: " << pName << "\n";
        return;
    }

    glBindBufferBase(GL_UNIFORM_BUFFER, pBindPoint, pBuffer);
    glUniformBlockBinding(mId, blockIdx, pBindPoint);
}

//======================
// GLSLShader
//======================

GLSLShader::GLSLShader(const std::string &pFilename) {
    mType = detectShaderType(pFilename);
    mFilename = pFilename;
}

//======================================================================
// compile a shader source file
// return the shader id if successful, or 0 if errors were encountered.
//======================================================================

bool GLSLShader::compile () {
    GLuint newId = 0;

    std::string source = readShaderFile(mFilename);
    if (source.empty()) {
        gConsole.errorf(" Shader source is empty: %s\n", mFilename.c_str());
        return false;
    }

    if (isCompiled()) {
        newId = mId;
    } else {
        newId = glCreateShader(mType);
    }

    if (newId <= 0) {
        gConsole.errorf(" Unable to assign new Shader ID: %s\n",
                       mFilename.c_str());
        return false;
    }

    gConsole.debugf(" Compiling %s shader (%u): %s\n",
                    shaderTypeString(mType), newId, mFilename.c_str());

    const char *src = source.c_str();
    glShaderSource(newId, 1, &src, nullptr);
    glCompileShader(newId);

    if (!checkCompileStatus(newId)) {
        gConsole.errorf(" Failed to compile shader: %s\n", mFilename.c_str());
        printShaderInfoLog(newId);
        glDeleteShader(newId);
        return false;
    }

    mId = newId;

    return true;
}

void GLSLShader::destroy () {
    if (isCompiled()) {
        glDeleteShader(mId);
        mId = 0;
    }
}

} /* namespace sge */
