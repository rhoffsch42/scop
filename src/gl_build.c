/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:14 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/21 20:39:49 by rhoffsch         ###   ########.fr       */
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

static void		create_buffer(t_gl_env *gl_e, const GLchar *varname, int size, GLenum type, GLuint *vbo)
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
}

static void		update_data(t_gl_env *gl_e, t_obj *obj)
{
	float	points[obj->f_amount * 9];
	float	colors[obj->f_amount * 9];
	float	tex[obj->f_amount * 6];

	gl_e->data_points = (float*)ft_strnew(obj->f_amount * 9);
	gl_e->data_black_white = (float*)ft_strnew(obj->f_amount * 9);
	gl_e->data_texture = (float*)ft_strnew(obj->f_amount * 6);
	fill_points_array(points, obj->f);
	fill_color_array(colors, obj->f, (gl_e->dismod == 1) ? obj->mat : NULL);
	fill_tex_array(tex, obj->f, gl_e);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->vbo);
	gl_e->face_drawed = (int)scale_d(gl_e->face_drawed, 1, obj->f_amount);
	glBufferData(GL_ARRAY_BUFFER, gl_e->face_drawed * 9 * sizeof(float), \
				points, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, gl_e->face_drawed * 9 * sizeof(float), \
				colors, GL_STATIC_DRAW);
	if (gl_e->tex_id)
	{
		glBindBuffer(GL_ARRAY_BUFFER, gl_e->tex_vbo);
		glBufferData(GL_ARRAY_BUFFER, gl_e->face_drawed * 6 * sizeof(float), \
					tex, GL_STATIC_DRAW);
		glBindTexture(GL_TEXTURE_2D, gl_e->tex_id[gl_e->tex_i]);
	}
}

void			create_program(t_gl_env *gl_e, t_obj *obj)
{
	int		p;

	gl_e->vshader = init_shader(gl_e->shaders[0], GL_VERTEX_SHADER);
	gl_e->fshader = init_shader(gl_e->shaders[1], GL_FRAGMENT_SHADER);
	
	gl_e->shader_programme = glCreateProgram();
	glAttachShader(gl_e->shader_programme, gl_e->vshader);
	glAttachShader(gl_e->shader_programme, gl_e->fshader);
	glLinkProgram(gl_e->shader_programme);
	p = -1;
	glValidateProgram(gl_e->shader_programme);
	glGetProgramiv(gl_e->shader_programme, GL_LINK_STATUS, &p);
	(GL_TRUE != p) ? print_programme_info_log(gl_e->shader_programme) : (void)p;
	glUseProgram(gl_e->shader_programme);

	gl_e->display_mod = glGetUniformLocation(gl_e->shader_programme, "dismod");
	gl_e->projection = glGetUniformLocation(gl_e->shader_programme, "pro");

	glGenVertexArrays(1, &gl_e->vao);
	glBindVertexArray(gl_e->vao);
	glEnableVertexAttribArray(0);
	create_buffer(gl_e, "vertex_position", 3, GL_FLOAT, &gl_e->vbo);
	create_buffer(gl_e, "vertex_colour", 3, GL_FLOAT, &gl_e->colors_vbo);
	glEnable(GL_TEXTURE_2D);
	create_buffer(gl_e, "vertexUV", 2, GL_FLOAT, &gl_e->tex_vbo);

	// update_data(gl_e, obj);
}
