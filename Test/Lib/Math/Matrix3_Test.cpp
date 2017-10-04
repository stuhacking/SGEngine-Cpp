//
// Mat3f Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

TEST (Mat3f_Test, Constructors) {
    EXPECT_EQ(Mat3f(0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f),
              Mat3f());

    EXPECT_EQ(Mat3f(1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f),
              Mat3f(1.0f));
}

TEST (Mat3f_Test, Inverse) {
    Mat3f M = Mat3f(2.0f, 2.0f, 3.0f,
                    4.0f, 2.0f, 5.0f,
                    4.0f, 2.0f, 1.0f);

    EXPECT_EQ(Mat3f(-0.5f, 0.25f, 0.25f,
                    1.0f, -0.625f, 0.125f,
                    0.0f, 0.25f, -0.25f),
              M.Inverse());

    M.InverseSelf();

    EXPECT_EQ(Mat3f(-0.5f, 0.25f, 0.25f,
                    1.0f, -0.625f, 0.125f,
                    0.0f, 0.25f, -0.25f),
              M);
}
