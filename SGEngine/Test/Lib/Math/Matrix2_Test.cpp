//
// Mat3f Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::Vec2f;
using sge::Mat2f;

TEST (Mat2f_Test, Constructors) {
    EXPECT_EQ(Mat2f(0.0f, 0.0f,
                      0.0f, 0.0f),
              Mat2f());

    EXPECT_EQ(Mat2f(1.0f, 1.0f,
                      1.0f, 1.0f),
              Mat2f(1.0f));

    EXPECT_EQ(Mat2f(1.0f, 2.0f, 3.0f, 4.0f),
              Mat2f(Vec2f(1.0f, 2.0f), Vec2f(3.0f, 4.0f)));

    float data1[4]  = {1.0f, 2.0f, 3.0f, 4.0f};
    EXPECT_EQ(Mat2f(1.0f, 2.0f, 3.0f, 4.0f),
              Mat2f(data1));

    float data2[2][2] = {{1.0f, 2.0f}, {3.0f, 4.0f}};
    EXPECT_EQ(Mat2f(1.0f, 2.0f, 3.0f, 4.0f),
              Mat2f(data2));
}

TEST (Mat2f_Test, add) {
    EXPECT_EQ(Mat2f(4.0f, 3.0f, 2.0f, 1.0f),
              Mat2f(1.0f, 4.0f, 5.0f, 0.0f) + Mat2f(3.0f, -1.0f, -3.0f, 1.0f));

    Mat2f M = Mat2f(1.0f, 4.0f, 5.0f, 0.0f);
    M += Mat2f(3.0f, -1.0f, -3.0f, 1.0f);

    EXPECT_EQ(Mat2f(4.0f, 3.0f, 2.0f, 1.0f), M);
}

TEST (Mat2f_Test, sub) {
    EXPECT_EQ(Mat2f(2.0f, 3.0f, 0.0f, 5.0f),
              Mat2f(3.0f, 3.0f, 1.0f, 2.0f) - Mat2f(1.0f, 0.0f, 1.0f, -3.0f));

    Mat2f M = Mat2f(3.0f, 3.0f, 1.0f, 2.0f);
    M -= Mat2f(1.0f, 0.0f, 1.0f, -3.0f);

    EXPECT_EQ(Mat2f(2.0f, 3.0f, 0.0f, 5.0f), M);
}

TEST (Mat2f_Test, scale) {
    EXPECT_EQ(Mat2f(2.0f, 4.0f, 3.0f, -2.0f),
              Mat2f(1.0f, 2.0f, 1.5f, -1.0f) * 2.0f);

    EXPECT_EQ(Mat2f(2.0f, 4.0f, 3.0f, -2.0f),
              2.0f * Mat2f(1.0f, 2.0f, 1.5f, -1.0f));

    Mat2f M = Mat2f(1.0f, 2.0f, 1.5f, -1.0f);
    M *= 2.0f;

    EXPECT_EQ(Mat2f(2.0f, 4.0f, 3.0f, -2.0f), M);
}

TEST (Mat2f_Test, multiplication) {
    Mat2f M = Mat2f(1.0f, 2.0f, 2.0f, 1.0f);
    Mat2f N = Mat2f(2.0f, 3.0f, 1.0f, 1.5f);
    EXPECT_EQ(M, M * sge::MAT2F_IDENTITY);

    EXPECT_EQ(Mat2f(4.0f, 6.0f, 5.0f, 7.5f), M * N);
    EXPECT_EQ(Mat2f(8.0f, 7.0f, 4.0f, 3.5f), N * M);

    M *= N;

    EXPECT_EQ(Mat2f(4.0f, 6.0f, 5.0f, 7.5f), M);
}
