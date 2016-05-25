//
//Vector Implementation.
//
#include "../Lib.h"

namespace sge {

//==================================
// VECTOR 2
//==================================

const Vec2f VEC2F_ZERO(0.0f);
const Vec2f VEC2F_ONE(1.0f);
const Vec2f VEC2F_X(1.0f, 0.0f);
const Vec2f VEC2F_Y(0.0f, 1.0f);

//==================================
// VECTOR 3
//==================================

const Vec3f VEC3F_ZERO(0.0f);
const Vec3f VEC3F_ONE(1.0f);
const Vec3f VEC3F_X(1.0f, 0.0f, 0.0f);
const Vec3f VEC3F_Y(0.0f, 1.0f, 0.0f);
const Vec3f VEC3F_Z(0.0f, 0.0f, 1.0f);

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

const Vec4f VEC4F_ZERO(0.0f);
const Vec4f VEC4F_ONE(1.0f);
const Vec4f VEC4F_X(1.0f, 0.0f, 0.0f, 0.0f);
const Vec4f VEC4F_Y(0.0f, 1.0f, 0.0f, 0.0f);
const Vec4f VEC4F_Z(0.0f, 0.0f, 1.0f, 0.0f);
const Vec4f VEC4F_W(0.0f, 0.0f, 0.0f, 1.0f);

} /* namespace sge */
