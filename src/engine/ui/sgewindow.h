/*---  SGEWindow.h - Application Window Header  --------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Define a Window class to initialize the gl/SDL context.
 */
#ifndef __SGE_SGEWINDOW_H
#define __SGE_SGEWINDOW_H

namespace sge {

/**
 * Initialize the context for an application using SGEngine. This must
 * be called to initialize the back-end graphics system.
 */
bool initSGEApplication (const char *const pTitle,
                         const u32 pWidth, const u32 pHeight,
                         const bool pFullScreen = false);

class SGEWindow {
public:

    /** Check if window and graphics context are ready. */
    bool isInitialized () const { return mInitialized; }

    /** Get current window width. */
    u32 width () const { return mWidth; }

    /** Get current window height. */
    u32 height () const { return mHeight; }

    /**
     * Get the center of this window in window coordinates
     * (top-left origin).
     */
    Vec2f center () const { return Vec2f(mWidth / 2, mHeight / 2); }

    /**
     * Tell graphics backend to update window contents.
     */
    virtual void update () const = 0;

    /**
     * Tell graphics backend to wait for a period of time
     * in milliseconds.
     *
     * @param period Duration of wait in milliseconds.
     */
    virtual void delay (u32 period) const = 0;

    /**
     * Tell graphics backend to clear the window contents.
     */
    virtual void clear () const = 0;

protected:
    u32 mWidth;
    u32 mHeight;
    bool mInitialized; /** False if the window is unusable. */
};

// Global Window
extern SGEWindow *gWindow;

} /* namespace sge */

#endif /* __SGE_SGEWINDOW_H  */
