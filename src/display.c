/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:04:35 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/27 19:40:39 by rhoffsch         ###   ########.fr       */
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

static void		draw_frame(t_gl_env *gl_e)
{
	glBindTexture(GL_TEXTURE_2D, gl_e->tex_id[gl_e->tex_i]);
	glBindVertexArray(gl_e->vao);
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

}

void			display_object(t_glfw *glfw, t_objfile **objf, t_xpm **xpm, \
								int *len)
{
	t_gl_env	*gl_e;
	t_fps		*fps;

	startf("display_object");
	gl_e = init_gl_env(objf, xpm, len, glfw->cwd);
	skybox(gl_e, objf[gl_e->obj_i]->obj);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(-1.0f);
	glDepthFunc(GL_GREATER);
	// gl_e->obj_i = 3;
	gl_e->obj_i = 0;
	create_program(gl_e, objf[gl_e->obj_i]->obj);
	gl_e->obj_face_amount = objf[gl_e->obj_i]->obj->f_amount;
	gl_e->face_drawed = (int)scale_d(gl_e->face_drawed, 1, gl_e->obj_face_amount);
	fps = init_t_fps();
	glfwGetCursorPos(glfw->win, &gl_e->mouse_origin_x, &gl_e->mouse_origin_y);
	printf("Origin mouse:\t%.2f:%.2f\n", gl_e->mouse_origin_y, gl_e->mouse_origin_x);
	while (!glfwWindowShouldClose(glfw->win))
	{
		if (wait_for_next_frame(fps))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.2f, 0.4f, 1.0f);

			if (1)
			{
			glDepthMask(GL_FALSE);
			glActiveTexture(GL_TEXTURE0);
			glUseProgram(gl_e->sky_programme);
			glBindTexture(GL_TEXTURE_CUBE_MAP, gl_e->sky_tex_id);
   			glBindVertexArray(gl_e->sky_vao);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawArrays(GL_TRIANGLES, 0, gl_e->obj_face_amount * 3);
            glDepthMask(GL_TRUE);
			}
			if (1)
			{
			glUseProgram(gl_e->shader_programme);
			draw_frame(gl_e);
			
			gl_e->pos.x -= 3;
			gl_e->model = model_matrix(gl_e, gl_e->matrix_zero);
			glUniformMatrix4fv(gl_e->gl_m, 1, GL_FALSE, gl_e->model.m.e);
			draw_frame(gl_e);
			gl_e->pos.x += 3;
			}
	
			glfwSwapBuffers(glfw->win);
			glfwPollEvents();
			events(glfw, gl_e, fps);
		}
	}
}
