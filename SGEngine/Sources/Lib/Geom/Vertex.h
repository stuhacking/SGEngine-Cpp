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
#ifndef __SHLIB_VERTEX_H_
#define __SHLIB_VERTEX_H_

namespace sge {

/**
 * Default Drawable Vertex. Default Drawable Vertex stores
 * position, texture coordinates, normal, and color.
 */
class Vertex {
public:
    Vector3 position;
    Vector2 texCoord;
    Vector3 normal;
    Color color;

public:
    /**
     * Construct a Vertex with component parts.
     */
    Vertex (const Vector3 &p_pos, const Vector2 &p_tex = Vector2::ZERO,
            const Vector3 &p_norm = Vector3(0.0f, 1.0f, 0.0f),
            const Color &p_col = Color(255, 255, 255, 255))
        : position(p_pos), texCoord(p_tex), normal(p_norm), color(p_col) { }

    /**
     * Construct a Vertex using float values.
     */
    Vertex (const float xx = 0.0f, const float yy = 0.0f, const float zz = 0.0f,
            const float s = 0.0f, const float t = 0.0f,
            const float nx = 0.0f, const float ny = 1.0f, const float nz = 0.0f,
            const u8 r = 255, const u8 g = 255, const u8 b = 255, const u8 a = 255)
        : position(Vector3(xx, yy, zz)), texCoord(Vector2(s, t)),
          normal(Vector3(nx, ny, nz)), color(Color(r, g, b, a)) { }

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

#endif /* __SHLIB_VERTEX_H_ */
