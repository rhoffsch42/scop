#include <scop.h>

static void		error_arg(char *s1, char *s2)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_errexit(s2, RED, BAD_ARGS);
}

static int		check_perm(char *path)
{
	if (is_readable(path))
		return (1);
	COLOR(YELLOW, STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n-d option ignored\n\n", STDERR_FILENO);
	COLOR(NOCOLOR, STDERR_FILENO);
	return (0);
}

static int		add_directory(char **av, int i)
{
	if (av[i + 1] == NULL)
		ft_errexit(SCOP_DIR_ERR, RED, BAD_ARGS);
	if (check_perm(av[i + 1]) && is_dir())
		return (1);
	return (0);
}

void	load_file(t_env *e, int ac, char **av)
{
	int		i;
	int		dir[ac];

	ft_bzero(dir, sizeof(int) * ac);
	i = 1;
	while (av[i])
	{
		// ft_putendl(av[i]);
		if (ft_strcmp(av[i], SCOP_DIR) == 0)
		{
			dir[i + 1] = add_directory(av, i);
			i++;
		}
		else if (is_typefile(av[i], ".obj"))
			add_objfile(&(e->objfile), av[i]);
		else if (is_typefile(av[i], ".mtl"))
			add_mtlfile(&(e->mtlfile), av[i]);
		else
			error_arg(av[i], SCOP_BAD_ARG);
		i++;
	}
}
