/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 03:52:26 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/01/07 08:22:12 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puttab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i]);
		i++;
		ft_putchar('\n');
	}
}
