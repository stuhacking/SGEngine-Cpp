/*---  Color.h - Color Type Header ---------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 * 
 * @brief Defines a 32 bit color class.
 */
#ifndef __SHLIB_COLOR_H_
#define __SHLIB_COLOR_H_

#include <string>
#include <cstdlib> // abs

namespace sge {

class Color {
public:
    u8 r;
    u8 g;
    u8 b;
    u8 a;

public:
    /** Construct a color with R, G, B, A values. */
    explicit Color (const u8 rr, const u8 gg, const u8 bb, const u8 aa = 255)
            : r(rr), g(gg), b(bb), a(aa) { }

    /** Construct a color from a single 32 bit unsigned int. */
    Color (const u32 val);

    /**
     * Create a new RGBA Color value by converting from 
     * Hue, Saturation, Lightness color space.
     *
     * @param {float} p_hue Hue value in the range 0.0f..360.0f representing the 
     *          spectrum of Red -> Green -> Blue -> Red
     * @param {float} p_sat Saturation value in range 0.0f..1.0f
     * @param {float} p_val Lightness value in range 0.0f..1.0f such that 0
     *          is black, 0.5 is full color and 1 is white.
     * @return {Color} Converted RGB Color value.
     */
    static Color FromHSL (const float p_hue, const float p_sat, const float p_val);

    /**
     * Create a new RGBA Color value by parsing a Hexadecimal color string.
     *
     * The string may begin with a leading #, though this is optional. Accepted formats are:
     *  #RGB, #RGBA, #RRGGBB, #RRGGBBAA.
     * In each case, if an alpha value is not given, it will default to 255 (fully opaque).
     *
     * @param hex A color value encoded as a hexadecimal string.
     */
    static Color FromHex (const std::string &hex);

    /**
     * Test if this color is fully opaque.
     * @return true if opaque, otherwise false;
     */
    bool IsOpaque () const;

    /**
     * Test if this color is fully transparent.
     * @return true if transparent, otherwise false;
     */
    bool IsHidden () const;

    bool Compare (const Color &other) const;

    bool Compare (const Color &other, const u8 threshold) const;

    bool operator== (const Color &other) const;

    bool operator!= (const Color &other) const;

private:
    static constexpr const float HUE_MAX = 360.0f;
    static constexpr const float HUE_STEP = HUE_MAX / 6.0f;
};

// --------------------------------------------------------------------------

inline Color::Color (const u32 val) {
    r = (val >> 24) & 0xFF;
    g = (val >> 16) & 0xFF;
    b = (val >> 8) & 0xFF;
    a = val & 0xFF;
}

inline bool Color::IsOpaque () const {
    return a == 255;
}

inline bool Color::IsHidden () const {
    return a == 0;
}

inline bool Color::Compare (const Color &other) const {
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

inline bool Color::Compare (const Color &other, const u8 threshold) const {
    if (abs(r - other.r) > threshold)
        return false;
    if (abs(g - other.g) > threshold)
        return false;
    if (abs(b - other.b) > threshold)
        return false;
    if (abs(a - other.a) > threshold)
        return false;

    return true;
}

inline bool Color::operator== (const Color &other) const {
    return Compare(other);
}

inline bool Color::operator!= (const Color &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SHLIB_COLOR_H_  */
