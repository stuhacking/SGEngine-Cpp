/*---  Console.h - Engine IO Console Header  ----------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief A class for Input/Output not tied to stdout.
 */
#ifndef __SGENGINE_CONSOLE_H_
#define __SGENGINE_CONSOLE_H_

namespace sge {

#ifndef NDEBUG

class Console {
public:
    /**
     * Print a simple string.
     */
    void Print (const char *msg);

    /**
     * Print a formatted string.
     */
    void Printf (const char *fmt, ...);
};

#else

class Console {
public:
    void Print (const char *msg) {}
    void Printf (const char *fmt, ...) {}
};

#endif /* !NDEBUG */

// Global console
extern Console console;

} /* namespace sge */

#endif /* __SGENGINE_CONSOLE_H_ */
