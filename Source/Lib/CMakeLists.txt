# SGECoreLib - Low level utilities
# Most of SGECoreLib is header only with a small portion
# of complex procedures provided in a static library.
cmake_minimum_required(VERSION 2.8.11)
project(SGECoreLib)

set(CMAKE_POSITION_INDEPENDENT_CODE True)

set(SOURCES
  Math/Vector.cpp
  Math/Quaternion.cpp
  Math/Matrix.cpp
  Math/Color.cpp
  Bounds/Line2D.cpp
  Geom/Mesh.cpp
  Geom/Primitive/Primitive.cpp
  Noise/Perlin.cpp
  Noise/Worley.cpp
  Util/StringUtil.cpp
  Util/Clock.cpp
  Util/LibIO.cpp
  )

# Builds: SGECoreLib
add_library(${PROJECT_NAME} ${SOURCES})
