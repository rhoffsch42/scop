/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:14 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:07:18 by rhoffsch         ###   ########.fr       */
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

static void		create_buffer(GLuint *vbo, int slot, int size, GLenum type)
{
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glVertexAttribPointer(slot, size, type, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(slot);
}

void			create_program(t_gl_env *gl_e)
{
	int		params;

	glGenVertexArrays(1, &gl_e->vao);
	glBindVertexArray(gl_e->vao);
	glEnableVertexAttribArray(0);
	create_buffer(&(gl_e->vbo), 0, 3, GL_FLOAT);
	create_buffer(&(gl_e->colors_vbo), 1, 3, GL_FLOAT);
	glEnable(GL_TEXTURE_2D);
	create_buffer(&(gl_e->tex_vbo), 2, 2, GL_FLOAT);
	gl_e->vshader = init_shader(VSHADER_FILE, GL_VERTEX_SHADER);
	gl_e->fshader = init_shader(FSHADER_FILE, GL_FRAGMENT_SHADER);
	gl_e->shader_programme = glCreateProgram();
	glAttachShader(gl_e->shader_programme, gl_e->vshader);
	glAttachShader(gl_e->shader_programme, gl_e->fshader);
	glLinkProgram(gl_e->shader_programme);
	gl_e->display_mod = glGetUniformLocation(gl_e->shader_programme, "dismod");
	gl_e->projection = glGetUniformLocation(gl_e->shader_programme, "pro");
	params = -1;
	glGetProgramiv(gl_e->shader_programme, GL_LINK_STATUS, &params);
	if (GL_TRUE != params)
		print_programme_info_log(gl_e->shader_programme);
	// glDeleteVertexArrays(1, &gl_e->vao);
	// glDeleteProgram(gl_e->shader_programme);
}
