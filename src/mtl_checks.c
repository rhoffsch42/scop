/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:08:29 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/01 12:53:25 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			regularize(float *v, float min, float max)
{
	if (*v < min)
	{
		*v = min;
		return (0);
	}
	if (*v > max)
	{
		*v = max;
		return (0);
	}
	return (1);
}

void		regularize_values(t_mat *mat, char *error)
{
	if (!regularize(&(mat->ka[0]), 0, 1) || !regularize(&(mat->ka[1]), 0, 1) \
		|| !regularize(&(mat->ka[2]), 0, 1))
		ft_strcat(error, "\t - ambiant color (Ka) regularized\n");
	if (!regularize(&(mat->kd[0]), 0, 1) || !regularize(&(mat->kd[1]), 0, 1) \
		|| !regularize(&(mat->kd[2]), 0, 1))
		ft_strcat(error, "\t - diffuse color (Kd) regularized\n");
	if (!regularize(&(mat->ks[0]), 0, 1) || !regularize(&(mat->ks[1]), 0, 1) \
		|| !regularize(&(mat->ks[2]), 0, 1))
		ft_strcat(error, "\t - specular color (Ks) regularized\n");
	if (!regularize(&(mat->ns), 0, 100))
		ft_strcat(error, "\t - specular exponent (Ns) regularized\n");
	if (!regularize(&(mat->ni), 0, 1))
		ft_strcat(error, "\t - optical density (Ni) regularized\n");
	if (!regularize(&(mat->d), 0, 1))
		ft_strcat(error, "\t - opacity (d) regularized\n");
}

t_void		*check_mat(t_void *matptr)
{
	t_mat	*mat;
	char	error[300];

	mat = (t_mat*)matptr;
	ft_bzero(error, 300);
	ft_strcat(error, "mat\t");
	ft_strcat(error, mat->name);
	ft_strcat(error, " (");
	ft_strcat(error, mat->id_char);
	ft_strcat(error, ") :\n");
	regularize_values(mat, error);
	ft_putstr_fd(error, STDERR_FILENO);
	return (NULL);
}

t_void		*check_mtlfile(t_void *link)
{
	t_mtlfile	*mtlfile;

	mtlfile = (t_mtlfile*)link;
	if (mtlfile->mat == NULL)
	{
		ft_putstr_fd(mtlfile->path, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		ft_errexit(MTLF_NO_MAT, RED, MTL_BAD_FORMAT);
	}
	return (for_list((t_void*)(mtlfile->mat), &check_mat));
}

void		mtl_checks(t_mtlfile *mtlfile)
{
	COLOR(YELLOW, STDERR_FILENO);
	for_list((t_void*)mtlfile, &check_mtlfile);
	COLOR(NOCOLOR, STDERR_FILENO);
}
