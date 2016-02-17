/*---  Lib.h - SGE Core Library Header  ----------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 */
#ifndef __SGENGINE_LIB_H_
#define __SGENGINE_LIB_H_

#include <cstdint>

// - Miscellaneous Utilities ------------------------------------------------

#ifndef NDEBUG
 #define DEBUG(x) do { x } while(0)
#else
 #define DEBUG(x) do { } while(0)
#endif /* NDEBUG */

// Unsigned aliases
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Signed aliases
typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

// --------------------------------------------------------------------------

#include "Math/FMath.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Quaternion.h"
#include "Math/Matrix2.h"
#include "Math/Matrix3.h"
#include "Math/Matrix4.h"
#include "Math/Color.h"
#include "Math/Transform.h"

#include "Util/Random.h"
#include "Util/StringUtil.h"
#include "Util/Clock.h"

#include "Bounds/Line2D.h"
#include "Bounds/Rectangle.h"
#include "Bounds/Circle.h"
#include "Bounds/AABB.h"

#include "Noise/Noise.h"
#include "Noise/Perlin.h"
#include "Noise/Worley.h"

#include "Geom/Vertex.h"
#include "Geom/Mesh.h"

#include "Geom/Primitive/Plane.h"
#include "Geom/Primitive/Cube.h"
#include "Geom/Primitive/ICOSphere.h"

#include "Util/LibIO.h"

#endif /* __SGENGINE_H_ */
