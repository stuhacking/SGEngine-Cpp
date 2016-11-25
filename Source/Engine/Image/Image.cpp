//
// Image loader.
//
// FIXME: Support for Indexed files or files that aren't 3-4 Bytes per pixel.
//
#include "../Engine.h"

#include <SOIL.h>

#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

namespace sge {

u32 Image::MaxTextureDimension () {
    i32 result;

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &result);

    return static_cast<u32>(result);
}

//======================
// Image Methods
//======================
Image::Image(const char * const filename) {
    m_repeat[0] = m_repeat[1] = GL_CLAMP_TO_BORDER;
    m_filter = GL_LINEAR;

    m_id = SOIL_load_OGL_texture(filename,
                                 SOIL_LOAD_AUTO,
                                 SOIL_CREATE_NEW_ID,
                                 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    if (0 == m_id) {
        console.Errorf("SOIL loading error: '%s'\n", SOIL_last_result());
    }
}

void Image::Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_repeat[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_repeat[1]);
}

void Image::SetRepeat (const bool repeat, const bool mirror) {
    if (repeat) {
        if (mirror) {
            m_repeat[0] = m_repeat[1] = GL_MIRRORED_REPEAT;
        } else {
            m_repeat[0] = m_repeat[1] = GL_REPEAT;
        }
    } else {
        m_repeat[0] = m_repeat[1] = GL_CLAMP_TO_BORDER;
    }
}

void Image::SetRepeatX (const bool repeat, const bool mirror) {
    if (repeat) {
        if (mirror) {
            m_repeat[0] = GL_MIRRORED_REPEAT;
        } else {
            m_repeat[0] = GL_REPEAT;
        }
    } else {
        m_repeat[0] = GL_CLAMP_TO_BORDER;
    }
}

void Image::SetRepeatY (const bool repeat, const bool mirror) {
    if (repeat) {
        if (mirror) {
            m_repeat[1] = GL_MIRRORED_REPEAT;
        } else {
            m_repeat[1] = GL_REPEAT;
        }
    } else {
        m_repeat[1] = GL_CLAMP_TO_BORDER;
    }
}

} /* namespace sge */
