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

	o = (m.order == MATRIX_ROW_MAJOR) ? (int[16])RM : (int[16])CM;
	if (m.order == MATRIX_ROW_MAJOR)
		printf("matrix4 (row-major order)\n");
	else if (m.order == MATRIX_COLUMN_MAJOR)
		printf("matrix4 (column-major order)\n");
	else
	{
		fprintf(stderr, "\033[31mCritical: matrix order not set \033[0m\n");
		exit(255);
	}
	printf("\t%.2f\t%.2f\t%.2f\t%.2f\n",
		m.m.e[o[0]], m.m.e[o[1]], m.m.e[o[2]], m.m.e[o[3]]);
	printf("\t%.2f\t%.2f\t%.2f\t%.2f\n", \
		m.m.e[o[4]], m.m.e[o[5]], m.m.e[o[6]], m.m.e[o[7]]);
	printf("\t%.2f\t%.2f\t%.2f\t%.2f\n", \
		m.m.e[o[8]], m.m.e[o[9]], m.m.e[o[10]], m.m.e[o[11]]);
	printf("\t%.2f\t%.2f\t%.2f\t%.2f\n", \
		m.m.e[o[12]], m.m.e[o[13]], m.m.e[o[14]], m.m.e[o[15]]);
}
