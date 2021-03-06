/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 18:38:52 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/10 13:49:10 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		events_one_press(t_glfw *glfw, t_gl *gle, t_prog *prog)
{
	t_blueprint_obj3d	*obj;

	obj = &prog->blueprints[gle->obj_i].obj3d;
	if (is_first_press(glfw, GLFW_KEY_EQUAL, gle))
		obj->current_faces = scale_d(obj->current_faces + 1, 1, obj->max_faces);
	if (is_first_press(glfw, GLFW_KEY_MINUS, gle))
		obj->current_faces = scale_d(obj->current_faces - 1, 1, obj->max_faces);
	if (is_first_press(glfw, GLFW_KEY_LEFT_BRACKET, gle))
		obj->current_faces = 1;
	if (is_first_press(glfw, GLFW_KEY_RIGHT_BRACKET, gle))
		obj->current_faces = obj->max_faces;
	if (is_first_press(glfw, GLFW_KEY_Y, gle))
		obj->cyl_mapping = !obj->cyl_mapping;
	if (is_first_press(glfw, GLFW_KEY_PAGE_DOWN, gle))
		gle->obj_i = (gle->obj_i + 1) % gle->obj_max;
	if (is_first_press(glfw, GLFW_KEY_PAGE_UP, gle))
		gle->obj_i = (gle->obj_i - 1 + gle->obj_max) % gle->obj_max;
	if (is_first_press(glfw, GLFW_KEY_HOME, gle))
		obj->tex = (obj->tex + 1 <= gle->tex_max) ? obj->tex + 1 : 1;
	if (is_first_press(glfw, GLFW_KEY_END, gle))
		obj->tex = (obj->tex - 1 != 0) ? obj->tex - 1 : gle->tex_max;
	if (is_first_press(glfw, GLFW_KEY_ENTER, gle))
		obj->display_mod = (obj->display_mod + 1) % MODS;
	if (is_first_press(glfw, GLFW_KEY_SPACE, gle))
		obj->rotate = !obj->rotate;
}

static void		events_obj_movements(t_glfw *glfw, t_fps *fps, \
									t_blueprint_obj3d *obj)
{
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_LEFT))
		obj->pos.x -= POS_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_RIGHT))
		obj->pos.x += POS_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_DOWN))
		obj->pos.y -= POS_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_UP))
		obj->pos.y += POS_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_1))
		obj->pos.z -= POS_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_0))
		obj->pos.z += POS_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_7))
		obj->rot.x += RAD_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_4))
		obj->rot.x -= RAD_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_8))
		obj->rot.y += RAD_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_5))
		obj->rot.y -= RAD_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_9))
		obj->rot.z += RAD_DELTA * fps->tick;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_6))
		obj->rot.z -= RAD_DELTA * fps->tick;
}

static void		events_parameters(t_glfw *glfw, t_gl *gle, \
								t_blueprint_obj3d *obj)
{
	char		*fps_char;

	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_P))
		gle->fps.fps = scale_d(gle->fps.fps + 20 * gle->fps.tick, 1, MAX_FPS);
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_L))
		gle->fps.fps = scale_d(gle->fps.fps - 20 * gle->fps.tick, 1, MAX_FPS);
	if (gle->fps.old_fps != gle->fps.fps)
	{
		gle->fps.old_fps = gle->fps.fps;
		gle->fps.tick = 1.0 / gle->fps.fps;
		fps_char = ft_itoa(gle->fps.fps);
		glfwSetWindowTitle(glfw->win, fps_char);
		free(fps_char);
	}
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_SUBTRACT))
		gle->fov = (float)scale_d(gle->fov + 40 * gle->fps.tick, 10, MAX_FOV);
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_ADD))
		gle->fov = (float)scale_d(gle->fov - 40 * gle->fps.tick, 10, MAX_FOV);
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_1))
		obj->draw_mod = GL_POINTS;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_2))
		obj->draw_mod = MOD_LINE;
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_3))
		obj->draw_mod = GL_TRIANGLES;
}

static void		events_cam(t_glfw *glfw, t_gl *gle)
{
	float		diff[2];
	t_vector3	mvt[3];

	glfwGetCursorPos(glfw->win, &gle->mouse_x, &gle->mouse_y);
	diff[1] = gle->mouse_origin_y - gle->mouse_y;
	diff[0] = gle->mouse_origin_x - gle->mouse_x;
	gle->cam.rot.y = -DTOR(diff[0] * 360.0f / SENSIBILITY);
	gle->cam.rot.x = diff[1] * 360.0f / SENSIBILITY;
	gle->cam.rot.x = -DTOR(scale_d(gle->cam.rot.x, -90.0, 90.0));
	update_cam_vector(&gle->cam);
	mvt[0] = vector3_mult_coef(gle->cam.forward, POS_DELTA * gle->fps.tick);
	mvt[1] = vector3_mult_coef(gle->cam.right, POS_DELTA * gle->fps.tick);
	mvt[2] = vector3_mult_coef(gle->cam.up, POS_DELTA * gle->fps.tick);
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_W))
		gle->cam.pos = vector3_add(gle->cam.pos, mvt[0]);
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_S))
		gle->cam.pos = vector3_sub(gle->cam.pos, mvt[0]);
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_A))
		gle->cam.pos = vector3_sub(gle->cam.pos, mvt[1]);
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_D))
		gle->cam.pos = vector3_add(gle->cam.pos, mvt[1]);
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_F))
		gle->cam.pos = vector3_sub(gle->cam.pos, mvt[2]);
	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_R))
		gle->cam.pos = vector3_add(gle->cam.pos, mvt[2]);
}

void			events(t_glfw *glfw, t_gl *gle, t_prog *prog)
{
	int					val;

	if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_ESCAPE))
		exit(0);
	if ((val = glfwGetKey(glfw->win, GLFW_KEY_C)) == GLFW_PRESS \
		&& !gle->boolens[GLFW_KEY_C])
	{
		gle->boolens[GLFW_KEY_C] = 1;
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	else if (val == GLFW_RELEASE)
	{
		gle->boolens[GLFW_KEY_C] = 0;
		glDisable(GL_CULL_FACE);
	}
	events_one_press(glfw, gle, prog);
	events_obj_movements(glfw, &gle->fps, &prog->blueprints[gle->obj_i].obj3d);
	events_parameters(glfw, gle, &prog->blueprints[gle->obj_i].obj3d);
	events_cam(glfw, gle);
	update_texture(glfw, gle, prog->blueprints);
	update_matrices(gle, prog->blueprints);
	if (GLFW_PRESS == glfwGetMouseButton(glfw->win, GLFW_MOUSE_BUTTON_LEFT))
		print_cam_properties(gle);
}
