/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:06:41 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/25 16:46:23 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static void		print_cam_pp(t_gl_env *gl_e)
{
	printf("Left mouse is being PRESSed\n");
	printf("Mouse:\t%d:%d\n", (int)gl_e->mouse_y, (int)gl_e->mouse_x);
	printf("fov : %.2f\n", gl_e->fov);
	printf("pos    \t");
	vector3_print(gl_e->cam.pos);
	printf("rot    \t");
	vector3_print(gl_e->cam.rot);
	printf("right  \t");
	vector3_print(gl_e->cam.right);
	printf("up     \t");
	vector3_print(gl_e->cam.up);
	printf("forward\t");
	vector3_print(gl_e->cam.forward);
	printf("--------------------------------\n");
}

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

static void		update_model_matrix(t_gl_env *gl_e)
{
	gl_e->model = model_matrix(gl_e, gl_e->matrix_zero);
	glUniformMatrix4fv(gl_e->gl_m, 1, GL_FALSE, gl_e->model.m.e);
	print_mvp_matrix(gl_e);
}

static void		update_projection_matrix(t_gl_env *gl_e)
{
	float	ratio;

	ratio = 1.0f / tanf(DTOR(gl_e->fov) / 2.0f);
	gl_e->projection.m.tab[0][0] = ratio / (DEF_WIN_X / DEF_WIN_Y);
	gl_e->projection.m.tab[1][1] = ratio;
	glUniformMatrix4fv(gl_e->gl_p, 1, GL_FALSE, gl_e->projection.m.e);
	print_mvp_matrix(gl_e);
}

static void		events_cam(t_glfw *glfw, t_gl_env *gl_e, t_fps *fps)
{
	int		state;
	float		diffx;
	float		diffy;

	glfwGetCursorPos(glfw->win, &gl_e->mouse_x, &gl_e->mouse_y);
	diffy = gl_e->mouse_origin_y - gl_e->mouse_y; 
	diffx = gl_e->mouse_origin_x - gl_e->mouse_x; 
	gl_e->cam.rot.y = -DTOR(diffx * 360.0f / SENSIBILITY);// diffx pour l'axe Y !
	if (ROT_X)
		gl_e->cam.rot.x = diffy * 360.0f / SENSIBILITY;// diffy pour l'axe X !
	gl_e->cam.rot.x = -DTOR(scale_d(gl_e->cam.rot.x, -90.0, 90.0));
	update_cam_vector(&gl_e->cam);
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_W))
		gl_e->cam.pos = vector3_add(gl_e->cam.pos, vector3_mult_coef(gl_e->cam.forward, POS_DELTA * fps->tick));
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_S))
		gl_e->cam.pos = vector3_sub(gl_e->cam.pos, vector3_mult_coef(gl_e->cam.forward, POS_DELTA * fps->tick));
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_A))
		gl_e->cam.pos = vector3_sub(gl_e->cam.pos, vector3_mult_coef(gl_e->cam.right, POS_DELTA * fps->tick));
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_D))
		gl_e->cam.pos = vector3_add(gl_e->cam.pos, vector3_mult_coef(gl_e->cam.right, POS_DELTA * fps->tick));
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_F))
		gl_e->cam.pos = vector3_sub(gl_e->cam.pos, vector3_mult_coef(gl_e->cam.up, POS_DELTA * fps->tick));
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_R))
		gl_e->cam.pos = vector3_add(gl_e->cam.pos, vector3_mult_coef(gl_e->cam.up, POS_DELTA * fps->tick));

	gl_e->view = view_matrix(gl_e, gl_e->matrix_zero);
	glUniformMatrix4fv(gl_e->gl_v, 1, GL_FALSE, gl_e->view.m.e);

	state = glfwGetMouseButton(glfw->win, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS)
		print_cam_pp(gl_e);
}

