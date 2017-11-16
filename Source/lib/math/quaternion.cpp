//
// Quat4f Implementation.
//
#include "../lib.h"

const Quat4f Quat4f_Identity {0.0f, 0.0f, 0.0f, 1.0f};



Vec3f Quat4f::rotate (const Vec3f &vec) const {
    Quat4f result = (*this) * vec * conjugate();

    return Vec3f(result.i, result.j, result.k);
}
