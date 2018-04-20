//
// Mesh Implementation.
//
#include "../lib.h"

#include <iostream>
#include <algorithm>

namespace sge {

void Mesh::printVertexInfo () const {
    std::cout << "Compiling Mesh: " << vertCount() << " vertices, "
              << faceCount() << " faces (" << indexCount() << ")";

    if (indexCount() % 3 == 0) {
        std::cout << " Valid";
    } else {
        std::cout << " Invalid";
    }

    for (const Vertex &vert : vertices) {
        std::cout << " " << std::count(std::begin(vertices), std::end(vertices), vert)
                  << " duplicates\n";
    }
}

void Mesh::simplify () {

}

} /* namespace sge */
