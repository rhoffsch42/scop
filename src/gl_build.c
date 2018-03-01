/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:14 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/28 18:16:23 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

// static void		fill_buffer(GLuint vbo, t_obj *obj, void (fill_func)(float*, t_face*), int size)//gl_build.c
// {
// 	float	points[obj->f_amount * size];
	
// 	fill_func(points, obj->f);
// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * size * sizeof(float), points, GL_STATIC_DRAW);
// }// si tout fonctionne, check avec cette fonction, remplacer le pave en dessous (load_data_obj3d)

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
	free((void*)gl_content);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE)
		gl_compile_error(shader, "shader compilation error:");
	return (shader);
}

t_prog			create_program(char *cwd, char *vshader_file, \
				char *fshader_file, void (get_slot_uniform)(t_prog*))
{
	t_prog		program;
	int			p;

	vshader_file = ft_strjoin(cwd, vshader_file);
	fshader_file = ft_strjoin(cwd, fshader_file);
	program.vshader = init_shader(vshader_file, GL_VERTEX_SHADER);
	program.fshader = init_shader(fshader_file, GL_FRAGMENT_SHADER);
	free(vshader_file);
	free(fshader_file);
	program.program = glCreateProgram();
	glAttachShader(program.program, program.vshader);
	glAttachShader(program.program, program.fshader);
	glLinkProgram(program.program);
	get_slot_uniform(&program);
	p = -1;
	glValidateProgram(program.program);
	glGetProgramiv(program.program, GL_LINK_STATUS, &p);
	if (p != GL_TRUE)
		print_programme_info_log(program.program);
	glUseProgram(program.program);
	return (program);
}
