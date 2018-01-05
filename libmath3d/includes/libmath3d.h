/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2017/05/24 14:02:47 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATH3D_H
# define LIBMATH3D_H

# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>

# define RGB(r, g, b)			(65536 * (int)(r) + 256 * (int)(g) + (int)(b))
# define RTOD(x)				((x) * (180.0f / M_PI))
# define DTOR(x)				((x) * M_PI / 180.0f)

# define MATRIX_COLUMN_MAJOR	0
# define MATRIX_ROW_MAJOR		1
# define IDENTITY				1
# define ROT_RIGHT				-1
# define ROT_LEFT				1
# define RM		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
# define CM		{0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15}

typedef struct	s_vector2
{
	float		x;
	float		y;
}				t_vector2;

typedef struct	s_vector3
{
	float		x;
	float		y;
	float		z;
}				t_vector3;

typedef union	u_matrix
{
	float		e[16];
	float		tab[4][4];
}				t_matrix;

typedef struct	s_matrix4
{
	uint8_t		order;
	t_matrix	m;
}				t_matrix4;

/*
**	typedef vector3
**	{
**		float	x
**		float	y
**		float	z
**		// ou bien faire une nouvelle structure
**		// et remplacer ces 3 valeurs par un t_vector3
**
**		bool	data_changed
**		float	magnitude
**		float	orher1
**		float	other2
**	} tvector3
**
**	if (data_changed)
**		calc_new magnitude/otherx
**	else
**		return magnitude/otherx
**
**	void			vector2_scale(t_vector2 dst, float f);
**	void			vector3_scale(t_vector3 dst, float v);
*/

void			vector2_print(const t_vector2 v);
void			vector3_print(const t_vector3 v);
void			matrix4_print(t_matrix4 m);

t_vector2		vector2(float x, float y);
t_vector2		vector2_add(t_vector2 v1, const t_vector2 v2);
t_vector2		vector2_sub(t_vector2 v1, const t_vector2 v2);
t_vector2		vector2_mult_coef(t_vector2 v, float coef);
float			vector2_magnitude(const t_vector2 v);
float			vector2_dot(const t_vector2 v1, const t_vector2 v2);
t_vector2		vector2_rot(t_vector2 v, float rad, float rot_direction);

t_vector3		vector3(float x, float y, float z);
t_vector3		vector3_add(t_vector3 v1, const t_vector3 v2);
t_vector3		vector3_sub(t_vector3 v1, const t_vector3 v2);
t_vector3		vector3_mult_coef(t_vector3 v, float coef);
float			vector3_magnitude(const t_vector3 v);
float			vector3_dot(const t_vector3 v1, const t_vector3 v2);
t_vector3		vector3_cross(const t_vector3 v1, const t_vector3 v2);
t_vector3		vector3_rot(const t_vector3 src, t_vector3 rad, float rot_way);

t_matrix4		matrix4(uint8_t is_identity, uint8_t order);
t_matrix4		matrix4_set_order(t_matrix4 m, uint8_t order);
t_matrix4		matrix4_add(t_matrix4 m1, const t_matrix4 m2);
t_matrix4		matrix4_sub(t_matrix4 m1, const t_matrix4 m2);
t_matrix4		matrix4_mult(t_matrix4 m1, const t_matrix4 m2);
t_matrix4		matrix4_mult_coef(t_matrix4 m, float coef);
t_matrix4		matrix4_cpy(t_matrix4 dst, const t_matrix4 src);

#endif
