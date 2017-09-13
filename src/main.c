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

void	dump_data(t_obj *obj)
{
	t_vertix	*v;
	t_face		*f;
	ft_putendl(":::::::::::::::::::::::::::checks:");
	printf("id:      \t%d\n", obj->id);
	printf("name:    \t%s\n", obj->name);
	if (obj->mtllib)
		printf("mtllib:  \t%s\n", obj->mtllib);
	if (obj->material)
		printf("material:\t%s\n", obj->material);
	printf("smooth: \t%d\n", obj->smooth);
	v = obj->v;
	while (v)
	{
		printf("vertix %d:\t%f\t%f\t%f\n", v->id, v->x, v->y, v->z);
		v = v->next;
	}
	f = obj->f;
	while (f)
	{
		printf("face   %d:\t%d\t%d\t%d\t%d\n", f->id, f->a, f->b, f->c, f->d);
		f = f->next;
	}
}

int		main(int ac, char **av)
{
	(void)ac;(void)av;
	// test_sscanf(lst);
	ft_putendl("________________BEGIN________________");
	t_obj	*object;
	object = build_object("./resources/42.obj");
	dump_data(object);
	ft_putendl("________________END________________");
	return (0);
}
