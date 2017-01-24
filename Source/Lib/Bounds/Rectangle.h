/*---  Rectangle.h - Bounding Rectangle Header  --------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a 2D axis aligned bounding rectangle type.
 */
#ifndef __SGE_RECTANGLE_H
#define __SGE_RECTANGLE_H

#include <cmath> // fabsf

namespace sge {

/**
 * 2D Bounding Rectangle. Test for intersections and envelopment
 * between 2D shapes.
 */
class Rectangle {
public:
    Vec2f min;
    Vec2f max;

public:
    /** Default Constructor */
    Rectangle ()
        : min{FMath::INFTY, FMath::INFTY}, max{-FMath::INFTY, -FMath::INFTY} { }

    /** Point Constructor */
    explicit Rectangle (const Vec2f &point)
        : min(point), max(point) { }

    /**
     * Construct a Rectangle with min and max bounds as Vec2f.
     */
    explicit Rectangle (const Vec2f &p_min, const Vec2f &p_max)
        : min(p_min), max(p_max) { }

    /**
     * Construct a Rectangle with min and max bounds as values.
     */
    explicit Rectangle (const float xMin, const float yMin,
                        const float xMax, const float yMax)
        : min{xMin, yMin}, max{xMax, yMax} { }

    /**
     * Clear the contents of this Rectangle.
     */
    void Clear ();

    /**
     * Expand this Rectangle to maximum size.
     */
    void Maximize ();

    /**
     * Get the center of this Rectangle as a Vec2f.
     */
    Vec2f Center () const;

    /**
     * Get the area of this Rectangle.
     */
    float Area () const;

    /**
     * Return a new Rectangle expanded by val in each direction,
     * which shares the same center as this Rectangle.
     */
    Rectangle Expand (const float val) const;

    /**
     * Expand the bounds of this Rectangle by val in each direction.
     * Destructive.
     */
    void ExpandSelf (const float val);

    /** Test if rectangle contains point. */
    friend bool Contains (const Rectangle &rect, const Vec2f &point);

    /** Test if rectangle entirely contains other rectangle. */
    friend bool Contains (const Rectangle &a, const Rectangle &b);

    /**
     * Test if this Rectangle partially (or fully) intersects
     * another Rectangle.
     */
    friend bool Intersects (const Rectangle &a, const Rectangle &b);

    /**
     * Test whether two Rectangles are equivalent.
     */
    bool Compare (const Rectangle &other) const;

    /**
     * Test whether two Rectangles are the same within a given
     * tolerance.
     */
    bool Compare (const Rectangle &other, const float threshold) const;

    /**
     * Test whether to Rectangles are equivalent.
     */
    bool operator== (const Rectangle &other) const;

    /**
     * Test whether two Rectangles are not equivalent.
     */
    bool operator!= (const Rectangle &other) const;
};

// --------------------------------------------------------------------------

inline void Rectangle::Clear () {
    min.x = min.y = FMath::INFTY;
    max.x = max.y = -FMath::INFTY;
}

inline void Rectangle::Maximize () {
    min.x = min.y = -FMath::INFTY;
    max.x = max.y = FMath::INFTY;
}

inline Vec2f Rectangle::Center () const {
    return (min + max) * 0.5f;
}

inline float Rectangle::Area () const {
    return fabsf((max.x - min.x) * (max.y - min.y));
}

inline Rectangle Rectangle::Expand (const float val) const {
    return Rectangle(min.x - val, min.y - val, max.x + val, max.y + val);
}

inline void Rectangle::ExpandSelf (const float val) {
    min.x -= val;
    min.y -= val;
    max.x += val;
    max.y += val;
}


inline bool Rectangle::Compare (const Rectangle &other) const {
    return min == other.min && max == other.max;
}

//======================
// Rectangle Comparison
//======================

inline bool Rectangle::Compare (const Rectangle &other, const float threshold) const {
    return min.Compare(other.min, threshold) && max.Compare(other.max, threshold);
}

inline bool Rectangle::operator== (const Rectangle &other) const {
    return Compare(other);
}

inline bool Rectangle::operator!= (const Rectangle &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGE_RECTANGLE_H */
