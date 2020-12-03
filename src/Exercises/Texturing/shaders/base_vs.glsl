#version 410

layout(location=0) in  vec4 a_vertex_position;
layout(location=1) in vec2 a_vertex_color;
layout(std140) uniform Matrices {
    mat4 pvm;
};

out vec2 texture_coords;

void main() {
    gl_Position = pvm * a_vertex_position;
    texture_coords = a_vertex_color;
}