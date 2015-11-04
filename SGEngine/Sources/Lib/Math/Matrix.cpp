//
// Matrix Implementation
//
#include "../Lib.h"

#include <iostream>

namespace sge {

//==================================
// MATRIX 2x2
//==================================

const Matrix2 Matrix2::ZERO(0.0f);
const Matrix2 Matrix2::ONE(1.0f);
const Matrix2 Matrix2::IDENTITY(1.0f, 0.0f,
                                0.0f, 1.0f);

//==================================
// MATRIX 3x3
//==================================

const Matrix3 Matrix3::ZERO(0.0f);
const Matrix3 Matrix3::ONE(1.0f);
const Matrix3 Matrix3::IDENTITY(1.0f, 0.0f, 0.0f,
                                0.0f, 1.0f, 0.0f,
                                0.0f, 0.0f, 1.0f);

Matrix3 Matrix3::Inverse () const {
    Matrix3 inv = *this;
    bool success = inv.InverseSelf();

    if (!success) {
        std::cerr << "ERROR: Matrix3 has no inverse: " << inv << "\n";
    }
    
    return inv;
}
    
bool Matrix3::InverseSelf () {
    float a[9];

    float det = Determinant();
    if (0 == det) {
        return false;
    }

    // Calculate sub-determinants
    a[0] = Matrix2(mat[1].y, mat[1].z, mat[2].y, mat[2].z).Determinant();
    a[1] = Matrix2(mat[1].x, mat[1].z, mat[2].x, mat[2].z).Determinant();
    a[2] = Matrix2(mat[1].x, mat[1].y, mat[2].x, mat[2].y).Determinant();

    a[3] = Matrix2(mat[0].y, mat[0].z, mat[2].y, mat[2].z).Determinant();
    a[4] = Matrix2(mat[0].x, mat[0].z, mat[2].x, mat[2].z).Determinant();
    a[5] = Matrix2(mat[0].x, mat[0].y, mat[2].x, mat[2].y).Determinant();

    a[6] = Matrix2(mat[0].y, mat[0].z, mat[1].y, mat[1].z).Determinant();
    a[7] = Matrix2(mat[0].x, mat[0].z, mat[1].x, mat[1].z).Determinant();
    a[8] = Matrix2(mat[0].x, mat[0].y, mat[1].x, mat[1].y).Determinant();

    float invd = 1.0f / det;
    Set(a[0] * invd, -a[3] * invd, a[6] * invd,
        -a[1] * invd, a[4] * invd, -a[7] * invd,
        a[2] * invd, -a[5] * invd, a[8] * invd);

    return true;
}

//==================================
// MATRIX 4x4
//==================================

const Matrix4 Matrix4::ZERO(0.0f);
const Matrix4 Matrix4::ONE(1.0f);
const Matrix4 Matrix4::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 1.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 1.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f);

Matrix4 Matrix4::Inverse () const {
    Matrix4 inv = *this;
    bool success = inv.InverseSelf();

    if (!success) {
        std::cerr << "ERROR: Matrix4 has no inverse: " << inv << "\n";
    }
    
    return inv;
}

bool Matrix4::InverseSelf () {
    float a[16];
    
    float det = Determinant();
    if (0 == det) {
        return false;
    }

    // Calculate sub-determinants
    a[0]  = Matrix3(mat[1].y, mat[1].z, mat[1].w, mat[2].y, mat[2].z, mat[2].w, mat[3].y, mat[3].z, mat[3].w).Determinant();
    a[1]  = Matrix3(mat[1].x, mat[1].z, mat[1].w, mat[2].x, mat[2].z, mat[2].w, mat[3].x, mat[3].z, mat[3].w).Determinant();
    a[2]  = Matrix3(mat[1].x, mat[1].y, mat[1].w, mat[2].x, mat[2].y, mat[2].w, mat[3].x, mat[3].y, mat[3].w).Determinant();
    a[3]  = Matrix3(mat[1].x, mat[1].y, mat[1].z, mat[2].x, mat[2].y, mat[2].z, mat[3].x, mat[3].y, mat[3].z).Determinant();

    a[4]  = Matrix3(mat[0].y, mat[0].z, mat[0].w, mat[2].y, mat[2].z, mat[2].w, mat[3].y, mat[3].z, mat[3].w).Determinant();
    a[5]  = Matrix3(mat[0].x, mat[0].z, mat[0].w, mat[2].x, mat[2].z, mat[2].w, mat[3].x, mat[3].z, mat[3].w).Determinant();
    a[6]  = Matrix3(mat[0].x, mat[0].y, mat[0].w, mat[2].x, mat[2].y, mat[2].w, mat[3].x, mat[3].y, mat[3].w).Determinant();
    a[7]  = Matrix3(mat[0].x, mat[0].y, mat[0].z, mat[2].x, mat[2].y, mat[2].z, mat[3].x, mat[3].y, mat[3].z).Determinant();

    a[8]  = Matrix3(mat[0].y, mat[0].z, mat[0].w, mat[1].y, mat[1].z, mat[1].w, mat[3].y, mat[3].z, mat[3].w).Determinant();
    a[9]  = Matrix3(mat[0].x, mat[0].z, mat[0].w, mat[1].x, mat[1].z, mat[1].w, mat[3].x, mat[3].z, mat[3].w).Determinant();
    a[10] = Matrix3(mat[0].x, mat[0].y, mat[0].w, mat[1].x, mat[1].y, mat[1].w, mat[3].x, mat[3].y, mat[3].w).Determinant();
    a[11] = Matrix3(mat[0].x, mat[0].y, mat[0].z, mat[1].x, mat[1].y, mat[1].z, mat[3].x, mat[3].y, mat[3].z).Determinant();

    a[12] = Matrix3(mat[0].y, mat[0].z, mat[0].w, mat[1].y, mat[1].z, mat[1].w, mat[2].y, mat[2].z, mat[2].w).Determinant();
    a[13] = Matrix3(mat[0].x, mat[0].z, mat[0].w, mat[1].x, mat[1].z, mat[1].w, mat[2].x, mat[2].z, mat[2].w).Determinant();
    a[14] = Matrix3(mat[0].x, mat[0].y, mat[0].w, mat[1].x, mat[1].y, mat[1].w, mat[2].x, mat[2].y, mat[2].w).Determinant();
    a[15] = Matrix3(mat[0].x, mat[0].y, mat[0].z, mat[1].x, mat[1].y, mat[1].z, mat[2].x, mat[2].y, mat[2].z).Determinant();

    float invd = 1.0f / det;
    Set(a[0] * invd, -a[4] * invd, a[8] * invd, -a[12] * invd,
        -a[1] * invd, a[5] * invd, -a[9] * invd, a[13] * invd,
        a[2] * invd, -a[6] * invd, a[10] * invd, -a[14] * invd,
        -a[3] * invd, a[7] * invd, -a[11] * invd, a[15] * invd);

    return true;
}

} /* namespace sge */
