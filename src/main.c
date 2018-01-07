/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:58 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:09:41 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	test_texture(char *path)
{
	ft_chkptr(path, "FUCK envoie une texture!\n", 1);
	t_str	*data = ft_getfile(path);

	while (data)
	{
		int i = 0;
		while (data->str[i])
		{
			ft_putnbr((unsigned char)(data->str[i]));
			ft_putchar(32);
			i++;
			if (i % 15 == 0)
				ft_putchar(10);
		}
		ft_putchar(10);
		data = data->next;
	}
	exit(0);
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
		ft_putendl("<=============>");
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
	if (DATA == 0)
		return ;
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

void	dump_datafile(t_objfile *objfile, t_mtlfile *mtlfile, t_str *dir, t_xpm *xpm)
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
	while (xpm)
	{
		ft_putendl(xpm->path);
		xpm = xpm->next;
	}
	ft_putendl("*******************************************");
}

void	print_memory(void)
{
	errno = 0;
	struct rusage* memory = malloc(sizeof(struct rusage));
	getrusage(RUSAGE_SELF, memory);
	if(errno == EFAULT)
		printf("Error: EFAULT\n");
	else if(errno == EINVAL)
		printf("Error: EINVAL\n");
	printf("Usage: %ld\n", memory->ru_ixrss);
	printf("Usage: %ld\n", memory->ru_isrss);
	printf("Usage: %ld\n", memory->ru_idrss);
	printf("Max: %ld\n", memory->ru_maxrss);
}

void	stacksize()
{
	size_t stksize;
	pthread_attr_t atr;
	if (pthread_attr_getstacksize(&atr, &stksize) == -1)
		printf("FUCKING SCOP\n");
	printf("Current stack size ->\t%lu\n", 140734679836896 - stksize);
}

void	gostack()
{
	// struct rlimit limit;
	// getrlimit (RLIMIT_STACK, &limit);
	// printf ("\nStack Limit = %llu and %llu max\n", limit.rlim_cur, limit.rlim_max);
	int x=0;
	printf("STACK\t%lu\n", (top_of_stack - (size_t) &x));
	// print_memory();
}
void	print_struct_offset()
{
	ft_putnbrendl(offsetof(t_rgb, next));
	ft_putnbrendl(offsetof(t_arg, next));
	ft_putnbrendl(offsetof(t_vertix, next));
	ft_putnbrendl(offsetof(t_face, next));
	ft_putnbrendl(offsetof(t_mat, next));
	ft_putnbrendl(offsetof(t_mtlfile, next));
	ft_putnbrendl(offsetof(t_obj, next));
	ft_putnbrendl(offsetof(t_objfile, next));
	ft_putnbrendl(offsetof(t_xpm, next));

	ft_putnbrendl(offsetof(t_void, next));
	ft_putnbrendl(offsetof(t_istr, next));
	ft_putnbrendl(offsetof(t_list, next));
	ft_putnbrendl(offsetof(t_str, next));
	exit(0);
}

void	test_stack(int i)
{
	int	l = i;
	(void)l;
	// stacksize();
	gostack();
	if (i < 20)
		test_stack(i+1);
	exit(0);
}

void	startf(char *func_name)
{
	deep++;
	size_t i = -1;
	while (++i != deep)
		printf("_ ");
	printf("%s", func_name);
	printf("\t\t\t\tend\n");
}

int		main(int ac, char **av)
{
	deep = 0;
	int x=0;
	top_of_stack = (size_t) &x;
	// test_stack(0);
	gostack();
	// print_struct_offset();
	// exit(0);
	// test_sscanf(lst);
	// test_texture(av[1]);
	ft_puttab(av);
	ft_putendl("________________BEGIN________________");
	t_env		*e;
	t_objfile	**object_tab;
	t_xpm		**texture_tab;
	e = init_env();
	load_file(e, ac, av);
	printf("___ dump_datafile\n");
	dump_datafile(e->objfile, e->mtlfile, e->dir, e->xpmfile);
	t_rgb *rgb = get_color(e->chart, "medium slate blue");
	if (rgb)
	{
		ft_putnbrendl(rgb->r);
		ft_putnbrendl(rgb->g);
		ft_putnbrendl(rgb->b);
	}
	object_tab = (t_objfile**)list_to_tab((t_void*)(e->objfile));
	texture_tab = (t_xpm**)list_to_tab((t_void*)(e->xpmfile));
	e->glfw = init_glfw(NULL);
	(void)texture_tab;
	display_object(e->glfw, object_tab, texture_tab, \
		(int[2]){ft_listlen(e->objfile), ft_listlen(e->xpmfile)});
	// display_object(e->sdl, e->objfile);
	// free_t_env((t_void*)e);
	ft_putendl("________________END________________");
	return (0);
}
