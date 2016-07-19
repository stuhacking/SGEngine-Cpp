//
// Rectangle bounds Tests.
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::FMath;
using sge::Vec2f;
using sge::Rectangle;

TEST (Rectangle_Test, Constructors) {
    EXPECT_EQ(Rectangle(), Rectangle(FMath::INFTY, FMath::INFTY,
                                     -FMath::INFTY, -FMath::INFTY));

    EXPECT_EQ(Rectangle(1.0f, 1.0f, 3.0f, 3.0f),
              Rectangle(Vec2f(1.0f, 1.0f), Vec2f(3.0f, 3.0f)));
}

TEST (Rectangle_Test, Clear) {
    Rectangle r = Rectangle(0.0f, 0.0f, 3.0f, 5.0f);

    r.Clear();

    EXPECT_FLOAT_EQ(FMath::INFTY, r.Area());
    EXPECT_FALSE(r.Contains(sge::Vec2f::ZERO));
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
static const Rectangle A = Rectangle(1.0f, 1.0f, 3.0f, 3.0f);
static const Rectangle B = Rectangle(2.0f, 2.0f, 7.0f, 4.0f);
static const Rectangle C = Rectangle(4.0f, 1.0f, 5.0f, 6.0f);
static const Rectangle D = Rectangle(6.0f, 1.0f, 8.0f, 3.0f);
static const Rectangle E = Rectangle(1.0f, 5.0f, 2.0f, 6.0f);
static const Rectangle F = Rectangle(3.0f, 6.0f, 4.0f, 7.0f);
static const Rectangle G = Rectangle(5.0f, 5.0f, 8.0f, 8.0f);
static const Rectangle H = Rectangle(6.0f, 6.0f, 7.0f, 7.0f);

TEST (Rectangle_Test, Intersects) {
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

TEST (Rectangle_Test, Contains_Point) {
    EXPECT_TRUE(A.Contains(Vec2f(2.0f, 2.0f)));
    EXPECT_TRUE(C.Contains(Vec2f(5.0f, 6.0f)));

    EXPECT_FALSE(E.Contains(Vec2f(0.0f, 0.0f)));
}

TEST (Rectangle_Test, Contains_Rectangle) {
    EXPECT_TRUE(G.Contains(H));

    EXPECT_FALSE(H.Contains(G));
    EXPECT_FALSE(A.Contains(B));
}

TEST (Rectangle_Test, Center) {
    EXPECT_EQ(Vec2f(2.0f, 2.0f), A.Center());
    EXPECT_EQ(Vec2f(4.5f, 3.0f), B.Center());
}

TEST (Rectangle_Test, Area) {
    EXPECT_FLOAT_EQ(4.0f, A.Area());
    EXPECT_FLOAT_EQ(9.0f, G.Area());
    EXPECT_FLOAT_EQ(5.0f, C.Area());
    EXPECT_FLOAT_EQ(1.0f, E.Area());
}

TEST (Rectangle_Test, expand) {
    Rectangle r1 = Rectangle(1.0f, 2.0f, 4.0f, 4.0f);

    Rectangle r2 = r1.Expand(1.0f);
    EXPECT_EQ(Rectangle(0.0f, 1.0f, 5.0f, 5.0f), r2);

    r1.ExpandSelf(2.5f);
    EXPECT_EQ(Rectangle(-1.5f, -0.5f, 6.5f, 6.5f), r1);
}
