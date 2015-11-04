//
// Primitive Shapes Implementation
//
#include "../../Lib.h"

namespace sge {

// Plane -> Mesh

Mesh Plane::ToMesh () const {
    Mesh m;

    Vector3 v1 = Vector3(center.x - hSize.x, center.y, center.z + hSize.y);
    Vector3 v2 = Vector3(center.x + hSize.x, center.y, center.z + hSize.y);
    Vector3 v3 = Vector3(center.x + hSize.x, center.y, center.z - hSize.y);
    Vector3 v4 = Vector3(center.x - hSize.x, center.y, center.z - hSize.y);

    m.AutoQuadFace(Vertex(v1, Vector2(0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)),
                   Vertex(v2, Vector2(1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)),
                   Vertex(v3, Vector2(1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)),
                   Vertex(v4, Vector2(0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)));

    return m;
}

// Cube -> Mesh

Mesh Cube::ToMesh () const {
    Mesh m;


    //    8    7
    //  5    6
    //
    //
    //    4    3
    //  1    2
    //
    
    // Bottom Vecs
    Vector3 v1 = Vector3(center.x - hSize.x, center.y - hSize.y, center.z + hSize.z);
    Vector3 v2 = Vector3(center.x + hSize.x, center.y - hSize.y, center.z + hSize.z);
    Vector3 v3 = Vector3(center.x + hSize.x, center.y - hSize.y, center.z - hSize.z);
    Vector3 v4 = Vector3(center.x - hSize.x, center.y - hSize.y, center.z - hSize.z);
    
    // Top Vecs
    Vector3 v5 = Vector3(center.x - hSize.x, center.y + hSize.y, center.z + hSize.z);
    Vector3 v6 = Vector3(center.x + hSize.x, center.y + hSize.y, center.z + hSize.z);
    Vector3 v7 = Vector3(center.x + hSize.x, center.y + hSize.y, center.z - hSize.z);
    Vector3 v8 = Vector3(center.x - hSize.x, center.y + hSize.y, center.z - hSize.z);

    // Top
    m.AutoQuadFace(Vertex(v5, Vector2(0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)),
                   Vertex(v6, Vector2(1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)),
                   Vertex(v7, Vector2(1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)),
                   Vertex(v8, Vector2(0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)));
    // Bottom
    m.AutoQuadFace(Vertex(v4, Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)),
                   Vertex(v3, Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)),
                   Vertex(v2, Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)),
                   Vertex(v1, Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)));


    // Left
    m.AutoQuadFace(Vertex(v4, Vector2(0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)),
                   Vertex(v1, Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)),
                   Vertex(v5, Vector2(1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)),
                   Vertex(v8, Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)));
    // Right
    m.AutoQuadFace(Vertex(v2, Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)),
                   Vertex(v3, Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)),
                   Vertex(v7, Vector2(1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)),
                   Vertex(v6, Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)));
    
    // Front
    m.AutoQuadFace(Vertex(v1, Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)),
                   Vertex(v2, Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)),
                   Vertex(v6, Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)),
                   Vertex(v5, Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)));
    // Back
    m.AutoQuadFace(Vertex(v3, Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)),
                   Vertex(v4, Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)),
                   Vertex(v8, Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)),
                   Vertex(v7, Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)));
    
    return m;
}

// ICOSphere -> Mesh

Mesh ICOSphere::ToMesh () const {
    Mesh m;
    Vector3 points[12];

    constexpr float t = (1.0f + sqrt(5.0f)) * 0.5f;

    points[0] = Vector3(-1.0f, t, 0);
    points[1] = Vector3(1.0f, t, 0);
    points[2] = Vector3(-1.0f, -t, 0);
    points[3] = Vector3(1.0f, -t, 0);
    
    points[4] = Vector3(0, -1, t);
    points[5] = Vector3(0, 1, t);
    points[6] = Vector3(0, -1, -t);
    points[7] = Vector3(0, 1, -t);
    
    points[8] = Vector3(t, 0, -1);
    points[9] = Vector3(t, 0, 1);
    points[10] = Vector3(-t, 0, -1);
    points[11] = Vector3(-t, 0, 1);

    // TODO Figure out how to project a texture properly, for now: Planar.
    for (auto &p : points) {
        m.AddVertex(Vertex(p * hSize + center,
                           Vector2(FMath::ToRatio(p.x, -1.0f, 1.0f),
                                   FMath::ToRatio(p.y, -1.0f, 1.0f)),
                           p.Normalize()));
    }
    
    m.AddFace(0, 11, 5);
    m.AddFace(0, 5, 1);
    m.AddFace(0, 1, 7);
    m.AddFace(0, 7, 10);
    m.AddFace(0, 10, 11);

    m.AddFace(1, 5, 9);
    m.AddFace(5, 11, 4);
    m.AddFace(11, 10, 2);
    m.AddFace(10, 7, 6);
    m.AddFace(7, 1, 8);

    m.AddFace(3, 9, 4);
    m.AddFace(3, 4, 2);
    m.AddFace(3, 2, 6);
    m.AddFace(3, 6, 8);
    m.AddFace(3, 8, 9);

    m.AddFace(4, 9, 5);
    m.AddFace(2, 4, 11);
    m.AddFace(6, 2, 10);
    m.AddFace(8, 6, 7);
    m.AddFace(9, 8, 1);

    return m;
}

} /* namespace sge */
