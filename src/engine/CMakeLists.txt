# SGEEngineLib - Rendering and ui library
# Interface to lower level graphics.
cmake_minimum_required(VERSION 3.8)
project(SGEEngineLib)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

# Link GLEW on non-apple.
if(NOT APPLE)
    find_package(GLEW REQUIRED)
endif()

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
target_include_directories(${PROJECT_NAME} PUBLIC ../lib)
target_link_libraries(${PROJECT_NAME} PUBLIC SGECoreLib)

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_gl_LIBRARY})

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARY})

target_include_directories(${PROJECT_NAME} PRIVATE ${RapidJSON_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${SOIL_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE SOIL)


if(NOT APPLE)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_LIBRARY})
endif()

