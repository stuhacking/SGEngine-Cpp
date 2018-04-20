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
     * @param pHue Hue value in the range 0.0f..360.0f representing the
     *        spectrum of Red -> Green -> Blue -> Red
     * @param pSat Saturation value in range 0.0f..1.0f
     * @param pVal Lightness value in range 0.0f..1.0f such that 0
     *          is black, 0.5 is full color and 1 is white.
     * @return Converted RGB Color value.
     */
    static Color fromHSL (const float pHue,
                          const float pSat = 1.0f,
                          const float pVal = 0.5f);

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
    static Color fromHex (const char *const hex);

    /**
     * Test if this color is fully opaque.
     * @return true if opaque, otherwise false;
     */
    bool isOpaque () const { return a == 255; }

    /**
     * Test if this color is fully transparent.
     * @return true if transparent, otherwise false;
     */
    bool isHidden () const { return a == 0; }

    /**
     * Write Color to <Vec4f R, G, B, A>.
     *
     * @param normalize If true, resize values to 0..1 range.
     */
    Vec4f toVec4f (const bool normalize = false) const;

    bool compare (const Color &other) const;
};

// --------------------------------------------------------------------------

inline Color::Color (const u32 val) {
    r = static_cast<u8>((val & 0xFF000000) >> 24);
    g = static_cast<u8>((val & 0x00FF0000) >> 16);
    b = static_cast<u8>((val & 0x0000FF00) >> 8);
    a = static_cast<u8>((val & 0x000000FF));
}

inline bool Color::compare (const Color &other) const {
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

inline bool operator== (const Color &a, const Color &b) {
    return a.compare(b);
}

inline bool operator!= (const Color &a, const Color &b) {
    return !a.compare(b);
}

#endif /* __SGE_COLOR_H  */
