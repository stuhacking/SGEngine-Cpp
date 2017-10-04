# SGECoreLib - Low level utilities
# Most of SGECoreLib is header only with a small portion
# of complex procedures provided in a static library.
cmake_minimum_required(VERSION 2.8)
project(SGECoreLib)

set(HEADERS
      Math/FMath.h
      Math/Vector2.h
      Math/Vector3.h
      Math/Vector4.h
      Math/Vector2i.h
      Math/Quaternion.h
      Math/Matrix2.h
      Math/Matrix3.h
      Math/Matrix4.h
      Math/Transform.h
      Math/Color.h

      Noise/Noise.h

      Bounds/Rectangle.h
      Bounds/Circle.h
      Bounds/AABB.h
      Bounds/Sphere.h
      Bounds/Line2D.h
      Bounds/Ray3D.h
      Bounds/Intersection.h

      Geom/Vertex.h
      Geom/Mesh.h
      Geom/Primitive/Plane.h
      Geom/Primitive/ICOSphere.h

      Util/Random.h
      Util/StringUtil.h
      Util/Clock.h
      Util/LibIO.h

      Containers/Grid.h

      System/Types.h
      System/Assert.h

      # "Precompiled"
      Lib.h
      )

set(SOURCES ${HEADERS}
      Math/Vector.cpp
      Math/Quaternion.cpp
      Math/Matrix.cpp
      Math/Color.cpp

      Noise/Perlin.cpp
      Noise/Worley.cpp

      Bounds/Line2D.cpp
      Bounds/Ray3D.cpp
      Bounds/Intersection.cpp

      Geom/Mesh.cpp
      Geom/Primitive/Primitive.cpp

      Util/StringUtil.cpp
      Util/Clock.cpp
      Util/LibIO.cpp

      System/Assert.cpp
      )

# Builds: SGECoreLib
add_library(${PROJECT_NAME} ${SOURCES})
