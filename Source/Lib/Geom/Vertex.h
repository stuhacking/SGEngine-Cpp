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
 * Default Drawable Vertex. Default Drawable Vertex stores
 * position, texture coordinates, normal, and color.
 */
class Vertex {
public:
    Vec3f position;
    Vec2f texCoord;
    Vec3f normal;
    Color color;

public:
    /**
     * Construct a Vertex with component parts.
     */
    Vertex (const Vec3f &p_pos, const Vec2f &p_tex = Vec2f::ZERO,
            const Vec3f &p_norm = Vec3f::Y,
            const Color &p_col = Color(255, 255, 255, 255))
        : position(p_pos), texCoord(p_tex), normal(p_norm), color(p_col) { }

    /**
     * Construct a Vertex using float values.
     */
    Vertex (const float xx = 0.0f, const float yy = 0.0f, const float zz = 0.0f,
            const float s = 0.0f, const float t = 0.0f,
            const float nx = 0.0f, const float ny = 1.0f, const float nz = 0.0f,
            const u8 r = 255, const u8 g = 255, const u8 b = 255, const u8 a = 255)
        : position(Vec3f(xx, yy, zz)), texCoord(Vec2f(s, t)),
          normal(Vec3f(nx, ny, nz)), color(Color(r, g, b, a)) { }

    /**
     * Test if this Vertex is equivalent to another Vertex.
     */
    bool Compare (const Vertex &other) const;

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

inline bool Vertex::Compare (const Vertex &other) const {
    return position == other.position &&
        normal == other.normal &&
        texCoord == other.texCoord &&
        color == other.color;
}

inline bool Vertex::operator== (const Vertex &other) const {
    return Compare(other);
}

inline bool Vertex::operator!= (const Vertex &other) const {
    return !Compare(other);
}

} /* namespace sge */

#endif /* __SGE_VERTEX_H */
