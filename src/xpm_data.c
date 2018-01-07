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

int	byte = 3;

static void		print_data(t_xpm *xpm)
{
	int		i;
	int		len;

	len = sizeof(unsigned char) * (xpm->width * xpm->height * byte + 1);
	i = 0;
	while (i < len - 1)
	{
		ft_putnbr(xpm->data[i]);
		ft_putstr(i % byte < 2 ? ":" : "    \t");
		if (((i + 1) % (xpm->width * byte)) == 0 && i != 0)
			ft_putchar(10);
		i++;
	}
	ft_putchar(10);
}

t_str	*build_pixels(t_xpm *xpm, t_rgb *rgb_tokens, int t_size, t_str *ptr)
{
	t_rgb	*rgb;
	char	tok[3];
	char	*s;
	int		len;
	int		i;
	int		index;
	int		line_count;

	startf("build_pixels");
	ft_bzero(tok, 3);
	len = sizeof(unsigned char) * (xpm->width * xpm->height * byte + 1);
	xpm->data = (unsigned char*)safe_malloc(len);
	ft_bzero(xpm->data, len);
	line_count = 0;
	while (line_count < xpm->height)
	{
		i = 0;
		s = chk_separator(ptr->str);
		while ((i / t_size) < xpm->width)
		{
			tok[0] = s[i];
			tok[1] = (t_size == 2) ? s[i + 1] : tok[1];
			if ((rgb = get_color(rgb_tokens, tok)) != NULL)
			{
				index = line_count * xpm->width * byte + (i / t_size) * byte;
				xpm->data[index + 0] = rgb->r;
				xpm->data[index + 1] = rgb->g;
				xpm->data[index + 2] = rgb->b;
				// xpm->data[index + 3] = 0;
			}
			i += t_size;
		}
		line_count++;
		ptr = ptr->next;
	}
	// print_data(xpm);
	(void)print_data;
	deep--;
	return (ptr);
}
