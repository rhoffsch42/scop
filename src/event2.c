/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 09:00:42 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/10 13:51:49 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		wait_for_next_frame(t_fps *fps)
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

int		is_first_press(t_glfw *glfw, int key, t_gl *gle)
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

void	update_texture(t_glfw *glfw, t_gl *gle, t_blueprint *blueprints)
{
	int					i;
	t_blueprint_obj3d	*obj;

	obj = &blueprints[gle->obj_i].obj3d;
	if (is_first_press(glfw, GLFW_KEY_T, gle))
		obj->show_texture = !obj->show_texture;
	i = 0;
	while (i < gle->obj_max)
	{
		obj = &blueprints[i].obj3d;
		if (obj->show_texture && obj->tex_coef < 1.0f)
			obj->tex_coef = scale_d(obj->tex_coef + 1 * gle->fps.tick, 0, 1);
		else if (!obj->show_texture && obj->tex_coef > 0.0f)
			obj->tex_coef = scale_d(obj->tex_coef - 1 * gle->fps.tick, 0, 1);
		i++;
	}
}
