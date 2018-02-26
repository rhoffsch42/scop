#version 410

in vec3 vertex;
uniform mat4 P;
uniform mat4 V;
out vec3 texcoords;

void main() {
  texcoords = vertex;
  gl_Position = P * V * vec4(vertex, 1.0);
}