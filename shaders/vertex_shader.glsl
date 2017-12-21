#version 410
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;
layout(location = 2) in vec2 vertexUV;

out vec2 UV;
out vec3 colour;

uniform int dismod;

void main()
{
	colour = vertex_colour;
	gl_Position = vec4(vertex_position, 1.0);
	UV = vertexUV;
}
