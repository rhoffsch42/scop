/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_strdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 12:15:19 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/04/04 19:27:51 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_istr		*ft_int_strdup(int *str, int size)
{
	t_istr	*newstr;

	newstr = (t_istr*)malloc(sizeof(t_istr));
	newstr->istr = (int*)malloc(sizeof(int) * size);
	newstr->size = size;
	while (size > 0)
	{
		(newstr->istr)[size - 1] = str[size - 1];
		size--;
	}
	return (newstr);
}
