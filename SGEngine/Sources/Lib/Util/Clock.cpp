//
// Clock Implementation.
//
#include "../Lib.h"

#include <chrono>

namespace sge {

// Initialize the internal high-res clock.
static auto start = std::chrono::high_resolution_clock::now();

u64 Clock::NanoTime() {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now-start).count();
}

u64 Clock::MillisTime () {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now-start).count();
}

} /* namespace sge */
