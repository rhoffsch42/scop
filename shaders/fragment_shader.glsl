#version 410
/*texture mod*/
in vec2 UV;
out vec4 color;
uniform sampler2D myTextureSampler;

/*color mod*/
in vec3 colour;
uniform int dismod;
uniform vec3 plain_color;
uniform float tex_coef;

void main()
{
	if (dismod == 0)
		color = (1.0 - tex_coef) * vec4(colour, 1.0) + tex_coef * texture(myTextureSampler, UV);
	else
		color = (1.0 - tex_coef) * vec4(plain_color, 1.0) + tex_coef * texture(myTextureSampler, UV);;
}
