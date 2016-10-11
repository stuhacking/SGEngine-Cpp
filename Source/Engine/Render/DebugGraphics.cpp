//
// Debug Graphics Implementation
//
#include "../Engine.h"

namespace sge {

//=====================================================
// DebugGraphics will typically be cleared each frame
// so roll compile into the render stage.
//=====================================================
void DebugGraphics::Render () {

    if (m_vertices.empty()) {
        return;
    }

    if (m_glVaoId == 0) {
        glGenVertexArrays(1, &m_glVaoId);
    }

    if (m_glVboId == 0) {
        glGenBuffers(1, &m_glVboId);
    }

    glBindVertexArray(m_glVaoId);
    glBindBuffer(GL_ARRAY_BUFFER, m_glVboId);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(DVertex), m_vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DVertex), BUFFER_OFFSET(0)); // Position
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DVertex), BUFFER_OFFSET(3)); // Color
    glEnableVertexAttribArray(0); // Position
    glEnableVertexAttribArray(1); // Color

    // Unbind the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_LINES, 0, m_vertices.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

// --------------------------------------------------------------------------
//   DebugGraphics Draw Commands

void DebugGraphics::AddPoint (const Vec3f &p, const float radius, const Color &col) {
    AddEdge(Vec3f(p.x - radius, p.y, p.z), Vec3f(p.x + radius, p.y, p.z), col);
    AddEdge(Vec3f(p.x, p.y - radius, p.z), Vec3f(p.x, p.y + radius, p.z), col);
    AddEdge(Vec3f(p.x, p.y, p.z - radius), Vec3f(p.x, p.y, p.z + radius), col);
}

void DebugGraphics::AddSphere (const Vec3f &p_center, const float radius, const Color &col) {
    float limit = TO_RADIANS(360.0f);
    float step = limit / SPHERE_INCREMENT;
    float x_ = radius * std::cos(0.0f);
    float y_ = radius * std::sin(0.0f);

    for (float theta = step, thetaMax = limit+step; theta <= thetaMax; theta += step) {
        float x = radius * std::cos(theta);
        float y = radius * std::sin(theta);

        AddEdge(p_center + Vec3f(x_, 0.0f, y_), p_center + Vec3f(x, 0.0f, y), col);
        AddEdge(p_center + Vec3f(x_, y_, 0.0f), p_center + Vec3f(x, y, 0.0f), col);
        AddEdge(p_center + Vec3f(0.0f, x_, y_), p_center + Vec3f(0.0f, x, y), col);

        x_ = x;
        y_ = y;
    }
}

void DebugGraphics::AddGrid (const Vec3f &p_center, const u32 size, const Color &col) {
    float hSize = size * 0.5f;
    i32 xMin = static_cast<i32>(p_center.x) - hSize;
    i32 zMin = static_cast<i32>(p_center.z) - hSize;

    for (u32 i = 0; i <= size; ++i) {
        i32 offset = static_cast<i32>(i);
        AddEdge(Vec3f(xMin, p_center.y, zMin + offset), Vec3f(xMin + size, p_center.y, zMin + offset), col);
        AddEdge(Vec3f(xMin + offset, p_center.y, zMin), Vec3f(xMin + offset, p_center.y, zMin + size), col);
    }
}

void DebugGraphics::AddBox (const Vec3f &p_min, const Vec3f &p_max, const Color &col) {
    AddEdge(Vec3f(p_min.x, p_min.y, p_min.z), Vec3f(p_max.x, p_min.y, p_min.z), col);
    AddEdge(Vec3f(p_min.x, p_min.y, p_max.z), Vec3f(p_max.x, p_min.y, p_max.z), col);
    AddEdge(Vec3f(p_min.x, p_min.y, p_min.z), Vec3f(p_min.x, p_min.y, p_max.z), col);
    AddEdge(Vec3f(p_max.x, p_min.y, p_min.z), Vec3f(p_max.x, p_min.y, p_max.z), col);

    AddEdge(Vec3f(p_min.x, p_max.y, p_min.z), Vec3f(p_max.x, p_max.y, p_min.z), col);
    AddEdge(Vec3f(p_min.x, p_max.y, p_max.z), Vec3f(p_max.x, p_max.y, p_max.z), col);
    AddEdge(Vec3f(p_min.x, p_max.y, p_min.z), Vec3f(p_min.x, p_max.y, p_max.z), col);
    AddEdge(Vec3f(p_max.x, p_max.y, p_min.z), Vec3f(p_max.x, p_max.y, p_max.z), col);

    AddEdge(Vec3f(p_min.x, p_min.y, p_min.z), Vec3f(p_min.x, p_max.y, p_min.z), col);
    AddEdge(Vec3f(p_min.x, p_min.y, p_max.z), Vec3f(p_min.x, p_max.y, p_max.z), col);
    AddEdge(Vec3f(p_max.x, p_min.y, p_min.z), Vec3f(p_max.x, p_max.y, p_min.z), col);
    AddEdge(Vec3f(p_max.x, p_min.y, p_max.z), Vec3f(p_max.x, p_max.y, p_max.z), col);
}

} /* namespace sge */
