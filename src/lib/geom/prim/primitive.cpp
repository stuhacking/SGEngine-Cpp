//
// Primitive Shapes Implementation
//
#include "../../lib.h"

namespace sge {

static const Color kDefaultColor = Color::fromHex("#FFFFFF");

// Plane -> Mesh
Mesh Plane::toMesh () const {
    Mesh m;

    Vec3f v1 = Vec3f(mCenter.x - mHalfSize.x, mCenter.y, mCenter.z + mHalfSize.y);
    Vec3f v2 = Vec3f(mCenter.x + mHalfSize.x, mCenter.y, mCenter.z + mHalfSize.y);
    Vec3f v3 = Vec3f(mCenter.x + mHalfSize.x, mCenter.y, mCenter.z - mHalfSize.y);
    Vec3f v4 = Vec3f(mCenter.x - mHalfSize.x, mCenter.y, mCenter.z - mHalfSize.y);

    m.autoQuad(
            Vertex(v1, Vec3f_Y, Vec2f(0.0f, 0.0f), kDefaultColor),
            Vertex(v2, Vec3f_Y, Vec2f(1.0f, 0.0f), kDefaultColor),
            Vertex(v3, Vec3f_Y, Vec2f(1.0f, 1.0f), kDefaultColor),
            Vertex(v4, Vec3f_Y, Vec2f(0.0f, 1.0f), kDefaultColor));

    return m;
}

// Cube -> Mesh
Mesh Cube::toMesh () const {
    Mesh m;

    //    8    7
    //  5    6
    //
    //    4    3
    //  1    2
    //

    // Bottom Vecs
    Vec3f v1 = Vec3f(mCenter.x - mHalfSize.x, mCenter.y - mHalfSize.y, mCenter.z + mHalfSize.z);
    Vec3f v2 = Vec3f(mCenter.x + mHalfSize.x, mCenter.y - mHalfSize.y, mCenter.z + mHalfSize.z);
    Vec3f v3 = Vec3f(mCenter.x + mHalfSize.x, mCenter.y - mHalfSize.y, mCenter.z - mHalfSize.z);
    Vec3f v4 = Vec3f(mCenter.x - mHalfSize.x, mCenter.y - mHalfSize.y, mCenter.z - mHalfSize.z);

    // Top Vecs
    Vec3f v5 = Vec3f(mCenter.x - mHalfSize.x, mCenter.y + mHalfSize.y, mCenter.z + mHalfSize.z);
    Vec3f v6 = Vec3f(mCenter.x + mHalfSize.x, mCenter.y + mHalfSize.y, mCenter.z + mHalfSize.z);
    Vec3f v7 = Vec3f(mCenter.x + mHalfSize.x, mCenter.y + mHalfSize.y, mCenter.z - mHalfSize.z);
    Vec3f v8 = Vec3f(mCenter.x - mHalfSize.x, mCenter.y + mHalfSize.y, mCenter.z - mHalfSize.z);

    // Top
    m.autoQuad(
            Vertex(v5, Vec3f_Y, Vec2f(0.0f, 0.0f), kDefaultColor),
            Vertex(v6, Vec3f_Y, Vec2f(1.0f, 0.0f), kDefaultColor),
            Vertex(v7, Vec3f_Y, Vec2f(1.0f, 1.0f), kDefaultColor),
            Vertex(v8, Vec3f_Y, Vec2f(0.0f, 1.0f), kDefaultColor));

    // Bottom
    m.autoQuad(
            Vertex(v4, -Vec3f_Y, Vec2f(0.0f, 0.0f), kDefaultColor),
            Vertex(v3, -Vec3f_Y, Vec2f(1.0f, 0.0f), kDefaultColor),
            Vertex(v2, -Vec3f_Y, Vec2f(1.0f, 1.0f), kDefaultColor),
            Vertex(v1, -Vec3f_Y, Vec2f(0.0f, 1.0f), kDefaultColor));

    // Left
    m.autoQuad(
            Vertex(v4, -Vec3f_X, Vec2f(0.0f, 0.0f), kDefaultColor),
            Vertex(v1, -Vec3f_X, Vec2f(1.0f, 0.0f), kDefaultColor),
            Vertex(v5, -Vec3f_X, Vec2f(1.0f, 1.0f), kDefaultColor),
            Vertex(v8, -Vec3f_X, Vec2f(0.0f, 1.0f), kDefaultColor));

    // Right
    m.autoQuad(
            Vertex(v2, Vec3f_X, Vec2f(0.0f, 0.0f), kDefaultColor),
            Vertex(v3, Vec3f_X, Vec2f(1.0f, 0.0f), kDefaultColor),
            Vertex(v7, Vec3f_X, Vec2f(1.0f, 1.0f), kDefaultColor),
            Vertex(v6, Vec3f_X, Vec2f(0.0f, 1.0f), kDefaultColor));

    // Front
    m.autoQuad(
            Vertex(v1, Vec3f_Z, Vec2f(0.0f, 0.0f), kDefaultColor),
            Vertex(v2, Vec3f_Z, Vec2f(1.0f, 0.0f), kDefaultColor),
            Vertex(v6, Vec3f_Z, Vec2f(1.0f, 1.0f), kDefaultColor),
            Vertex(v5, Vec3f_Z, Vec2f(0.0f, 1.0f), kDefaultColor));

    // Back
    m.autoQuad(
            Vertex(v3, -Vec3f_Z, Vec2f(0.0f, 0.0f), kDefaultColor),
            Vertex(v4, -Vec3f_Z, Vec2f(1.0f, 0.0f), kDefaultColor),
            Vertex(v8, -Vec3f_Z, Vec2f(1.0f, 1.0f), kDefaultColor),
            Vertex(v7, -Vec3f_Z, Vec2f(0.0f, 1.0f), kDefaultColor));

    return m;
}

// ICOSphere -> Mesh
Mesh ICOSphere::toMesh () const {
    Mesh m;

    Vec3f points[12];

    float t = (1.0f + sqrtf(5.0f)) * 0.5f;

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
        m.addVertex(Vertex(p * mHalfSize + mCenter, p.normalize(),
                           Vec2f(math::toRatio(p.x, -1.0f, 1.0f),
                                 math::toRatio(p.y, -1.0f, 1.0f)),
                           kDefaultColor));
    }

    m.addFace(0, 11, 5);
    m.addFace(0, 5, 1);
    m.addFace(0, 1, 7);
    m.addFace(0, 7, 10);
    m.addFace(0, 10, 11);

    m.addFace(1, 5, 9);
    m.addFace(5, 11, 4);
    m.addFace(11, 10, 2);
    m.addFace(10, 7, 6);
    m.addFace(7, 1, 8);

    m.addFace(3, 9, 4);
    m.addFace(3, 4, 2);
    m.addFace(3, 2, 6);
    m.addFace(3, 6, 8);
    m.addFace(3, 8, 9);

    m.addFace(4, 9, 5);
    m.addFace(2, 4, 11);
    m.addFace(6, 2, 10);
    m.addFace(8, 6, 7);
    m.addFace(9, 8, 1);

    return m;
}

} /* namespace sge */
