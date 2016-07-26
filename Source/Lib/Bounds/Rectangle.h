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
#ifndef __SGENGINE_RECTANGLE_H_
#define __SGENGINE_RECTANGLE_H_

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
    bool Contains (const Vec2f &point) const;

    /** Test if rectangle entirely contains other rectangle. */
    bool Contains (const Rectangle &other) const;

    /**
     * Test if this Rectangle partially (or fully) intersects
     * another Rectangle.
     */
    bool Intersects (const Rectangle &other) const;

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

INLINE void Rectangle::Clear () {
    min.x = min.y = FMath::INFTY;
    max.x = max.y = -FMath::INFTY;
}

INLINE void Rectangle::Maximize () {
    min.x = min.y = -FMath::INFTY;
    max.x = max.y = FMath::INFTY;
}

INLINE Vec2f Rectangle::Center () const {
    return (min + max) * 0.5f;
}

INLINE float Rectangle::Area () const {
    return fabsf((max.x - min.x) * (max.y - min.y));
}

INLINE Rectangle Rectangle::Expand (const float val) const {
    return Rectangle(min.x - val, min.y - val, max.x + val, max.y + val);
}

INLINE void Rectangle::ExpandSelf (const float val) {
    min.x -= val;
    min.y -= val;
    max.x += val;
    max.y += val;
}

INLINE bool Rectangle::Contains (const Vec2f &point) const {
    return point.x >= min.x && point.x <= max.x &&
        point.y >= min.y && point.y <= max.y;
}

INLINE bool Rectangle::Contains (const Rectangle &other) const {
    return Contains(other.min) && Contains(other.max);
}

INLINE bool Rectangle::Intersects (const Rectangle &other) const {
    return (other.max.x >= min.x && other.max.y >= min.y &&
            other.min.x <= max.x && other.min.y <= max.y);
}

INLINE bool Rectangle::Compare (const Rectangle &other) const {
    return min == other.min && max == other.max;
}

//======================
// Rectangle Comparison
//======================

INLINE bool Rectangle::Compare (const Rectangle &other, const float threshold) const {
    return min.Compare(other.min, threshold) && max.Compare(other.max, threshold);
}

INLINE bool Rectangle::operator== (const Rectangle &other) const {
    return Compare(other);
}

INLINE bool Rectangle::operator!= (const Rectangle &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGENGINE_RECTANGLE_H_ */
