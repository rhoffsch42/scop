/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:06:58 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/01 12:50:48 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_void	*free_t_env(t_void *list)
{
	t_env	*ptr;
	t_void	*next;

	if (!list)
		return (NULL);
	next = list->next;
	ptr = (t_env*)list;
	ft_free_list(ptr->objfile, free_t_objfile);
	ft_free_list(ptr->mtlfile, free_t_mtlfile);
	ft_free_list(ptr->dir, free_t_str);
	free_t_glfw((t_void*)ptr->glfw);
	ft_free_list(ptr->chart, free_t_rgb);
	ft_bzero(list, sizeof(t_env));
	free(list);
	ptr = NULL;
	list = NULL;
	return (next);
}

t_void	*free_t_xpm(t_void *list)
{
	t_xpm	*ptr;
	t_void	*next;

	if (!list)
		return (NULL);
	next = list->next;
	ptr = (t_xpm*)list;
	ptr->next = NULL;
	ft_strdel(&(ptr->name));
	ft_strdel(&(ptr->path));
	ft_strdel((char**)&ptr->data);
	ft_bzero(list, sizeof(t_xpm));
	free(list);
	ptr = NULL;
	list = NULL;
	return (next);
}

t_void	*free_t_rgb(t_void *list)
{
	t_rgb	*ptr;
	t_void	*next;

	if (!list)
		return (NULL);
	next = list->next;
	ptr = (t_rgb*)list;
	ptr->next = NULL;
	ft_strdel(&(ptr->name));
	ft_bzero(list, sizeof(t_rgb));
	free(list);
	ptr = NULL;
	list = NULL;
	return (next);
}

t_void	*free_t_vertix(t_void *list)
{
	t_vertix	*ptr;
	t_void		*next;

	if (!list)
		return (NULL);
	next = list->next;
	ptr = (t_vertix*)list;
	ptr->next = NULL;
	ft_bzero(list, sizeof(t_vertix));
	free(list);
	ptr = NULL;
	list = NULL;
	return (next);
}

t_void	*free_t_face(t_void *list)
{
	t_face	*ptr;
	t_void	*next;

	if (!list)
		return (NULL);
	next = list->next;
	ptr = (t_face*)list;
	ptr->next = NULL;
	free_t_vertix((t_void*)ptr->v1);
	free_t_vertix((t_void*)ptr->v2);
	free_t_vertix((t_void*)ptr->v3);
	free_t_vertix((t_void*)ptr->v4);
	ft_bzero(list, sizeof(t_face));
	free(list);
	ptr = NULL;
	list = NULL;
	return (next);
}