static void		events_parameters(t_glfw *glfw, t_gl_env *gl_e, t_fps *fps)
{
	char *fps_char;

	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_P))
	{
		fps->fps = scale_d(fps->fps + 20 * fps->tick, 1, MAX_FPS);
		fps->tick = 1.0 / fps->fps;
		fps_char = ft_itoa(fps->fps);
		glfwSetWindowTitle(glfw->win, fps_char);
		free(fps_char);
	}
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_L))
	{
		fps->fps = scale_d(fps->fps - 20 * fps->tick, 1, MAX_FPS);
		fps->tick = 1.0 / fps->fps;
		fps_char = ft_itoa(fps->fps);
		glfwSetWindowTitle(glfw->win, ft_itoa(fps->fps));
		free(fps_char);
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
}

static void		events_obj_movements(t_glfw *glfw, t_gl_env *gl_e, t_fps *fps)
{
	if (gl_e->rotate)
		gl_e->rot.y += RAD_DELTA * fps->tick;
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

static void		events_one_press(t_glfw *glfw, t_gl_env *gl_e)
{
	if (is_first_press(glfw, GLFW_KEY_PAGE_DOWN, gl_e))
	{
		gl_e->obj_i = (gl_e->obj_i < gl_e->obj_len - 1) ? gl_e->obj_i + 1 : 0;
		gl_e->face_drawed = gl_e->obj_face_amount;
	}
	if (is_first_press(glfw, GLFW_KEY_PAGE_UP, gl_e))
	{
		gl_e->obj_i = (gl_e->obj_i > 0) ? gl_e->obj_i - 1 : gl_e->obj_len - 1;
		gl_e->face_drawed = gl_e->obj_face_amount;;
	}
	if (is_first_press(glfw, GLFW_KEY_HOME, gl_e))
		gl_e->tex_i = (gl_e->tex_i < gl_e->xpm_len - 1) ? gl_e->tex_i + 1 : 0;
	if (is_first_press(glfw, GLFW_KEY_END, gl_e))
		gl_e->tex_i = (gl_e->tex_i != 0) ? gl_e->tex_i - 1 : gl_e->xpm_len - 1;
	if (is_first_press(glfw, GLFW_KEY_ENTER, gl_e))
	{
		gl_e->dismod = (gl_e->dismod < MODS - 1) ? gl_e->dismod + 1 : 0;
		glUniform1i(gl_e->gl_display_mod, gl_e->dismod);
	}
	if (is_first_press(glfw, GLFW_KEY_SPACE, gl_e))
		gl_e->rotate = !gl_e->rotate;
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
		gl_e->face_drawed = (int)scale_d(gl_e->face_drawed + 1, 1, gl_e->obj_face_amount);
	if (is_first_press(glfw, GLFW_KEY_MINUS, gl_e))
		gl_e->face_drawed = (int)scale_d(gl_e->face_drawed - 1, 1, gl_e->obj_face_amount);
	if (is_first_press(glfw, GLFW_KEY_LEFT_BRACKET, gl_e))
		gl_e->face_drawed = 1;
	if (is_first_press(glfw, GLFW_KEY_RIGHT_BRACKET, gl_e))
		gl_e->face_drawed = gl_e->obj_face_amount;;
	if (is_first_press(glfw, GLFW_KEY_T, gl_e))
	{
		if ((gl_e->texture_mod = !gl_e->texture_mod))
		{
			glBindBuffer(GL_ARRAY_BUFFER, gl_e->tex_vbo);
			glVertexAttribPointer(gl_e->tex_slot, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, gl_e->tex_cylinder_vbo);
			glVertexAttribPointer(gl_e->tex_cylinder_slot, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		}
	}
	events_one_press(glfw, gl_e);
	events_obj_movements(glfw, gl_e, fps);
	events_parameters(glfw, gl_e, fps);
	events_cam(glfw, gl_e, fps);
	update_projection_matrix(gl_e);
	update_model_matrix(gl_e);
}
