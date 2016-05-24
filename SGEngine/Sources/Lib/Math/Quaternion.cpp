//
// Quaternion Implementation.
//
#include "../Lib.h"

namespace sge {

const Quaternion Quaternion::IDENTITY(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion Quaternion::AxisAngle (const Vec3f &axis, const float angle) {
    float sinHalf, cosHalf;
    FMath::SinCos(angle * 0.5f, sinHalf, cosHalf);

    return Quaternion(axis.x * sinHalf, axis.y * sinHalf, axis.z * sinHalf,
                      cosHalf);
}

Vec3f Quaternion::Rotate (const Vec3f &vec) const {
    Quaternion result = (*this) * vec * Conjugate();

    return Vec3f(result.i, result.j, result.k);
}

} /* namespace sge */
