/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:09:12 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:09:14 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	print_data(t_xpm *xpm)
{
	int		i;
	int		len;

	len = sizeof(unsigned char) * (xpm->width * xpm->height * BYTE + 1);
	i = 0;
	while (i < len - 1)
	{
		ft_putnbr(xpm->data[i]);
		ft_putstr(i % BYTE < 2 ? ":" : "    \t");
		if (((i + 1) % (xpm->width * BYTE)) == 0 && i != 0)
			ft_putchar(10);
		i++;
	}
	ft_putchar(10);
}

t_str	*build_pixels(t_xpm *xpm, t_rgb *rgb_tokens, int tok_size, t_str *ptr)
{
	t_rgb	*rgb;
	char	tok[3];
	char	*s;
	int		pos[2];

	ft_bzero(tok, 3);
	xpm->data = (unsigned char*)ft_strnew(xpm->width * xpm->height * BYTE + 1);
	pos[0] = 0;
	while (pos[0] < xpm->height && (pos[1] = 0) == 0)
	{
		s = chk_separator(ptr->str);
		while ((pos[1] / tok_size) < xpm->width)
		{
			memcpy(tok, s + pos[1], tok_size);
			if ((rgb = get_color(rgb_tokens, tok)) != NULL)
				memcpy((void*)&(xpm->data[pos[0] * xpm->width * BYTE \
					+ (pos[1] / tok_size) * BYTE]), (void*)&(rgb->r), 3);
			else
				error_xpm(tok, XPM_COLOR_TOKEN);
			pos[1] += tok_size;
		}
		pos[0]++;
		ptr = ptr->next;
	}
	return (ptr);
}
