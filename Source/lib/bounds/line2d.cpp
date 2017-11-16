//
// Line2D Implementation
//
#include "../lib.h"

namespace sge {

Vec2f Line2D::intersection (const Line2D &rhs) const {
    Vec2f l1 = m_end - m_start;
    Vec2f l2 = rhs.m_end - rhs.m_start;

    // Not intersecting if parallel
    float cross = l1.cross(l2);
    if (cross == 0) {
        return extrapolate(math::Infinity);
    }

    Vec2f distance = rhs.m_start - m_start;
    float a = distance.cross(l2) / cross;
    float b = distance.cross(l1) / cross;

    if ((0.0f < a) && (a < 1.0f) && (0.0f < b) && (b < 1.0f)) {
        return m_start + (l1 * a);
    }

    return extrapolate(math::Infinity);
}

} /* namespace sge */
