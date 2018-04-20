# SGEEngineLib - Rendering and ui library
# Interface to lower level graphics.
cmake_minimum_required(VERSION 2.8.11)
project(SGEEngineLib)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Link GLEW on non-apple.
if(NOT APPLE)
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

include_directories(${RapidJSON_SOURCE_DIR}/include)
include_directories(${SOIL_SOURCE_DIR}/include)

include_directories(../lib)

set(HEADERS
    data/jsonfile.h
    gl/glprojection.h
    gl/glslshader.h
    gl/glslprogram.h
    gl/glsllight.h
    image/image.h
    render/debuggraphics.h
    render/meshrenderer.h
    render/imagemanager.h
    ui/console.h
    ui/input.h
    ui/sgewindow.h
    model/obj.h
    engine.h
    )

set(SOURCES ${HEADERS}
    data/jsonfile.cpp
    gl/glsl.cpp
    gl/glprojection.cpp
    image/image.cpp
    model/obj.cpp
    render/meshrenderer.cpp
    render/debuggraphics.cpp
    ui/console.cpp

    platform/sdl2/sdl2_input.cpp
    platform/sdl2/sdl2_window.cpp
    )

# Builds: SGEEngineLib
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} SGECoreLib)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
if(NOT APPLE)
    target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARY})
endif()
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries(${PROJECT_NAME} SOIL)
