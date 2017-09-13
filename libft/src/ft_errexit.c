/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/28 07:37:13 by rhoffsch          #+#    #+#             */
/*   Updated: 2016/02/28 07:38:00 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_errexit(const char *message, char *color, int code)
{
	ft_putstr_color((char*)message, color, 2);
	ft_putchar_fd(10, 2);
	exit(code);
}
