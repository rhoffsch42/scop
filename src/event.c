/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:06:41 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:06:43 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static int		is_first_press(t_glfw *glfw, int key, t_gl_env *gl_e)
{
	int		val;

	if ((val = glfwGetKey(glfw->win, key)) == GLFW_PRESS \
		&& gl_e->boolens[key] == 0)
	{
		gl_e->boolens[key] = 1;
		return (1);
	}
	else if (val == GLFW_RELEASE)
	{
		gl_e->boolens[key] = 0;
		return (0);
	}
	return (0);
}

static void		events_one_press(t_glfw *glfw, t_gl_env *gl_e)
{
	if (is_first_press(glfw, GLFW_KEY_PAGE_DOWN, gl_e))
	{
		gl_e->obj_i = (gl_e->obj_i < gl_e->obj_len - 1) ? gl_e->obj_i + 1 : 0;
		gl_e->face_drawed = MAX_FACE;
	}
	if (is_first_press(glfw, GLFW_KEY_PAGE_UP, gl_e))
	{
		gl_e->obj_i = (gl_e->obj_i > 0) ? gl_e->obj_i - 1 : gl_e->obj_len - 1;
		gl_e->face_drawed = MAX_FACE;
	}
	if (is_first_press(glfw, GLFW_KEY_HOME, gl_e))
		gl_e->tex_i = (gl_e->tex_i < gl_e->xpm_len - 1) ? gl_e->tex_i + 1 : 0;
	if (is_first_press(glfw, GLFW_KEY_END, gl_e))
		gl_e->tex_i = (gl_e->tex_i != 0) ? gl_e->tex_i - 1 : gl_e->xpm_len - 1;
	if (is_first_press(glfw, GLFW_KEY_ENTER, gl_e))
	{
		gl_e->dismod = (gl_e->dismod < MODS - 1) ? gl_e->dismod + 1 : 0;
		glUniform1i(gl_e->display_mod, gl_e->dismod);
	}
	if (is_first_press(glfw, GLFW_KEY_SPACE, gl_e))
		gl_e->rotate = !gl_e->rotate;
}

static void		events_movements(t_glfw *glfw, t_gl_env *gl_e, t_fps *fps)
{
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_LEFT))
		gl_e->pos.x -= POS_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_RIGHT))
		gl_e->pos.x += POS_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_DOWN))
		gl_e->pos.y -= POS_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_UP))
		gl_e->pos.y += POS_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_1))
		gl_e->pos.z -= POS_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_0))
		gl_e->pos.z += POS_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_7))
		gl_e->rot.x += RAD_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_4))
		gl_e->rot.x -= RAD_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_8))
		gl_e->rot.y += RAD_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_5))
		gl_e->rot.y -= RAD_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_9))
		gl_e->rot.z += RAD_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_6))
		gl_e->rot.z -= RAD_DELTA * fps->tick;
}

static void		events_parameters(t_glfw *glfw, t_gl_env *gl_e, t_fps *fps)
{
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_P))
	{
		fps->fps = scale_d(fps->fps + 20 * fps->tick, 1, MAX_FPS);
		fps->tick = 1.0 / fps->fps;
		glfwSetWindowTitle(glfw->win, ft_itoa(fps->fps));
	}
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_L))
	{
		fps->fps = scale_d(fps->fps - 20 * fps->tick, 1, MAX_FPS);
		fps->tick = 1.0 / fps->fps;
		glfwSetWindowTitle(glfw->win, ft_itoa(fps->fps));
	}
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_SUBTRACT))
		gl_e->fov = (float)scale_d(gl_e->fov + 40 * fps->tick, 10, 120);
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_ADD))
		gl_e->fov = (float)scale_d(gl_e->fov - 40 * fps->tick, 10, 120);
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_1))
		gl_e->draw_mod = GL_POINTS;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_2))
		gl_e->draw_mod = MOD_LINE;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_3))
		gl_e->draw_mod = GL_TRIANGLES;
	if (gl_e->rotate)
		gl_e->rot.y += RAD_DELTA * fps->tick;
}

/*
**	glFrontFace(GL_CW); // GL_CCW for counter clock-wise
*/

void			events(t_glfw *glfw, t_gl_env *gl_e, t_fps *fps)
{
	int		val;

	if ((val = glfwGetKey(glfw->win, GLFW_KEY_C)) == GLFW_PRESS \
		&& !gl_e->boolens[GLFW_KEY_C])
	{
		gl_e->boolens[GLFW_KEY_C] = 1;
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	else if (val == GLFW_RELEASE)
	{
		gl_e->boolens[GLFW_KEY_C] = 0;
		glDisable(GL_CULL_FACE);
	}
	if (is_first_press(glfw, GLFW_KEY_EQUAL, gl_e))
		gl_e->face_drawed = (int)scale_d(gl_e->face_drawed + 1, 1, MAX_FACE);
	if (is_first_press(glfw, GLFW_KEY_MINUS, gl_e))
		gl_e->face_drawed = (int)scale_d(gl_e->face_drawed - 1, 1, MAX_FACE);
	if (is_first_press(glfw, GLFW_KEY_LEFT_BRACKET, gl_e))
		gl_e->face_drawed = 1;
	if (is_first_press(glfw, GLFW_KEY_RIGHT_BRACKET, gl_e))
		gl_e->face_drawed = MAX_FACE;
	events_one_press(glfw, gl_e);
	events_movements(glfw, gl_e, fps);
	events_parameters(glfw, gl_e, fps);
}
