/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:09:07 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/01 12:54:19 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

char	*basename(char *path)
{
	char	*ptr;

	startf("basename");
	ptr = ft_strrchr(path, '/');
	if (ptr)
		return (ptr + 1);
	return (path);
}

int		is_directory(const char *path)
{
	int			i;
	struct stat	*buf;

	buf = (struct stat*)safe_malloc(sizeof(struct stat));
	if (lstat(path, buf) == -1)
		return (-1);
	i = (S_ISDIR(buf->st_mode)) ? 1 : 0;
	free(buf);
	return (i);
}

int		is_readable(char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) != -1)
	{
		close(fd);
		return (1);
	}
	return (0);
}

int		is_typefile(char *file, char *type)
{
	char	*ptr;

	ptr = ft_strstr(file, type);
	if (ptr && strcmp(ptr, type) == 0 && ft_strlen(file) > ft_strlen(type))
		return (1);
	return (0);
}

char	*remove_trailing_slach(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '/')
		str[len - 1] = 0;
	return (str);
}
