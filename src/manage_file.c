#include <scop.h>

t_mtlfile	*get_mtlfile(t_mtlfile *ptr, char *file)
{
	while (ptr)
	{
		if (ft_strcmp(basename(file), ptr->name) == 0)
		{
			ft_putendl("Found!");
			return (ptr);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

t_objfile	*get_objfile(t_objfile *ptr, char *file)
{
	while (ptr)
	{
		if (ft_strcmp(basename(file), ptr->name) == 0)
		{
			ft_putendl("Found!");
			return (ptr);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

void	add_objfile(t_objfile **addr, char *file)
{
	static int	id = 0;
	t_objfile	*new_objfile;

	if (!chk_objfile(*addr, file))
		return ;
	new_objfile = (t_objfile*)safe_malloc(sizeof(t_objfile));
	new_objfile->id = id;
	new_objfile->path = ft_strdup(file);
	new_objfile->name = ft_strdup(basename(file));
	new_objfile->obj = build_object(file);
	new_objfile->next = *addr;
	*addr = new_objfile;
	id++;
}

void	add_mtlfile(t_mtlfile **addr, char *file)
{
	static int	id = 0;
	t_mtlfile	*new_mtlfile;

	if (!chk_mtlfile(*addr, file))
		return ;
	new_mtlfile = (t_mtlfile*)safe_malloc(sizeof(t_mtlfile));
	new_mtlfile->id = id;
	new_mtlfile->path = ft_strdup(file);
	new_mtlfile->name = ft_strdup(basename(file));
	new_mtlfile->mat = NULL;// build_mat() en fait.
	new_mtlfile->next = *addr;
	*addr = new_mtlfile;
	id++;
}
