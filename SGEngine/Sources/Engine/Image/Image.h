/*---  Image.h - Image Header  -------------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 * 
 * @brief Defines a class for Managing Texture IDs.
 */
#ifndef __SHENGINE_IMAGE_H_
#define __SHENGINE_IMAGE_H_

#include <string>

namespace sge {

/**
 * Image/Texture class. Load an image from a
 * file, store the assigned Texture ID and bind textures.
 */
class Image {
public:
    Image(const std::string &filename);

    /**
     * Make this the active texture.
     */
    void Bind() const;

    /**
     * Use nearest pixel filtering when drawing texture.
     */
    void SetFilterNearest ();

    /**
     * Use linear filtering when drawing texture.
     */
    void SetFilterLinear ();

    /**
     * Set Whether the texture should be repeated and mirrored on both axes.
     *
     * @param repeat Enabled repeating texture.
     * @param mirror Repeated texture will be alternately mirrored.
     */
    void SetRepeat (const bool repeat, const bool mirror = false);

    /**
     * Set Whether the texture should be repeated and mirrored on the X axis.
     *
     * @param repeat Enabled repeating texture.
     * @param mirror Repeated texture will be alternately mirrored.
     */
    void SetRepeatX (const bool repeat, const bool mirror = false);

    /**
     * Set Whether the texture should be repeated and mirrored on the Y axis.
     *
     * @param repeat Enabled repeating texture.
     * @param mirror Repeated texture will be alternately mirrored.
     */
    void SetRepeatY (const bool repeat, const bool mirror = false);

private:
    GLuint m_id;
    GLenum m_repeat[2];
    GLenum m_filter;
    bool m_initialized;
};

// --------------------------------------------------------------------------

inline void Image::SetFilterNearest () {
    m_filter = GL_NEAREST;
}

inline void Image::SetFilterLinear () {
    m_filter = GL_LINEAR;
}

inline void Image::SetRepeat (const bool repeat, const bool mirror) {
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

inline void Image::SetRepeatX (const bool repeat, const bool mirror) {
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

inline void Image::SetRepeatY (const bool repeat, const bool mirror) {
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

#endif /* __SHENGINE_IMAGE_H_  */