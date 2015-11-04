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
#ifndef __SHLIB_STRINGUTIL_H_
#define __SHLIB_STRINGUTIL_H_

#include <string>
#include <regex>
#include <vector>

namespace sge {

class String {
public:
    
    /**
     * Test if a string starts with another pattern.
     */
    static bool StartsWith (const std::string &str, const std::string &pattern);
    
    /**
     * Test if a string ends with another pattern.
     */
    static bool EndsWith (const std::string &str, const std::string &pattern);

    /**
     * Trim whitespace from the beginning of a string.
     *
     * @param str String to trim
     */
    static std::string TrimLeft (const std::string &str);
    
    /**
     * Trim whitespace from the end of a string.
     *
     * @param str String to trim
     */
    static std::string TrimRight (const std::string &str);

    /**
     * Trim whitespace from both ends of a string.
     *
     * @param str String to trim
     */
    static std::string Trim (const std::string &str);
    
    /**
     * Pad a String with trailing spaces if the input string is narrower than the desired width.
     *
     * @param str String to pad
     * @param width Total width of output string
     * @param c Char to use for padding
     */
    static std::string PadLeft (const std::string &str, const size_t width, const char c = ' ');
    
    /**
     * Pad a String with leading spaces if the input string is narrower than the desired width.
     *
     * @param value String to pad
     * @param width Total width of output string
     * @param c Char to use for padding
     */
    static std::string PadRight (const std::string &str, const size_t width, const char c = ' ');
    
    /**
     * Pad a String with spaces either side if the input string is
     * narrower than the desired width.
     *
     * @param str String to pad
     * @param width Total width of output string
     * @param c Char to use for padding
     */
    static std::string PadCenter (const std::string &str, const size_t width, const char c = ' ');
    
    /**
     * Truncate a String if the length is greater than the
     * desired width.
     *
     * @param str String to truncate
     * @param width Maximum width of output string
     */
    static std::string Truncate (const std::string &str, const size_t width);
    
    /**
     * Truncate a String if the length is greater than the
     * desired width and add ellipsis to the output (resulting
     * in a string that always has length >= 3).
     *
     * @param str String to truncate
     * @param width Maximum width of output string
     */
    static std::string TruncateEllipsis (const std::string &str, const size_t width);
    
    /**
     * Truncate or PadLeft a string such that the resulting string's length
     * matches width.
     */
    static std::string SetWidth (const std::string &str, const size_t width);
    
    /**
     * Return the extension of a filename (no leading point).
     */
    static std::string FileExtension (const std::string &filename);
    
    /**
     * Return the file name from a path.
     */
    static std::string FileName (const std::string &path);
    
    /**
     * Return the base directory of a path.
     */
    static std::string BasePath (const std::string &path);
    
    /**
     * Split a string using another string as the separator pattern.
     */
    static std::vector<std::string> Split (const std::string &text, const char sep = ' ');

#if 0
    /**
     * Split a string using a regular expression string as the separator pattern.
     */
    static std::vector<std::string> ReSplit (const std::string &text, const std::string &sep = "\\s+");
#endif
};
    
} /* namespace sge */

#endif /* __SHLIB_STRINGUTIL_H_ */
