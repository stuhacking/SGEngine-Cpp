# SGEngine Top-level CMake File
cmake_minimum_required(VERSION 2.8.11)
project(SGEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# Start with modern standard: C++14, or C++1y
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
if(COMPILER_SUPPORTS_CXX14)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX1Y)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
else()
  message(FATAL_ERROR "${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

# Automatically download/build External Dependencies
execute_process(
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND ./deps.sh
)

# Library Targets
add_subdirectory(External/googletest/googletest)
add_subdirectory(External/rapidjson)

# Build Targets
add_subdirectory(Source)
add_subdirectory(Test)

# Example Programs
add_subdirectory(Examples/HelloWorld)
add_subdirectory(Examples/Noise)
