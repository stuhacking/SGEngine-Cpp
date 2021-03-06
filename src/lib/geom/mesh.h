/*---  Mesh.h - Mesh Header  ---------------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a Mesh class.
 */
#ifndef __SGE_MESH_H
#define __SGE_MESH_H

#include <vector>

#include "vertex.h"

namespace sge {

class Mesh {
public:
    void addVertex (const Vertex &v);

    void addFace (u32 a, u32 b, u32 c);

    void autoFace (const Vertex &v1, const Vertex &v2, const Vertex &v3);

    void autoQuad (const Vertex &v1, const Vertex &v2, const Vertex &v3,
                   const Vertex &v4);

    u32 vertCount () const;

    u32 indexCount () const;

    u32 faceCount () const;

    void printVertexInfo () const;

    /**
     * Identify duplicate vertex data and fix indices to share a single instance.
     */
    void simplify ();

public:
    std::vector<Vertex> vertices;
    std::vector<u32> indices;
};

// --------------------------------------------------------------------------

inline void Mesh::addVertex (const Vertex &v) {
    vertices.push_back(v);
}

inline void Mesh::addFace (const u32 a, const u32 b, const u32 c) {
    indices.push_back(a);
    indices.push_back(b);
    indices.push_back(c);
}

//  v3---v2
//   | /
//  v1
inline void Mesh::autoFace (const Vertex &v1, const Vertex &v2,
                            const Vertex &v3) {
    u32 size = vertCount();

    addVertex(v1);
    addVertex(v2);
    addVertex(v3);

    addFace(size, size + 1, size + 2);
}

//  v4---v3
//   |   |
//  v1---v2
inline void Mesh::autoQuad (const Vertex &v1, const Vertex &v2,
                            const Vertex &v3, const Vertex &v4) {
    u32 size = vertCount();

    addVertex(v1);
    addVertex(v2);
    addVertex(v3);
    addVertex(v4);

    addFace(size, size + 2, size + 3);
    addFace(size, size + 1, size + 2);
}

inline u32 Mesh::vertCount () const {
    return static_cast<u32>(vertices.size());
}

inline u32 Mesh::indexCount () const {
    return static_cast<u32>(indices.size());
}

inline u32 Mesh::faceCount () const {
    return static_cast<u32>(indices.size()) / 3;
}

} /* namespace sge */

#endif /* __SGE_MESH_H  */
