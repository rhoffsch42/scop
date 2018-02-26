#version 410
in vec3 vertex_position;
in vec3 vertex_colour;
in vec2 vertexUV;

out vec2 UV;
out vec3 colour;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
	colour = vertex_colour;
	gl_Position = P * V * M * vec4(vertex_position, 1.0);
	UV = vertexUV;
}
