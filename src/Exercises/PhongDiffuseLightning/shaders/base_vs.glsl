#version 410

layout(location=0) in  vec4 a_vertex_position;
layout(location=1) in vec2 a_vertex_color;
layout(location=2) in  vec3 a_vertex_normal;
layout(std140) uniform Matrices {
    mat4 P;
    mat4 VM;
    mat3 N;
};

out vec2 texture_coords;
out vec3 vertex_normal_in_vs;
out vec3 vertex_position_in_vs;

void main() {
    gl_Position = P * VM * a_vertex_position;
    texture_coords = a_vertex_color;
    vertex_position_in_vs = (VM * a_vertex_position).xyz;
    vertex_normal_in_vs = normalize(N*a_vertex_normal);
}
