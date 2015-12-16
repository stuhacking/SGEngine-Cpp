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
#ifndef __SHENGINE_DEBUGGRAPHICS_H_
#define __SHENGINE_DEBUGGRAPHICS_H_

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

    void AddEdge (const Vector3 &v1, const Vector3 &v2);
    void AddEdge (const Vector3 &v1, const Vector3 &v2, const Color &col);

    void AddPoint (const Vector3 &p, const float radius = 1.0f);
    void AddPoint (const Vector3 &p, const float radius, const Color &col);

    void AddSphere (const Vector3 &p_center, const float radius = 1.0f);
    void AddSphere (const Vector3 &p_center, const float radius, const Color &col);

    void AddGrid (const Vector3 &p_center, const u32 size = 10);
    void AddGrid (const Vector3 &p_center, const u32 size, const Color &col);
    
private:
    struct DVertex {
        Vector3 v1;
        Color color;
        
        DVertex (const Vector3 &p_v1, const Color &p_col)
        : v1(p_v1), color(p_col) { }
    };
    
private:
    Color color;
    u32 m_glVaoId;
    u32 m_glVboId;

    std::vector<DVertex> m_vertices;
};

// --------------------------------------------------------------------------

inline void DebugGraphics::AddEdge (const Vector3 &v1, const Vector3 &v2) {
    AddEdge(v1, v2, color);
}

inline void DebugGraphics::AddEdge (const Vector3 &v1, const Vector3 &v2, const Color &col) {
    m_vertices.emplace_back(v1, col);
    m_vertices.emplace_back(v2, col);
}

} /* namespace sge */

#endif /* __SHENGINE_DEBUGGRAPHICS_H_ */
