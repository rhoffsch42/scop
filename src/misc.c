#include <scop.h>

int		safe_open(char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(" : ", STDERR_FILENO);
		ft_errexit(strerror(errno), RED, errno);
	}
	return (fd);
}

void	hex_to_rgb(unsigned char *rgb, char *s)
{
	char	*hexmap;
	int		i;
	int		j;

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	if (*s == '#')
		s++;
	hexmap = "0123456789ABCDEF\0";
	j = 0;
	while (j < 3)
	{
		i = 0;
		while (s[j * 2] != hexmap[i])
			i++;
		rgb[j] += i * 16;
		i = 0;
		while (s[j * 2 + 1] != hexmap[i])
			i++;
		rgb[j] += i;
		j++;
	}
}
