/*---  Line2D.h - 2D Line Section Header  --------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a 2D Line Section for intersection tests.
 */
#ifndef __SGENGINE_LINE2D_H_
#define __SGENGINE_LINE2D_H_

namespace sge {

/**
 * 2D Line Section. Implements intersection tests against
 * other lines.
 */
class Line2D {
public:
    Line2D(const Vec2f &p_start, const Vec2f &p_end)
        : m_start(p_start), m_end(p_end) { }

    /**
     * Get the length of this Line Section.
     */
    float Length () const;

    /**
     * Test if this Line2D intersects another Line2D.
     */
    bool Intersects(const Line2D &rhs) const;

    /**
     * Return the point at which this Line2D intersects
     * another Line2D, or extend the Input line to
     * INFINITY if no intersection exists.
     */
    Vec2f Intersection(const Line2D &rhs) const;

private:
    Vec2f m_start;
    Vec2f m_end;
};

// --------------------------------------------------------------------------

INLINE float Line2D::Length () const {
    return (m_end - m_start).Length();
}

} /* namespace sge */

#endif /* __SGENGINE_LINE2D_H_ */
