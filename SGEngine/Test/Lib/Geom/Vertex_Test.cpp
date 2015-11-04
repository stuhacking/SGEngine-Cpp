//
// Vertex Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::Vector2;
using sge::Vector3;
using sge::Color;
using sge::Vertex;

TEST (Vertex_Test, Constructors) {
    Vertex V = Vertex(2.0f, 3.0f, 4.0f,
                      0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f,
                      255, 255, 255, 255);
    Vertex W = Vertex(2.0f, 3.0f, 4.0f,
                      0.5f, 1.0f,
                      0.0f, 1.0f, 0.0f,
                      255, 255, 255, 255);
    
    EXPECT_EQ(V, Vertex(Vector3(2.0f, 3.0f, 4.0f)));
    EXPECT_EQ(V, Vertex(Vector3(2.0f, 3.0f, 4.0f), Vector2::ZERO,
                        Vector3(0.0f, 1.0f, 0.0f), Color(255, 255, 255, 255)));

    EXPECT_EQ(W, Vertex(Vector3(2.0f, 3.0f, 4.0f), Vector2(0.5f, 1.0f),
                        Vector3(0.0f, 1.0f, 0.0f), Color(255, 255, 255, 255)));
}
