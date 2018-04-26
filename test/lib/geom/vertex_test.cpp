//
// Vertex Tests
//
#include <gtest/gtest.h>
#include "lib.h"

using sge::Vertex;

TEST (Vertex_Test, Constructors) {
    Vertex V = Vertex(2.0f, 3.0f, 4.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 255, 255,
                      255, 255);
    Vertex W = Vertex(2.0f, 3.0f, 4.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 255, 255,
                      255, 255);

    EXPECT_EQ(V, Vertex(Vec3f(2.0f, 3.0f, 4.0f), Vec3f(0.0f, 1.0f, 0.0f),
                        Vec2f_Zero, Color(255, 255, 255, 255)));

    EXPECT_EQ(W, Vertex(Vec3f(2.0f, 3.0f, 4.0f), Vec3f(0.0f, 1.0f, 0.0f),
                        Vec2f(0.5f, 1.0f), Color(255, 255, 255, 255)));
}
