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

void	dump_data_mtl(t_mat *mat)
{
	ft_putendl("\tDATAS :");
	while (mat)
	{
		printf("ID:      \t%d\n", mat->id);
		printf("Name:    \t%s\n", mat->name);
		printf("Ns:      \t%f\n", mat->ns);
		printf("Ka:      \t%f\t%f\t%f\n", mat->ka[0], mat->ka[1], mat->ka[2]);
		printf("Kd:      \t%f\t%f\t%f\n", mat->kd[0], mat->kd[1], mat->kd[2]);
		printf("Ks:      \t%f\t%f\t%f\n", mat->ks[0], mat->ks[1], mat->ks[2]);
		printf("ni:      \t%f\n", mat->ni);
		printf("d:       \t%f\n", mat->d);
		printf("illum:   \t%d\n", mat->illum);
		mat = mat->next;
		ft_putendl(">>>");
	}
}

void	dump_data_obj(t_obj *obj)
{
	t_vertix	*v;
	t_face		*f;
	ft_putendl("\tDATAS :");
	printf("ID:      \t%d\n", obj->id);
	printf("Name:    \t%s\n", obj->name);
	printf("Mtl library:\t%s\n", obj->mtllib ? obj->mtllib : "\'N/D\'");
	if (obj->mat_name)
		printf("Material:\t%s (id: %d)\n", obj->mat_name, obj->mat ? obj->mat->id : -1);
	else
		printf("Material:\t%s\n", "\'N/D\'");
	printf("Smooth: \t%s\n", obj->smooth == 0 ? "off" : "on");
	printf("Vertix amount:\t%d\n", obj->v_amount);
	printf("Faces amount:\t%d\n", obj->f_amount);
	v = obj->v;
	return ;// comment it to print data
	while (v)
	{
		printf("vertix %d:\t%f\t%f\t%f\n", v->id, v->x, v->y, v->z);
		// printf("vertix %d:\t%f\t%f\t%f\n", v->id, v->x * 2 + 2, v->y * 2 + 2, v->z * 2 + 2);
		v = v->next;
	}
	f = obj->f;
	while (f)
	{
		printf("face   %d:\t%d\t%d\t%d\t%d\n", f->id, f->a, f->b, f->c, f->d);
		f = f->next;
	}
}

void	dump_datafile(t_objfile *objfile, t_mtlfile *mtlfile, t_str *dir)
{
	ft_putendl("*******************************************");
	while (objfile)
	{
		printf("type:   \tobjfile\n");
		printf("id:     \t%d\n", objfile->id);
		printf("path:   \t%s\n", objfile->path);
		printf("name:   \t%s\n", objfile->name);
		dump_data_obj(objfile->obj);
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
		dump_data_mtl(mtlfile->mat);
		mtlfile = mtlfile->next;
		ft_putendl("- - - - - - - - - - - - - - - - - - - -");
	}
	ft_putendl("*******************************************");
	while (dir)
	{
		ft_putstr("-d ");
		ft_putendl(dir->str);
		dir = dir->next;
	}
}

int		main(int ac, char **av)
{
	// exit(0);
	// test_sscanf(lst);
	ft_putendl("________________BEGIN________________");
	t_env	*e;
	e = init_env();
	load_file(e, ac, av);
	dump_datafile(e->objfile, e->mtlfile, e->dir);
	ft_putendl("________________END________________");
	ft_putnbrendl(ft_listlen(e->objfile->obj->v));
	ft_putnbrendl(ft_listlen(e->objfile->obj->f));
	return (0);
}
