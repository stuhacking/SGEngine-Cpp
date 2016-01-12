/**
 * Vector Implementation.
 */
#include "../Lib.h"

namespace sge {

//==================================
// VECTOR 2
//==================================

const Vector2 Vector2::ZERO(0.0f);
const Vector2 Vector2::ONE(1.0f);
const Vector2 Vector2::X(1.0f, 0.0f);
const Vector2 Vector2::Y(0.0f, 1.0f);

//==================================
// VECTOR 3
//==================================

const Vector3 Vector3::ZERO(0.0f);
const Vector3 Vector3::ONE(1.0f);
const Vector3 Vector3::X(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Y(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Z(0.0f, 0.0f, 1.0f);

Vector3 Vector3::Rotate (const float angle, const Vector3 &axis) const {
    Vector3 rot = *this;
    rot.RotateSelf(angle, axis);

    return rot;
}

void Vector3::RotateSelf (const float angle, const Vector3 &axis) {
    float sinHalfAngle, cosHalfAngle;
    FMath::SinCos(TO_RADIANS(angle / 2.0f), sinHalfAngle, cosHalfAngle);

    Quaternion rotation = Quaternion(axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle, cosHalfAngle);
    Quaternion w = rotation * (*this) * rotation.Conjugate();

    x = w.i;
    y = w.j;
    z = w.k;
}

//==================================
// VECTOR 4
//==================================

const Vector4 Vector4::ZERO(0.0f);
const Vector4 Vector4::ONE(1.0f);
const Vector4 Vector4::X(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::Y(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::Z(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::W(0.0f, 0.0f, 0.0f, 1.0f);

} /* namespace sge */
