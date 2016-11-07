// Debug Fragment shader for drawing colored lines.
#version 330

in vec4 vertex_color0;

out vec4 final_color;

void main () {
    final_color = vertex_color0;
}
