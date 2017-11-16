//
// Created by Stuart Hacking on 13/08/2015.
//
#include <gtest/gtest.h>
#include "lib.h"

using sge::Mesh;
using sge::Vertex;

TEST (Mesh_Test, VertCount) {
    Mesh m;
    m.AddVertex(Vertex(1.0f, 0.0f, 0.0f));
    m.AddVertex(Vertex(0.0f, 1.0f, 0.0f));

    ASSERT_EQ(2, m.VertCount());
}

TEST (Mesh_Test, FaceCount) {
    Mesh m;
    m.AddVertex(Vertex(0.0f, 0.0f, 0.0f));
    m.AddVertex(Vertex(0.0f, 1.0f, 0.0f));
    m.AddVertex(Vertex(1.0f, 0.0f, 0.0f));
    m.AddVertex(Vertex(1.0f, 1.0f, 0.0f));

    ASSERT_EQ(0, m.FaceCount());

    m.AddFace(1, 3, 2);
    m.AddFace(1, 4, 3);

    ASSERT_EQ(2, m.FaceCount());
}
