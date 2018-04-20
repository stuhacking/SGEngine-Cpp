/*
 *
 * Created by shacking on 21/02/17.
 */
#ifndef __SGE_GLSLLIGHT_H
#define __SGE_GLSLLIGHT_H

namespace sge {

class GLSLAttenuation {
public:
    float constant;
    float linear;
    float exponent;

    GLSLAttenuation (const float pConstant = 0.5f,
                     const float pLinear = 0.5f,
                     const float pExponent = 0.5f)
            : constant{pConstant}, linear{pLinear}, exponent{pExponent} {}
};

/**
 * 16byte aligned light struct to match data expected by shaders.
 */
class alignas(16) GLSLLight {
public:
    Vec3f albedo;
    Vec3f position;
    Vec3f direction;
    GLSLAttenuation attenuation;
    float range;

    GLSLLight (const Vec3f &pAlbedo = Vec3f_Zero,
               const Vec3f &pPosition = Vec3f_Zero,
               const Vec3f &pDirection = Vec3f_Y,
               const GLSLAttenuation &pAttenuation = GLSLAttenuation(),
               const float pRange = 0.0f)
            : albedo{pAlbedo}, position{pPosition}, direction{pDirection},
              attenuation{pAttenuation}, range{pRange} {}
};

} /* namespace sge */

#endif /* __SGE_GLSLLIGHT_H */
