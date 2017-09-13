/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 15:56:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/04/04 19:28:10 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_istr		ft_atoi_str(char **tab)
{
	int		i;
	t_istr	istr;

	i = ft_tablen(tab);
	istr.size = i;
	istr.istr = (int*)malloc(sizeof(int) * i);
	i = 0;
	while (tab[i] != NULL)
	{
		(istr.istr)[i] = ft_atoi(tab[i]);
		i++;
	}
	return (istr);
}
