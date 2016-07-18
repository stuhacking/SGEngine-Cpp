cmake_minimum_required(VERSION 2.8.11)
project(SGEngineTest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../Source/Lib)

# Source Files
file(GLOB_RECURSE SOURCES *.cpp .)

# Build Targets
add_executable(SGEngineTest ${SOURCES})
target_link_libraries(SGEngineTest gtest gtest_main pthread)
target_link_libraries(SGEngineTest SGECoreLib)
