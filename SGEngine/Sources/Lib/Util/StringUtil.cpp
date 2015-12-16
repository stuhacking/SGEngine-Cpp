//
// StringUtil implementation.
//
#include "StringUtil.h"

#include <sstream>

namespace sge {

static constexpr auto whitespace = " \t";
static constexpr auto path_sep = "/";

bool String::StartsWith (const std::string &str, const std::string &pattern) {
    return str.length() >= pattern.length() && 0 == str.find(pattern);
}

bool String::EndsWith (const std::string &str, const std::string &pattern) {
    return str.length() >= pattern.length() &&
        (str.length() - pattern.length()) == str.rfind(pattern);
}

std::string String::TrimLeft (const std::string &str) {
    auto pos = str.find_first_not_of(whitespace);
    return (std::string::npos == pos) ? "" : str.substr(pos);
}

std::string String::TrimRight (const std::string &str) {
    auto pos = str.find_last_not_of(whitespace);
    return (std::string::npos == pos) ? "" : str.substr(0, pos + 1);
}

std::string String::Trim (const std::string &str) {
    return TrimLeft(TrimRight(str));
}

std::string String::PadLeft (const std::string &str, const size_t width, const char c) {
    int padding = width - str.length();
    
    if (padding <= 0) {
        return str;
    }
    
    return std::string(width, c).replace(0, str.length(), str);
}

std::string String::PadRight (const std::string &str, const size_t width, const char c) {
    int padding = width - str.length();
    
    if (padding <= 0) {
        return str;
    }
    
    return std::string(width, c).replace(padding, str.length(), str);
}

std::string String::PadCenter (const std::string &str, const size_t width, const char c) {
    int padding = width - str.length();
    
    if (padding <= 0) {
        return str;
    }

    padding = (padding % 2 == 0) ? padding / 2 : padding / 2 + 1;
    
    return std::string(width, c).replace(padding, str.length(), str);
}

std::string String::Truncate (const std::string &str, const size_t width) {
    if (width <= 0) {
        return "";
    }
    
    if (str.length() <= width) {
        return str;
    }
    
    return str.substr(0, width);
}

std::string String::TruncateEllipsis (const std::string &str, const size_t width) {
    if (width <= 0) {
        return "";
    }

    if (str.length() <= width) {
        return str;
    }

    return Truncate(str, width - 1) + ">"; // Ellipsis char
}

std::string String::SetWidth (const std::string &str, const size_t width) {
    if (str.length() <= width) {
        return PadLeft(str, width);
    }

    return TruncateEllipsis(str, width);
}

std::string String::FileExtension (const std::string &filename) {
    auto pos = filename.find_last_of(".");
    return (std::string::npos == pos) ? "" : filename.substr(pos + 1);
}

std::string String::FileName (const std::string &path) {
    auto pos = path.find_last_of(path_sep);
    return path.substr(pos + 1);
}

std::string String::BasePath (const std::string &path) {
    size_t pos = path.find_last_of(path_sep);
    return (std::string::npos == pos) ? "" : path.substr(0, pos + 1);
}

std::vector<std::string> String::Split (const std::string &text, const char sep) {
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
std::vector<std::string> String::ReSplit (const std::string &text, const std::string &sep) {
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

} /* namespace sge */
