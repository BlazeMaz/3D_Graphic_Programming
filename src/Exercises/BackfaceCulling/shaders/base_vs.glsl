#version 410

layout(location=0) in  vec4 a_vertex_position;
layout(location=1) in vec3 a_vertex_color;

layout(std140) uniform Matrices {
    mat4 pvm;
};

out vec3 vertex_color;

void main() {
    gl_Position = pvm * a_vertex_position;
    vertex_color = a_vertex_color;
}