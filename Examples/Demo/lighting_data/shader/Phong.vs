// VERTEX SHADER - Phong Lighting
#version 330

// Frame Uniforms.

uniform mat4 mvp;
uniform mat4 view;
uniform mat4 model;

// Draw Inputs.

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec4 vertColor;

// Vertex outputs

out vec3 worldPos0;
out vec2 texCoord0;
out vec3 normal0;
out vec4 vertColor0;

void main () {
    worldPos0 = (model * vec4(position, 1.0)).xyz;
    normal0 = normal; //normalize(inverse(mat3(model)) * normal);
    texCoord0 = texCoord;
    vertColor0 = vertColor;

    gl_Position = mvp * vec4(position, 1.0);
}
