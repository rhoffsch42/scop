/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:57:12 by rhoffsch          #+#    #+#             */
/*   Updated: 2016/02/19 15:32:49 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char *cp, int i)
{
	if (ft_isdigit(cp[i]) == 0 && cp[i] != 43 && cp[i] != 45)
		return (0);
	if (cp[i] == 43 || cp[i] == 45)
		if (cp[i + 1] == 43 || cp[i + 1] == 45)
			return (0);
	return (1);
}

int			ft_atoi(const char *str)
{
	char	*cp;
	int		i;
	int		n;

	n = 0;
	i = 0;
	cp = ft_strtrim_extended(str, WHITESPACES);
	if (ft_check(cp, i) != 1)
		return (0);
	i++;
	while (ft_isdigit(cp[i]) == 1)
		i++;
	cp[i] = '\0';
	if (ft_isdigit(cp[0]) == 1)
		i = 0;
	else
		i = 1;
	while (i < ft_strlen(cp))
		n = 10 * n + (int)cp[i++] - 48;
	if (cp[0] == 45)
		n = -n;
	return (n);
}
