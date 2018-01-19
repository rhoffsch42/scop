/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2017/05/24 14:02:47 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmath3d.h>

t_vector3	vector3_cross(const t_vector3 v1, const t_vector3 v2)
{
	return ((t_vector3){v1.y * v2.z - v1.z * v2.y, \
						v1.z * v2.x - v1.x * v2.z, \
						v1.x * v2.y - v1.y * v2.x});
}