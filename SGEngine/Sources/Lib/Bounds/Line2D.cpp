//
// Line2D Implementation
//
#include "../Lib.h"

namespace sge {

bool Line2D::Intersects(const Line2D &rhs) const {
    Vector2 l1 = m_end - m_start;
    Vector2 l2 = rhs.m_end - rhs.m_start;

    // Not intersecting if parallel
    float cross = l1.Cross(l2);
    if (cross == 0) {
        return false;
    }

    Vector2 distance = rhs.m_start - m_start;
    float a = distance.Cross(l1) / cross;
    float b = distance.Cross(l2) / cross;

    return (0.0f < a) && (a < 1.0f) && (0.0f < b) && (b < 1.0f);
}

Vector2 Line2D::Intersection(const Line2D &rhs) const {
    Vector2 l1 = m_end - m_start;
    Vector2 l2 = rhs.m_end - rhs.m_start;

    // Not intersecting if parallel
    float cross = l1.Cross(l2);
    if (cross == 0) {
        return l1.SetLength(FMath::INFTY);
    }

    Vector2 distance = rhs.m_start - m_start;
    float a = distance.Cross(l2) / cross;
    float b = distance.Cross(l1) / cross;

    if ((0.0f < a) && (a < 1.0f) && (0.0f < b) && (b < 1.0f)) {
        return m_start + (l1 * a);
    }

    return l1.SetLength(FMath::INFTY);
}

} /* namespace sge */
