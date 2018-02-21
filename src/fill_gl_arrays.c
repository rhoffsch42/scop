/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_gl_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:06:47 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/21 20:17:15 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		fill_color_array(float *arr, t_face *face, t_mat *mat)
{
	int			i;
	t_vector3	color;

	srand(1);
	i = 0;
	while (face)
	{
		color.x = (float)(rand() % 200) / 200.0f;
		color.y = color.x;
		color.z = color.x;
		if (mat)
			memcpy(&color, (void*)(mat->kd), 3 * sizeof(float));
		arr[i + 0] = color.x;
		arr[i + 1] = color.y;
		arr[i + 2] = color.z;
		arr[i + 3] = color.x;
		arr[i + 4] = color.y;
		arr[i + 5] = color.z;
		arr[i + 6] = color.x;
		arr[i + 7] = color.y;
		arr[i + 8] = color.z;
		i += 9;
		face = face->next;
	}
}

void		fill_tex_array(float *arr, t_face *face, t_gl_env *gl_e)
{
	int			i;
	float		scale;
	float		offset_y;

	scale = 0.75f;
	offset_y = -0.5f;
	i = 0;
	while (face)
	{
		arr[i + 0] = (face->v1->z) * scale;
		arr[i + 1] = (1 - face->v1->y) * scale + offset_y;
		arr[i + 2] = (face->v2->z) * scale;
		arr[i + 3] = (1 - face->v2->y) * scale + offset_y;
		arr[i + 4] = (face->v3->z) * scale;
		arr[i + 5] = (1 - face->v3->y) * scale + offset_y;
		if (gl_e->texture_mod)
		{
			arr[i + 0] = atan2f(face->v1->z, face->v1->x) / M_PI_2;
			arr[i + 2] = atan2f(face->v2->z, face->v2->x) / M_PI_2;
			arr[i + 4] = atan2f(face->v3->z, face->v3->x) / M_PI_2;
		}
		i += 6;
		face = face->next;
	}
}

void		fill_points_array(float *arr, t_face *face)
{
	int			i;

	i = 0;
	while (face)
	{
		arr[i + 0] = face->v1->x;
		arr[i + 1] = face->v1->y;
		arr[i + 2] = face->v1->z;
		arr[i + 3] = face->v2->x;
		arr[i + 4] = face->v2->y;
		arr[i + 5] = face->v2->z;
		arr[i + 6] = face->v3->x;
		arr[i + 7] = face->v3->y;
		arr[i + 8] = face->v3->z;
		i += 9;
		face = face->next;
	}
}
