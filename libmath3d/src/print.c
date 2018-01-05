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

void	matrix4_print(const t_matrix4 m)
{
	if (m.order == MATRIX_ROW_MAJOR)
		printf("matrix4 (row-major order)\n");
	else if (m.order == MATRIX_COLUMN_MAJOR)
		printf("matrix4 (column-major order)\n");
	else
	{
		fprintf(stderr, "\033[31mCritical: matrix order not set \033[0m\n");
		exit(255);
	}
	printf("\t%.2f\t%.2f\t%.2f\t%.2f\n", \
		m.m.e[0], m.m.e[1], m.m.e[2], m.m.e[3]);
	printf("\t%.2f\t%.2f\t%.2f\t%.2f\n", \
		m.m.e[4], m.m.e[5], m.m.e[6], m.m.e[7]);
	printf("\t%.2f\t%.2f\t%.2f\t%.2f\n", \
		m.m.e[8], m.m.e[9], m.m.e[10], m.m.e[11]);
	printf("\t%.2f\t%.2f\t%.2f\t%.2f\n", \
		m.m.e[12], m.m.e[13], m.m.e[14], m.m.e[15]);
}
