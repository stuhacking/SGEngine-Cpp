//
// GLProjection Implementation
//
#include "../Engine.h"

#include <cmath> // tanf

namespace sge {

Mat4f GLProjection::GetPerspectiveProjection(const u32 w, const u32 h) const {
    float aspect = static_cast<float>(w) / static_cast<float>(h);
    float size = near * static_cast<float>(tanf(TO_RADIANS(fov)) / 2.0f);
    float l = -size;
    float r = size;
    float t = size / aspect;
    float b = -t;

    return Mat4f(
        (2.0f * near) / (r - l), 0.0f, 0.0f, 0.0f,
        0.0f, (2.0f * near) / (t - b), 0.0f, 0.0f,
        (r + l) / (r - l), (t + b) / (t - b), -(far + near) / (far - near), -1.0f,
        0.0f, 0.0f, -(2.0f * far * near) / (far - near), 0.0f);
}

Mat4f GLProjection::GetOrthographicProjection(const u32 w, const u32 h) const {
    float aspect = static_cast<float>(w) / static_cast<float>(h);
    float size = FMath::Min(w / 2.0f, h / 2.0f);
    float l = -size;
    float r = size;
    float t = size / aspect;
    float b = -t;

    return Mat4f(
        2.0f / (r - l), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / (t - b), 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f / (far - near), 0.0f,
        -(r + l) / (r - l), -(t + b) / (t - b), -(far + near) / (far - near), 1.0f);
}

} /* namespace sge */