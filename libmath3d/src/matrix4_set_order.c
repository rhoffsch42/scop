/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_set_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2017/05/24 14:02:47 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmath3d.h>

/*
** transpose the matrix if the order is not correct
*/

t_matrix4	matrix4_set_order(t_matrix4 m, uint8_t order)
{
	t_matrix4	tmp;
	int			i;
	int			j;

	if (order == m.order)
		return (m);
	tmp.order = order;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			tmp.m.tab[i][j] = m.m.tab[j][i];
			j++;
		}
		i++;
	}
	return (matrix4_cpy(m, tmp));
}
