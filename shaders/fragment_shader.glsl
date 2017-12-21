#version 410
/*texture mod*/
in vec2 UV;
out vec4 color;
uniform sampler2D myTextureSampler;

/*color mod*/
in vec3 colour;

uniform int dismod;

void main()
{
	if (dismod == 0)
		color = texture(myTextureSampler, UV);
	else
		color = vec4(colour, 1.0);
}
