//
// StringUtil implementation.
//
#include "StringUtil.h"

#include <sstream>

namespace sge { namespace str {

static constexpr auto whitespace = " \t";
static constexpr auto path_sep = "/";
static constexpr auto continuation_char = "~";

bool StartsWith (const std::string &str, const std::string &pattern) {
    return str.length() >= pattern.length() && 0 == str.find(pattern);
}

bool EndsWith (const std::string &str, const std::string &pattern) {
    return str.length() >= pattern.length() &&
        (str.length() - pattern.length()) == str.rfind(pattern);
}

std::string TrimLeft (const std::string &str) {
    auto pos = str.find_first_not_of(whitespace);
    return (std::string::npos == pos) ? "" : str.substr(pos);
}

std::string TrimRight (const std::string &str) {
    auto pos = str.find_last_not_of(whitespace);
    return (std::string::npos == pos) ? "" : str.substr(0, pos + 1);
}

std::string Trim (const std::string &str) {
    return TrimLeft(TrimRight(str));
}

std::string PadLeft (const std::string &str, const size_t width, const char c) {
    int padding = width - str.length();

    if (padding <= 0) {
        return str;
    }

    return std::string(width, c).replace(0, str.length(), str);
}

std::string PadRight (const std::string &str, const size_t width, const char c) {
    int padding = width - str.length();

    if (padding <= 0) {
        return str;
    }

    return std::string(width, c).replace(padding, str.length(), str);
}

std::string PadCenter (const std::string &str, const size_t width, const char c) {
    int padding = width - str.length();

    if (padding <= 0) {
        return str;
    }

    padding = (padding % 2 == 0) ? padding / 2 : padding / 2 + 1;

    return std::string(width, c).replace(padding, str.length(), str);
}

std::string Truncate (const std::string &str, const size_t width) {
    if (width <= 0) {
        return "";
    }

    if (str.length() <= width) {
        return str;
    }

    return str.substr(0, width);
}

std::string TruncateEllipsis (const std::string &str, const size_t width) {
    if (width <= 0) {
        return "";
    }

    if (str.length() <= width) {
        return str;
    }

    return Truncate(str, width - 1) + continuation_char; // Ellipsis char
}

std::string SetWidth (const std::string &str, const size_t width) {
    if (str.length() <= width) {
        return PadLeft(str, width);
    }

    return TruncateEllipsis(str, width);
}

std::string FileExtension (const std::string &filename) {
    auto pos = filename.find_last_of(".");
    return (std::string::npos == pos) ? "" : filename.substr(pos + 1);
}

std::string FileName (const std::string &path) {
    auto pos = path.find_last_of(path_sep);
    return path.substr(pos + 1);
}

std::string BasePath (const std::string &path) {
    size_t pos = path.find_last_of(path_sep);
    return (std::string::npos == pos) ? "" : path.substr(0, pos + 1);
}

std::vector<std::string> Split (const std::string &text, const char sep) {
    std::vector<std::string> elems;
    std::stringstream ss(text);
    std::string item;
    while (std::getline(ss, item, sep)) {
        elems.push_back(item);
    }
    return elems;
}

#if 0
// <regex> not fully supported in GCC < 4.9
std::vector<std::string> ReSplit (const std::string &text, const std::string &sep) {
    std::vector<std::string> tokens;
    std::regex rgx(sep);
    std::sregex_token_iterator iter(std::begin(text),
                                    std::end(text),
                                    rgx,
                                    -1);
    std::sregex_token_iterator end;
    for ( ; iter != end; ++iter) {
        tokens.push_back(*iter);
    }

    return tokens;
}
#endif

}} /* namespace sge::str */
