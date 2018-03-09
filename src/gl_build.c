/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:14 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/08 14:43:46 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			fill_buffer(GLuint vbo, t_obj *obj, \
						void (fill_func)(float*, t_face*), int summit)
{
	float	points[obj->f_amount * summit * 3];

	fill_func(points, obj->f);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * summit * 3 * sizeof(float), \
			points, GL_STATIC_DRAW);
}

void			create_buffer(t_vbo *vertex_buffer, int size, GLenum type)
{
	glGenBuffers(1, &vertex_buffer->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->vbo);
	glVertexAttribPointer(vertex_buffer->slot, size, type, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vertex_buffer->slot);
}

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
	glCompileShader(shader);
	free((void*)gl_content);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE)
		gl_compile_error(shader, "shader compilation error:");
	return (shader);
}

void			create_program(t_prog *program, char *vshader_file, \
				char *fshader_file, void (get_slot_uniform)(t_prog*))
{
	int			p;

	program->vshader = init_shader(vshader_file, GL_VERTEX_SHADER);
	program->fshader = init_shader(fshader_file, GL_FRAGMENT_SHADER);
	program->program = glCreateProgram();
	glAttachShader(program->program, program->vshader);
	glAttachShader(program->program, program->fshader);
	glLinkProgram(program->program);
	get_slot_uniform(program);
	p = -1;
	glValidateProgram(program->program);
	glGetProgramiv(program->program, GL_LINK_STATUS, &p);
	if (p != GL_TRUE)
		print_programme_info_log(program->program);
}
