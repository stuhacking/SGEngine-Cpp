//
// Axis-Aligned Bounding Box Tests
//
#include <gtest/gtest.h>
#include "lib.h"

using sge::Aabb;

TEST (Aabb_Test, Constructors) {
    EXPECT_EQ(Aabb(), Aabb(math::kInfty, math::kInfty, math::kInfty,
                           -math::kInfty, -math::kInfty, -math::kInfty));

    EXPECT_EQ(Aabb(1.0f, 1.0f, 1.0f, 3.0f, 3.0f, 3.0f),
              Aabb(Vec3f(1.0f, 1.0f, 1.0f), Vec3f(3.0f, 3.0f, 3.0f)));
}

TEST (Aabb_Test, Clear) {
    Aabb r = Aabb(0.0f, 0.0f, 0.0f, 3.0f, 5.0f, 4.0f);

    r.reset();

    EXPECT_FLOAT_EQ(math::kInfty, r.volume());
    EXPECT_FALSE(sge::contains(r, Vec3f_Zero));
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
static const Aabb A = Aabb(1.0f, 1.0f, 1.0f, 3.0f, 3.0f, 3.0f);
static const Aabb B = Aabb(2.0f, 2.0f, 2.0f, 7.0f, 4.0f, 7.0f);
static const Aabb C = Aabb(4.0f, 1.0f, 3.0f, 5.0f, 6.0f, 5.0f);
static const Aabb D = Aabb(6.0f, 1.0f, 5.0f, 8.0f, 3.0f, 8.0f);
static const Aabb E = Aabb(1.0f, 5.0f, 3.0f, 2.0f, 6.0f, 4.0f);
static const Aabb F = Aabb(3.0f, 6.0f, 5.0f, 4.0f, 7.0f, 7.0f);
static const Aabb G = Aabb(5.0f, 5.0f, 2.0f, 8.0f, 8.0f, 5.0f);
static const Aabb H = Aabb(6.0f, 6.0f, 3.0f, 7.0f, 7.0f, 4.0f);


TEST (Aabb_Test, Center) {
    EXPECT_EQ(Vec3f(2.0f, 2.0f, 2.0f), A.center());
    EXPECT_EQ(Vec3f(4.5f, 3.0f, 4.5f), B.center());
}

TEST (Aabb_Test, Volume) {
    EXPECT_FLOAT_EQ(8.0f, A.volume());
    EXPECT_FLOAT_EQ(27.0f, G.volume());
    EXPECT_FLOAT_EQ(10.0f, C.volume());
    EXPECT_FLOAT_EQ(1.0f, E.volume());
}
