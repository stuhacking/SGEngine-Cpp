/*---  Input.h - SDL2 Realtime Input Header  ----------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 * 
 * @brief Define wrapper for querying keyboard and mouse state from SDL2.
 */
#ifndef __SHENGINE_INPUT_H_
#define __SHENGINE_INPUT_H_

#include <SDL2/SDL.h>

namespace sge {

class Input {
public:
    /**
     * Poll the internal SDL2 Event Queue and update the
     * current mouse and keyboard state.
     * Should be called once per frame, or once per input
     * poll in your application.
     */
    static void Update ();

    /**
     * Test if a keyCode is currently being held. Use for continuous
     * input.
     */
    static bool KeyDown (const SDL_Keycode keyCode);

    /**
     * Test if a keyCode was pressed in the previous Update. Use for
     * single presses.
     */
    static bool KeyPressed (const SDL_Keycode keyCode);

    /**
     * Test if a keyCode was released in the previous Update.
     * Use for single presses.
     */
    static bool KeyReleased (const SDL_Keycode keyCode);

    /**
     * Capture the mouse pointer.
     */
    static void LockMouse ();

    /**
     * Release the mouse pointer.
     */
    static void ReleaseMouse ();

    /**
     * Check if the mouse is currently locked.
     */
    static bool MouseLocked ();
    
    /**
     * Get the current position (in top-left origin window coordinates)
     * of the mouse cursor
     */
    static Vector2 GetMousePosition ();

    /**
     * Get the relative position of the mouse since the last time
     * Input was updated.
     */
    static Vector2 GetMouseDelta ();

    /**
     * Test if the given mouse button is currently held. Use for
     * continuous input.
     */
    static bool MouseDown (const u32 button);

    /**
     * Test if the given mouse button was pressed in the previous
     * update. Use for single clicks.
     */
    static bool MousePressed (const u32 button);

    /**
     * Test if the given mouse button was released in the previous
     * update. Use for single clicks.
     */
    static bool MouseReleased (const u32 button);

    /**
     * Check if the user has sent an SDL_QUIT event by clicking
     * the window close button.
     */
    static bool SignalQuit ();
};

} /* namespace sge */

#endif /* __SHENGINE_INPUT_H_ */
