#version 410
/*texture mod*/
in vec2 UV;
out vec4 color;
uniform sampler2D myTextureSampler;

/*color mod*/
in vec3 colour;
uniform int dismod;
uniform vec3 plain_color;

void main()
{
	if (dismod == 0)
		color = texture(myTextureSampler, UV);
	else if (dismod == 1)
		color = vec4(colour, 1.0);
	else
		color = vec4(plain_color, 1.0);
}
