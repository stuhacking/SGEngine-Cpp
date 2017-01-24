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
bool InitSGEApplication (const char * const name, const u32 width, const u32 height,
                      const bool fullScreen = false);

class SGEWindow {
public:

    /** Check if window and graphics context are ready. */
    bool IsInitialized () const;

    /** Get current window width. */
    u32 GetWidth () const;

    /** Get current window height. */
    u32 GetHeight () const;

    /**
     * Get the center of this window in window coordinates
     * (top-left origin).
     */
    Vec2f Center () const;

    /**
     * Tell graphics backend to update window contents.
     */
    virtual void Update () const = 0;

    /**
     * Tell graphics backend to wait for a period of time
     * in milliseconds.
     *
     * @param period Duration of wait in milliseconds.
     */
    virtual void Delay (u32 period) const = 0;

    /**
     * Tell graphics backend to clear the window contents.
     */
    virtual void Clear () const = 0;

protected:
    std::string m_name;
    u32 m_width;
    u32 m_height;
    bool m_initialized; /** False if the window is unusable. */
};

// Global Window
extern SGEWindow *window;

// --------------------------------------------------------------------------

inline bool SGEWindow::IsInitialized () const {
    return m_initialized;
}

inline u32 SGEWindow::GetWidth () const {
    return m_width;
}

inline u32 SGEWindow::GetHeight () const {
    return m_height;
}

inline Vec2f SGEWindow::Center () const {
    return Vec2f(m_width / 2, m_height / 2);
}

} /* namespace sge */

#endif /* __SGE_SGEWINDOW_H  */
