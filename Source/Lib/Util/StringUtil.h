/*---  StringUtil.h - String Utilities Header  ---------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Convenient utilities for std::strings.
 */
#ifndef __SGE_STRINGUTIL_H
#define __SGE_STRINGUTIL_H

#include <string>
#include <regex>
#include <vector>

namespace sge { namespace str {

/**
 * Test if a string starts with another pattern.
 */
bool StartsWith (const std::string &str, const std::string &pattern);

/**
 * Test if a string ends with another pattern.
 */
bool EndsWith (const std::string &str, const std::string &pattern);

/**
 * Trim whitespace from the beginning of a string.
 *
 * @param str String to trim
 */
std::string TrimLeft (const std::string &str);

/**
 * Trim whitespace from the end of a string.
 *
 * @param str String to trim
 */
std::string TrimRight (const std::string &str);

/**
 * Trim whitespace from both ends of a string.
 *
 * @param str String to trim
 */
std::string Trim (const std::string &str);

/**
 * Pad a String with trailing spaces if the input string is narrower than the desired width.
 *
 * @param str String to pad
 * @param width Total width of output string
 * @param c Char to use for padding
 */
std::string PadLeft (const std::string &str, const int width, const char c = ' ');

/**
 * Pad a String with leading spaces if the input string is narrower than the desired width.
 *
 * @param value String to pad
 * @param width Total width of output string
 * @param c Char to use for padding
 */
std::string PadRight (const std::string &str, const int width, const char c = ' ');

/**
 * Pad a String with spaces either side if the input string is
 * narrower than the desired width.
 *
 * @param str String to pad
 * @param width Total width of output string
 * @param c Char to use for padding
 */
std::string PadCenter (const std::string &str, const int width, const char c = ' ');

/**
 * Truncate a String if the length is greater than the
 * desired width.
 *
 * @param str String to truncate
 * @param width Maximum width of output string
 */
std::string Truncate (const std::string &str, const int width);

/**
 * Truncate a String if the length is greater than the
 * desired width and add ellipsis to the output (resulting
 * in a string that always has length >= 3).
 *
 * @param str String to truncate
 * @param width Maximum width of output string
 */
std::string TruncateEllipsis (const std::string &str, const int width);

/**
 * Truncate or PadLeft a string such that the resulting string's length
 * matches width.
 */
std::string SetWidth (const std::string &str, const int width);

/**
 * Return the extension of a filename (no leading point).
 */
std::string FileExtension (const std::string &filename);

/**
 * Return the file name from a path.
 */
std::string FileName (const std::string &path);

/**
 * Return the base directory of a path.
 */
std::string BasePath (const std::string &path);

/**
 * Split a string using another string as the separator pattern.
 */
std::vector<std::string> Split (const std::string &text, const char sep = ' ');

#if 0
/**
 * Split a string using a regular expression string as the separator pattern.
 */
std::vector<std::string> ReSplit (const std::string &text, const std::string &sep = "\\s+");
#endif

}} /* namespace sge::str */

#endif /* __SGE_STRINGUTIL_H */
