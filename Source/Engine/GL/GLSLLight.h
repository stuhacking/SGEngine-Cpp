/*
 *
 * Created by shacking on 21/02/17.
 */
#ifndef __SGENGINE_GLSLLIGHT_H
#define __SGENGINE_GLSLLIGHT_H

namespace sge {

class GLSLAttenuation {
public:
    float constant;
    float linear;
    float exponent;

    GLSLAttenuation (const float p_constant = 0.5f, const float p_linear = 0.5f, const float p_exponent = 0.5f)
        : constant{p_constant}, linear{p_linear}, exponent{p_exponent} {}
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

    GLSLLight (const Vec3f &p_albedo = Vec3f_Zero, const Vec3f &p_position = Vec3f_Zero, const Vec3f &p_direction = Vec3f_Y,
                        const GLSLAttenuation &p_attenuation = GLSLAttenuation(), const float p_range = 0.0f)
        : albedo{p_albedo}, position{p_position}, direction{p_direction},
          attenuation{p_attenuation}, range{p_range} {}
};

} /* namespace sge */

#endif /* __SGENGINE_GLSLLIGHT_H */
