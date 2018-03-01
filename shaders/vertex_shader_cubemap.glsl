#version 410

in vec3 vertex_position;
uniform mat4 P;
uniform mat4 V;
out vec3 texcoords;

void main() {
  texcoords = vertex_position;
  gl_Position = P * V * vec4(vertex_position, 1.0);
}