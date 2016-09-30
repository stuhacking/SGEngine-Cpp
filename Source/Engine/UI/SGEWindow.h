/*---  SGEWindow.h - Application Window Header  --------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Define a Window class to initialize the GL/SDL context.
 */
#ifndef __SGE_SGEWINDOW_H
#define __SGE_SGEWINDOW_H

#include <string>

namespace sge {

/**
 * Initialize the context for an application using SGEngine. This must
 * be called to initialize the back-end graphics system.
 */
bool InitSGEApplication (const std::string name, const u32 width, const u32 height,
                      const bool fullScreen = false);

class SGEWindow {
public:

    bool IsInitialized () const;

    u32 GetWidth () const;

    u32 GetHeight () const;

    virtual void Update () const = 0;

    virtual void Delay (u32 period) const = 0;

    /**
     * Set the clear color of the rendering back-end.
     */
    virtual void SetClearColor (const float r, const float g, const float b,
                        const float a = 1.0f) const = 0;

    /**
     * Clear contents of the panel using the rendering back-end.
     */
    virtual void Clear () const = 0;

    /**
     * Get the center of this window in window coordinates
     * (top-left origin).
     */
    Vec2f Center () const;

protected:
    bool m_initialized;
    u32 m_width;
    u32 m_height;
    std::string m_name;
};

// Global Window
extern SGEWindow *window;

// --------------------------------------------------------------------------

INLINE bool SGEWindow::IsInitialized () const {
    return m_initialized;
}

INLINE u32 SGEWindow::GetWidth () const {
    return m_width;
}

INLINE u32 SGEWindow::GetHeight () const {
    return m_height;
}

INLINE Vec2f SGEWindow::Center () const {
    return Vec2f(m_width / 2, m_height / 2);
}

} /* namespace sge */

#endif /* __SGE_SGEWINDOW_H  */
