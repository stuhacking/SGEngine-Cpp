//
// Created by Stuart Hacking on 13/08/2015.
//
#include <gtest/gtest.h>
#include "lib.h"

using sge::Mesh;
using sge::Vertex;

TEST (Mesh_Test, VertCount) {
    Mesh m;
    m.addVertex(Vertex(1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    m.addVertex(Vertex(0.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0));

    ASSERT_EQ(2, m.vertCount());
}

TEST (Mesh_Test, FaceCount) {
    Mesh m;
    m.addVertex(Vertex(0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    m.addVertex(Vertex(0.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    m.addVertex(Vertex(1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    m.addVertex(Vertex(1.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0));

    ASSERT_EQ(0, m.faceCount());

    m.addFace(1, 3, 2);
    m.addFace(1, 4, 3);

    ASSERT_EQ(2, m.faceCount());
}
