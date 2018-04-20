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
bool startsWith (const std::string &pStr, const std::string &pPattern);

/**
 * Test if a string ends with another pattern.
 */
bool endsWith (const std::string &pStr, const std::string &pPattern);

/**
 * Trim whitespace from the beginning of a string.
 *
 * @param pStr String to trim
 */
std::string trimLeft (const std::string &pStr);

/**
 * Trim whitespace from the end of a string.
 *
 * @param pStr String to trim
 */
std::string trimRight (const std::string &pStr);

/**
 * Trim whitespace from both ends of a string.
 *
 * @param pStr String to trim
 */
std::string trim (const std::string &pStr);

/**
 * Pad a String with trailing spaces if the input string is narrower than the desired width.
 *
 * @param pStr String to pad
 * @param pWidth Total width of output string
 * @param c Char to use for padding
 */
std::string padLeft (const std::string &pStr, size_t pWidth, char c = ' ');

/**
 * Pad a String with leading spaces if the input string is narrower than the desired width.
 *
 * @param value String to pad
 * @param pWidth Total width of output string
 * @param c Char to use for padding
 */
std::string padRight (const std::string &pStr, size_t pWidth, char c = ' ');

/**
 * Pad a String with spaces either side if the input string is
 * narrower than the desired width.
 *
 * @param pStr String to pad
 * @param pWidth Total width of output string
 * @param c Char to use for padding
 */
std::string padCenter (const std::string &pStr, size_t pWidth, char c = ' ');

/**
 * Truncate a String if the length is greater than the
 * desired width.
 *
 * @param pStr String to truncate
 * @param pWidth Maximum width of output string
 */
std::string truncate (const std::string &pStr, size_t pWidth);

/**
 * Truncate a String if the length is greater than the
 * desired width and add ellipsis to the output (resulting
 * in a string that always has length >= 3).
 *
 * @param pStr String to truncate
 * @param pWidth Maximum width of output string
 */
std::string truncateEllipsis (const std::string &pStr, size_t pWidth);

/**
 * Truncate or PadLeft a string such that the resulting string's length
 * matches width.
 */
std::string setWidth (const std::string &pStr, size_t pWidth);

/**
 * Return the extension of a filename (no leading point).
 */
std::string fileExt (const std::string &pFilename);

/**
 * Return the file name from a path.
 */
std::string fileName (const std::string &pPath);

/**
 * Return the base directory of a path.
 */
std::string basePath (const std::string &pPath);

/**
 * Split a string using a character separator.
 */
std::vector<std::string> split (const std::string &pText, char pSep = ' ');

#if 0
/**
 * Split a string using a regular expression string as the separator pattern.
 */
std::vector<std::string> reSplit (const std::string &text, const std::string &sep = "\\s+");
#endif

}} /* namespace sge::str */

#endif /* __SGE_STRINGUTIL_H */
