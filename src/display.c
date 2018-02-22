/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:04:35 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/22 20:13:37 by rhoffsch         ###   ########.fr       */
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

static void		draw_frame(t_gl_env *gl_e, t_glfw *glfw)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, gl_e->tex_id[gl_e->tex_i]);
	// glBindVertexArray(gl_e->vao);
	if (gl_e->draw_mod == MOD_LINE)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, gl_e->face_drawed * 3);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(gl_e->draw_mod, 0, gl_e->face_drawed * 3);
	}
	// glBindVertexArray(0);

	glfwSwapBuffers(glfw->win);
}

void			display_object(t_glfw *glfw, t_objfile **objf, t_xpm **xpm, \
								int *len)
{
	t_gl_env	*gl_e;
	t_fps		*fps;

	startf("display_object");
	gl_e = init_gl_env(objf, xpm, len, glfw->cwd);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(-1.0f);
	glDepthFunc(GL_GREATER);
	gl_e->obj_i = 3;//42
	gl_e->obj_i = 0;//teapot
	create_program(gl_e, objf[gl_e->obj_i]->obj);
	gl_e->obj_face_amount = objf[gl_e->obj_i]->obj->f_amount;
	gl_e->face_drawed = (int)scale_d(gl_e->face_drawed, 1, gl_e->obj_face_amount);
	fps = init_t_fps();
	// skybox(gl_e);
	while (!glfwWindowShouldClose(glfw->win))
	{
		if (wait_for_next_frame(fps))
		{
			load_matrix(gl_e->gl_projection, gl_e);
			draw_frame(gl_e, glfw);
			glfwPollEvents();
			events(glfw, gl_e, fps);

		}
	}
}
