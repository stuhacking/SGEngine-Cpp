//
// Mat4f Tests
//
#include <gtest/gtest.h>
#include "lib.h"

TEST (Mat4f_Test, Inverse) {
    Mat4f M = Mat4f(2.0f, 2.0f, 4.0f, 0.0f,
                        4.0f, 2.0f, 6.0f, 0.0f,
                        4.0f, 2.0f, 2.0f, 0.0f,
                        2.0f, 4.0f, 2.0f, 1.0f);

    EXPECT_EQ(Mat4f(-0.5f, 0.25f, 0.25f, 0.0f,
                      1.0f, -0.75f, 0.25f, 0.0f,
                      0.0f, 0.25f, -0.25f, 0.0f,
                      -3.0f, 2.0f, -1.0f, 1.0f),
              M.inverse());

    M.inverseSelf();

    EXPECT_EQ(Mat4f(-0.5f, 0.25f, 0.25f, 0.0f,
                      1.0f, -0.75f, 0.25f, 0.0f,
                      0.0f, 0.25f, -0.25f, 0.0f,
                      -3.0f, 2.0f, -1.0f, 1.0f),
              M);
}
