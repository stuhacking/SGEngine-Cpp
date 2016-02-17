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
#ifndef __SGENGINE_INPUT_H_
#define __SGENGINE_INPUT_H_

#include <SDL2/SDL.h>

namespace sge {

class Input {
public:
    /* Define our own common key codes to avoid exposing
       SDL specifics. */
    enum Key : SDL_Keycode {
        Space = SDLK_SPACE,
        Escape = SDLK_ESCAPE,
        Backspace = SDLK_BACKSPACE,
        Return = SDLK_RETURN,
        KeypadEnter = SDLK_KP_ENTER,
        Insert = SDLK_INSERT,
        Delete = SDLK_DELETE,
        End = SDLK_END,
        Home = SDLK_HOME,
        PageUp = SDLK_PAGEUP,
        PageDown = SDLK_PAGEDOWN,
        Pause = SDLK_PAUSE,
        Print = SDLK_PRINTSCREEN,
        LCtrl = SDLK_LCTRL,
        RCtrl = SDLK_RCTRL,
        Alt = SDLK_LALT,
        AltGr = SDLK_RALT,
        LShift = SDLK_LSHIFT,
        RShift = SDLK_RSHIFT,
        Tab = SDLK_TAB,
        Up = SDLK_UP,
        Down = SDLK_DOWN,
        Left = SDLK_LEFT,
        Right = SDLK_RIGHT
    };

public:
    /**
     * Poll the internal SDL2 Event Queue and update the
     * current mouse and keyboard state.
     * Should be called once per frame, or once per input
     * poll in your application.
     */
    static void Update ();

    /**
     * Test if a key code is currently being held. Use for continuous
     * input.
     */
    static bool KeyDown (const Key keyCode);

    /**
     * Test is a character key is currently being held. Test is
     * case insensitive.
     */
    static bool KeyDown (const char keyCode);

    /**
     * Test if a key code was pressed in the previous Update. Use for
     * single presses.
     */
    static bool KeyPressed (const Key keyCode);

    /**
     * Test if a character key has been pressed in the previous
     * update. Case insensitive.
     */
    static bool KeyPressed (const char keyCode);

    /**
     * Test if a key code was released in the previous Update.
     * Use for single presses.
     */
    static bool KeyReleased (const Key keyCode);

    /**
     * Test if a character key was released in the previous update.
     * Case insensitive
     */
    static bool KeyReleased (const char keyCode);

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

#endif /* __SGENGINE_INPUT_H_ */
