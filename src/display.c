/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:04:35 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:04:48 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	gl_compile_error(GLuint shader, char *intro)
{
	GLsizei		maxl;
	GLsizei		l;
	GLchar		*info;

	maxl = 1000;
	info = safe_malloc(1000);
	glGetShaderInfoLog(shader, maxl, &l, info);
	(void)intro;
	printf("%s\n%s\n", intro, info);
	ft_errexit(GL_COMPILE_SHADER, RED, GL_ERROR);
}

void	draw_glfour(t_obj *obj, t_gl_env *gl_e)
{
	float	points[obj->f_amount * 9];
	float	colors[obj->f_amount * 9];
	float	tex[obj->f_amount * 6];

	fill_points_array(points, obj->f, gl_e);
	fill_color_array(colors, obj->f);
	fill_tex_array(tex, obj->f);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float), \
	points, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float), \
	colors, GL_STATIC_DRAW);
	if (gl_e->tex_id)//que faire si pas de texture ? voir les shaders glsl
	{
		glBindBuffer(GL_ARRAY_BUFFER, gl_e->tex_vbo);
		glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 6 * sizeof(float), \
		tex, GL_STATIC_DRAW);
		glBindTexture(GL_TEXTURE_2D, gl_e->tex_id[gl_e->tex_i]);
	}
}

void	display_object(t_glfw *glfw, t_objfile **objf, t_xpm **xpm, int *len)
{
	t_gl_env	*gl_e;
	char		*boolens;

	startf("display_object");
	boolens = (char*)safe_malloc(sizeof(char) * 348);
	ft_bzero(boolens, sizeof(char) * 348);
	gl_e = init_gl_env(objf, xpm, len);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(-1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_GREATER);
	create_program(gl_e);
	glUseProgram(gl_e->shader_programme);
	load_matrix(gl_e->projection);
	while (!glfwWindowShouldClose(glfw->win))
	{
		draw_glfour(objf[gl_e->obj_i]->obj, gl_e);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(gl_e->vao);
		glDrawArrays(GL_TRIANGLES, 0, objf[gl_e->obj_i]->obj->f_amount * 3);
		glBindVertexArray(0);
		glfwSwapBuffers(glfw->win);
		glfwPollEvents();
		events(glfw, gl_e, &boolens);
	}
	deep--;
}
