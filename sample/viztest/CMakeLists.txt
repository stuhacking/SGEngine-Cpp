# HelloWorld - A Demo app for SGEngine
cmake_minimum_required(VERSION 2.8.11)
project(viztests)

# Set up Compiler warnings for GCC/Clang
if (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wundef -Wno-unused-parameter -pedantic -Wno-long-long")
endif()

include_directories(../../src/lib)

# Builds: Color - Draw color space.
add_executable(colors src/colors.cpp)
target_link_libraries(colors SGECoreLib)

# Builds: Perlin - Perlin noise demo.
add_executable(perlin src/noise.cpp)
target_link_libraries(perlin SGECoreLib)
