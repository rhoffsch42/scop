/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:14 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/25 17:42:56 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static GLuint	init_shader(char *filename, int type)
{
	GLint			ret;
	GLuint			shader;
	t_str			*content;
	const GLchar	*gl_content;

	content = ft_getfile(filename);
	gl_content = t_str_to_char(content);
	ft_free_list(content, free_t_str);
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &gl_content, NULL);
	free((void*)gl_content);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE)
		gl_compile_error(shader, "shader compilation error:");
	return (shader);
}

static int		create_buffer(t_gl_env *gl_e, const GLchar *varname, int size, GLenum type, GLuint *vbo)
{
	int		slot;

	if ((slot = glGetAttribLocation(gl_e->shader_programme, varname)) == -1)
	{
		glGetError();
		ft_errexit("glGetAttribLocation failed (-1)", RED, GL_ERROR);
	}
	printf("slot %d:\t%s\n", slot, varname);
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(slot, size, type, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(slot);
	return (slot);
}

static void		load_data(t_gl_env *gl_e, t_obj *obj)
{
	float	points[obj->f_amount * 9];
	float	colors[obj->f_amount * 9];
	float	tex[obj->f_amount * 6];
	float	tex_cylinder[obj->f_amount * 6];

	fill_points_array(points, obj->f);
	fill_color_array(colors, obj->f);
	fill_tex_array(tex, obj->f);
	fill_tex_cylinder_array(tex_cylinder, obj->f);
	
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float), points, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float), colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->tex_vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 6 * sizeof(float), tex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->tex_cylinder_vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 6 * sizeof(float), tex_cylinder, GL_STATIC_DRAW);
}

void			create_program(t_gl_env *gl_e, t_obj *obj)
{
	int			p;

	gl_e->vshader = init_shader(gl_e->shaders[0], GL_VERTEX_SHADER);
	gl_e->fshader = init_shader(gl_e->shaders[1], GL_FRAGMENT_SHADER);

	gl_e->shader_programme = glCreateProgram();
	glAttachShader(gl_e->shader_programme, gl_e->vshader);
	glAttachShader(gl_e->shader_programme, gl_e->fshader);
	glLinkProgram(gl_e->shader_programme);

	p = -1;
	glValidateProgram(gl_e->shader_programme);
	glGetProgramiv(gl_e->shader_programme, GL_LINK_STATUS, &p);
	(p != GL_TRUE) ? print_programme_info_log(gl_e->shader_programme) : (void)p;
	glUseProgram(gl_e->shader_programme);

	gl_e->gl_display_mod = glGetUniformLocation(gl_e->shader_programme, "dismod");
	gl_e->gl_m = glGetUniformLocation(gl_e->shader_programme, "M");
	gl_e->gl_v = glGetUniformLocation(gl_e->shader_programme, "V");
	gl_e->gl_p = glGetUniformLocation(gl_e->shader_programme, "P");
	gl_e->gl_plain_color = glGetUniformLocation(gl_e->shader_programme, "plain_color");
	if (obj->mat)
		glUniform3f(gl_e->gl_plain_color, obj->mat->kd[0], obj->mat->kd[1], obj->mat->kd[2]);
	else
		glUniform3f(gl_e->gl_plain_color, 1.0f, 0.0f, 0.3f);


	glGenVertexArrays(1, &gl_e->vao);
	glBindVertexArray((&gl_e->vao)[0]);//vao[x] pour object x ? => 1 program pour x objects similaires (ie skybox != teapot) 
	glEnableVertexAttribArray(0);//utile ?
	gl_e->vbo_slot = create_buffer(gl_e, "vertex_position", 3, GL_FLOAT, &gl_e->vbo);
	gl_e->colors_slot = create_buffer(gl_e, "vertex_colour", 3, GL_FLOAT, &gl_e->colors_vbo);
	glEnable(GL_TEXTURE_2D);
	gl_e->tex_slot = create_buffer(gl_e, "vertexUV", 2, GL_FLOAT, &gl_e->tex_vbo);
	gl_e->tex_cylinder_slot = create_buffer(gl_e, "vertexUV", 2, GL_FLOAT, &gl_e->tex_cylinder_vbo);

	load_data(gl_e, obj);
	load_matrix(gl_e);
}
