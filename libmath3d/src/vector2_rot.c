/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2_rot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2017/05/24 14:02:47 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmath3d.h>

t_vector2	vector2_rot(t_vector2 v, float rad, float rot_direction)
{
	rad *= rot_direction;
	return ((t_vector2){v.x * cosf(rad) - v.y * sinf(rad), \
						v.x * sinf(rad) + v.y * cosf(rad)});
}
