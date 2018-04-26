/** Phong Lighting -- GLSL Vertex Shader */
#version 330

//*****************
// Draw Uniforms
//*****************
layout (std140) uniform MatrixBlock {
    mat4 model;
    mat4 view;
    mat4 mvp;
} matrices;

//*****************
// Draw parameters
//*****************
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 vertColor;

//*****************
// Vertex Outputs
//*****************
out vec3 worldPos0;
out vec2 texCoord0;
out vec3 normal0;
out vec4 vertColor0;

/**
 * Phong vertex shader
 */
void main () {
    worldPos0 = (matrices.model * vec4(position, 1.0)).xyz;
    normal0 = normalize(mat3(matrices.model) * normal);
    texCoord0 = texCoord;
    vertColor0 = vertColor;

    gl_Position = matrices.mvp * vec4(position, 1.0);
}
