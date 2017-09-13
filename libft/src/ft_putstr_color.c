/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 07:39:19 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/04/01 00:33:32 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcolor(char *c1, char *color, char *c2, int fd)
{
	char	tmp[6];

	tmp[0] = 0;
	tmp[1] = 0;
	tmp[2] = 0;
	tmp[3] = 0;
	tmp[4] = 0;
	tmp[5] = 0;
	ft_strcat(tmp, c1);
	ft_strcat(tmp, color);
	ft_strcat(tmp, c2);
	ft_putstr_fd(tmp, fd);
}

void	ft_putchar_color(char c, char *color)
{
	COLOR(color, 1);
	ft_putchar(c);
	COLOR(WHITE, 1);
}

void	ft_putstr_color(char *str, char *color, int fd)
{
	COLOR(color, fd);
	ft_putstr_fd(str, fd);
	COLOR(WHITE, fd);
}
