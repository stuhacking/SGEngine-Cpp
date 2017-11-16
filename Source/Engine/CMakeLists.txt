# SGEEngineLib - Rendering and UI library
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

set(SOURCES
  Data/jsonfile.cpp
  GL/GLSL.cpp
  GL/GLProjection.cpp
  Image/Image.cpp
  Model/Obj.cpp
  Render/MeshRenderer.cpp
  Render/DebugGraphics.cpp
  UI/Console.cpp

  platform/sdl2/sdl2_Input.cpp
  platform/sdl2/sdl2_Window.cpp
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
