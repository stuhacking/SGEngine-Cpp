Stuart's Game Engine
====================

This is my on-again off-again zen Game Engine project. It's Very much a learning experience for
my own enjoyment, not intended for serious use, but I've licensed it as 3-clause
BSD so if any of it is useful, have at it.

Core Library
------------

Code under the `Source/Lib` directory is mostly stand-alone math utilities that have no external
dependencies, so they can be pulled out and used elsewhere with little modification.

- Math: 2D/3D Vectors, Quaternion, Square Matrices
- Bounds Testing: Circles, Rectangles, Spheres, Axis Aligned Boxes
- 2D Noise: Perlin, Worley
- Geometry: Vertex, Mesh
- String utilities

Engine Library
--------------

Code under the `Source/Engine` directory currently depends on OpenGL, SDL2, and SDL2_image. If you're running
on Linux it will also require GLEW to manage GL extensions. Development happens on OS X and Linux; Windows
support is untested, it probably doesn't work.

- Rendering:
  - GLSL Shader support
  - Texturing (via SDL2_image)
  - Mesh Rendering, Wavefront .obj importer
  - Debug Graphics: Simple Line drawing
- UI:
  - Window Creation and Input Handling (via SDL2)
