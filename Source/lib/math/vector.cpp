//
//Vector Implementation.
//
#include "../lib.h"

#include <random>

//==================================
// VECTOR 2
//==================================

const Vec2f Vec2f_Zero {0.0f};
const Vec2f Vec2f_One  {1.0f};
const Vec2f Vec2f_X    {1.0f, 0.0f};
const Vec2f Vec2f_Y    {0.0f, 1.0f};

//==================================
// VECTOR 2i
//==================================

const Vec2i Vec2i_Zero {0};
const Vec2i Vec2i_One  {1};
const Vec2i Vec2i_X    {1, 0};
const Vec2i Vec2i_Y    {0, 1};

//==================================
// VECTOR 3
//==================================

const Vec3f Vec3f_Zero {0.0f};
const Vec3f Vec3f_One  {1.0f};
const Vec3f Vec3f_X    {1.0f, 0.0f, 0.0f};
const Vec3f Vec3f_Y    {0.0f, 1.0f, 0.0f};
const Vec3f Vec3f_Z    {0.0f, 0.0f, 1.0f};


Vec3f Vec3f::rotate (const float angle, const Vec3f &axis) const {
    Vec3f rot = *this;
    rot.rotateSelf(angle, axis);

    return rot;
}


void Vec3f::rotateSelf (const float angle, const Vec3f &axis) {
    *this = Quat4f(angle, axis).rotate(*this);
}

// TODO: Is this an appropriate member func? Create a Library for producing procedural values.
static std::default_random_engine e;
static std::uniform_real_distribution<float> dist{0.0f, 1.0f};

Vec3f Vec3f::random (const s32 seed) {
    e.seed(noise::hash(seed, 0));

    float theta = math::Tau * dist(e);
    float phi = acosf(2.0f * dist(e) - 1.0f);

    return Vec3f(sinf(phi) * cosf(theta),
                 sinf(phi) * sinf(theta),
                 cosf(phi));
}

//==================================
// VECTOR 4
//==================================

const Vec4f Vec4f_Zero {0.0f};
const Vec4f Vec4f_One  {1.0f};
const Vec4f Vec4f_X    {1.0f, 0.0f, 0.0f, 0.0f};
const Vec4f Vec4f_Y    {0.0f, 1.0f, 0.0f, 0.0f};
const Vec4f Vec4f_Z    {0.0f, 0.0f, 1.0f, 0.0f};
const Vec4f Vec4f_W    {0.0f, 0.0f, 0.0f, 1.0f};
