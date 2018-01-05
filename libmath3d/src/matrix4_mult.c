/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_mult_coef.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2017/05/24 14:02:47 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmath3d.h>

t_matrix4	matrix4_mult(t_matrix4 m1, const t_matrix4 m2)
{
	t_matrix4	tmp;
	int			i;
	int			w;
	int			h;

	if (m1.order != m2.order)
		fprintf(stderr, \
			"\033[33m/!\\ Multiplying matrices with different order\033[0m\n");
	tmp = matrix4(0, m1.order);
	i = 0;
	while (i < 16)
	{
		w = i / 4 * 4;
		h = i % 4;
		while (h < 16)
		{
			tmp.m.e[i] += m1.m.e[w] * m2.m.e[h];
			w++;
			h += 4;
		}
		i++;
	}
	return (tmp);
}
