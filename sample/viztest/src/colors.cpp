//
// A Basic test of colors.
//
#include <iostream>
#include <fstream>
#include <ctime>

#include "lib.h"

static constexpr auto gOutput = "./colors.out.pgm";

using namespace sge;

int main (int argc, char *argv[]) {
    std::ofstream output_file (gOutput);
    Random r = Random();

    if (output_file.is_open()) {
        output_file << "P3\n# Colors Demo\n512 768\n255\n";
        for (int x = 0; x < 256; ++x) {
            for (int y = 0; y < 512; ++y) {
                Color c = Color::fromHSL(math::fit(y, 0.0f, 512.0f, 0.0f, 360.0f), 1.0f, math::toRatio(x, 255, 0));
                output_file << "" << (u32)c.r << " " << (u32)c.g << " " << (u32)c.b << " ";
            }
            output_file << "\n";
        }
        for (int x = 0; x < 256; ++x) {
            for (int y = 0; y < 128; ++y) {
                Color c = Color(math::fit(y, 0, 128, 0, 255), 0, 0);
                output_file << "" << (u32)c.r << " " << (u32)c.g << " " << (u32)c.b << " ";
            }
            for (int y = 128; y < 256; ++y) {
                Color c = Color(0, math::fit(y, 128, 256, 0, 255), 0);
                output_file << "" << (u32)c.r << " " << (u32)c.g << " " << (u32)c.b << " ";
            }
            for (int y = 256; y < 384; ++y) {
                Color c = Color(0, 0, math::fit(y, 256, 384, 0, 255));
                output_file << "" << (u32)c.r << " " << (u32)c.g << " " << (u32)c.b << " ";
            }
            for (int y = 384; y < 512; ++y) {
                Color c = Color(r.nextInt());
                output_file << "" << (u32)c.r << " " << (u32)c.g << " " << (u32)c.b << " ";
            }
            output_file << "\n";
        }
        for (int x = 0; x < 256; ++x) {
            for (int y = 0; y < 512; ++y) {
                Color c = Color::fromHSL(math::fit(y, 0, 512.0f, 0, 360.0f), 1.0f, 0.5f);
                output_file << "" << (u32)c.r << " " << (u32)c.g << " " << (u32)c.b << " ";
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
