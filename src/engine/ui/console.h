/*---  Console.h - Engine IO Console Header  ----------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief A class for Input/Output not tied to stdout... maybe.
 */
#ifndef __SGE_CONSOLE_H
#define __SGE_CONSOLE_H

namespace sge {

class Console {
public:

    /**
     * Log an error.
     */
    void error (const char *msg);

    /**
     * Log a formatted error.
     */
    void errorf (const char *const fmt, ...);

#ifndef NDEBUG
    /**
     * Print a simple string.
     */
    void debug (const char *msg);

    /**
     * Print a formatted string.
     */
    void debugf (const char *const fmt, ...);
#else
    void debug (const char *msg) {}
    void debugf (const char * const fmt, ...) {}
#endif /* !NDEBUG */

};

// Global console
extern Console gConsole;

} /* namespace sge */

#endif /* __SGE_CONSOLE_H */
