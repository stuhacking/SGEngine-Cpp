//
// Ray3D Implementation
//
#include "../lib.h"

namespace sge {

Vec3f Ray3D::intersection (const Ray3D &rhs) const {
    Vec3f l1 = end - start;
    Vec3f l2 = rhs.end - rhs.start;

    // Not intersecting if parallel
    float cross = l1.cross(l2).mag();
    if (cross == 0) {
        return extrapolate(math::kInfty);
    }

    Vec3f distance = rhs.start - start;
    float a = distance.cross(l2).mag() / cross;
    float b = distance.cross(l1).mag() / cross;

    if ((0.0f < a) && (a < 1.0f) && (0.0f < b) && (b < 1.0f)) {
        return start + (l1 * a);
    }

    return extrapolate(math::kInfty);
}

} /* namespace sge */
