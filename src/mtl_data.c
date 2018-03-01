/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:08:34 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/01 13:12:42 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		chk_matname(t_mat *mat, char *name)
{
	while (mat)
	{
		if (strcmp(mat->name, name) == 0)
			error_mtl(name, MTL_USED);
		mat = mat->next;
	}
}

t_str			*add_mtlname(t_mat **mat, t_str *ptr)
{
	t_mat	*new_mat;
	char	token[100];
	char	name[500];

	ft_bzero(token, 100);
	ft_bzero(name, 500);
	sscanf(ptr->str, "%s %s", token, name);
	if (ft_strlen(name) == 0)
		error_mtl(ptr->str, MTL_NO_NAME);
	chk_matname(*mat, name);
	new_mat = init_mat();
	new_mat->next = *mat;
	*mat = new_mat;
	if (ft_strlen(name) > 0)
	{
		free(new_mat->name);
		new_mat->name = ft_strdup(name);
	}
	return (ptr->next);
}

t_str			*add_color(t_str *ptr, float *color)
{
	char	token[100];

	sscanf(ptr->str, "%s %f %f %f", token, \
		&(color[0]), &(color[1]), &(color[2]));
	return (ptr->next);
}

t_str			*add_value_f(t_str *ptr, float *var)
{
	char	token[100];

	sscanf(ptr->str, "%s %f", token, var);
	return (ptr->next);
}

t_str			*add_value(t_str *ptr, int *var)
{
	char	token[100];

	sscanf(ptr->str, "%s %d", token, var);
	return (ptr->next);
}
