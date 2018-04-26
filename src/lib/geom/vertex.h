/*---  Vertex.h - Drawable Vertex Header  --------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a drawable Vertex class.
 */
#ifndef __SGE_VERTEX_H
#define __SGE_VERTEX_H

namespace sge {

/**
 * Default Drawable Vertex.
 *
 * Default Drawable Vertex stores position, texture coordinates, normal,
 * and color.
 */
class Vertex {
public:
    Vec3f position;
    Vec3f normal;
    Vec2f texCoord;
    Color color;

public:
    /**
     * Construct a Vertex with component parts.
     */
    Vertex (const Vec3f &pPos, const Vec3f &pNorm, const Vec2f &pTex,
            const Color &pCol)
            : position{pPos}, normal{pNorm}, texCoord{pTex}, color{pCol} { }

    /**
     * Construct a Vertex using float values.
     */
    Vertex (const float xx, const float yy, const float zz,
            const float nx, const float ny, const float nz,
            const float s, const float t,
            const u8 r, const u8 g, const u8 b, const u8 a)
            : position{Vec3f(xx, yy, zz)}, normal{Vec3f(nx, ny, nz)},
              texCoord{Vec2f(s, t)}, color{Color(r, g, b, a)} { }

    /**
     * Test if this Vertex is equivalent to another Vertex.
     */
    bool compare (const Vertex &other) const;

    /**
     * Test if this Vertex is equivalent to another Vertex.
     */
    bool operator== (const Vertex &other) const;

    /**
     * Test if this Vertex is not equivalent to another Vertex.
     */
    bool operator!= (const Vertex &other) const;
};

// --------------------------------------------------------------------------

inline bool Vertex::compare (const Vertex &other) const {
    return position == other.position &&
           normal == other.normal &&
           texCoord == other.texCoord &&
           color == other.color;
}

inline bool Vertex::operator== (const Vertex &other) const {
    return compare(other);
}

inline bool Vertex::operator!= (const Vertex &other) const {
    return !compare(other);
}

} /* namespace sge */

#endif /* __SGE_VERTEX_H */
