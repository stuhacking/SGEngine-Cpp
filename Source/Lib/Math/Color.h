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
#ifndef __SGE_COLOR_H
#define __SGE_COLOR_H

#include <cstdlib> // abs

namespace sge {

class Color {
public:
    /** Color components. */
    u8 r, g, b, a;

public:
    /** Construct a color with R, G, B, A values. */
    explicit Color (const u8 rr, const u8 gg, const u8 bb, const u8 aa = 255)
            : r(rr), g(gg), b(bb), a(aa) { }

    /** Construct a color from a single 32 bit unsigned int. */
    explicit Color (const u32 val);

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
    static Color FromHSL (const float p_hue,
                          const float p_sat = 1.0f,
                          const float p_val = 0.5f);

    /**
     * Create a new RGBA Color value by parsing a Hexadecimal
     * color string.
     *
     * A leading # is optional. Accepted formats are: #RGB, #RGBA, #RRGGBB,
     * #RRGGBBAA. In each case, if an alpha value is not given, it will default
     * to 255 (fully opaque).
     *
     * @param hex A color value encoded as a hexadecimal string.
     */
    static Color FromHex (const char * const hex);

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

    /**
     * Write Color to <Vec4f R, G, B, A>.
     *
     * @param normalize If true, resize values to 0..1 range.
     */
    Vec4f ToVec4f (const bool normalize = false) const;

    bool Compare (const Color &other) const;

    bool operator== (const Color &other) const;

    bool operator!= (const Color &other) const;
};

// --------------------------------------------------------------------------

INLINE Color::Color (const u32 val) {
    r = (val & 0xFF000000) >> 24;
    g = (val & 0x00FF0000) >> 16;
    b = (val & 0x0000FF00) >> 8;
    a = (val & 0x000000FF);
}

INLINE bool Color::IsOpaque () const {
    return a == 255;
}

INLINE bool Color::IsHidden () const {
    return a == 0;
}

INLINE bool Color::Compare (const Color &other) const {
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

INLINE bool Color::operator== (const Color &other) const {
    return Compare(other);
}

INLINE bool Color::operator!= (const Color &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGE_COLOR_H  */
