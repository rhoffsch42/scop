/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 18:38:52 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/27 21:33:39 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		is_first_press(t_glfw *glfw, int key, t_gl *gle)
{
	int		val;

	if ((val = glfwGetKey(glfw->win, key)) == GLFW_PRESS \
		&& gle->boolens[key] == 0)
	{
		gle->boolens[key] = 1;
		return (1);
	}
	else if (val == GLFW_RELEASE)
	{
		gle->boolens[key] = 0;
		return (0);
	}
	return (0);
}

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
	if (is_first_press(glfw, GLFW_KEY_T, gle))//marche pas
	{
		if ((obj->cyl_mapping = !obj->cyl_mapping) == 1)
		{
			glBindBuffer(GL_ARRAY_BUFFER, obj->vertex_texture_cylinder.vbo);
			glVertexAttribPointer(obj->vertex_texture_cylinder.slot, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, obj->vertex_texture.vbo);
			glVertexAttribPointer(obj->vertex_texture.slot, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		}
	}
	// if (is_first_press(glfw, GLFW_KEY_PAGE_DOWN, gle))
	// {
		// gle->obj_i = (gle->obj_i < gle->obj_len - 1) ? gle->obj_i + 1 : 0;
		// gle->face_drawed = gle->obj_face_amount;
	// }
	// if (is_first_press(glfw, GLFW_KEY_PAGE_UP, gle))
	// {
	// 	gle->obj_i = (gle->obj_i > 0) ? gle->obj_i - 1 : gle->obj_len - 1;
	// 	gle->face_drawed = gle->obj_face_amount;;
	// }
	if (is_first_press(glfw, GLFW_KEY_HOME, gle))
		obj->tex = (obj->tex + 1 <= gle->tex_max) ? obj->tex + 1 : 1;
	if (is_first_press(glfw, GLFW_KEY_END, gle))
		obj->tex = (obj->tex - 1 != 0) ? obj->tex - 1 : gle->tex_max;
	if (is_first_press(glfw, GLFW_KEY_ENTER, gle))
		obj->display_mod = (obj->display_mod < MODS - 1) ? obj->display_mod + 1 : 0;
	if (is_first_press(glfw, GLFW_KEY_SPACE, gle))
		obj->rotate = !obj->rotate;// faire la boucle sur les obj, pour rotate ceux qui ont le rotate a 1
}


void			events2(t_glfw *glfw, t_gl *gle, t_prog *prog)
{
	int					val;
	t_blueprint_obj3d	*obj;

	obj = &prog->blueprints[gle->obj_i].obj3d;
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
	// events_obj_movements(glfw, gle, fps);
	// events_parameters(glfw, gle, fps);
	// events_cam(glfw, gle, fps);
	// update_projection_matrix(gle);
	// update_model_matrix(gle);
}
