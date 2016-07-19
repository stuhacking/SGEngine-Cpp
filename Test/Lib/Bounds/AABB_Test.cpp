//
// Axis-Aligned Bounding Box Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::FMath;
using sge::Vec3f;
using sge::AABB;

TEST (AABB_Test, Constructors) {
    EXPECT_EQ(AABB(), AABB(FMath::INFTY, FMath::INFTY, FMath::INFTY,
                           -FMath::INFTY, -FMath::INFTY, -FMath::INFTY));

    EXPECT_EQ(AABB(1.0f, 1.0f, 1.0f, 3.0f, 3.0f, 3.0f),
              AABB(Vec3f(1.0f, 1.0f, 1.0f), Vec3f(3.0f, 3.0f, 3.0f)));
}

TEST (AABB_Test, Clear) {
    AABB r = AABB(0.0f, 0.0f, 0.0f, 3.0f, 5.0f, 4.0f);

    r.Clear();

    EXPECT_FLOAT_EQ(FMath::INFTY, r.Volume());
    EXPECT_FALSE(r.Contains(sge::Vec3f::ZERO));
}

// Basic Tests
//     8                        +--------------5
//                              |              |
//     7              +----7    |    +----4    |
//                    |    |    |    |    |    |
//     6    +----4   F5----+----5   H3----+    |
//          |    |         |    |              |
//     5   E3----+         |   G2--------------+
//                         |    |
//     4         +---------+----+---------7
//               |         |    |         |
//     3    +----+----3    |    |    +----+----8
//          |    |    |    |    |    |    |    |
//     2    |   B2----+----+----+----+----+    |
//          |         |    |    |    |         |
//     1   A1---------+   C3----+   D5---------+
//
//     0    1    2    3    4    5    6    7    8
//
static const AABB A = AABB(1.0f, 1.0f, 1.0f, 3.0f, 3.0f, 3.0f);
static const AABB B = AABB(2.0f, 2.0f, 2.0f, 7.0f, 4.0f, 7.0f);
static const AABB C = AABB(4.0f, 1.0f, 3.0f, 5.0f, 6.0f, 5.0f);
static const AABB D = AABB(6.0f, 1.0f, 5.0f, 8.0f, 3.0f, 8.0f);
static const AABB E = AABB(1.0f, 5.0f, 3.0f, 2.0f, 6.0f, 4.0f);
static const AABB F = AABB(3.0f, 6.0f, 5.0f, 4.0f, 7.0f, 7.0f);
static const AABB G = AABB(5.0f, 5.0f, 2.0f, 8.0f, 8.0f, 5.0f);
static const AABB H = AABB(6.0f, 6.0f, 3.0f, 7.0f, 7.0f, 4.0f);

TEST (AABB_Test, Intersects) {
    EXPECT_TRUE(A.Intersects(A));
    EXPECT_TRUE(A.Intersects(B));
    EXPECT_TRUE(B.Intersects(A));
    EXPECT_TRUE(B.Intersects(C));
    EXPECT_TRUE(C.Intersects(B));
    EXPECT_TRUE(B.Intersects(D));
    EXPECT_TRUE(F.Intersects(C));
    EXPECT_TRUE(C.Intersects(F));
    EXPECT_TRUE(C.Intersects(G));
    EXPECT_TRUE(G.Intersects(H));
    EXPECT_TRUE(H.Intersects(G));

    EXPECT_FALSE(E.Intersects(A));
    EXPECT_FALSE(A.Intersects(E));
}

TEST (AABB_Test, Center) {
    EXPECT_EQ(Vec3f(2.0f, 2.0f, 2.0f), A.Center());
    EXPECT_EQ(Vec3f(4.5f, 3.0f, 4.5f), B.Center());
}

TEST (AABB_Test, Volume) {
    EXPECT_FLOAT_EQ(8.0f, A.Volume());
    EXPECT_FLOAT_EQ(27.0f, G.Volume());
    EXPECT_FLOAT_EQ(10.0f, C.Volume());
    EXPECT_FLOAT_EQ(1.0f, E.Volume());
}

TEST (AABB_Test, ContainsPoint) {
    EXPECT_TRUE(A.Contains(Vec3f(2.0f, 2.0f, 2.0f)));
    EXPECT_TRUE(C.Contains(Vec3f(5.0f, 6.0f, 5.0f)));

    EXPECT_FALSE(E.Contains(Vec3f(0.0f, 0.0f, 0.0f)));
}

TEST (AABB_Test, ContainsBox) {
    EXPECT_TRUE(G.Contains(H));

    EXPECT_FALSE(H.Contains(G));
    EXPECT_FALSE(A.Contains(B));
}
