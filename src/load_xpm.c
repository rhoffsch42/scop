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

t_xpm	*load_xpm(char *path)
{
	t_xpm	*xpm;
	t_str	*str;
	t_str	*lst;

	if (!is_typefile(path, ".xpm"))
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_errexit(" is not a valid xpm file", RED, BAD_ARGS);
	}
	xpm = init_xpm();
	xpm->path = ft_strdup(path);
	xpm->name = ft_strdup(basename(path));
	str = ft_getfile(path);
	char *all = t_str_to_char(str);
	remove_comments_vl(all, "/*", "*/", "//");
	lst = char_to_t_str(all);
	remove_white_spaces(lst);
	lst = (t_str*)remove_list((t_void*)lst, is_empty, del);
	while (lst)
	{
		ft_putendl(lst->str);
		lst = lst->next;
	}
	return (xpm);
}
