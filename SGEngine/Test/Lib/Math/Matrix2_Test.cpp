//
// Matrix3 Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::Vec2f;
using sge::Matrix2;

TEST (Matrix2_Test, Constructors) {
    EXPECT_EQ(Matrix2(0.0f, 0.0f,
                      0.0f, 0.0f),
              Matrix2());
    
    EXPECT_EQ(Matrix2(1.0f, 1.0f,
                      1.0f, 1.0f),
              Matrix2(1.0f));

    EXPECT_EQ(Matrix2(1.0f, 2.0f, 3.0f, 4.0f),
              Matrix2(Vec2f(1.0f, 2.0f), Vec2f(3.0f, 4.0f)));

    float data1[4]  = {1.0f, 2.0f, 3.0f, 4.0f};
    EXPECT_EQ(Matrix2(1.0f, 2.0f, 3.0f, 4.0f),
              Matrix2(data1));

    float data2[2][2] = {{1.0f, 2.0f}, {3.0f, 4.0f}};
    EXPECT_EQ(Matrix2(1.0f, 2.0f, 3.0f, 4.0f),
              Matrix2(data2));
}

TEST (Matrix2_Test, add) {
    EXPECT_EQ(Matrix2(4.0f, 3.0f, 2.0f, 1.0f),
              Matrix2(1.0f, 4.0f, 5.0f, 0.0f) + Matrix2(3.0f, -1.0f, -3.0f, 1.0f));

    Matrix2 M = Matrix2(1.0f, 4.0f, 5.0f, 0.0f);
    M += Matrix2(3.0f, -1.0f, -3.0f, 1.0f);

    EXPECT_EQ(Matrix2(4.0f, 3.0f, 2.0f, 1.0f), M);
}

TEST (Matrix2_Test, sub) {
    EXPECT_EQ(Matrix2(2.0f, 3.0f, 0.0f, 5.0f),
              Matrix2(3.0f, 3.0f, 1.0f, 2.0f) - Matrix2(1.0f, 0.0f, 1.0f, -3.0f));

    Matrix2 M = Matrix2(3.0f, 3.0f, 1.0f, 2.0f);
    M -= Matrix2(1.0f, 0.0f, 1.0f, -3.0f);

    EXPECT_EQ(Matrix2(2.0f, 3.0f, 0.0f, 5.0f), M);
}

TEST (Matrix2_Test, scale) {
    EXPECT_EQ(Matrix2(2.0f, 4.0f, 3.0f, -2.0f),
              Matrix2(1.0f, 2.0f, 1.5f, -1.0f) * 2.0f);
    
    EXPECT_EQ(Matrix2(2.0f, 4.0f, 3.0f, -2.0f),
              2.0f * Matrix2(1.0f, 2.0f, 1.5f, -1.0f));

    Matrix2 M = Matrix2(1.0f, 2.0f, 1.5f, -1.0f);
    M *= 2.0f;

    EXPECT_EQ(Matrix2(2.0f, 4.0f, 3.0f, -2.0f), M);
}

TEST (Matrix2_Test, multiplication) {
    Matrix2 M = Matrix2(1.0f, 2.0f, 2.0f, 1.0f);
    Matrix2 N = Matrix2(2.0f, 3.0f, 1.0f, 1.5f);
    EXPECT_EQ(M, M * Matrix2::IDENTITY);

    EXPECT_EQ(Matrix2(4.0f, 6.0f, 5.0f, 7.5f), M * N);
    EXPECT_EQ(Matrix2(8.0f, 7.0f, 4.0f, 3.5f), N * M);

    M *= N;

    EXPECT_EQ(Matrix2(4.0f, 6.0f, 5.0f, 7.5f), M);
}
