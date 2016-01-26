//
// Quaternion Implementation.
//
#include "../Lib.h"

namespace sge {

const Quaternion Quaternion::IDENTITY(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion Quaternion::AxisAngle (const Vector3 &axis, const float angle) {
    float sinHalf, cosHalf;
    FMath::SinCos(angle * 0.5f, sinHalf, cosHalf);

    return Quaternion(axis.x * sinHalf, axis.y * sinHalf, axis.z * sinHalf,
                      cosHalf);
}

Vector3 Quaternion::Rotate (const Vector3 &vec) const {
    Quaternion result = (*this) * vec * Conjugate();

    return Vector3(result.i, result.j, result.k);
}

} /* namespace sge */
