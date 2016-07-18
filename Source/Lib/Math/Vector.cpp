//
//Vector Implementation.
//
#include "../Lib.h"

namespace sge {

//==================================
// VECTOR 2
//==================================

const Vec2f Vec2f::ZERO(0.0f);
const Vec2f Vec2f::ONE(1.0f);
const Vec2f Vec2f::X(1.0f, 0.0f);
const Vec2f Vec2f::Y(0.0f, 1.0f);

//==================================
// VECTOR 3
//==================================

const Vec3f Vec3f::ZERO(0.0f);
const Vec3f Vec3f::ONE(1.0f);
const Vec3f Vec3f::X(1.0f, 0.0f, 0.0f);
const Vec3f Vec3f::Y(0.0f, 1.0f, 0.0f);
const Vec3f Vec3f::Z(0.0f, 0.0f, 1.0f);


Vec3f Vec3f::Rotate (const float angle, const Vec3f &axis) const {
    Vec3f rot = *this;
    rot.RotateSelf(angle, axis);

    return rot;
}


void Vec3f::RotateSelf (const float angle, const Vec3f &axis) {
    *this = Quat4f::AxisAngle(axis, angle).Rotate(*this);
}

//==================================
// VECTOR 4
//==================================

const Vec4f Vec4f::ZERO(0.0f);
const Vec4f Vec4f::ONE(1.0f);
const Vec4f Vec4f::X(1.0f, 0.0f, 0.0f, 0.0f);
const Vec4f Vec4f::Y(0.0f, 1.0f, 0.0f, 0.0f);
const Vec4f Vec4f::Z(0.0f, 0.0f, 1.0f, 0.0f);
const Vec4f Vec4f::W(0.0f, 0.0f, 0.0f, 1.0f);

} /* namespace sge */
