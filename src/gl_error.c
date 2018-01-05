/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:25 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:07:30 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

/*
**	5124	GL_INT
**	5126	GL_FLOAT
**	35664	GL_FLOAT_VEC2
**	35665	GL_FLOAT_VEC3
**	35666	GL_FLOAT_VEC4
**	35670	GL_BOOL
**	35674	GL_FLOAT_MAT2
**	35675	GL_FLOAT_MAT3
**	35676	GL_FLOAT_MAT4
**	35678	GL_SAMPLER_2D
**	35679	GL_SAMPLER_3D
**	35680	GL_SAMPLER_CUBE
**	35682	GL_SAMPLER_2D_SHADOW
*/

const char		*gl_type_to_string2(GLenum type)
{
	if (type == GL_SAMPLER_3D)
		return ("sampler3D");
	if (type == GL_SAMPLER_CUBE)
		return ("samplerCube");
	if (type == GL_SAMPLER_2D_SHADOW)
		return ("sampler2DShadow");
	return ("other");
}

const char		*gl_type_to_string(GLenum type)
{
	if (type == GL_BOOL)
		return ("bool");
	if (type == GL_INT)
		return ("int");
	if (type == GL_FLOAT)
		return ("float");
	if (type == GL_FLOAT_VEC2)
		return ("vec2");
	if (type == GL_FLOAT_VEC3)
		return ("vec3");
	if (type == GL_FLOAT_VEC4)
		return ("vec4");
	if (type == GL_FLOAT_MAT2)
		return ("mat2");
	if (type == GL_FLOAT_MAT3)
		return ("mat3");
	if (type == GL_FLOAT_MAT4)
		return ("mat4");
	if (type == GL_SAMPLER_2D)
		return ("sampler2D");
	return (gl_type_to_string2(type));
}

static t_logs	init_logs(void)
{
	t_logs	logs;

	logs.params = -1;
	logs.length = 64;
	logs.actual_length = 64;
	logs.size = 0;
	logs.i = -1;
	exit(0);
	return (logs);
}

static void		program_logs(GLuint programme, GLenum pname, \
							GLint (func)(GLuint, const GLchar *), char *msg)
{
	t_logs	l;

	l = init_logs();
	glGetProgramiv(programme, pname, &l.params);
	printf(msg, l.params);
	while (++l.i < l.params)
	{
		glGetActiveAttrib(programme, l.i, l.length, &l.actual_length, \
			&l.size, &l.type, l.name);
		l.j = -1;
		if (l.size > 1)
			while (++l.j < l.size)
			{
				sprintf(l.long_name, "%s[%i]", l.name, l.j);
				l.location = func(programme, l.long_name);
				printf(" %i) type:%s name:%s location:%i\n",
				l.i, gl_type_to_string(l.type), l.long_name, l.location);
			}
		else
		{
			l.location = func(programme, l.name);
			printf(" %i) type:%s name:%s location:%i\n",
			l.i, gl_type_to_string(l.type), l.name, l.location);
		}
	}
}

void			print_programme_info_log(GLuint programme)
{
	int		params;
	int		max_len;
	int		len;
	char	program_log[2048];

	params = -1;
	fprintf(stderr,
		"ERROR: could not link shader programme GL index %u\n", programme);
	printf("--------------------\nshader programme %i info:\n", programme);
	glGetProgramiv(programme, GL_LINK_STATUS, &params);
	printf("GL_LINK_STATUS = %i\n", params);
	glGetProgramiv(programme, GL_ATTACHED_SHADERS, &params);
	printf("GL_ATTACHED_SHADERS = %i\n", params);
	program_logs(programme, GL_ACTIVE_ATTRIBUTES, glGetAttribLocation, \
		"GL_ACTIVE_ATTRIBUTES = %i\n");
	program_logs(programme, GL_ACTIVE_UNIFORMS, glGetUniformLocation, \
		"GL_ACTIVE_UNIFORMS = %i\n");
	max_len = 2048;
	len = 0;
	glGetProgramInfoLog(programme, max_len, &len, program_log);
	printf("program info log for GL index %u:\n%s", programme, program_log);
	exit(GL_ERROR);
}
