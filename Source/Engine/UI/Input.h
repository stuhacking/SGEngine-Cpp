/*---  Input.h - Real-time Input Header  --------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Define wrapper for querying keyboard and mouse state.
 */
#ifndef __SGE_INPUT_H
#define __SGE_INPUT_H

namespace sge {

class Input {
public:
    /**
     * Enumerate special Key Codes which can be mapped onto
     * implementation specific codes depending on backend.
     */
    enum Key : u8 {
        Space = 0,
        Escape = 1,
        Backspace = 2,
        Return = 3,
        KeypadEnter = 4,
        Insert = 5,
        Delete = 6,
        End = 7,
        Home = 8,
        PageUp = 9,
        PageDown = 10,
        Pause = 11,
        Print = 12,
        LCtrl = 13,
        RCtrl = 14,
        Alt = 15,
        AltGr = 16,
        LShift = 17,
        RShift = 18,
        Tab = 19,
        Up = 20,
        Down = 21,
        Left = 22,
        Right = 23
    };

public:

    /**
     * Initialize input handling.
     */
    static void Init ();

    /**
     * Poll the internal input Event Queue and update the
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
    static Vec2f GetMousePosition ();

    /**
     * Get the relative position of the mouse since the last time
     * Input was updated.
     */
    static Vec2f GetMouseDelta ();

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
     * Check if the window manager has sent a QUIT event.
     */
    static bool SignalQuit ();
};

} /* namespace sge */

#endif /* __SGE_INPUT_H */
