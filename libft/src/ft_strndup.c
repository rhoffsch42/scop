/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:58 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:09:41 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
**	renvoie NULL si:
**	- start < 0
**	- start > end
**	- src == NULL
**
**	comportement indetermine si:
**		- end > ft_strlen(str) + 1
**
**	ceci est valide:
**		"test1\0test2\0"
**		ft_strndup(src, 2, 11);
**		=> "st1\0test\0\0" (il y a toujours un ajout de \0 a la fin)
*/

char	*ft_strndup(char *src, int start, int end)
{
	char	*dst;
	int		i;

	if (src == NULL || start < 0 || start > end)
		return (NULL);
	dst = (char*)malloc(sizeof(char) * (end - start + 2));
	i = 0;
	while (start <= end)
	{
		dst[i] = src[start];
		start++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
