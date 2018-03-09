/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 23:06:50 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/07 08:50:17 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		print_mvp_matrix2(t_gl *gle, t_blueprint_obj3d *obj)
{
	if (DATA && DATA_MATRIX)
	{
		printf("Current object Model Matrix:\n");
		matrix4_print(obj->model_matrix);
		printf("View Matrix:\n");
		matrix4_print(gle->view);
		printf("Projection Matrix:\n");
		matrix4_print(gle->projection);
		printf("Current object Properties:\n");
		vector3_print(obj->pos);
		vector3_print(obj->rot);
		printf("================\n");
	}
}

void		print_cam_properties(t_gl *gle)
{
	printf("Left mouse is being PRESSed\n");
	printf("Mouse:\t%d:%d\n", (int)gle->mouse_y, (int)gle->mouse_x);
	printf("fov : %.2f\n", gle->fov);
	printf("pos    \t");
	vector3_print(gle->cam.pos);
	printf("rot    \t");
	vector3_print(gle->cam.rot);
	printf("right  \t");
	vector3_print(gle->cam.right);
	printf("up     \t");
	vector3_print(gle->cam.up);
	printf("forward\t");
	vector3_print(gle->cam.forward);
	printf("--------------------------------\n");
}

void		update_matrices(t_gl *gle, t_blueprint *blueprints)
{
	int					i;
	float				ratio;
	t_blueprint_obj3d	*obj;

	i = 0;
	while (i < gle->obj_max)
	{
		obj = &blueprints[i].obj3d;
		if (obj->rotate)
			obj->rot.y += RAD_DELTA * gle->fps.tick;
		obj->model_matrix = model_matrix(obj->pos, obj->rot, gle->matrix_zero);
		i++;
	}
	ratio = 1.0f / tanf(DTOR(gle->fov) / 2.0f);
	gle->projection.m.tab[0][0] = ratio / (DEF_WIN_X / DEF_WIN_Y);
	gle->projection.m.tab[1][1] = ratio;
	gle->view = view_matrix(&gle->cam, gle->identity);
}
