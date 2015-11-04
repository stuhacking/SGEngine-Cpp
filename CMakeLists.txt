cmake_minimum_required(VERSION 2.8.11)
project(SGEngine)

# Start with modern standard: C++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y -Wall -pedantic")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

# Library Targets
add_subdirectory(lib/googletest/googletest)

# Build Targets
add_subdirectory(SGEngine/Sources)
add_subdirectory(SGEngine/Test)
