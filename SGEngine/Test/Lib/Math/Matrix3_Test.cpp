//
// Matrix3 Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::Vec3f;
using sge::Matrix3;

TEST (Matrix3_Test, Constructors) {
    EXPECT_EQ(Matrix3(0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f),
              Matrix3());
    
    EXPECT_EQ(Matrix3(1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f),
              Matrix3(1.0f));
}

TEST (Matrix3_Test, Inverse) {
    Matrix3 M = Matrix3(2.0f, 2.0f, 3.0f,
                        4.0f, 2.0f, 5.0f,
                        4.0f, 2.0f, 1.0f);
    
    EXPECT_EQ(Matrix3(-0.5f, 0.25f, 0.25f,
                      1.0f, -0.625f, 0.125f,
                      0.0f, 0.25f, -0.25f),
              M.Inverse());
    
    M.InverseSelf();
    
    EXPECT_EQ(Matrix3(-0.5f, 0.25f, 0.25f,
                      1.0f, -0.625f, 0.125f,
                      0.0f, 0.25f, -0.25f),
              M);
}
