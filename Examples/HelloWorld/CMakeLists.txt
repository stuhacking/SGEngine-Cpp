cmake_minimum_required(VERSION 2.8.11)
project(HelloWorld)

find_library(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

if(NOT APPLE)
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()

include_directories(../../SGEngine/Sources/Lib)
include_directories(../../SGEngine/Sources/Engine)

file(GLOB_RECURSE SOURCES *.cpp .)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_image)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
if(NOT APPLE)
    target_link_libraries(${PROJECT_NAME} GLEW)
endif()
target_link_libraries(${PROJECT_NAME} SGEEngineLib SGECoreLib)
