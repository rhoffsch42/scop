/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:08:13 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/25 16:38:00 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#define COS_A	val[0]
#define SIN_A	val[1]
#define COS_B	val[2]
#define SIN_B	val[3]
#define COS_C	val[4]
#define SIN_C	val[5]

void				update_cam_vector(t_cam *cam)
{
	t_vector3	right = {1.0f, 0.0f, 0.0f};
	t_vector3	up = {0.0f, 1.0f, 0.0f};

	cam->right = vector3_rot(right, cam->rot, -ROT_WAY);
	cam->up = vector3_rot(up, cam->rot, -ROT_WAY);
	cam->forward = vector3_cross(cam->up, cam->right);
}

static t_cam		init_cam(t_vector3 pos, t_vector3 rot)
{
	t_cam	cam;

	cam.pos = pos;
	cam.rot = rot;
	cam.right.x = 1;
	cam.right.y = 0;
	cam.right.z = 0;
	cam.up.x = 0;
	cam.up.y = 1;
	cam.up.z = 0;
	update_cam_vector(&cam);
	return (cam);
}

t_matrix4	view_matrix(t_gl_env *gl_e, t_matrix4 viewmatrix)
{
	t_vector3	res;
	float		val[8];

	COS_A = cosf(gl_e->cam.rot.x);
	SIN_A = sinf(gl_e->cam.rot.x);
	COS_B = cosf(gl_e->cam.rot.y);
	SIN_B = sinf(gl_e->cam.rot.y);
	COS_C = cosf(gl_e->cam.rot.z);
	SIN_C = sinf(gl_e->cam.rot.z);
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
	res = vector3_rot(gl_e->cam.pos, gl_e->cam.rot, ROT_WAY);
	viewmatrix.m.tab[0][3] = -res.x;
	viewmatrix.m.tab[1][3] = -res.y;
	viewmatrix.m.tab[2][3] = -res.z;
	viewmatrix.m.tab[3][3] = 1;
	viewmatrix = matrix4_set_order(viewmatrix, !viewmatrix.order);
	return (viewmatrix);
}

static t_matrix4	pro_matrix(float rad, float far, float near)
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

t_matrix4	model_matrix(t_gl_env *gl_e, t_matrix4 model)
{
	float		val[8];

	val[0] = cosf(gl_e->rot.x);
	val[1] = sinf(gl_e->rot.x);
	val[2] = cosf(gl_e->rot.y);
	val[3] = sinf(gl_e->rot.y);
	val[4] = cosf(gl_e->rot.z);
	val[5] = sinf(gl_e->rot.z);
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
	model.m.tab[0][3] = gl_e->pos.x;
	model.m.tab[1][3] = gl_e->pos.y;
	model.m.tab[2][3] = gl_e->pos.z;
	model.m.tab[3][3] = 1;
	model = matrix4_set_order(model, !model.order);
	return (model);
}

void				print_mvp_matrix(t_gl_env *gl_e)
{
	if (DATA && DATA_MATRIX)
	{
		printf("Model Matrix:\n");
		matrix4_print(gl_e->model);
		printf("View Matrix:\n");
		matrix4_print(gl_e->view);
		printf("Projection Matrix:\n");
		matrix4_print(gl_e->projection);
		vector3_print(gl_e->pos);
		vector3_print(gl_e->rot);
		printf("================\n");
	}
}

void				load_matrix(t_gl_env *gl_e)
{
	gl_e->cam = init_cam((t_vector3){0.0f, 0.0f, 5.0f}, \
						(t_vector3){DTOR(0), DTOR(0), DTOR(0)});
	gl_e->matrix_zero = matrix4(0, MATRIX_ROW_MAJOR);
	gl_e->model = model_matrix(gl_e, gl_e->matrix_zero);
	gl_e->view = view_matrix(gl_e, gl_e->matrix_zero);
	gl_e->projection = pro_matrix(DTOR(gl_e->fov), FAR, NEAR);
	if (DATA && DATA_MATRIX)
	{
		printf("Model Matrix:\n");
		matrix4_print(gl_e->model);
		printf("View Matrix:\n");
		matrix4_print(gl_e->view);
		printf("Projection Matrix:\n");
		matrix4_print(gl_e->projection);
	}
	glUniformMatrix4fv(gl_e->gl_m, 1, GL_FALSE, gl_e->model.m.e);
	glUniformMatrix4fv(gl_e->gl_v, 1, GL_FALSE, gl_e->view.m.e);
	glUniformMatrix4fv(gl_e->gl_p, 1, GL_FALSE, gl_e->projection.m.e);
}
