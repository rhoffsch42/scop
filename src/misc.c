/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:08:18 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/01 12:51:57 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

char	*get_current_directory(void)
{
	char path[1024];

	ft_bzero(&path, sizeof(path));
	if (getcwd(path, sizeof(path)) == NULL)
		ft_errexit("getcwd error", RED, UNKNOW_ERROR);
	return (ft_strdup(path));
}

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
		while (s[j * 2] != hexmap[i] && hexmap[i])
			i++;
		(hexmap[i] == '\0') ? error_xpm(s, XPM_ERROR) : (void)i;
		rgb[j] += i * 16;
		i = 0;
		while (s[j * 2 + 1] != hexmap[i] && hexmap[i])
			i++;
		(hexmap[i] == '\0') ? error_xpm(s, XPM_ERROR) : (void)i;
		rgb[j] += i;
		j++;
	}
}

void	vertix_to_vector3(t_vertix *vertix, t_vector3 *vector)
{
	vector->x = vertix->x;
	vector->y = vertix->y;
	vector->z = vertix->z;
}

double	scale_d(double val, double min, double max)
{
	val = (val > max) ? max : val;
	val = (val < min) ? min : val;
	return (val);
}
