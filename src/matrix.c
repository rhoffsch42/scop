/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:08:13 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:08:16 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

static t_cam		init_cam(float x, float y, float z)
{
	t_cam	cam;

	cam.pos.x = x;
	cam.pos.y = y;
	cam.pos.z = z;
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

	cam = init_cam(0, 0, 0);
	viewmatrix = matrix4(0, MATRIX_ROW_MAJOR);
	viewmatrix.m.tab[0][0] = cam.right.x;
	viewmatrix.m.tab[1][0] = cam.right.y;
	viewmatrix.m.tab[2][0] = cam.right.z;
	viewmatrix.m.tab[0][1] = cam.up.x;
	viewmatrix.m.tab[1][1] = cam.up.y;
	viewmatrix.m.tab[2][1] = cam.up.z;
	viewmatrix.m.tab[0][2] = cam.forward.x;
	viewmatrix.m.tab[1][2] = cam.forward.y;
	viewmatrix.m.tab[2][2] = cam.forward.z;
	viewmatrix.m.tab[0][3] = cam.pos.x;
	viewmatrix.m.tab[1][3] = cam.pos.y;
	viewmatrix.m.tab[2][3] = cam.pos.z;
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

void				load_matrix(GLuint projection, float fov)
{
	t_matrix4	promatrix;
	t_matrix4	viewmatrix;

	viewmatrix = view_matrix();
	promatrix = pro_matrix(DTOR(fov), FAR, NEAR);
	promatrix = matrix4_mult(promatrix, viewmatrix);
	if (DATA)
	{
		printf("Projection * View Matrix:\n");
		matrix4_print(promatrix);
	}
	glUniformMatrix4fv(projection, 1, GL_FALSE, promatrix.m.e);
}
