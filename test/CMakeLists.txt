# SGEngine test Suite
cmake_minimum_required(VERSION 3.8)
project(sgetest)

# src Files (Any .cpp file under test/ will be included.)
file(GLOB_RECURSE SOURCES *.cpp .)

# Convenience test command
add_custom_target(tests
  DEPENDS ${PROJECT_NAME}
  COMMAND ${PROJECT_NAME}
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

# Builds: sgetest
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ../src/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE SGECoreLib)

target_include_directories(${PROJECT_NAME} PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main pthread)
