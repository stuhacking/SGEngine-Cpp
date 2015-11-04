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
#ifndef __SHENGINE_SGEWINDOW_h_
#define __SHENGINE_SGEWINDOW_h_

#include <SDL2/SDL.h>
#include <string>

namespace sge {

class SGEWindow {
public:
    /**
     * Create a new window and initialize the SDL and OpenGL contexts.
     */
    SGEWindow (const std::string &name, const u32 w, const u32 h,
               const bool fullScreen = false);

    /**
     * Destroy SDL subsystems and free up pointers.
     */
    ~SGEWindow ();

    bool IsInitialized () const;

    u32 GetWidth () const;

    u32 GetHeight () const;

    void Update () const;

    void Delay (u32 period) const;

    /**
     * Set the clear color of the rendering back-end.
     */
    void SetClearColor (const float r, const float g, const float b,
                        const float a = 1.0f) const;

    /**
     * Clear contents of the panel using the rendering back-end.
     */
    void Clear () const;

    /**
     * Get the center of this window in window coordinates
     * (top-left origin).
     */
    Vector2 Center () const;
    
private:
    SDL_Window *window;
    bool m_initialized;
    u32 m_width;
    u32 m_height;
    std::string m_name;
};

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
    return Vector2(m_width * 0.5f, m_height * 0.5f);
}

} /* namespace sge */

#endif /* __SHENGINE_SGEWINDOW_h_  */
