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
#ifndef __SGE_LINE2D_H
#define __SGE_LINE2D_H

namespace sge {

/**
 * 2D Line Section. Implements intersection tests against
 * other lines.
 */
class Line2D {
public:

    /**
     * Create a Line2D with (x1, y1)..(x2, y2) values.
     */
    explicit Line2D (const float x1, const float y1, const float x2, const float y2)
        : m_start{x1, y1}, m_end{x2, y2} { }

    /**
     * Create a Line2D with start and end points.
     */
    explicit Line2D (const Vec2f &p_start, const Vec2f &p_end)
        : m_start(p_start), m_end(p_end) { }

    /**
     * Get the length of this Line Section.
     */
    float Length () const;

    /**
     * Test if this Line2D intersects another Line2D.
     */
    friend bool Intersects (const Line2D &a, const Line2D &b);

    /**
     * Return the point at which this Line2D intersects
     * another Line2D, or extend the Input line to
     * INFINITY if no intersection exists.
     */
    Vec2f Intersection (const Line2D &rhs) const;

    /**
     * Find the point along this Line that occurs at time t.
     * If time is between 0..1 then this point will lie on the
     * line.
     */
    Vec2f Extrapolate (const float t) const;

    bool Compare (const Line2D &other) const;

    bool Compare (const Line2D &other, const float threshold) const;

    bool operator== (const Line2D &other) const;

    bool operator!= (const Line2D &other) const;

private:
    Vec2f m_start;
    Vec2f m_end;
};

// --------------------------------------------------------------------------

inline float Line2D::Length () const {
    return (m_end - m_start).Length();
}

inline Vec2f Line2D::Extrapolate (const float t) const {
    return m_start + (m_end - m_start) * t;
}

inline bool Line2D::Compare (const Line2D &other) const {
    return m_start == other.m_start && m_end == other.m_end;
}

inline bool Line2D::Compare (const Line2D &other, const float threshold) const {
    return m_start.Compare(other.m_start, threshold) &&
           m_end.Compare(other.m_end, threshold);
}

inline bool Line2D::operator== (const Line2D &other) const {
    return Compare(other);
}

inline bool Line2D::operator!= (const Line2D &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGE_LINE2D_H */
