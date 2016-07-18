/*---  DebugGraphics.h - Debug Graphics Header  --------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Defines a class for drawing simple line graphics for visually
 *    debugging a scene.
 */
#ifndef __SGENGINE_DEBUGGRAPHICS_H_
#define __SGENGINE_DEBUGGRAPHICS_H_

#define SPHERE_INCREMENT 12.0f

#include <cmath> // cos, sin

namespace sge {

class DebugGraphics {
public:
    /**
     * Create a DebugGraphics object with an optional default
     * draw color.
     */
    DebugGraphics (const Color &p_col = Color(255, 255, 255))
        : color(p_col), m_glVaoId(0), m_glVboId(0) { }

    /**
     * Clear current debug graphics.
     * Destructive.
     */
    void Clear () { m_vertices.clear(); }

    void Render ();

    /**
     * Draw an edge using the default color of this DebugGraphics
     * object.
     */
    void AddEdge (const Vec3f &v1, const Vec3f &v2);

    /**
     * Draw an edge using a custom color.
     */
    void AddEdge (const Vec3f &v1, const Vec3f &v2, const Color &col);

    /**
     * Draw a point as an intersection of 3 edges where the intersection
     * occurs at point p and the edges extends radius units from p. Uses
     * the default color of the DebugGraphics object.
     */
    void AddPoint (const Vec3f &p, const float radius = 1.0f);

    /**
     * Draw a point as an intersection of 3 edges where the intersection
     * occurs at point p and the edges extends radius units from p using
     * a custom color.
     */
    void AddPoint (const Vec3f &p, const float radius, const Color &col);

    /**
     * Draw a sphere container as a set of axis aligned rings where the center
     * of each ring is point p_center, and each ring extends radius units from
     * p_center. Uses the default color of the DebugGraphics object.
     */
    void AddSphere (const Vec3f &p_center, const float radius = 1.0f);

    /**
     * Draw a sphere container as a set of axis aligned rings where the center
     * of each ring is point p_center, and each ring extends radius units from
     * p_center. Uses a custom color.
     */
    void AddSphere (const Vec3f &p_center, const float radius, const Color &col);

    /**
     * Draw a Grid on the (X, Z) plane at Y = 0, where the center of the grid
     * is point p_center, and the grid extends size / 2 units in X and Z. Grid
     * squares are drawn 1 unit apart. Uses the default color of this
     * DebugGraphics object.
     *
     * TODO More configurable grids?
     */
    void AddGrid (const Vec3f &p_center, const u32 size = 10);

    /**
     * Draw a Grid on the (X, Z) plane at Y = 0, where the center of the grid
     * is point p_center, and the grid extends size / 2 units in X and Z. Grid
     * squares are drawn 1 unit apart. Uses a custom color.
     *
     * TODO More configurable grids?
     */
    void AddGrid (const Vec3f &p_center, const u32 size, const Color &col);

    /**
     * Draw a bounding box enclosing the region defined by points p_min..p_max.
     * Uses the default color of this DebugGraphics object.
     */
    void AddBox (const Vec3f &p_min, const Vec3f &p_max);

    /**
     * Draw a bounding box enclosing the region defined by points p_min..p_max.
     * Uses a custom color of this DebugGraphics object.
     */
    void AddBox (const Vec3f &p_min, const Vec3f &p_max, const Color &col);

private:
    struct DVertex {
        Vec3f v1;
        Color color;

        DVertex (const Vec3f &p_v1, const Color &p_col)
        : v1(p_v1), color(p_col) { }
    };

private:
    Color color;
    u32 m_glVaoId;
    u32 m_glVboId;

    std::vector<DVertex> m_vertices;
};

// --------------------------------------------------------------------------

INLINE void DebugGraphics::AddEdge (const Vec3f &v1, const Vec3f &v2) {
    AddEdge(v1, v2, color);
}

INLINE void DebugGraphics::AddEdge (const Vec3f &v1, const Vec3f &v2, const Color &col) {
    m_vertices.emplace_back(v1, col);
    m_vertices.emplace_back(v2, col);
}

INLINE void DebugGraphics::AddPoint (const Vec3f &p, const float radius) {
    AddPoint(p, radius, color);
}

INLINE void DebugGraphics::AddSphere (const Vec3f &p_center, const float radius) {
    AddSphere(p_center, radius, color);
}

INLINE void DebugGraphics::AddGrid (const Vec3f &p_center, const u32 size) {
    AddGrid(p_center, size, color);
}

INLINE void DebugGraphics::AddBox (const Vec3f &p_min, const Vec3f &p_max) {
    AddBox(p_min, p_max, color);
}

} /* namespace sge */

#endif /* __SGENGINE_DEBUGGRAPHICS_H_ */
