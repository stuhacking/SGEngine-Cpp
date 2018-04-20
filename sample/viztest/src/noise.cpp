//
// A Basic test of Noise generators.
//
#include <iostream>
#include <fstream>
#include <ctime>

#include "lib.h"

static constexpr auto gOutput = "./noise.out.pgm";

using namespace sge;

int main (int argc, char *argv[]) {
    std::ofstream output_file (gOutput);

    int offset = time(nullptr) & 0xFF;

    if (output_file.is_open()) {
        output_file << "P2\n# Perlin Demo\n512 512\n255\n";
        for (int x = 0; x < 256; ++x) {
            for (int y = 0; y < 512; ++y) {
                float z = noise::perlin(x / 512.0f + offset, y / 512.0f,
                                        1.0f, 1.0f, 0.5f, 8);
                output_file << (int)math::fit(z, -1.0f, 1.0f, 0.0f, 255.0f) << " ";
            }
            output_file << "\n";
        }
        for (int x = 0; x < 256; ++x) {
            for (int y = 0; y < 512; ++y) {
                float z = noise::worley(x / 512.0f + offset, y / 512.0f,
                                        8.0f, 1.4f);

                output_file << (int)math::fit(z, -1.0f, 1.0f, 255.0f, 0.0f) << " ";
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
