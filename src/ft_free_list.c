/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:09 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/01 12:50:32 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_void	*free_t_str(t_void *list)
{
	t_str	*ptr;
	t_void	*next;

	if (!list)
		return (NULL);
	next = list->next;
	ptr = (t_str*)list;
	ptr->next = NULL;
	ft_strdel(&(ptr->str));
	ft_bzero(list, sizeof(t_str));
	free(list);
	ptr = NULL;
	list = NULL;
	return (next);
}

void	ft_free_list(void *list, t_void *(custom_free)(t_void*))
{
	t_void	*ptr;
	t_void	*f;

	startf("ft_free_list");
	ptr = (t_void*)list;
	while (ptr)
	{
		f = ptr;
		ptr = ptr->next;
		custom_free(f);
	}
}
