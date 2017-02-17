// Phong lit object shader.
#version 330

#define ENABLE_AMBIENT 0
#define ENABLE_DIRECTIONAL 1
#define ENABLE_SPOT 0
#define ENABLE_POINT 1

const int MAX_LIGHTS = 16;

//*****************
// Data Structures
//*****************

struct Attenuation {
    float constant;
    float linear;
    float exponent;
};

struct Light_Info {
    vec3 albedo;
    Attenuation atten;
    vec3 position;
    vec3 direction;
    float range;
};

//*****************
// Frame Uniforms
//*****************

// Sort lights into ambient, directional, spot, point and store offsets in a vec4 such that:
//    0 .. < [0] = ambients
//  [0] .. < [1] = directionals
//  [1] .. < [2] = spots
//  [2] .. < [3] = points
// Don't branch on light type, all lights have the same info, just iterate array slices.
Light_Info lights[MAX_LIGHTS];
int lightOffsets[4];

/* View Information */
uniform vec3 eyePos;

//*****************
// Draw Uniforms
//*****************

/* Material Information */
float specularIntensity;
float specularExponent;

uniform sampler2D sampler;

//*****************
// Draw parameters
//*****************

in vec3 normal0;
in vec2 texCoord0;
in vec4 vertColor0;

in vec3 worldPos0;

out vec4 fragColor;

/**
 * Calculate the basic lighting effect.
 */
vec3 calculateLight (Light_Info light, vec3 direction, vec3 normal) {
    float diffuseF = dot(-direction, normal);
    vec3 diffuseCol = vec3(0, 0, 0);
    vec3 specCol = vec3(0, 0, 0);


    if (diffuseF > 0) {
        diffuseCol = light.albedo * diffuseF;

        vec3 dirToEye = normalize(eyePos - worldPos0);
        vec3 reflectDirection = normalize(reflect(-direction, normal));

        float specFactor = dot(dirToEye, reflectDirection);
        specFactor = pow(specFactor, specularExponent);

        if (specFactor > 0) {
            specCol = light.albedo * specularIntensity * specFactor;
        }
    }

    return diffuseCol + specCol;
}

vec3 calculateAmbientLight (Light_Info light) {
    return light.albedo;
}

/**
 * Calculate Directional Light color effect.
 */
vec3 calculateDirectionalLight (Light_Info light, vec3 normal) {
    return calculateLight(light, light.direction, normal);
}

/**
 * Calculate Point Light color effect.
 */
vec3 calculatePointLight (Light_Info light, vec3 normal) {
    vec3 lightDirection = worldPos0 - light.position;
    float distanceToPoint = length(lightDirection);

    if (distanceToPoint > light.range) {
        return vec3(0, 0, 0);
    }

    lightDirection = normalize(lightDirection);

    vec3 color = calculateLight(light, lightDirection, normal);

    float attenuation = light.atten.constant +
                        light.atten.linear * distanceToPoint +
                        light.atten.exponent * distanceToPoint * distanceToPoint +
                        0.0001;

    return color / attenuation;
}

vec4 calculateLightColor (vec3 normal) {
    vec3 lightColor = vec3(0, 0, 0);

    int k = 0, kMax;

    for (kMax = lightOffsets[0]; k < kMax; ++k) {
#if ENABLE_AMBIENT
        lightColor += calculateAmbientLight(lights[k]);
#endif
    }
    for (kMax = lightOffsets[1]; k < kMax; ++k) {
#if ENABLE_DIRECTIONAL
        lightColor += calculateDirectionalLight(lights[k], normal);
#endif
    }
    for (kMax = lightOffsets[2]; k < kMax; ++k) {
#if ENABLE_SPOT
#endif
    }
    for (kMax = lightOffsets[3]; k < kMax; ++k) {
#if ENABLE_POINT
        lightColor += calculatePointLight(lights[k], normal);
#endif
    }

    return vec4(lightColor, 1.0);
}

void main () {
    specularIntensity = 0.7;
    specularExponent = 0.8;

    lights[0] = Light_Info(vec3(0.05, 0.05, 0.2), Attenuation(1.0, 0.5, 0.2), vec3(0, 4, 0), vec3(0, -1, 0), 0.0);
    lights[1] = Light_Info(vec3(1.5, 1.5, 1.2), Attenuation(1.0, 0.5, 0.2), vec3(0, 4, 0), vec3(0, -1, 0), 0.0);
    lights[2] = Light_Info(vec3(0.3, 0.3, 0.5), Attenuation(1.0, 0.5, 0.2), vec3(0, -4, 0), vec3(0, 1, 0), 0.0);
    lights[3] = Light_Info(vec3(1.0, 1.0, 0.0), Attenuation(1, 1, 1), vec3(-3, 5, -5), vec3(0, 0, -1), 10.0);

    lightOffsets[0] = 1;
    lightOffsets[1] = 3;
    lightOffsets[2] = 3;
    lightOffsets[3] = 4;

    vec4 color = vertColor0;
    vec4 textureColor = texture(sampler, texCoord0);

    if (textureColor.a < 1.0) discard;

    vec3 normal = normalize(normal0);

    vec4 lightColor = calculateLightColor(normal);

    fragColor = color * textureColor * lightColor;
}
