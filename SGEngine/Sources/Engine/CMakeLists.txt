cmake_minimum_required(VERSION 2.8.11)
project(SGEEngineLib)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

if(NOT APPLE)
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()

find_library(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

include_directories(../Lib)

file(GLOB_RECURSE SOURCES *.cpp .)
add_library(SGEEngineLib ${SOURCES})
target_link_libraries(SGEEngineLib SGECoreLib)
target_link_libraries(SGEEngineLib ${OPENGL_gl_LIBRARY})
if(NOT APPLE)
    target_link_libraries(SGEEngineLib ${GLEW_LIBRARY})
endif()
target_link_libraries(SGEEngineLib ${SDL2_LIBRARIES})
