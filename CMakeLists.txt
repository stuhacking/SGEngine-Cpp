cmake_minimum_required(VERSION 2.8.11)
project(SGEngine)

# Start with modern standard: C++14, or C++1y if using APPLE
# TODO Better check for C++14 compiler support, and fallback/failure.
if (APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y")
endif()

# Automatically download/build External Dependencies
execute_process(
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND ./deps.sh
)

# Library Targets
add_subdirectory(External/googletest/googletest)

# Build Targets
add_subdirectory(SGEngine/Sources)
add_subdirectory(SGEngine/Test)

# Example Programs
add_subdirectory(Examples/HelloWorld)
