#version 330

uniform mat4 mvp;

layout(location=0) in vec3 position;
layout(location=1) in vec2 texCoord;
layout(location=2) in vec3 normal;
layout(location=3) in vec4 color;

out vec2 tex_coord0;
out vec4 vertex_color0;

void main () {
    tex_coord0 = texCoord;
    vertex_color0 = color;
    gl_Position = mvp * vec4(position, 1.0);
}
