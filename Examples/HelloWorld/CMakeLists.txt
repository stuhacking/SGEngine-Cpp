# HelloWorld - A Demo app for SGEngine
cmake_minimum_required(VERSION 2.8.11)
project(HelloWorld)

# Set up Compiler warnings for GCC/Clang
if (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wundef -Wno-unused-parameter -pedantic -Wno-long-long")
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

if(NOT APPLE)
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()

include_directories(${RapidJSON_SOURCE_DIR}/include)

include_directories(../../Source/Lib)
include_directories(../../Source/Engine)

file(GLOB_RECURSE SOURCES *.cpp .)

# Builds: HelloWorld
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
if(NOT APPLE)
    target_link_libraries(${PROJECT_NAME} GLEW)
endif()
target_link_libraries(${PROJECT_NAME} SGEEngineLib SGECoreLib)
