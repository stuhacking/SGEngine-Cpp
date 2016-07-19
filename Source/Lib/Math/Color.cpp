//
// Color Implementation.
//
#include "../Lib.h"

#include <sstream>

namespace sge {

static constexpr const float HUE_MAX = 360.0f;
static constexpr const float HUE_STEP = HUE_MAX / 6.0f;

Vec4f Color::ToVec4f (const bool normalize) const {
    float f = normalize ? (1.0f / 255.0f) : 1.0f;

    return Vec4f((float)r * f, (float)g * f, (float)b * f, (float)a * f);
}

Color Color::FromHSL (const float p_hue, const float p_sat, const float p_val) {
    float chroma = (1.0f - fabsf(2.0f * p_val - 1.0f)) * p_sat;
    float hSplit = p_hue / HUE_STEP;
    float x = chroma * (1.0f - fabsf(fmodf(hSplit, 2.0f) - 1.0f));
    float r = 0.0f, g = 0.0f, b = 0.0f;

    if (hSplit >= 0.0f && hSplit < 1.0f) { // Red is chroma
        r = chroma;
        g = x;
        b = 0.0f;
    } else if (hSplit >= 1.0f && hSplit < 2.0f) { // Green is chroma
        r = x;
        g = chroma;
        b = 0.0f;
    } else if (hSplit >= 2.0f && hSplit < 3.0f) {
        r = 0.0f;
        g = chroma;
        b = x;
    } else if (hSplit >= 3.0f && hSplit < 4.0f) { // Blue is chroma
        r = 0.0f;
        g = x;
        b = chroma;
    } else if (hSplit >= 4.0f && hSplit < 5.0f) {
        r = x;
        g = 0.0f;
        b = chroma;
    } else if (hSplit >= 5.0f && hSplit < 6.0f) { // Red is chroma
        r = chroma;
        g = 0.0f;
        b = x;
    }

    float m = p_val - 0.5f * chroma;

    return Color(static_cast<u8>(FMath::Lerp(0, 255, r + m)),
                 static_cast<u8>(FMath::Lerp(0, 255, g + m)),
                 static_cast<u8>(FMath::Lerp(0, 255, b + m)));
}

static std::string expandColorCode (const std::string &code) {
    std::ostringstream oss;

    if (code.length() == 3) {
        oss << code[0] << code[0] << code[1] << code[1] << code[2] << code[2] << "FF";
        return oss.str();
    }

    if (code.length() == 4) {
        oss << code[0] << code[0] << code[1] << code[1] << code[2] << code[2] << code[3] << code[3];
        return oss.str();
    }

    if (code.length() == 6) {
        return code + "FF";
    }

    if (code.length() == 8){
        return code;
    }

    return "000000FF";
}

Color Color::FromHex (const std::string &hex) {
    // Parse a color code given as Hex string
    // Discard first character if #
    // Valid string lengths are 3 (RGB), 4 (RGBA), 6 (RRGGBB) or 8 (RRGGBBAA)
    // Expand each of the first 3 options to match an 8 byte string and then
    // parse as Hex
    std::string code = (hex[0] == '#') ? hex.substr(1) : hex;
    code = expandColorCode(code);

    u32 val = static_cast<u32>(strtoul(code.c_str(), nullptr, 16));

    return Color(val);
}

} /* namespace sge */
