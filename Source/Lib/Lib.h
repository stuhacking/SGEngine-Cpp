/*---  Lib.h - SGE Core Library Header  ----------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 */
#ifndef __SGE_LIB_H
#define __SGE_LIB_H

// - Miscellaneous Utilities ------------------------------------------------

#ifndef NDEBUG
 #define IF_DEBUG(x) do { x } while(false)
#else
 #define IF_DEBUG(x) do { } while(0)
#endif /* NDEBUG */

// --------------------------------------------------------------------------

#include "System/Assert.h"
#include "System/Types.h"

#include "Math/FMath.h"
#include "Math/Color.h"
#include "Math/Transform.h"

#include "Util/Random.h"
#include "Util/StringUtil.h"
#include "Util/Clock.h"

#include "Bounds/Line2D.h"
#include "Bounds/Rectangle.h"
#include "Bounds/Circle.h"
#include "Bounds/Ray3D.h"
#include "Bounds/AABB.h"
#include "Bounds/Sphere.h"
#include "Bounds/Intersection.h"

#include "Noise/Noise.h"

#include "Geom/Vertex.h"
#include "Geom/Mesh.h"

#include "Geom/Primitive/Plane.h"
#include "Geom/Primitive/Cube.h"
#include "Geom/Primitive/ICOSphere.h"

#include "Containers/Grid.h"
#include "Util/LibIO.h"

#endif /* __SGE_H */
