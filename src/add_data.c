#include <scop.h>

t_str	*link_mtlfile(t_obj *obj, t_str *ptr)
{
	char	token[100];
	char	path[500];

	sscanf(ptr->str, "%s %s", token, path);
	obj->mtllib = ft_strdup(path);
	return (ptr->next);
}

t_str	*link_material(t_obj *obj, t_str *ptr)
{
	char	token[100];
	char	path[500];

	sscanf(ptr->str, "%s %s", token, path);
	obj->material = ft_strdup(path);
	return (ptr->next);
}

t_str	*add_smooth(t_obj *obj, t_str *ptr)
{
	char	token[20];
	char	token2[10];

	sscanf(ptr->str, "%s %s", token, token2);
	if (ft_strcmp(token2, "on") == 0)
		obj->smooth = 1;
	else if (ft_strcmp(token2, "off") == 0)
		obj->smooth = 0;
	else
		error_obj(ptr->str, OBJ_ERROR);
	return (ptr->next);
}

t_str	*add_vertix(t_obj *obj, t_str *ptr)
{
	char		token[100];
	t_vertix	*v;
	int			id;

	obj->v = (t_vertix*)safe_malloc(sizeof(t_vertix));
	id = 0;
	v = obj->v;
	while (ptr)
	{
		sscanf(ptr->str, "%s", token);
		if (ft_strcmp(token, OBJ_VERTIX) != 0)
			break ;
		if (++id != 1)
		{
			v->next = (t_vertix*)safe_malloc(sizeof(t_vertix));
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

	obj->f = (t_face*)safe_malloc(sizeof(t_face));
	id = 0;
	f = obj->f;
	while (ptr)
	{
		sscanf(ptr->str, "%s", token);
		if (ft_strcmp(token, OBJ_FACE) != 0)
			break ;
		if (++id != 1)
		{
			f->next = (t_face*)safe_malloc(sizeof(t_face));
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
