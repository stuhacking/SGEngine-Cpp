//
// Debug Graphics Implementation
//
#include "../engine.h"

#include <cmath> // cos, sin

namespace sge {

//=====================================================
// DebugGraphics will typically be cleared/modified
// each frame so roll compile into the render stage.
//=====================================================
void DebugGraphics::render () {

    if (mVertices.empty()) {
        return;
    }

    if (mGlVaoId == 0) {
        glGenVertexArrays(1, &mGlVaoId);
    }

    if (mGlVboId == 0) {
        glGenBuffers(1, &mGlVboId);
    }

    glBindVertexArray(mGlVaoId);
    glBindBuffer(GL_ARRAY_BUFFER, mGlVboId);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(DVertex), mVertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DVertex), BUFFER_OFFSET(0)); // Position
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DVertex), BUFFER_OFFSET(3)); // Color
    glEnableVertexAttribArray(0); // Position
    glEnableVertexAttribArray(1); // Color

    // Unbind the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(mVertices.size()));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

// --------------------------------------------------------------------------
//   DebugGraphics Draw Commands

void DebugGraphics::point (const Vec3f &pPos, const float pRadius,
                           const Color &pCol) {
    edge(Vec3f(pPos.x - pRadius, pPos.y, pPos.z), Vec3f(pPos.x + pRadius, pPos.y, pPos.z), pCol);
    edge(Vec3f(pPos.x, pPos.y - pRadius, pPos.z), Vec3f(pPos.x, pPos.y + pRadius, pPos.z), pCol);
    edge(Vec3f(pPos.x, pPos.y, pPos.z - pRadius), Vec3f(pPos.x, pPos.y, pPos.z + pRadius), pCol);
}

void DebugGraphics::sphere (const Vec3f &pCenter, const float pRadius,
                            const Color &pCol) {
    // Calculate circle resolution.
    constexpr float limit = math::rad(360.0f);
    constexpr float increment = limit / 12.0f;

    float x_ = pRadius * std::cos(0.0f);
    float y_ = pRadius * std::sin(0.0f);

    for (float theta = increment, thetaMax = limit + increment; theta <= thetaMax; theta += increment) {
        float x = pRadius * std::cos(theta);
        float y = pRadius * std::sin(theta);

        edge(pCenter + Vec3f(x_, 0.0f, y_), pCenter + Vec3f(x, 0.0f, y),
             pCol);
        edge(pCenter + Vec3f(x_, y_, 0.0f), pCenter + Vec3f(x, y, 0.0f),
             pCol);
        edge(pCenter + Vec3f(0.0f, x_, y_), pCenter + Vec3f(0.0f, x, y),
             pCol);

        x_ = x;
        y_ = y;
    }
}

void DebugGraphics::grid (const Vec3f &pCenter, const u32 pSize,
                          const Color &pCol) {
    s32 hSize = pSize / 2;
    s32 xMin = static_cast<s32>(pCenter.x) - hSize;
    s32 zMin = static_cast<s32>(pCenter.z) - hSize;

    for (u32 i = 0; i <= pSize; ++i) {
        s32 offset = static_cast<s32>(i);
        edge(Vec3f(xMin, pCenter.y, zMin + offset),
             Vec3f(xMin + pSize, pCenter.y, zMin + offset), pCol);
        edge(Vec3f(xMin + offset, pCenter.y, zMin),
             Vec3f(xMin + offset, pCenter.y, zMin + pSize), pCol);
    }
}

void DebugGraphics::box (const Vec3f &pMin, const Vec3f &pMax,
                         const Color &pCol) {
    // Bottom Square
    edge(Vec3f(pMin.x, pMin.y, pMin.z), Vec3f(pMax.x, pMin.y, pMin.z),
         pCol);
    edge(Vec3f(pMin.x, pMin.y, pMax.z), Vec3f(pMax.x, pMin.y, pMax.z),
         pCol);
    edge(Vec3f(pMin.x, pMin.y, pMin.z), Vec3f(pMin.x, pMin.y, pMax.z),
         pCol);
    edge(Vec3f(pMax.x, pMin.y, pMin.z), Vec3f(pMax.x, pMin.y, pMax.z),
         pCol);

    // Top Square
    edge(Vec3f(pMin.x, pMax.y, pMin.z), Vec3f(pMax.x, pMax.y, pMin.z),
         pCol);
    edge(Vec3f(pMin.x, pMax.y, pMax.z), Vec3f(pMax.x, pMax.y, pMax.z),
         pCol);
    edge(Vec3f(pMin.x, pMax.y, pMin.z), Vec3f(pMin.x, pMax.y, pMax.z),
         pCol);
    edge(Vec3f(pMax.x, pMax.y, pMin.z), Vec3f(pMax.x, pMax.y, pMax.z),
         pCol);

    // Vertical edges
    edge(Vec3f(pMin.x, pMin.y, pMin.z), Vec3f(pMin.x, pMax.y, pMin.z),
         pCol);
    edge(Vec3f(pMin.x, pMin.y, pMax.z), Vec3f(pMin.x, pMax.y, pMax.z),
         pCol);
    edge(Vec3f(pMax.x, pMin.y, pMin.z), Vec3f(pMax.x, pMax.y, pMin.z),
         pCol);
    edge(Vec3f(pMax.x, pMin.y, pMax.z), Vec3f(pMax.x, pMax.y, pMax.z),
         pCol);
}

} /* namespace sge */
