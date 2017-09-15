#include <scop.h>

int		chk_objfile(t_objfile *objfile, char *path)
{
	t_objfile	*ptr;

	ptr = get_objfile(objfile, path);
	if (ptr)
	{
		COLOR(YELLOW, STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(" : name already in use (", STDERR_FILENO);
		ft_putstr_fd(ptr->path, STDERR_FILENO);
		ft_putstr_fd(")\nEntry ignored\n\n", STDERR_FILENO);
		COLOR(NOCOLOR, STDERR_FILENO);
		return (0);
	}
	return (1);
}

int		chk_mtlfile(t_mtlfile *mtlfile, char *path)
{
	t_mtlfile	*ptr;

	ptr = get_mtlfile(mtlfile, path);
	if (ptr)
	{
		COLOR(YELLOW, STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(" : name already in use (", STDERR_FILENO);
		ft_putstr_fd(ptr->path, STDERR_FILENO);
		ft_putstr_fd(")\nEntry ignored\n\n", STDERR_FILENO);
		COLOR(NOCOLOR, STDERR_FILENO);
		return (0);
	}
	return (1);
}
