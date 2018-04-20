# SGEngine test Suite
cmake_minimum_required(VERSION 2.8.11)
project(sgetest)

# Library includes:
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# test includes:
include_directories(../src/lib)

# src Files (Any .cpp file under test/ will be included.)
file(GLOB_RECURSE SOURCES *.cpp .)

# Convenience test command
add_custom_target(tests
  DEPENDS ${PROJECT_NAME}
  COMMAND ${PROJECT_NAME}
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

# Builds: sgetest
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} gtest gtest_main pthread)
target_link_libraries(${PROJECT_NAME} SGECoreLib)
