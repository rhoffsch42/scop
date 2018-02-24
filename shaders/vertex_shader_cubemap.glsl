#version 410

in vec3 vertex;
uniform mat4 P;
uniform mat4 V;
out vec3 texcoords;

void main() {
  // vec4 v1 = vec4(1.0f, 0.0f, 0.0f, 0.0f);
  // vec4 v2 = vec4(0.0f, 1.0f, 0.0f, 0.0f);
  // vec4 v3 = vec4(0.0f, 0.0f, 1.0f, 0.0f);
  // vec4 v4 = vec4(0.0f, 0.0f, 0.0f, 1.0f);
  // mat4 m4 = mat4(v1, v2, v3, v4);

  texcoords = vertex;
  gl_Position = P * V * vec4(vertex, 1.0);
  // gl_Position = m4 * vec4(vertex, 1.0);
}