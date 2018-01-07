/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:09 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:07:13 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_void	*free_t_str(t_void *list)
{
	t_str	*ptr;
	t_void	*next;

	// startf("free_t_str");
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
	// deep--;
	return (next);
}

void	ft_free_list(void *list, t_void *(custom_free)(t_void*))
{
	t_void	*ptr;
	t_void	*f;

	startf("ft_free_list");
	if (!list)printf("FUCK\n");else printf("OK\n");
	if (!custom_free)printf("FUCK\n");else printf("OK\n");

	printf(".");
	ptr = (t_void*)list;
	printf(".");
	while (ptr)
	{
		printf(".");
		f = ptr;
		ptr = ptr->next;
		custom_free(f);
	}
	printf("\n");
	deep--;
}
