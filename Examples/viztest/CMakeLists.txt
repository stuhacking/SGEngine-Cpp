# HelloWorld - A Demo app for SGEngine
cmake_minimum_required(VERSION 2.8.11)
project(VizTests)

# Set up Compiler warnings for GCC/Clang
if (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wundef -Wno-unused-parameter -pedantic -Wno-long-long")
endif()

include_directories(../../Source/lib)

# Builds: Color - Draw color space.
add_executable(Colors Source/Colors.cpp)
target_link_libraries(Colors SGECoreLib)

# Builds: Perlin - Perlin noise demo.
add_executable(Perlin Source/Noise.cpp)
target_link_libraries(Perlin SGECoreLib)
