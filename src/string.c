#include <scop.h>

char	*basename(char *path)
{
	char	*ptr;

	ptr = ft_strrchr(path, '/');
	if (ptr)
		return (ptr + 1);
	return (path);
}

int		is_dir(void)
{
	return (1);
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
	if (ptr && ft_strcmp(ptr, type) == 0 && ft_strlen(file) > ft_strlen(type))
		return (1);
	return (0);
}
