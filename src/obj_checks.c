/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:08:44 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/01 13:12:28 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_void		*check_obj(t_void *objptr)
{
	t_obj	*obj;
	char	error[300];

	obj = (t_obj*)objptr;
	ft_bzero(error, 300);
	ft_strcat(error, "obj\t");
	ft_strcat(error, obj->name);
	ft_strcat(error, " (");
	ft_strcat(error, obj->id_char);
	ft_strcat(error, ") :\n");
	if (obj->mtlfile == NULL)
		ft_strcat(error, "\t - has no valid mtl configuration file\n");
	if (obj->mat == NULL)
		ft_strcat(error, "\t - has no valid material\n");
	if (obj->v == NULL)
		ft_strcat(error, "\t - has no valid vertix\n");
	if (obj->f == NULL)
		ft_strcat(error, "\t - has no valid faces\n");
	ft_putstr_fd(error, STDERR_FILENO);
	return (NULL);
}

t_void		*check_objfile(t_void *link)
{
	t_objfile	*objfile;

	objfile = (t_objfile*)link;
	if (objfile->obj == NULL)
	{
		ft_putstr_fd(objfile->path, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		ft_errexit(OBJF_NO_OBJ, RED, OBJ_BAD_FORMAT);
	}
	return (for_list((t_void*)(objfile->obj), &check_obj));
}

void		obj_checks(t_objfile *objfile)
{
	COLOR(YELLOW, STDERR_FILENO);
	for_list((t_void*)objfile, &check_objfile);
	COLOR(NOCOLOR, STDERR_FILENO);
}
