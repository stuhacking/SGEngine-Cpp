/*---  Assert.h - Debugging and assertion macros  -----------------*- C++ -*---
*
*                           Stuart's Game Engine
*
* This file is distributed under the Revised BSD License. See LICENSE.TXT
* for details.
*
* --------------------------------------------------------------------------
*/
#ifndef __SGENGINE_ASSERT_H
#define __SGENGINE_ASSERT_H

/**
 * Log an assertion failure with the filename, line number and failing expression.
 * @param file
 * @param line
 * @param expr
 */
void assert_failed (const char * const file, const int line, const char * const expr);

#ifndef NDEBUG
// Assertions in debug mode.

#define verify(x) ((x) ? true : (assert_failed(__FILE__, __LINE__, #x), false))

#else
// Assertions in release mode.

#define verify(x) ((x) ? true : false)

#endif /* !NDEBUG */

#endif /* __SGENGINE_ASSERT_H */
