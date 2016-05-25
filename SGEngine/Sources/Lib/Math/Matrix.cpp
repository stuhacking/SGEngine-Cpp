//
// Matrix Implementation
//
#include "../Lib.h"

#include <iostream>

namespace sge {

//==================================
// MATRIX 2x2
//==================================

const Mat2f MAT2F_ZERO(0.0f);
const Mat2f MAT2F_ONE(1.0f);
const Mat2f MAT2F_IDENTITY(1.0f, 0.0f,
                           0.0f, 1.0f);

//==================================
// MATRIX 3x3
//==================================

const Mat3f MAT3F_ZERO(0.0f);
const Mat3f MAT3F_ONE(1.0f);
const Mat3f MAT3F_IDENTITY(1.0f, 0.0f, 0.0f,
                           0.0f, 1.0f, 0.0f,
                           0.0f, 0.0f, 1.0f);

template <typename T>
Mat3_T<T> Mat3_T<T>::Inverse () const {
    Mat3_T<T> inv = *this;
    bool success = inv.InverseSelf();

    if (!success) {
        std::cerr << "ERROR -- Matrix3 has no Inverse: " << inv << "\n";
    }

    return inv;
}

template <typename T>
bool Mat3_T<T>::InverseSelf () {
    T a[9];

    T det = Determinant();
    if (0 == det) {
        return false;
    }

    // Calculate sub-determinants
    a[0] = Mat2_T<T>(mat[1].y, mat[1].z, mat[2].y, mat[2].z).Determinant();
    a[1] = Mat2_T<T>(mat[1].x, mat[1].z, mat[2].x, mat[2].z).Determinant();
    a[2] = Mat2_T<T>(mat[1].x, mat[1].y, mat[2].x, mat[2].y).Determinant();

    a[3] = Mat2_T<T>(mat[0].y, mat[0].z, mat[2].y, mat[2].z).Determinant();
    a[4] = Mat2_T<T>(mat[0].x, mat[0].z, mat[2].x, mat[2].z).Determinant();
    a[5] = Mat2_T<T>(mat[0].x, mat[0].y, mat[2].x, mat[2].y).Determinant();

    a[6] = Mat2_T<T>(mat[0].y, mat[0].z, mat[1].y, mat[1].z).Determinant();
    a[7] = Mat2_T<T>(mat[0].x, mat[0].z, mat[1].x, mat[1].z).Determinant();
    a[8] = Mat2_T<T>(mat[0].x, mat[0].y, mat[1].x, mat[1].y).Determinant();

    T invd = 1.0f / det;
    Set(a[0] * invd, -a[3] * invd, a[6] * invd,
        -a[1] * invd, a[4] * invd, -a[7] * invd,
        a[2] * invd, -a[5] * invd, a[8] * invd);

    return true;
}

// Generate code for common types
template class Mat3_T<float>;

//==================================
// MATRIX 4x4
//==================================

const Mat4f MAT4F_ZERO(0.0f);
const Mat4f MAT4F_ONE(1.0f);
const Mat4f MAT4F_IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                           0.0f, 1.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 1.0f, 0.0f,
                           0.0f, 0.0f, 0.0f, 1.0f);

template <typename T>
Mat4_T<T> Mat4_T<T>::Inverse () const {
    Mat4_T<T> inv = *this;
    bool success = inv.InverseSelf();

    if (!success) {
        std::cerr << "ERROR: Matrix4 has no inverse: " << inv << "\n";
    }

    return inv;
}

template <typename T>
bool Mat4_T<T>::InverseSelf () {
    T a[16];

    T det = Determinant();
    if (0 == det) {
        return false;
    }

    // Calculate sub-determinants
    a[0]  = Mat3_T<T>(mat[1].y, mat[1].z, mat[1].w, mat[2].y, mat[2].z, mat[2].w, mat[3].y, mat[3].z, mat[3].w).Determinant();
    a[1]  = Mat3_T<T>(mat[1].x, mat[1].z, mat[1].w, mat[2].x, mat[2].z, mat[2].w, mat[3].x, mat[3].z, mat[3].w).Determinant();
    a[2]  = Mat3_T<T>(mat[1].x, mat[1].y, mat[1].w, mat[2].x, mat[2].y, mat[2].w, mat[3].x, mat[3].y, mat[3].w).Determinant();
    a[3]  = Mat3_T<T>(mat[1].x, mat[1].y, mat[1].z, mat[2].x, mat[2].y, mat[2].z, mat[3].x, mat[3].y, mat[3].z).Determinant();

    a[4]  = Mat3_T<T>(mat[0].y, mat[0].z, mat[0].w, mat[2].y, mat[2].z, mat[2].w, mat[3].y, mat[3].z, mat[3].w).Determinant();
    a[5]  = Mat3_T<T>(mat[0].x, mat[0].z, mat[0].w, mat[2].x, mat[2].z, mat[2].w, mat[3].x, mat[3].z, mat[3].w).Determinant();
    a[6]  = Mat3_T<T>(mat[0].x, mat[0].y, mat[0].w, mat[2].x, mat[2].y, mat[2].w, mat[3].x, mat[3].y, mat[3].w).Determinant();
    a[7]  = Mat3_T<T>(mat[0].x, mat[0].y, mat[0].z, mat[2].x, mat[2].y, mat[2].z, mat[3].x, mat[3].y, mat[3].z).Determinant();

    a[8]  = Mat3_T<T>(mat[0].y, mat[0].z, mat[0].w, mat[1].y, mat[1].z, mat[1].w, mat[3].y, mat[3].z, mat[3].w).Determinant();
    a[9]  = Mat3_T<T>(mat[0].x, mat[0].z, mat[0].w, mat[1].x, mat[1].z, mat[1].w, mat[3].x, mat[3].z, mat[3].w).Determinant();
    a[10] = Mat3_T<T>(mat[0].x, mat[0].y, mat[0].w, mat[1].x, mat[1].y, mat[1].w, mat[3].x, mat[3].y, mat[3].w).Determinant();
    a[11] = Mat3_T<T>(mat[0].x, mat[0].y, mat[0].z, mat[1].x, mat[1].y, mat[1].z, mat[3].x, mat[3].y, mat[3].z).Determinant();

    a[12] = Mat3_T<T>(mat[0].y, mat[0].z, mat[0].w, mat[1].y, mat[1].z, mat[1].w, mat[2].y, mat[2].z, mat[2].w).Determinant();
    a[13] = Mat3_T<T>(mat[0].x, mat[0].z, mat[0].w, mat[1].x, mat[1].z, mat[1].w, mat[2].x, mat[2].z, mat[2].w).Determinant();
    a[14] = Mat3_T<T>(mat[0].x, mat[0].y, mat[0].w, mat[1].x, mat[1].y, mat[1].w, mat[2].x, mat[2].y, mat[2].w).Determinant();
    a[15] = Mat3_T<T>(mat[0].x, mat[0].y, mat[0].z, mat[1].x, mat[1].y, mat[1].z, mat[2].x, mat[2].y, mat[2].z).Determinant();

    T invd = 1.0f / det;
    Set(a[0] * invd, -a[4] * invd, a[8] * invd, -a[12] * invd,
        -a[1] * invd, a[5] * invd, -a[9] * invd, a[13] * invd,
        a[2] * invd, -a[6] * invd, a[10] * invd, -a[14] * invd,
        -a[3] * invd, a[7] * invd, -a[11] * invd, a[15] * invd);

    return true;
}

// Generate code for common types
template class Mat4_T<float>;

} /* namespace sge */
