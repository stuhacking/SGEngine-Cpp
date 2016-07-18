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
#ifndef __SGENGINE_MESH_H_
#define __SGENGINE_MESH_H_

#include <vector>

#include "Vertex.h"

namespace sge {

class Mesh {
public:
    void AddVertex (const Vertex &v);

    void AddFace (const u32 a, const u32 b, const u32 c);

    void AutoTriFace (const Vertex &v1, const Vertex &v2, const Vertex &v3);

    void AutoQuadFace (const Vertex &v1, const Vertex &v2, const Vertex &v3,
                       const Vertex &v4);
    
    u32 VertCount () const;

    u32 IndexCount () const;

    u32 FaceCount () const;

    void PrintVertexInfo () const;
    
    /**
     * Identify duplicate vertex data and fix indices to share a single instance.
     */
    void Simplify ();

public:
    std::vector<Vertex> vertices;
    std::vector<u32> indices;
};

// --------------------------------------------------------------------------

INLINE void Mesh::AddVertex (const Vertex &v) {
    vertices.push_back(v);
}

INLINE void Mesh::AddFace (const u32 a, const u32 b, const u32 c) {
    indices.push_back(a);
    indices.push_back(b);
    indices.push_back(c);
}

//  v3---v2
//   | /  
//  v1
INLINE void Mesh::AutoTriFace (const Vertex &v1, const Vertex &v2,
                               const Vertex &v3) {
    u32 size = VertCount();
    
    AddVertex(v1);
    AddVertex(v2);
    AddVertex(v3);
    
    AddFace(size, size + 1, size + 2);
}

//  v4---v3
//   |   |
//  v1---v2
INLINE void Mesh::AutoQuadFace (const Vertex &v1, const Vertex &v2,
                                const Vertex &v3, const Vertex &v4) {
    u32 size = VertCount();
    
    AddVertex(v1);
    AddVertex(v2);
    AddVertex(v3);
    AddVertex(v4);
    
    AddFace(size, size + 2, size + 3);
    AddFace(size, size + 1, size + 2);
}

INLINE u32 Mesh::VertCount () const {
    return vertices.size();
}

INLINE u32 Mesh::IndexCount () const {
    return indices.size();
}

INLINE u32 Mesh::FaceCount () const {
    return indices.size() / 3;
}

} /* namespace sge */

#endif /* __SGENGINE_MESH_H_  */
