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

static void		add_directory(char **av, int i, t_str **dir)
{
	t_str	*new_dir;
	t_str	*ptr;

	if (av[i + 1] == NULL)
		ft_errexit(SCOP_DIR_ERR, RED, BAD_ARGS);
	if (check_perm(av[i + 1]) && is_dir())
	{
		new_dir = (t_str*)safe_malloc(sizeof(t_str));
		new_dir->next = NULL;
		new_dir->str = ft_strdup(av[i + 1]);
		remove_trailing_slach(new_dir->str);
		ptr = *dir;
		if (ptr)
		{
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = new_dir;
		}
		else
			*dir = new_dir;
	}
}

void	load_file(t_env *e, int ac, char **av)
{
	int		i;

	if (ac == 1)
		error_arg(av[0], SCOP_BAD_ARG);
	i = 1;
	while (av[i])
	{
		if (ft_strcmp(av[i], SCOP_DIR) == 0)
		{
			add_directory(av, i, &(e->dir));
			i++;
		}
		else if (is_typefile(av[i], ".obj") && is_readable(av[i]))
			add_objfile(&(e->objfile), av[i]);
		else if (is_typefile(av[i], ".mtl") && is_readable(av[i]))
			add_mtlfile(&(e->mtlfile), av[i]);
		else
			error_arg(av[i], SCOP_BAD_ARG);
		i++;
	}
	link_file(e);
	obj_checks(e->objfile);
	mtl_checks(e->mtlfile);
}
