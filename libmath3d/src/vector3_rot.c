/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_rot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2017/05/24 14:02:47 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmath3d.h>

static void		init_rot_matrix(float *val, t_vector3 rad, float rot_way)
{
	rad.x *= rot_way;
	rad.y *= rot_way;
	rad.z *= rot_way;
	val[0] = cosf(rad.x);
	val[1] = sinf(rad.x);
	val[2] = cosf(rad.y);
	val[3] = sinf(rad.y);
	val[4] = cosf(rad.z);
	val[5] = sinf(rad.z);
	val[6] = val[0] * val[3];
	val[7] = val[1] * val[3];
}

t_vector3		vector3_rot(const t_vector3 v, t_vector3 rad, float rot_way)
{
	float		val[8];
	float		mat[16];
	t_vector3	dst;

	init_rot_matrix(val, rad, rot_way);
	mat[0] = val[2] * val[4];
	mat[1] = -val[2] * val[5];
	mat[2] = val[3];
	mat[3] = 0;
	mat[4] = val[7] * val[4] + val[0] * val[5];
	mat[5] = -val[7] * val[5] + val[0] * val[4];
	mat[6] = -val[1] * val[2];
	mat[7] = 0;
	mat[8] = -val[6] * val[4] + val[1] * val[5];
	mat[9] = val[6] * val[5] + val[1] * val[4];
	mat[10] = val[0] * val[2];
	mat[11] = 0;
	mat[12] = 0;
	mat[13] = 0;
	mat[14] = 0;
	mat[15] = 1;
	dst.x = v.x * mat[0] + v.y * mat[1] + v.z * mat[2];
	dst.y = v.x * mat[4] + v.y * mat[5] + v.z * mat[6];
	dst.z = v.x * mat[8] + v.y * mat[9] + v.z * mat[10];
	return (dst);
}
