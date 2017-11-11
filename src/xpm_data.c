#include <scop.h>

int	bpp = 3;

static void		print_data(t_xpm *xpm)
{
	int		i;
	int		len;

	len = sizeof(unsigned char) * (xpm->width * xpm->height * bpp + 1);
	i = 0;
	while (i < len - 1)
	{
		ft_putnbr(xpm->data[i]);
		ft_putstr(i % bpp < 2 ? ":" : "    \t");
		if (((i + 1) % (xpm->width * bpp)) == 0 && i != 0)
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

	ft_bzero(tok, 3);
	len = sizeof(unsigned char) * (xpm->width * xpm->height * 3 + 1);
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
				index = line_count * xpm->width * bpp + (i / t_size) * bpp;
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
	return (ptr);
}
