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
#ifndef __SGE_IMAGE_H
#define __SGE_IMAGE_H

#include <string>

namespace sge {

/**
 * Image/Texture class. Load an image from a
 * file, store the assigned Texture ID and bind textures.
 */
class Image {
public:
    static u32 MaxTextureDimension ();

public:
    Image(const char * const filename);

    /**
     * Make this the active texture.
     */
    void Bind() const;

    /**
     * Use nearest pixel filtering when drawing texture.
     */
    void SetFilterNearest () { m_filter = GL_NEAREST; }

    /**
     * Use linear filtering when drawing texture.
     */
    void SetFilterLinear () { m_filter = GL_LINEAR; }

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
};

} /* namespace sge */

#endif /* __SGE_IMAGE_H  */
