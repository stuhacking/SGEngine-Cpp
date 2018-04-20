//
// Rect bounds Tests.
//
#include <gtest/gtest.h>
#include "lib.h"

using sge::Rect;

TEST (Rect_Test, Constructors) {
    EXPECT_EQ(Rect(), Rect(math::kInfty, math::kInfty,
                           -math::kInfty, -math::kInfty));

    EXPECT_EQ(Rect(1.0f, 1.0f, 3.0f, 3.0f),
              Rect(Vec2f(1.0f, 1.0f), Vec2f(3.0f, 3.0f)));
}

TEST (Rect_Test, Clear) {
    Rect r = Rect(0.0f, 0.0f, 3.0f, 5.0f);

    r.reset();

    EXPECT_FLOAT_EQ(math::kInfty, r.area());
    EXPECT_FALSE(sge::contains(r, Vec2f_Zero));
}

// Basic Tests
//     8                        +--------------+
//                              |              |
//     7              +----+    |    +----+    |
//                    |    |    |    |    |    |
//     6    +----+    F----+----+    H----+    |
//          |    |         |    |              |
//     5    E----+         |    G--------------+
//                         |    |
//     4         +---------+----+---------+
//               |         |    |         |
//     3    +----+----+    |    |    +----+----+
//          |    |    |    |    |    |    |    |
//     2    |    B----+----+----+----+----+    |
//          |         |    |    |    |         |
//     1    A---------+    C----+    D---------+
//
//     0    1    2    3    4    5    6    7    8
//
static const Rect A = Rect(1.0f, 1.0f, 3.0f, 3.0f);
static const Rect B = Rect(2.0f, 2.0f, 7.0f, 4.0f);
static const Rect C = Rect(4.0f, 1.0f, 5.0f, 6.0f);
static const Rect D = Rect(6.0f, 1.0f, 8.0f, 3.0f);
static const Rect E = Rect(1.0f, 5.0f, 2.0f, 6.0f);
static const Rect F = Rect(3.0f, 6.0f, 4.0f, 7.0f);
static const Rect G = Rect(5.0f, 5.0f, 8.0f, 8.0f);
static const Rect H = Rect(6.0f, 6.0f, 7.0f, 7.0f);

TEST (Rect_Test, Center) {
    EXPECT_EQ(Vec2f(2.0f, 2.0f), A.center());
    EXPECT_EQ(Vec2f(4.5f, 3.0f), B.center());
}

TEST (Rect_Test, area) {
    EXPECT_FLOAT_EQ(4.0f, A.area());
    EXPECT_FLOAT_EQ(9.0f, G.area());
    EXPECT_FLOAT_EQ(5.0f, C.area());
    EXPECT_FLOAT_EQ(1.0f, E.area());
}

TEST (Rect_Test, expand) {
    Rect r1 = Rect(1.0f, 2.0f, 4.0f, 4.0f);

    Rect r2 = r1.expand(1.0f);
    EXPECT_EQ(Rect(0.0f, 1.0f, 5.0f, 5.0f), r2);

    r1.expandSelf(2.5f);
    EXPECT_EQ(Rect(-1.5f, -0.5f, 6.5f, 6.5f), r1);
}
