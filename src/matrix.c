/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:08:13 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/28 22:29:25 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void				print_mvp_matrix(t_gl *gle, t_blueprint_obj3d *obj)
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

void				update_cam_vector(t_cam *cam)
{
	t_vector3	right = {1.0f, 0.0f, 0.0f};
	t_vector3	up = {0.0f, 1.0f, 0.0f};

	cam->right = vector3_rot(right, cam->rot, -ROT_WAY);
	cam->up = vector3_rot(up, cam->rot, -ROT_WAY);
	cam->forward = vector3_cross(cam->up, cam->right);
}

t_matrix4	view_matrix(t_cam *cam, t_matrix4 viewmatrix)
{
	t_vector3	res;
	float		val[8];

	COS_A = cosf(cam->rot.x);
	SIN_A = sinf(cam->rot.x);
	COS_B = cosf(cam->rot.y);
	SIN_B = sinf(cam->rot.y);
	COS_C = cosf(cam->rot.z);
	SIN_C = sinf(cam->rot.z);
	val[6] = COS_A * SIN_B;
	val[7] = SIN_A * SIN_B;
	viewmatrix.m.tab[0][0] = COS_B * COS_C;
	viewmatrix.m.tab[1][0] = val[7] * COS_C + COS_A * SIN_C;
	viewmatrix.m.tab[2][0] = -val[6] * COS_C + SIN_A * SIN_C;
	viewmatrix.m.tab[0][1] = -COS_B * SIN_C;
	viewmatrix.m.tab[1][1] = -val[7] * SIN_C + COS_A * COS_C;
	viewmatrix.m.tab[2][1] = val[6] * SIN_C + SIN_A * COS_C;
	viewmatrix.m.tab[0][2] = SIN_B;
	viewmatrix.m.tab[1][2] = -SIN_A * COS_B;
	viewmatrix.m.tab[2][2] = COS_A * COS_B;
	res = vector3_rot(cam->pos, cam->rot, ROT_WAY);
	viewmatrix.m.tab[0][3] = -res.x;
	viewmatrix.m.tab[1][3] = -res.y;
	viewmatrix.m.tab[2][3] = -res.z;
	viewmatrix.m.tab[3][3] = 1;
	viewmatrix = matrix4_set_order(viewmatrix, !viewmatrix.order);
	return (viewmatrix);
}

t_matrix4	pro_matrix(float rad, float far, float near)
{
	t_matrix4	promatrix;
	float		ratio;

	ratio = 1.0f / tanf(rad / 2.0f);
	promatrix = matrix4(0, MATRIX_ROW_MAJOR);
	promatrix.m.tab[0][0] = ratio / (DEF_WIN_X / DEF_WIN_Y);
	promatrix.m.tab[1][1] = ratio;
	promatrix.m.tab[2][2] = -(far + near) / (far - near);
	promatrix.m.tab[2][3] = -2.0f * far * near / (far - near);
	promatrix.m.tab[3][2] = -1.0f;
	promatrix = matrix4_set_order(promatrix, !promatrix.order);
	return (promatrix);
}

t_matrix4	model_matrix(t_vector3 pos, t_vector3 rot, t_matrix4 model)
{
	float		val[8];

	val[0] = cosf(rot.x);
	val[1] = sinf(rot.x);
	val[2] = cosf(rot.y);
	val[3] = sinf(rot.y);
	val[4] = cosf(rot.z);
	val[5] = sinf(rot.z);
	val[6] = COS_A * SIN_B;
	val[7] = SIN_A * SIN_B;
	val[6] = COS_A * SIN_B;
	val[7] = SIN_A * SIN_B;
	model.m.tab[0][0] = COS_B * COS_C;
	model.m.tab[1][0] = val[7] * COS_C + COS_A * SIN_C;
	model.m.tab[2][0] = -val[6] * COS_C + SIN_A * SIN_C;
	model.m.tab[0][1] = -COS_B * SIN_C;
	model.m.tab[1][1] = -val[7] * SIN_C + COS_A * COS_C;
	model.m.tab[2][1] = val[6] * SIN_C + SIN_A * COS_C;
	model.m.tab[0][2] = SIN_B;
	model.m.tab[1][2] = -SIN_A * COS_B;
	model.m.tab[2][2] = COS_A * COS_B;
	model.m.tab[0][3] = pos.x;
	model.m.tab[1][3] = pos.y;
	model.m.tab[2][3] = pos.z;
	model.m.tab[3][3] = 1;
	model = matrix4_set_order(model, !model.order);
	return (model);
}
