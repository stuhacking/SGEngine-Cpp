//
// Quat4f Implementation.
//
#include "../Lib.h"

namespace sge {

const Quat4f QUAT4F_IDENTITY(0.0f, 0.0f, 0.0f, 1.0f);

template <typename T>
Quat4_T<T> Quat4_T<T>::AxisAngle (const Vec3_T<T> &axis, const T angle) {
    T sinHalf, cosHalf;
    FMath::SinCos(angle * 0.5f, sinHalf, cosHalf);

    return Quat4_T<T>(axis.x * sinHalf, axis.y * sinHalf, axis.z * sinHalf,
                      cosHalf);
}

template <typename T>
Vec3_T<T> Quat4_T<T>::Rotate (const Vec3_T<T> &vec) const {
    Quat4_T<T> result = (*this) * vec * Conjugate();

    return Vec3_T<T>(result.i, result.j, result.k);
}

// Generate code for common types
template class Quat4_T<float>;

} /* namespace sge */
