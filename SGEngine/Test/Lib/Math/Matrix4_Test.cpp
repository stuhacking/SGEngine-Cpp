//
// Matrix4 Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::Vec4f;
using sge::Matrix4;

TEST (Matrix4_Test, Inverse) {
    Matrix4 M = Matrix4(2.0f, 2.0f, 4.0f, 0.0f,
                        4.0f, 2.0f, 6.0f, 0.0f,
                        4.0f, 2.0f, 2.0f, 0.0f,
                        2.0f, 4.0f, 2.0f, 1.0f);
    
    EXPECT_EQ(Matrix4(-0.5f, 0.25f, 0.25f, 0.0f,
                      1.0f, -0.75f, 0.25f, 0.0f,
                      0.0f, 0.25f, -0.25f, 0.0f,
                      -3.0f, 2.0f, -1.0f, 1.0f),
              M.Inverse());
    
    M.InverseSelf();
    
    EXPECT_EQ(Matrix4(-0.5f, 0.25f, 0.25f, 0.0f,
                      1.0f, -0.75f, 0.25f, 0.0f,
                      0.0f, 0.25f, -0.25f, 0.0f,
                      -3.0f, 2.0f, -1.0f, 1.0f),
              M);
}
