#include <scop.h>

char	*get_line(t_str *lst, int n)
{
	int		i;

	i = 1;
	if (n == 0)
		return (NULL);
	while (i < n && lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (lst->str);
}

void	test_sscanf(t_str *lst)
{
	float	x, y, z = 0;
	char	prefix[10];
	t_str	*ptr = lst;
	while (ptr)
	{
		sscanf(ptr->str, "%s", prefix);
		if (strcmp(prefix, OBJ_VERTIX) == 0)
		{
			sscanf(ptr->str, "%s %f %f %f", prefix, &x, &y, &z);
			printf("::\t%s\t%f\t%f\t%f\n", prefix, x, y, z);
		}
		else
			ft_putendl(ptr->str);
		ptr = ptr->next;
	}
	ft_putendl("------------------");
	ft_putendl(get_line(lst, 0));
	ft_putendl(get_line(lst, 1));
	ft_putendl(get_line(lst, 2));
	ft_putendl(get_line(lst, 3));

	// ft_putendl(get_line(lst, 99));
	ft_putendl("------------------");
}

void	dump_data_obj(t_obj *obj)
{
	t_vertix	*v;
	t_face		*f;
	ft_putendl("\tDATAS :");
	printf("id:      \t%d\n", obj->id);
	printf("name:    \t%s\n", obj->name);
	if (obj->mtllib)
		printf("mtllib:  \t%s\n", obj->mtllib);
	if (obj->material)
		printf("material:\t%s\n", obj->material);
	printf("smooth: \t%s\n", obj->smooth == 0 ? "off" : "on");
	v = obj->v;
	if (!v)
		printf("No vertix\n");
	while (v)
	{
		printf("vertix %d:\t%f\t%f\t%f\n", v->id, v->x, v->y, v->z);
		// printf("vertix %d:\t%f\t%f\t%f\n", v->id, v->x * 2 + 2, v->y * 2 + 2, v->z * 2 + 2);
		v = v->next;
	}
	f = obj->f;
	if (!f)
		printf("No faces\n");
	while (f)
	{
		printf("face   %d:\t%d\t%d\t%d\t%d\n", f->id, f->a, f->b, f->c, f->d);
		f = f->next;
	}
}

void	dump_datafile(t_objfile *objfile, t_mtlfile *mtlfile)
{
	ft_putendl("*******************************************");
	while (objfile)
	{
		printf("type:   \tobjfile\n");
		printf("id:     \t%d\n", objfile->id);
		printf("path:   \t%s\n", objfile->path);
		printf("name:   \t%s\n", objfile->name);
		// dump_data_obj(objfile->obj);
		objfile = objfile->next;
		ft_putendl("- - - - - - - - - - - - - - - - - - - -");
	}
	ft_putendl("*******************************************");
	while (mtlfile)
	{
		printf("type:   \tmtlfile\n");
		printf("id:     \t%d\n", mtlfile->id);
		printf("path:   \t%s\n", mtlfile->path);
		printf("name:   \t%s\n", mtlfile->name);
		mtlfile = mtlfile->next;
		ft_putendl("- - - - - - - - - - - - - - - - - - - -");
	}
	ft_putendl("*******************************************");
}

int		main(int ac, char **av)
{
	// exit(0);
	(void)ac;(void)av;
	// test_sscanf(lst);
	ft_putendl("________________BEGIN________________");
	t_env	*e;
	e = init_env();
	load_file(e, ac, av);
	dump_datafile(e->objfile, e->mtlfile);
	exit(0);
	e->obj = build_object("./resources/42.obj");
	dump_data_obj(e->obj);
	ft_putendl("________________END________________");
	return (0);
}
