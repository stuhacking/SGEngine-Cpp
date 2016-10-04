//
// A Basic Test that SDL2 + OpenGL is working.
//
#include <iostream>
#include <fstream>
#include <ctime>

#include "Lib.h"

using namespace sge;

int main (int argc, char *argv[]) {
    std::ofstream output_file ("./out.pgm");
    int offset = time(NULL) & 0xFF;

    if (output_file.is_open()) {
        output_file << "P2\n# Perlin Demo\n512 512\n255\n";
        for (int x = 0; x < 512; ++x) {
            for (int y = 0; y < 512; ++y) {
                float z = Noise::Perlin(x / 512.0f + offset, y / 512.0f,
                                        2.0f, 1.0f, 0.6f, 8);
                // float z = viztest::Worley(x / 512.0f + offset, y / 512.0f,
                //                         12.0f, 1.0f);

                output_file << (int)FMath::Fit(z, -1.0f, 1.0f, 0.0f, 255.0f) << " ";
            }
            output_file << "\n";
        }
        output_file.close();
    } else {
        std::cerr << "Unable to open output file.\n";
        return 1;
    }

    return 0;
}
