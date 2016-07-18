//
// Primitive Shapes Implementation
//
#include "../../Lib.h"

namespace sge {

// Plane -> Mesh

Mesh Plane::ToMesh () const {
    Mesh m;

    Vec3f v1 = Vec3f(center.x - hSize.x, center.y, center.z + hSize.y);
    Vec3f v2 = Vec3f(center.x + hSize.x, center.y, center.z + hSize.y);
    Vec3f v3 = Vec3f(center.x + hSize.x, center.y, center.z - hSize.y);
    Vec3f v4 = Vec3f(center.x - hSize.x, center.y, center.z - hSize.y);

    m.AutoQuadFace(Vertex(v1, Vec2f(0.0f, 0.0f), Vec3f::Y),
                   Vertex(v2, Vec2f(1.0f, 0.0f), Vec3f::Y),
                   Vertex(v3, Vec2f(1.0f, 1.0f), Vec3f::Y),
                   Vertex(v4, Vec2f(0.0f, 1.0f), Vec3f::Y));

    return m;
}

// Cube -> Mesh

Mesh Cube::ToMesh () const {
    Mesh m;

    //    8    7
    //  5    6
    //
    //    4    3
    //  1    2
    //
    
    // Bottom Vecs
    Vec3f v1 = Vec3f(center.x - hSize.x, center.y - hSize.y, center.z + hSize.z);
    Vec3f v2 = Vec3f(center.x + hSize.x, center.y - hSize.y, center.z + hSize.z);
    Vec3f v3 = Vec3f(center.x + hSize.x, center.y - hSize.y, center.z - hSize.z);
    Vec3f v4 = Vec3f(center.x - hSize.x, center.y - hSize.y, center.z - hSize.z);
    
    // Top Vecs
    Vec3f v5 = Vec3f(center.x - hSize.x, center.y + hSize.y, center.z + hSize.z);
    Vec3f v6 = Vec3f(center.x + hSize.x, center.y + hSize.y, center.z + hSize.z);
    Vec3f v7 = Vec3f(center.x + hSize.x, center.y + hSize.y, center.z - hSize.z);
    Vec3f v8 = Vec3f(center.x - hSize.x, center.y + hSize.y, center.z - hSize.z);

    // Top
    m.AutoQuadFace(Vertex(v5, Vec2f(0.0f, 0.0f), Vec3f::Y),
                   Vertex(v6, Vec2f(1.0f, 0.0f), Vec3f::Y),
                   Vertex(v7, Vec2f(1.0f, 1.0f), Vec3f::Y),
                   Vertex(v8, Vec2f(0.0f, 1.0f), Vec3f::Y));
    // Bottom
    m.AutoQuadFace(Vertex(v4, Vec2f(0.0f, 0.0f), -Vec3f::Y),
                   Vertex(v3, Vec2f(1.0f, 0.0f), -Vec3f::Y),
                   Vertex(v2, Vec2f(1.0f, 1.0f), -Vec3f::Y),
                   Vertex(v1, Vec2f(0.0f, 1.0f), -Vec3f::Y));


    // Left
    m.AutoQuadFace(Vertex(v4, Vec2f(0.0f, 0.0f), -Vec3f::X),
                   Vertex(v1, Vec2f(1.0f, 0.0f), -Vec3f::X),
                   Vertex(v5, Vec2f(1.0f, 1.0f), -Vec3f::X),
                   Vertex(v8, Vec2f(0.0f, 1.0f), -Vec3f::X));
    // Right
    m.AutoQuadFace(Vertex(v2, Vec2f(0.0f, 0.0f), Vec3f::X),
                   Vertex(v3, Vec2f(1.0f, 0.0f), Vec3f::X),
                   Vertex(v7, Vec2f(1.0f, 1.0f), Vec3f::X),
                   Vertex(v6, Vec2f(0.0f, 1.0f), Vec3f::X));
    
    // Front
    m.AutoQuadFace(Vertex(v1, Vec2f(0.0f, 0.0f), Vec3f::Z),
                   Vertex(v2, Vec2f(1.0f, 0.0f), Vec3f::Z),
                   Vertex(v6, Vec2f(1.0f, 1.0f), Vec3f::Z),
                   Vertex(v5, Vec2f(0.0f, 1.0f), Vec3f::Z));
    // Back
    m.AutoQuadFace(Vertex(v3, Vec2f(0.0f, 0.0f), -Vec3f::Z),
                   Vertex(v4, Vec2f(1.0f, 0.0f), -Vec3f::Z),
                   Vertex(v8, Vec2f(1.0f, 1.0f), -Vec3f::Z),
                   Vertex(v7, Vec2f(0.0f, 1.0f), -Vec3f::Z));
    
    return m;
}

// ICOSphere -> Mesh

Mesh ICOSphere::ToMesh () const {
    Mesh m;
    Vec3f points[12];

    float t = (1.0f + sqrt(5.0f)) * 0.5f;

    points[0] = Vec3f(-1.0f, t, 0);
    points[1] = Vec3f(1.0f, t, 0);
    points[2] = Vec3f(-1.0f, -t, 0);
    points[3] = Vec3f(1.0f, -t, 0);
    
    points[4] = Vec3f(0, -1, t);
    points[5] = Vec3f(0, 1, t);
    points[6] = Vec3f(0, -1, -t);
    points[7] = Vec3f(0, 1, -t);
    
    points[8] = Vec3f(t, 0, -1);
    points[9] = Vec3f(t, 0, 1);
    points[10] = Vec3f(-t, 0, -1);
    points[11] = Vec3f(-t, 0, 1);

    // TODO Figure out how to project a texture properly, for now: Planar.
    for (auto &p : points) {
        m.AddVertex(Vertex(p * hSize + center,
                           Vec2f(FMath::ToRatio(p.x, -1.0f, 1.0f),
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
