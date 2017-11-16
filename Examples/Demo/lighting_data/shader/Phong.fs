// FRAGMENT SHADER - Phong lighting
#version 330

#define ENABLE_AMBIENT 1
#define ENABLE_DIRECTIONAL 1
#define ENABLE_SPOT 0
#define ENABLE_POINT 1

const int MAX_LIGHTS = 16;

//***********************************************************************************
// Phong Lighting Support
//***********************************************************************************

//*****************
// Data Structures
//*****************

// Alignment - 12 + 12 + 12 + 12 + 4 = 52
// Pads to %64  (12).
struct Light_Info {
    float r, g, b;               // Albedo
    float x, y, z;               // Position
    float dx, dy, dz;            // Direction
    float foCon, foLin, foExp;   // Falloff/Attenuation
    float range;                 // Range
};

struct Material {
    float specIntensity;
    float specExponent;
};

//****************
// Functions
//****************

/**
 * Calculate ambient using albedo.
 */
vec3 calculateAmbientLight (Light_Info light) {
    return vec3(light.r, light.g, light.b);
}

/**
 * Calculate the basic lighting effect.
 */
vec3 calculateLight (
    in Light_Info light,
    in vec3 direction,
    in vec3 normal,
    in vec3 position,
    in vec3 eyePosition,
    in Material mat) {
    float diffuseF = dot(-direction, normal);
    vec3 albedo = vec3(light.r, light.g, light.b);
    vec3 colDiffuse = vec3(0, 0, 0), colSpecular = vec3(0, 0, 0);

    if (diffuseF > 0) {
        colDiffuse = albedo * diffuseF;

        vec3 dirToEye = normalize(eyePosition - position);
        vec3 reflectDirection = normalize(reflect(-direction, normal));

        float specFactor = dot(dirToEye, reflectDirection);
        specFactor = pow(specFactor, mat.specExponent);

        if (specFactor > 0) {
            colSpecular = albedo * mat.specIntensity * specFactor;
        }
    }

    return colDiffuse + colSpecular;
}

/**
 * Calculate Directional Light color effect.
 */
vec3 calculateDirectionalLight (
    in Light_Info light,
    in vec3 normal,
    in vec3 position,
    in vec3 eyePosition,
    in Material mat) {
    return calculateLight(light, vec3(light.dx, light.dy, light.dz), normal,
                          position, eyePosition, mat);
}

/**
 * Calculate Point Light color effect.
 */
vec3 calculatePointLight (
    in Light_Info light,
    in vec3 normal,
    in vec3 position,
    in vec3 eyePosition,
    in Material mat) {
    vec3 lightDirection = position - vec3(light.x, light.y, light.z);
    float distanceToPoint = length(lightDirection);

    if (distanceToPoint > light.range) {
        return vec3(0, 0, 0);
    }

    lightDirection = normalize(lightDirection);

    vec3 color = calculateLight(light, lightDirection, normal, position, eyePosition, mat);

    float attenuation = light.foCon +
                        light.foLin * distanceToPoint +
                        light.foExp * distanceToPoint * distanceToPoint +
                        0.0001;

    return color / attenuation;
}

/**
 * Calculate lighting influence for this fragment.
 */
vec4 calculateLightColor (
    in Light_Info lights[MAX_LIGHTS],
    in ivec4 offsets,
    in vec3 normal,
    in vec3 position,
    in vec3 eyePosition,
    in Material mat) {
    vec3 lightColor = vec3(0, 0, 0);

    int k = 0, kMax;

    for (kMax = offsets[0]; k < kMax; ++k) {
#if ENABLE_AMBIENT
        lightColor += calculateAmbientLight(lights[k]);
#endif
    }

    for (kMax = offsets[1]; k < kMax; ++k) {
#if ENABLE_DIRECTIONAL
        lightColor += calculateDirectionalLight(lights[k], normal, position, eyePosition, mat);
#endif
    }

    for (kMax = offsets[2]; k < kMax; ++k) {
#if ENABLE_SPOT
#endif
    }

    for (kMax = offsets[3]; k < kMax; ++k) {
#if ENABLE_POINT
        lightColor += calculatePointLight(lights[k], normal, position, eyePosition, mat);
#endif
    }

    return vec4(lightColor, 1.0);
}

//***********************************************************************************
// Shader Section
//***********************************************************************************

//*****************
// Frame Uniforms
//*****************

// Sort lights into ambient, directional, spot, point and store offsets in a vec4 such that:
//    0 .. < [0] = ambient
//  [0] .. < [1] = directional
//  [1] .. < [2] = spot
//  [2] .. < [3] = point
// Don't branch on light type, all lights have the same info, just iterate array slices.
layout (std140) uniform LightingBlock {
    ivec4 offsets;
    Light_Info data[MAX_LIGHTS];
} lights;

/* View Information */
uniform vec3 eyePos;

//*****************
// Draw Uniforms
//*****************

uniform Material material;
uniform sampler2D sampler;

//*****************
// Draw parameters
//*****************

in vec3 worldPos0;
in vec3 normal0;
in vec2 texCoord0;
in vec4 vertColor0;

//*****************
// Fragment Outputs
//*****************

out vec4 fragColor;

/**
 * Phong Fragment Shader.
 */
void main () {
    vec3 normal = normalize(normal0);
    vec4 baseColor = vertColor0 * texture(sampler, texCoord0);

    vec4 lightColor = calculateLightColor(lights.data, lights.offsets, normal,
                                          worldPos0, eyePos, material);

    fragColor = baseColor * lightColor;
}
