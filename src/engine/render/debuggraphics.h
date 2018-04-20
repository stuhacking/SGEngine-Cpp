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
#ifndef __SGE_DEBUGGRAPHICS_H
#define __SGE_DEBUGGRAPHICS_H



namespace sge {

class DebugGraphics {
public:
    /**
     * Create a DebugGraphics object with an optional default
     * draw color.
     */
    DebugGraphics () : mGlVaoId{0}, mGlVboId{0} {
        mVertices.reserve(64);
    }

    /**
     * Clear current debug graphics.
     * Destructive.
     */
    void clear () { mVertices.clear(); }

    void render ();
    /**
     * Draw an edge using a custom color.
     */
    void edge (const Vec3f &pStart, const Vec3f &pEnd, const Color &pCol);

    /**
     * Draw a point as an intersection of 3 edges where the intersection
     * occurs at point p and the edges extends radius units from p using
     * a custom color.
     */
    void point (const Vec3f &pPos, const float pRadius, const Color &pCol);

    /**
     * Draw a sphere container as a set of axis aligned rings where the center
     * of each ring is point p_center, and each ring extends radius units from
     * p_center. Uses a custom color.
     */
    void sphere (const Vec3f &pCenter, const float pRadius, const Color &pCol);

    /**
     * Draw a Grid on the (X, Z) plane at Y = 0, where the center of the grid
     * is point p_center, and the grid extends size / 2 units in X and Z. Grid
     * squares are drawn 1 unit apart. Uses a custom color.
     */
    void grid (const Vec3f &pCenter, const u32 pSize, const Color &pCol);

    /**
     * Draw a bounding box enclosing the region defined by points p_min..p_max.
     * Uses a custom color of this DebugGraphics object.
     */
    void box (const Vec3f &pMin, const Vec3f &pMax, const Color &pCol);

private:
    /**
     * @brief Smaller vertex struct with just position and colour.
     */
    struct DVertex {
        Vec3f pos;
        Color color;

        DVertex (const Vec3f &pPos, const Color &pCol)
        : pos(pPos), color(pCol) { }
    };

private:
    u32 mGlVaoId;
    u32 mGlVboId;

    std::vector<DVertex> mVertices;
};

// --------------------------------------------------------------------------

inline void DebugGraphics::edge (const Vec3f &pStart, const Vec3f &pEnd,
                                 const Color &pCol) {
    mVertices.emplace_back(pStart, pCol);
    mVertices.emplace_back(pEnd, pCol);
}

} /* namespace sge */

#endif /* __SGE_DEBUGGRAPHICS_H */
