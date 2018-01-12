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

static int		wait_for_next_frame(t_fps *fps)
{
	fps->ellapsed_time = glfwGetTime() - fps->last_time;
	if (fps->ellapsed_time >= fps->tick)
	{
		fps->last_time += fps->ellapsed_time;
		fps->ellapsed_time = 0.0;
		return (1);
	}
	else
		return (0);
}

void			gl_compile_error(GLuint shader, char *intro)
{
	GLsizei		maxl;
	GLsizei		l;
	GLchar		*info;

	maxl = 1000;
	info = safe_malloc(1000);
	glGetShaderInfoLog(shader, maxl, &l, info);
	printf("%s\n%s\n", intro, info);
	ft_errexit(GL_COMPILE_SHADER, RED, GL_ERROR);
}

void			draw_glfour(t_obj *obj, t_gl_env *gl_e)
{
	float	points[obj->f_amount * 9];
	float	colors[obj->f_amount * 9];
	float	tex[obj->f_amount * 6];

	fill_points_array(points, obj->f, gl_e);
	fill_color_array(colors, obj->f);
	fill_tex_array(tex, obj->f);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->vbo);
	gl_e->face_drawed = (int)scale_d(gl_e->face_drawed, 1, obj->f_amount);
	glBufferData(GL_ARRAY_BUFFER, gl_e->face_drawed * 9 * sizeof(float), points, GL_STATIC_DRAW);
	// glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float),
	// points, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, gl_e->face_drawed * 9 * sizeof(float), colors, GL_STATIC_DRAW);
	// glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float),
	// colors, GL_STATIC_DRAW);
	if (gl_e->tex_id)
	{
		glBindBuffer(GL_ARRAY_BUFFER, gl_e->tex_vbo);
		glBufferData(GL_ARRAY_BUFFER, gl_e->face_drawed * 6 * sizeof(float), tex, GL_STATIC_DRAW);
		// glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 6 * sizeof(float),
		// tex, GL_STATIC_DRAW);
		glBindTexture(GL_TEXTURE_2D, gl_e->tex_id[gl_e->tex_i]);
	}
}

static void		draw_frame(t_objfile **objf, t_gl_env *gl_e, t_glfw *glfw)
{
	draw_glfour(objf[gl_e->obj_i]->obj, gl_e);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 51.0f / 255.0f, 102.0f / 255.0f, 1);
	glBindVertexArray(gl_e->vao);
	if (gl_e->draw_mod == MOD_LINE)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, objf[gl_e->obj_i]->obj->f_amount * 3);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(gl_e->draw_mod, 0, objf[gl_e->obj_i]->obj->f_amount * 3);
	}
	glBindVertexArray(0);
	glfwSwapBuffers(glfw->win);
}

void			display_object(t_glfw *glfw, t_objfile **objf, t_xpm **xpm, \
								int *len)
{
	t_gl_env	*gl_e;
	t_fps		*fps;

	startf("display_object");
	gl_e = init_gl_env(objf, xpm, len);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(-1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_GREATER);
	create_program(gl_e);
	glUseProgram(gl_e->shader_programme);
	fps = init_t_fps();
	gl_e->face_drawed = 1;
	while (!glfwWindowShouldClose(glfw->win))
	{
		if (wait_for_next_frame(fps))
		{
			load_matrix(gl_e->projection, gl_e->fov);
			draw_frame(objf, gl_e, glfw);
			glfwPollEvents();
			events(glfw, gl_e, fps);
		}
	}
}
