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
#ifndef __SGENGINE_SGEWINDOW_h_
#define __SGENGINE_SGEWINDOW_h_

#include <string>

namespace sge {

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
    Vector2 Center () const;

protected:
    bool m_initialized;
    u32 m_width;
    u32 m_height;
    std::string m_name;
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

inline Vector2 SGEWindow::Center () const {
    return Vector2(m_width / 2, m_height / 2);
}

} /* namespace sge */

#endif /* __SGENGINE_SGEWINDOW_h_  */
