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

class Console {
public:
    /**
     * Print a simple string.
     */
    virtual void Print (const std::string &msg) = 0;

    /**
     * Print a formatted string.
     */
    virtual void Printf (const std::string &fmt, ...) = 0;
};

// Global console
extern Console *console;

} /* namespace sge */

#endif /* __SGENGINE_CONSOLE_H_ */
