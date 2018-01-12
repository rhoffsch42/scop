/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:58 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:09:41 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_chkptr(void *ptr, char *message, int code)
{
	if (ptr == NULL)
		ft_errexit(message, RED, code);
}

void	*safe_malloc(int size)
{
	void	*ptr;

	ptr = malloc(size);
	ft_chkptr(ptr, "Error : malloc failed\n", MALLOC_FAIL);
	return (ptr);
}
