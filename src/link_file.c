#include <scop.h>

static void		check_directory(t_env *e, char *filename)
{
	char	*bigpath;
	t_str	*dir;
	int		len[2];

	dir = e->dir;
	bigpath = NULL;
	len[1] = ft_strlen(filename);
	while (dir)
	{
		if (bigpath)
			ft_strdel(&bigpath);
		len[0] = len[1] + ft_strlen(dir->str) + 1;
		bigpath = (char*)safe_malloc(sizeof(char) * len[0]);
		ft_bzero(bigpath, len[0]);
		ft_strcat(bigpath, dir->str);
		ft_strcat(bigpath, "/");
		ft_strcat(bigpath, filename);
		if (is_readable(bigpath))
			add_mtlfile(&(e->mtlfile), bigpath);
		dir = dir->next;
	}
}

static void		link_material(t_obj *obj, t_mtlfile *mtlf)
{
	t_mat	*mat;

	if (obj->mat_name == NULL)
		return ;
	while (mtlf)
	{
		if (ft_strcmp(obj->mtllib, mtlf->name) == 0)
		{
			mat = mtlf->mat;
			while (mat)
			{
				if (ft_strcmp(mat->name, obj->mat_name) == 0)
				{
					ft_putendl("linking mat:");
					ft_putendl(obj->name);
					ft_putendl(mat->name);
					obj->mtlfile = mtlf;
					obj->mat = mat;
					break ;
				}
				mat = mat->next;
			}
			if (obj->mat)
				break ;
		}
		mtlf = mtlf->next;
	}
}

void	link_file(t_env *e)
{
	t_objfile	*objf;
	t_obj		*obj;

	objf = e->objfile;
	while (objf)
	{
		obj = objf->obj;
		while (obj)
		{
			link_material(obj, e->mtlfile);
			if (obj->mat == NULL)
			{
				check_directory(e, obj->mtllib);
				link_material(obj, e->mtlfile);
			}
			obj = obj->next;
		}
		objf = objf->next;
	}
}
