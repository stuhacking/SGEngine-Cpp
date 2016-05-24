//
// Line2D Implementation
//
#include "../Lib.h"

namespace sge {

bool Line2D::Intersects(const Line2D &rhs) const {
    Vec2f l1 = m_end - m_start;
    Vec2f l2 = rhs.m_end - rhs.m_start;

    // Not intersecting if parallel
    float cross = l1.Cross(l2);
    if (cross == 0) {
        return false;
    }

    Vec2f distance = rhs.m_start - m_start;
    float a = distance.Cross(l1) / cross;
    float b = distance.Cross(l2) / cross;

    return (0.0f < a) && (a < 1.0f) && (0.0f < b) && (b < 1.0f);
}

Vec2f Line2D::Intersection(const Line2D &rhs) const {
    Vec2f l1 = m_end - m_start;
    Vec2f l2 = rhs.m_end - rhs.m_start;

    // Not intersecting if parallel
    float cross = l1.Cross(l2);
    if (cross == 0) {
        return l1.SetLength(FMath::INFTY);
    }

    Vec2f distance = rhs.m_start - m_start;
    float a = distance.Cross(l2) / cross;
    float b = distance.Cross(l1) / cross;

    if ((0.0f < a) && (a < 1.0f) && (0.0f < b) && (b < 1.0f)) {
        return m_start + (l1 * a);
    }

    return l1.SetLength(FMath::INFTY);
}

} /* namespace sge */
