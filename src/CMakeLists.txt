# SGEngine Sub-projects
cmake_minimum_required(VERSION 2.8.11)
project(SGEngine)

# Set up Compiler warnings for GCC/Clang
if (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wundef -Wno-unused-parameter -pedantic -Wno-long-long")
endif()

add_subdirectory(lib)
add_subdirectory(engine)
