//
// MeshRenderer Implementation.
//
#include "../engine.h"

namespace sge {

void MeshRenderer::compile () {

    if (mGlVaoId == 0) {
        glGenVertexArrays(1, &mGlVaoId);
    }

    if (mBuffers[0] == 0) {
        glGenBuffers(2, mBuffers);
    }

    glBindVertexArray(mGlVaoId);

    glBindBuffer(GL_ARRAY_BUFFER, mBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertCount() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));        // Position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(3));        // Normal
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(6));        // Texture coord
    glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), BUFFER_OFFSET(8)); // Color

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indexCount() * sizeof(int), mesh.indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void MeshRenderer::render () const {
    if (!isCompiled()) {
        IF_DEBUG(gConsole.error("Attempt to render mesh before compilation!\n"); );
        return;
    }

    glBindVertexArray(mGlVaoId);
    glEnableVertexAttribArray(0); // Position
    glEnableVertexAttribArray(1); // Normal
    glEnableVertexAttribArray(2); // Texture coord
    glEnableVertexAttribArray(3); // Color

    // Debug: Line Rendering
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.indexCount()), GL_UNSIGNED_INT, BUFFER_OFFSET(0));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

    glBindVertexArray(0);
}

} /* namespace sge */
