/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_gl_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:06:47 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:09:39 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		fill_color_array(float *arr, t_face *face)
{
	int		i;
	float	color;

	srand(1);
	i = 0;
	while (face)
	{
		color = (float)(rand() % 200) / 200.0f;
		arr[i + 0] = color;
		arr[i + 1] = color;
		arr[i + 2] = color;
		arr[i + 3] = color;
		arr[i + 4] = color;
		arr[i + 5] = color;
		arr[i + 6] = color;
		arr[i + 7] = color;
		arr[i + 8] = color;
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

void		fill_points_array(float *arr, t_face *face, t_gl_env *gl_e)
{
	int			i;
	t_vector3	tmp;

	i = 0;
	while (face)
	{
		vertix_to_vector3(face->v1, &tmp);
		tmp = vector3_rot(tmp, gl_e->rot, ROT_WAY);
		arr[i + 0] = tmp.x * gl_e->scale + gl_e->pos.x;
		arr[i + 1] = tmp.y * gl_e->scale + gl_e->pos.y;
		arr[i + 2] = tmp.z * gl_e->scale + gl_e->pos.z;
		vertix_to_vector3(face->v2, &tmp);
		tmp = vector3_rot(tmp, gl_e->rot, ROT_WAY);
		arr[i + 3] = tmp.x * gl_e->scale + gl_e->pos.x;
		arr[i + 4] = tmp.y * gl_e->scale + gl_e->pos.y;
		arr[i + 5] = tmp.z * gl_e->scale + gl_e->pos.z;
		vertix_to_vector3(face->v3, &tmp);
		tmp = vector3_rot(tmp, gl_e->rot, ROT_WAY);
		arr[i + 6] = tmp.x * gl_e->scale + gl_e->pos.x;
		arr[i + 7] = tmp.y * gl_e->scale + gl_e->pos.y;
		arr[i + 8] = tmp.z * gl_e->scale + gl_e->pos.z;
		i += 9;
		face = face->next;
	}
}
