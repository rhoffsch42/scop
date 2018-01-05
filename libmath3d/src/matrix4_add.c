/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2017/05/24 14:02:47 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmath3d.h>

t_matrix4	matrix4_add(t_matrix4 m1, const t_matrix4 m2)
{
	int		i;

	if (m1.order != m2.order)
		fprintf(stderr, \
			"\033[33m/!\\ Adding matrices with different order\033[0m\n");
	i = 0;
	while (i < 16)
	{
		m1.m.e[i] += m2.m.e[i];
		i++;
	}
	return (m1);
}
