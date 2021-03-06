/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:03 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/07 11:23:28 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_void	*free_t_mat(t_void *list)
{
	t_mat	*ptr;
	t_void	*next;

	if (!list)
		return (NULL);
	next = list->next;
	ptr = (t_mat*)list;
	ptr->next = NULL;
	ft_strdel(&ptr->id_char);
	ft_strdel(&ptr->name);
	ft_bzero(list, sizeof(t_mat));
	free(list);
	ptr = NULL;
	list = NULL;
	return (next);
}

t_void	*free_t_mtlfile(t_void *list)
{
	t_mtlfile	*ptr;
	t_void		*next;

	if (!list)
		return (NULL);
	next = list->next;
	ptr = (t_mtlfile*)list;
	ptr->next = NULL;
	ft_strdel(&ptr->path);
	ft_strdel(&ptr->name);
	ft_free_list(ptr->mat, free_t_mat);
	ft_bzero(list, sizeof(t_mtlfile));
	free(list);
	ptr = NULL;
	list = NULL;
	return (next);
}

t_void	*free_t_obj(t_void *list)
{
	t_obj	*ptr;
	t_void	*next;

	if (!list)
		return (NULL);
	next = list->next;
	ptr = (t_obj*)list;
	ptr->next = NULL;
	ft_strdel(&ptr->id_char);
	ft_strdel(&ptr->name);
	if (ptr->mtllib)
		ft_strdel(&ptr->mtllib);
	if (ptr->mat_name)
		ft_strdel(&ptr->mat_name);
	if (ptr->mtlfile)
		free_t_mtlfile((t_void*)ptr->mtlfile);
	if (ptr->mat)
		free_t_mat((t_void*)ptr->mat);
	ft_free_list(ptr->v, free_t_vertix);
	ft_free_list(ptr->f, free_t_face);
	ft_bzero(list, sizeof(t_obj));
	free(ptr);
	ptr = NULL;
	list = NULL;
	return (next);
}

t_void	*free_t_objfile(t_void *list)
{
	t_objfile	*ptr;
	t_void		*next;

	if (!list)
		return (NULL);
	next = list->next;
	ptr = (t_objfile*)list;
	ptr->next = NULL;
	ft_strdel(&ptr->path);
	ft_strdel(&ptr->name);
	ft_free_list(ptr->obj, free_t_obj);
	ft_bzero(list, sizeof(t_objfile));
	free(list);
	ptr = NULL;
	list = NULL;
	return (next);
}

t_void	*free_t_glfw(t_void *list)
{
	t_glfw	*ptr;
	t_void	*next;

	if (!list)
		return (NULL);
	next = list->next;
	ptr = (t_glfw*)list;
	ft_strdel(&ptr->title);
	ft_bzero(list, sizeof(t_glfw));
	free(list);
	ptr = NULL;
	list = NULL;
	return (next);
}
