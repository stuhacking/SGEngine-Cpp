// Debug Shader for drawing colored lines.
#version 330

uniform mat4 mvp;

layout(location=0) in vec3 position;
layout(location=1) in vec4 color;

out vec4 vertex_color0;

void main () {
    vertex_color0 = color;
    gl_Position = mvp * vec4(position, 1.0);
}
