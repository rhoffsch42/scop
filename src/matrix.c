/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:08:13 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/24 16:57:14 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

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
	cam.forward.x = 0;
	cam.forward.y = 0;
	cam.forward.z = 1;
	cam.front = vector3_cross(cam.up, cam.right);
	return (cam);
}

static t_matrix4	view_matrix(void)
{
	t_cam		cam;
	t_matrix4	viewmatrix;
	t_vector3	res;

	cam = init_cam((t_vector3){DTOR(0), DTOR(0), DTOR(0)}, \
					(t_vector3){DTOR(0), DTOR(0), DTOR(0)});
	viewmatrix = matrix4(0, MATRIX_ROW_MAJOR);
	res = vector3_rotZYX(cam.right, cam.rot, ROT_WAY);
	viewmatrix.m.tab[0][0] = res.x;
	viewmatrix.m.tab[1][0] = res.y;
	viewmatrix.m.tab[2][0] = res.z;
	res = vector3_rotZYX(cam.up, cam.rot, ROT_WAY);
	viewmatrix.m.tab[0][1] = res.x;
	viewmatrix.m.tab[1][1] = res.y;
	viewmatrix.m.tab[2][1] = res.z;
	res = vector3_rotZYX(cam.forward, cam.rot, ROT_WAY);
	viewmatrix.m.tab[0][2] = res.x;
	viewmatrix.m.tab[1][2] = res.y;
	viewmatrix.m.tab[2][2] = res.z;
	viewmatrix.m.tab[0][3] = -cam.pos.x;
	viewmatrix.m.tab[1][3] = -cam.pos.y;
	viewmatrix.m.tab[2][3] = -cam.pos.z;
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

#define COS_A	val[0]
#define SIN_A	val[1]
#define COS_B	val[2]
#define SIN_B	val[3]
#define COS_C	val[4]
#define SIN_C	val[5]

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
	model.m.tab[0][0] = COS_B * COS_C;
	model.m.tab[1][0] = COS_B * SIN_C;
	model.m.tab[2][0] = -SIN_B;
	model.m.tab[0][1] = -SIN_C * COS_A + val[7] * COS_C;
	model.m.tab[1][1] = COS_A * COS_C + val[7] * SIN_C;
	model.m.tab[2][1] = SIN_A * COS_B;
	model.m.tab[0][2] = SIN_C * SIN_A + val[6] * COS_C;
	model.m.tab[1][2] = -COS_C * SIN_A + val[6] * SIN_C;
	model.m.tab[2][2] = COS_A * COS_B;
	model.m.tab[0][3] = gl_e->pos.x;
	model.m.tab[1][3] = gl_e->pos.y;
	model.m.tab[2][3] = gl_e->pos.z;
	model.m.tab[3][3] = 1;
	model = matrix4_set_order(model, !model.order);
	return (model);
}

void				load_matrix(t_gl_env *gl_e)
{
	gl_e->matrix_zero = matrix4(0, MATRIX_COLUMN_MAJOR);
	gl_e->model = model_matrix(gl_e, gl_e->matrix_zero);
	gl_e->view = view_matrix();
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
