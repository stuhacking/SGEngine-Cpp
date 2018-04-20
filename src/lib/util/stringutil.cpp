//
// StringUtil implementation.
//
#include "stringutil.h"

#include <sstream>

namespace sge { namespace str {

static constexpr auto whitespace = " \t";
static constexpr auto path_sep = '/';
static constexpr auto continuation_char = "\u2026"; // Horizontal Ellipsis - 3bytes.

bool startsWith (const std::string &pStr, const std::string &pPattern) {
    return pStr.size() >= pPattern.size() && 0 == pStr.find(pPattern);
}

bool endsWith (const std::string &pStr, const std::string &pPattern) {
    return pStr.size() >= pPattern.size() &&
        (pStr.size() - pPattern.size()) == pStr.rfind(pPattern);
}

std::string trimLeft (const std::string &pStr) {
    auto pos = pStr.find_first_not_of(whitespace);
    return (std::string::npos == pos) ? "" : pStr.substr(pos);
}

std::string trimRight (const std::string &pStr) {
    auto pos = pStr.find_last_not_of(whitespace);
    return (std::string::npos == pos) ? "" : pStr.substr(0, pos + 1);
}

std::string trim (const std::string &pStr) {
    return trimLeft(trimRight(pStr));
}

std::string padLeft (const std::string &pStr, const size_t pWidth, const char c) {
    size_t size = pStr.size();

    if (size > pWidth) {
        return pStr;
    }

    return std::string(pWidth, c).replace(0, size, pStr);
}

std::string padRight (const std::string &pStr, const size_t pWidth, const char c) {
    size_t size = pStr.size();

    if (size > pWidth) {
        return pStr;
    }

    size_t padAmt = pWidth - pStr.size();

    return std::string(pWidth, c).replace(padAmt, size, pStr);
}

std::string padCenter (const std::string &pStr, const size_t pWidth, const char c) {
    size_t size = pStr.size();

    if (size > pWidth) {
        return pStr;
    }

    size_t padAmt = pWidth - pStr.size();

    padAmt = (padAmt % 2 == 0) ? padAmt / 2 : padAmt / 2 + 1;

    return std::string(pWidth, c).replace(padAmt, size, pStr);
}

std::string truncate (const std::string &pStr, const size_t pWidth) {
    if (pWidth == 0) {
        return "";
    }

    if (pStr.size() <= pWidth) {
        return pStr;
    }

    return pStr.substr(0, pWidth);
}

std::string truncateEllipsis (const std::string &pStr, const size_t pWidth) {
    if (pWidth == 0) {
        return "";
    }

    if (pStr.size() <= pWidth) {
        return pStr;
    }

    return truncate(pStr, pWidth - 1) + continuation_char; // Ellipsis char
}

std::string setWidth (const std::string &pStr, const size_t pWidth) {
    if (pStr.size() <= pWidth) {
        return padLeft(pStr, pWidth);
    }

    return truncateEllipsis(pStr, pWidth);
}

std::string fileExt (const std::string &pFilename) {
    auto pos = pFilename.find_last_of('.');
    return (std::string::npos == pos) ? "" : pFilename.substr(pos + 1);
}

std::string fileName (const std::string &pPath) {
    auto pos = pPath.find_last_of(path_sep);
    return pPath.substr(pos + 1);
}

std::string basePath (const std::string &pPath) {
    size_t pos = pPath.find_last_of(path_sep);
    return (std::string::npos == pos) ? "" : pPath.substr(0, pos + 1);
}

std::vector<std::string> split (const std::string &pText, const char pSep) {
    std::vector<std::string> tokens;
    std::stringstream ss(pText);
    std::string item;
    while (std::getline(ss, item, pSep)) {
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
