//
//Vector Implementation.
//
#include "../Lib.h"

namespace sge {

//==================================
// VECTOR 2
//==================================

template <typename T> const Vec2_T<T> Vec2_T<T>::ZERO(0);
template <typename T> const Vec2_T<T> Vec2_T<T>::ONE(1);
template <typename T> const Vec2_T<T> Vec2_T<T>::X(1, 0);
template <typename T> const Vec2_T<T> Vec2_T<T>::Y(0, 1);

// Generate code for common types
template class Vec2_T<float>;

//==================================
// VECTOR 3
//==================================

template <typename T> const Vec3_T<T> Vec3_T<T>::ZERO(0);
template <typename T> const Vec3_T<T> Vec3_T<T>::ONE(1);
template <typename T> const Vec3_T<T> Vec3_T<T>::X(1, 0, 0);
template <typename T> const Vec3_T<T> Vec3_T<T>::Y(0, 1, 0);
template <typename T> const Vec3_T<T> Vec3_T<T>::Z(0, 0, 1);

template <typename T>
Vec3_T<T> Vec3_T<T>::Rotate (const T angle, const Vec3_T<T> &axis) const {
    Vec3_T<T> rot = *this;
    rot.RotateSelf(angle, axis);

    return rot;
}

template <typename T>
void Vec3_T<T>::RotateSelf (const T angle, const Vec3_T<T> &axis) {
    *this = Quat4f::AxisAngle(axis, angle).Rotate(*this);
}

// Generate code for common types.
template class Vec3_T<float>;

//==================================
// VECTOR 4
//==================================

template <typename T> const Vec4_T<T> Vec4_T<T>::ZERO(0);
template <typename T> const Vec4_T<T> Vec4_T<T>::ONE(1);
template <typename T> const Vec4_T<T> Vec4_T<T>::X(1, 0, 0, 0);
template <typename T> const Vec4_T<T> Vec4_T<T>::Y(0, 1, 0, 0);
template <typename T> const Vec4_T<T> Vec4_T<T>::Z(0, 0, 1, 0);
template <typename T> const Vec4_T<T> Vec4_T<T>::W(0, 0, 0, 1);

// Generate code for common types
template class Vec4_T<float>;

} /* namespace sge */
