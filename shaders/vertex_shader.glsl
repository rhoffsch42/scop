#version 410
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;
layout(location = 2) in vec2 vertexUV;

out vec2 UV;
out vec3 colour;

uniform int dismod;
uniform mat4 pro;

void main()
{
	colour = vertex_colour;
	gl_Position = pro * vec4(vertex_position, 1.0);
	UV = vertexUV;
}
