//
// Mesh Implementation.
//
#include "../Lib.h"

#include <iostream>
#include <algorithm>

namespace sge {

void Mesh::PrintVertexInfo () const {
    std::cout << "Compiling Mesh: " << VertCount() << " vertices, "
              << FaceCount() << " faces (" << IndexCount() << ")";

    if (IndexCount() % 3 == 0) {
        std::cout << " Valid";
    } else {
        std::cout << " Invalid";
    }

    for (const Vertex &vert : vertices) {
        std::cout << vert << " " << std::count(std::begin(vertices), std::end(vertices), vert)
                  << " duplicates\n";
    }
}

void Mesh::Simplify () {

}

} /* namespace sge */
