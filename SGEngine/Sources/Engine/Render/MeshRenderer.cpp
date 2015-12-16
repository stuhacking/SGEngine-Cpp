//
// MeshRenderer Implementation.
//
#include "../Engine.h"

#include <iostream>
#include <algorithm>

namespace sge {

void MeshRenderer::Compile() {

    if (m_glVaoId == 0) {
        glGenVertexArrays(1, &m_glVaoId);
    }

    if (m_buffers[0] == 0) {
        glGenBuffers(2, m_buffers);
    }

    glBindVertexArray(m_glVaoId);

    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, mesh.VertCount() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));        // Position
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(3));        // Texture coord
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(5));        // Normal
    glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), BUFFER_OFFSET(8)); // Color

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.IndexCount() * sizeof(int), mesh.indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void MeshRenderer::Render() const {
    if (!IsCompiled()) {
        std::cerr << "Error: Attempt to render mesh before compilation!\n";
        return;
    }

    glBindVertexArray(m_glVaoId);
    glEnableVertexAttribArray(0); // Position
    glEnableVertexAttribArray(1); // Texture coord
    glEnableVertexAttribArray(2); // Normal
    glEnableVertexAttribArray(3); // Color

    // Debug: Line Rendering
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.IndexCount()), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

    glBindVertexArray(0);
}

} /* namespace sge */
