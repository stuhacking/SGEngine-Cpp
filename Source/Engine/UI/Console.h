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
#ifndef __SGE_CONSOLE_H
#define __SGE_CONSOLE_H

namespace sge {

class Console {
public:

    /**
     * Log an error.
     */
    void Error (const char *msg);

    /**
     * Log a formatted error.
     */
    void Errorf (const char * const fmt, ...);

#ifndef NDEBUG
    /**
     * Print a simple string.
     */
    void Debug (const char *msg);

    /**
     * Print a formatted string.
     */
    void Debugf (const char * const fmt, ...);
#else
    void Debug (const char *msg) {}
    void Debugf (const char * const fmt, ...) {}
#endif /* !NDEBUG */

};

// Global console
extern Console console;

} /* namespace sge */

#endif /* __SGE_CONSOLE_H */
