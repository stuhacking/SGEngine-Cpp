// Basic Fragment Shader.
#version 330

uniform sampler2D sampler;

in vec2 tex_coord0;
in vec4 vertex_color0;

out vec4 final_color;

void main () {
    final_color = texture(sampler, tex_coord0) * vertex_color0;
}
