/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:49 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:07:52 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_void		**list_to_tab(t_void *list)
{
	t_void	**tab;
	int		len;
	int		i;

	len = ft_listlen(list);
	tab = (t_void**)malloc(sizeof(t_void*) * (len + 1));
	i = 0;
	while (i < len)
	{
		tab[i] = list;
		list = list->next;
		ft_putchar('.');
		i++;
	}
	tab[i] = NULL;
	ft_putchar(10);
	return (tab);
}
