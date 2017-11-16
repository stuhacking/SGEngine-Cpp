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

#include "sys/assert.h"
#include "sys/types.h"
#include "sys/util.h"

#include "math/math.h"
#include "math/color.h"
#include "math/transform.h"

#include "util/random.h"
#include "util/stringutil.h"
#include "util/clock.h"

#include "bounds/line2d.h"
#include "bounds/rect.h"
#include "bounds/circle.h"
#include "bounds/ray3d.h"
#include "bounds/aabb.h"
#include "bounds/sphere.h"
#include "bounds/intersection.h"

#include "noise/noise.h"

#include "container/grid.h"

#include "geom/Vertex.h"
#include "geom/Mesh.h"
#include "geom/Primitive/Plane.h"
#include "geom/Primitive/Cube.h"
#include "geom/Primitive/ICOSphere.h"

#include "util/libio.h"

#endif /* __SGE_H */
