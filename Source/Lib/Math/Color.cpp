//
// Color Implementation.
//
#include "../Lib.h"

#include <cstdlib> // strtoul
#include <cstring> // strncpy, strchr

namespace sge {

static constexpr float HUE_MAX = 360.0f;
static constexpr float HUE_STEP = HUE_MAX / 6.0f;

Vec4f Color::ToVec4f (const bool normalize) const {
    float f = normalize ? (1.0f / 255.0f) : 1.0f;

    return Vec4f((float)r * f, (float)g * f, (float)b * f, (float)a * f);
}

Color Color::FromHSL (const float p_hue, const float p_sat, const float p_val) {
    float chroma = (1.0f - fabsf(2.0f * p_val - 1.0f)) * p_sat;
    float nHue = p_hue / HUE_STEP; // Normalize Hue
    float x = chroma * (1.0f - fabsf(fmodf(nHue, 2.0f) - 1.0f));
    float r = 0.0f, g = 0.0f, b = 0.0f;

    if (nHue >= 0.0f && nHue < 1.0f) { // Red is chroma
        r = chroma;
        g = x;
        b = 0.0f;
    } else if (nHue >= 1.0f && nHue < 2.0f) { // Green is chroma
        r = x;
        g = chroma;
        b = 0.0f;
    } else if (nHue >= 2.0f && nHue < 3.0f) {
        r = 0.0f;
        g = chroma;
        b = x;
    } else if (nHue >= 3.0f && nHue < 4.0f) { // Blue is chroma
        r = 0.0f;
        g = x;
        b = chroma;
    } else if (nHue >= 4.0f && nHue < 5.0f) {
        r = x;
        g = 0.0f;
        b = chroma;
    } else if (nHue >= 5.0f && nHue < 6.0f) { // Red is chroma
        r = chroma;
        g = 0.0f;
        b = x;
    }

    float m = p_val - 0.5f * chroma;

    return Color(static_cast<u8>(FMath::Lerp(r + m, 0, 255)),
                 static_cast<u8>(FMath::Lerp(g + m, 0, 255)),
                 static_cast<u8>(FMath::Lerp(b + m, 0, 255)));
}

/**
 * <pre> code != nullptr
 */
static char * expandColorCode (const char * const code, char result[9]) {
    size_t len = strlen(code);

    // Initialize result.
    strncpy(result, "000000FF", 8);

    if (len == 3) {
        result[0] = result[1] = code[0];
        result[2] = result[3] = code[1];
        result[4] = result[5] = code[2];
    } else if (len == 4) {
        result[0] = result[1] = code[0];
        result[2] = result[3] = code[1];
        result[4] = result[5] = code[2];
        result[6] = result[7] = code[3];
    } else if (len == 6 || len == 8) {
        strncpy(result, code, len);
    }

    return result;
}

// Parse a color code given as Hex string
// Discard first character if #
// Valid string lengths are 3 (RGB), 4 (RGBA), 6 (RRGGBB) or 8 (RRGGBBAA)
// Expand each of the first 3 options to match an 8 byte string and then
// parse as Hex
Color Color::FromHex (const char * const hex) {
    char fullCode[9] = {0};
    const char *dropHash = strchr(hex, '#');

    if (nullptr != dropHash) {
        ++dropHash;
        expandColorCode(dropHash, fullCode);
    } else {
        expandColorCode(hex, fullCode);
    }

    u32 val = static_cast<u32>(strtoul(fullCode, nullptr, 16));

    return Color(val);
}

} /* namespace sge */
