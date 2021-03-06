/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/07 09:42:03 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmath3d.h>

void	vector2_print(const t_vector2 v)
{
	printf("vector2\t\t%.2f\t%.2f\n", v.x, v.y);
}

void	vector3_print(const t_vector3 v)
{
	printf("vector3\t\t%.2f\t%.2f\t%.2f\n", v.x, v.y, v.z);
}

void	matrix4_print(t_matrix4 m)
{
	int		*o;
	float	*e;
	int		i;

	if (m.order == MATRIX_ROW_MAJOR)
		printf("matrix4 (row-major order)\n");
	else if (m.order == MATRIX_COLUMN_MAJOR)
		printf("matrix4 (column-major order)\n");
	else
	{
		fprintf(stderr, "\033[31mCritical: matrix order not set \033[0m\n");
		exit(255);
	}
	o = (m.order == MATRIX_ROW_MAJOR) ? (int[16])RM : (int[16])CM;
	e = m.m.e;
	i = 0;
	while (i < 16)
		printf("%.2f ", e[i++]);
	printf("\n\t%.2f\t%.2f\t%.2f\t%.2f\n", e[o[0]], e[o[1]], e[o[2]], e[o[3]]);
	printf("\t%.2f\t%.2f\t%.2f\t%.2f\n", e[o[4]], e[o[5]], e[o[6]], e[o[7]]);
	printf("\t%.2f\t%.2f\t%.2f\t%.2f\n", e[o[8]], e[o[9]], e[o[10]], e[o[11]]);
	printf("\t%.2f\t%.2f\t%.2f\t%.2f\n", \
			e[o[12]], e[o[13]], e[o[14]], e[o[15]]);
}
