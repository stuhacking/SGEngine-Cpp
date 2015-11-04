/*---  Clock.h - Clock Header  -------------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 * 
 * @brief Defines a Clock class and timing functions using 
 *   the system's High Frequency Timer via std::chrono.
 */
#ifndef __SHLIB_CLOCK_H_
#define __SHLIB_CLOCK_H_

namespace sge {

/**
 * Clock Class.
 */
class Clock {
public:
    static u64 NanoTime ();
    static u64 MillisTime ();

};

} /* namespace sge */

#endif /* __SHLIB_CLOCK_H_ */
