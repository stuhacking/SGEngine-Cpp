/*---  fmath.h - Float Math Header  --------------------------------*- C++ -*---
 *
 *                           Stuart's Game Engine
 *
 * This file is distributed under the Revised BSD License. See LICENSE.TXT
 * for details.
 *
 * --------------------------------------------------------------------------
 *
 * @brief Implements simple math functions for floats
 */
#ifndef __SGE_FMATH_H
#define __SGE_FMATH_H

#include <cmath>
#include <cfloat>

#include "../sys/assert.h"

namespace math {

constexpr float kPi = static_cast<float>(M_PI);
constexpr float kTau = kPi * 2.0f;
constexpr float kHalfPi = kPi * 0.5f;

constexpr float kE = static_cast<float>(M_E);
constexpr float kInfty = static_cast<float>(INFINITY);


/** Degrees to radians. */
inline constexpr
float rad (const float a) { return a * (kPi / 180.0f); }

/** Radians to degrees. */
inline constexpr
float deg (const float a) { return a * (180.0f / kPi); }

/**
 * @brief Return the smaller of two numbers.
 */
inline constexpr
float min (const float a, const float b) {
    return (a < b) ? a : b;
}

/**
 * @brief Return the smaller of two numbers.
 */
inline constexpr
int min (const int a, const int b) {
    return (a < b) ? a : b;
}

/**
 * @brief Return the greater of two numbers.
 */
inline constexpr
float max (const float a, const float b) {
    return (a > b) ? a : b;
}

/**
 * @brief Return the greater of two numbers.
 */
inline constexpr
int max (const int a, const int b) {
    return (a > b) ? a : b;
}

/**
 * Clamp float value within min/max boundaries.
 */
inline constexpr
float clamp (const float val,
             const float a, const float b) {
    return max(a, min(b, val));
}

/**
 * Clamp int value within min/max boundaries.
 */
inline constexpr
int clamp (const int val, const int a, const int b) {
    return max(a, min(b, val));
}

/**
 * Convert a value within a range to a ratio. Resulting value may
 * fall outside the 0.0f .. 1.0f range.
 */
inline constexpr
float toRatio (float val, float min, float max) {
    return (val - min) / (max - min);
}

/**
 * Convert a value within a range to a ratio strictly clamped to
 * 0.0f .. 1.0f
 */
inline constexpr
float clampRatio (float val, float min, float max) {
    return clamp(toRatio(val, min, max), 0.0f, 1.0f);
}

/**
 * @brief Find the nearest power of 2 after value.
 * @param val
 * @return
 */
inline
int nearest2Pow (const int val) {
    verify(val >= 0);

    int result = 2;
    while (result < val) {
        result <<= 1;
    }
    return result;
}

/**
 * @brief Linear interpolation
 * @param ratio
 * @param min
 * @param max
 * @return
 */
inline
float lerp (float ratio, float min, float max) {
    if (ratio <= 0.0f)
        return min;
    else if (ratio >= 1.0f)
        return max;
    else
        return min + ratio * (max - min);
}

/**
 * @brief Sine interpolation
 * @param min
 * @param max
 * @param ratio
 * @return
 */
inline
float sinInterpolate (const float min, const float max,
                      const float ratio) {
    float f = ratio * math::kPi;
    f = (1.0f - sinf(f)) * 0.5f;

    return min * (1.0f - f) + max * f;
}

/**
 * @brief Cosine interpolation
 * @param min
 * @param max
 * @param ratio
 * @return
 */
inline
float cosInterpolate (const float min, const float max,
                      const float ratio) {
    float f = ratio * math::kPi;
    f = (1.0f - cosf(f)) * 0.5f;

    return min * (1.0f - f) + max * f;
}

/**
 * @brief Fit a value from one range into another range.
 * @param val Old value
 * @param oMin old minimum
 * @param oMax old maximum
 * @param nMin new minimum
 * @param nMax new maximum
 * @return New resized value.
 */
inline
float fit (float val, float oMin, float oMax, float nMin,
           float nMax) {
    return lerp(toRatio(val, oMin, oMax), nMin, nMax);
}

} /* namespace math */

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "vector2i.h"
#include "quaternion.h"
#include "matrix2.h"
#include "matrix3.h"
#include "matrix4.h"

#endif /* __SGE_FMATH_H */
