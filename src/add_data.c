#include <scop.h>

t_str	*add_mtlfile(t_obj *obj, t_str *ptr)
{
	char	token[100];
	char	path[500];

	sscanf(ptr->str, "%s %s", token, path);
	obj->mtllib = ft_strdup(path);
	return (ptr->next);
}

t_str	*add_material(t_obj *obj, t_str *ptr)
{
	char	token[100];
	char	path[500];

	sscanf(ptr->str, "%s %s", token, path);
	obj->material = ft_strdup(path);
	return (ptr->next);
}

t_str	*add_vertix(t_obj *obj, t_str *ptr)
{
	char		token[100];
	t_vertix	*v;
	int			id;

	ft_chkmalloc(obj->v = (t_vertix*)malloc(sizeof(t_vertix)));
	id = 0;
	v = obj->v;
	while (ptr)
	{
		sscanf(ptr->str, "%s", token);
		if (ft_strcmp(token, OBJ_VERTIX) != 0)
			break ;
		if (++id != 1)
		{
			ft_chkmalloc(v->next = (t_vertix*)malloc(sizeof(t_vertix)));
			v = v->next;
		}
		ft_bzero(v, sizeof(t_vertix));
		v->id = id;
		sscanf(ptr->str, "%s %f %f %f", token, &(v->x), &(v->y), &(v->z));
		v->next = NULL;
		ptr = ptr->next;
	}
	return (ptr);
}

t_str	*add_face(t_obj *obj, t_str *ptr)
{
	char		token[100];
	t_face		*f;
	int			id;

	ft_chkmalloc(obj->f = (t_face*)malloc(sizeof(t_face)));
	id = 0;
	f = obj->f;
	while (ptr)
	{
		sscanf(ptr->str, "%s", token);
		if (ft_strcmp(token, OBJ_FACE) != 0)
			break ;
		if (++id != 1)
		{
			ft_chkmalloc(f->next = (t_face*)malloc(sizeof(t_face)));
			f = f->next;
		}
		ft_bzero(f, sizeof(t_face));
		f->id = id;
		f->next = NULL;
		sscanf(ptr->str, "%s %d %d %d %d", token, \
			&(f->a), &(f->b), &(f->c), &(f->d));
		ptr = ptr->next;
	}
	return (ptr);
}
