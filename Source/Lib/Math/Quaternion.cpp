//
// Quat4f Implementation.
//
#include "../Lib.h"

namespace sge {

const Quat4f Quat4f::IDENTITY{0.0f, 0.0f, 0.0f, 1.0f};

Quat4f Quat4f::AxisAngle (const Vec3f &axis, const float angle) {
    float sinHalf, cosHalf;
    FMath::SinCos(angle * 0.5f, sinHalf, cosHalf);

    return Quat4f(axis.x * sinHalf, axis.y * sinHalf, axis.z * sinHalf,
                  cosHalf);
}


Vec3f Quat4f::Rotate (const Vec3f &vec) const {
    Quat4f result = (*this) * vec * Conjugate();

    return Vec3f(result.i, result.j, result.k);
}

} /* namespace sge */
