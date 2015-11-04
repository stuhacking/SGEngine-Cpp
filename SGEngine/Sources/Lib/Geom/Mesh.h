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
#ifndef __SHLIB_MESH_H_
#define __SHLIB_MESH_H_

#include <vector>

#include "Vertex.h"

namespace sge {

class Mesh {
public:
    void AddVertex (const Vertex &v);

    void AddFace (const int a, const int b, const int c);

    void AutoTriFace (const Vertex &v1, const Vertex &v2, const Vertex &v3);

    void AutoQuadFace (const Vertex &v1, const Vertex &v2, const Vertex &v3,
                       const Vertex &v4);
    
    u64 VertCount () const;

    u64 IndexCount () const;

    u64 FaceCount () const;

public:
    std::vector<Vertex> vertices;
    std::vector<int> indices;
};

// --------------------------------------------------------------------------

inline void Mesh::AddVertex (const Vertex &v) {
    vertices.push_back(v);
}

inline void Mesh::AddFace (const int a, const int b, const int c) {
    indices.push_back(a);
    indices.push_back(b);
    indices.push_back(c);
}

//  v3---v2
//   | /  
//  v1
inline void Mesh::AutoTriFace (const Vertex &v1, const Vertex &v2,
                               const Vertex &v3) {
    u64 size = VertCount();
    
    AddVertex(v1);
    AddVertex(v2);
    AddVertex(v3);
    
    AddFace(size, size + 1, size + 2);
}

//  v4---v3
//   |   |
//  v1---v2
inline void Mesh::AutoQuadFace (const Vertex &v1, const Vertex &v2,
                                const Vertex &v3, const Vertex &v4) {
    u64 size = VertCount();
    
    AddVertex(v1);
    AddVertex(v2);
    AddVertex(v3);
    AddVertex(v4);
    
    AddFace(size, size + 2, size + 3);
    AddFace(size, size + 1, size + 2);
}

inline unsigned long Mesh::VertCount () const {
    return vertices.size();
}

inline unsigned long Mesh::IndexCount () const {
    return indices.size();
}

inline unsigned long Mesh::FaceCount () const {
    return indices.size() / 3;
}

} /* namespace sge */

#endif /* __SHLIB_MESH_H_  */
