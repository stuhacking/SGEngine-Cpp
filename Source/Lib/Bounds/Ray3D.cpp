//
// Ray3D Implementation
//
#include "../Lib.h"

namespace sge {

Vec3f Ray3D::Intersection (const Ray3D &rhs) const {
    Vec3f l1 = end - start;
    Vec3f l2 = rhs.end - rhs.start;

    // Not intersecting if parallel
    float cross = l1.Cross(l2).Length();
    if (cross == 0) {
        return Extrapolate(FMath::INFTY);
    }

    Vec3f distance = rhs.start - start;
    float a = distance.Cross(l2).Length() / cross;
    float b = distance.Cross(l1).Length() / cross;

    if ((0.0f < a) && (a < 1.0f) && (0.0f < b) && (b < 1.0f)) {
        return start + (l1 * a);
    }

    return Extrapolate(FMath::INFTY);
}

} /* namespace sge */
