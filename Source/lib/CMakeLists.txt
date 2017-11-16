# SGECoreLib - Low level utilities
# Most of SGECoreLib is header only with a small portion
# of complex procedures provided in a static library.
cmake_minimum_required(VERSION 3.8)
project(SGECoreLib)

set(HEADERS
      math/math.h
      math/vector2.h
      math/vector3.h
      math/vector4.h
      math/vector2i.h
      math/quaternion.h
      math/matrix2.h
      math/matrix3.h
      math/matrix4.h
      math/transform.h
      math/color.h

      noise/noise.h

      bounds/rect.h
      bounds/circle.h
      bounds/aabb.h
      bounds/sphere.h
      bounds/line2d.h
      bounds/ray3d.h
      bounds/intersection.h

      util/random.h
      util/stringutil.h
      util/clock.h
      util/libio.h

      container/grid.h

      sys/types.h
      sys/assert.h
      sys/util.h

      geom/Vertex.h
      geom/Mesh.h
      geom/Primitive/Plane.h
      geom/Primitive/Cube.h
      geom/Primitive/ICOSphere.h

      # "Precompiled"
      lib.h
      )

set(SOURCES ${HEADERS}
      math/vector.cpp
      math/quaternion.cpp
      math/matrix.cpp
      math/color.cpp

      noise/noise.cpp

      bounds/line2d.cpp
      bounds/ray3d.cpp

      util/stringutil.cpp
      util/clock.cpp
      util/libio.cpp

      sys/assert.cpp
      sys/util.cpp

      geom/Mesh.cpp
      geom/Primitive/Primitive.cpp
      )

# Builds: SGECoreLib
add_library(${PROJECT_NAME} ${SOURCES})
