//
// StringUtil implementation.
//
#include "stringutil.h"

#include <sstream>

namespace sge { namespace str {

static constexpr auto whitespace = " \t";
static constexpr auto path_sep = "/";
static constexpr auto continuation_char = "\u2026"; // Horizontal Ellipsis

bool startsWith (const std::string &str, const std::string &pattern) {
    return str.size() >= pattern.size() && 0 == str.find(pattern);
}

bool endsWith (const std::string &str, const std::string &pattern) {
    return str.size() >= pattern.size() &&
        (str.size() - pattern.size()) == str.rfind(pattern);
}

std::string trimLeft (const std::string &str) {
    auto pos = str.find_first_not_of(whitespace);
    return (std::string::npos == pos) ? "" : str.substr(pos);
}

std::string trimRight (const std::string &str) {
    auto pos = str.find_last_not_of(whitespace);
    return (std::string::npos == pos) ? "" : str.substr(0, pos + 1);
}

std::string trim (const std::string &str) {
    return trimLeft(trimRight(str));
}

std::string padLeft (const std::string &str, const int width, const char c) {
    long padding = width - str.size();

    if (padding <= 0) {
        return str;
    }

    return std::string(width, c).replace(0, str.size(), str);
}

std::string padRight (const std::string &str, const int width, const char c) {
    long padding = width - str.size();

    if (padding <= 0) {
        return str;
    }

    return std::string(width, c).replace(padding, str.size(), str);
}

std::string padCenter (const std::string &str, const int width, const char c) {
    long padding = width - str.size();

    if (padding <= 0) {
        return str;
    }

    padding = (padding % 2 == 0) ? padding / 2 : padding / 2 + 1;

    return std::string(width, c).replace(padding, str.size(), str);
}

std::string truncate (const std::string &str, const int width) {
    if (width <= 0) {
        return "";
    }

    if (str.size() <= width) {
        return str;
    }

    return str.substr(0, width);
}

std::string truncateEllipsis (const std::string &str, const int width) {
    if (width <= 0) {
        return "";
    }

    if (str.size() <= width) {
        return str;
    }

    return truncate(str, width - 1) + continuation_char; // Ellipsis char
}

std::string setWidth (const std::string &str, const int width) {
    if (str.size() <= width) {
        return padLeft(str, width);
    }

    return truncateEllipsis(str, width);
}

std::string fileExt (const std::string &filename) {
    auto pos = filename.find_last_of(".");
    return (std::string::npos == pos) ? "" : filename.substr(pos + 1);
}

std::string fileName (const std::string &path) {
    auto pos = path.find_last_of(path_sep);
    return path.substr(pos + 1);
}

std::string basePath (const std::string &path) {
    size_t pos = path.find_last_of(path_sep);
    return (std::string::npos == pos) ? "" : path.substr(0, pos + 1);
}

std::vector<std::string> split (const std::string &text, const char sep) {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string item;
    while (std::getline(ss, item, sep)) {
        tokens.push_back(item);
    }
    return tokens;
}

#if 0
// <regex> not fully supported in GCC < 4.9
std::vector<std::string> reSplit (const std::string &text, const std::string &sep) {
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
