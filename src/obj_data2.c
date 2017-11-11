#include <scop.h>

t_str	*add_objname(t_obj *obj, t_str *ptr)
{
	char	token[100];
	char	name[500];

	ft_bzero(token, 100);
	ft_bzero(name, 500);
	sscanf(ptr->str, "%s %s", token, name);
	if (ft_strlen(name) > 0)
	{
		ft_strdel(&obj->name);
		obj->name = ft_strdup(name);
	}
	return (ptr->next);
}

void		translate_obj(t_vertix *vertix, float x, float y, float z)
{
	while (vertix)
	{
		vertix->x += x;
		vertix->y += y;
		vertix->z += z;
		vertix = vertix->next;
	}
}

static t_void		*center_obj(t_void *objptr)
{
	t_vertix	*vertix;
	float		vmin[3];
	float		vmax[3];

	vertix = ((t_obj*)objptr)->v;
	vmin[0] = vertix->x;
	vmin[1] = vertix->y;
	vmin[2] = vertix->z;
	vmax[0] = vertix->x;
	vmax[1] = vertix->y;
	vmax[2] = vertix->z;
	while (vertix)
	{
		vmin[0] = (vertix->x < vmin[0]) ? vertix->x : vmin[0];
		vmin[1] = (vertix->y < vmin[1]) ? vertix->y : vmin[1];
		vmin[2] = (vertix->z < vmin[2]) ? vertix->z : vmin[2];
		vmax[0] = (vertix->x > vmax[0]) ? vertix->x : vmax[0];
		vmax[1] = (vertix->y > vmax[1]) ? vertix->y : vmax[1];
		vmax[2] = (vertix->z > vmax[2]) ? vertix->z : vmax[2];
		vertix = vertix->next;
	}
	translate_obj(((t_obj*)objptr)->v, -(vmin[0] + vmax[0]) / 2, \
										-(vmin[1] + vmax[1]) / 2, \
										-(vmin[2] + vmax[2]) / 2);
	return (NULL);
}

t_void		*rewrite_objects(t_void *objfile)
{
	return (for_list((t_void*)(((t_objfile*)objfile)->obj), center_obj));
}

void	triangularize(t_obj* obj)
{
	t_face	*f;
	t_face	*new_f;
	int		id;

	f = obj->f;
	while (f->next)
		f = f->next;
	id = f->id;
	f = obj->f;
	while (f)
	{
		if (f->d != 0)
		{
			id++;
			new_f = (t_face*)safe_malloc(sizeof(t_face));
			new_f->next = f->next;
			new_f->id = id;
			new_f->a = f->b;
			new_f->b = f->c;
			new_f->c = f->d;
			new_f->d = 0;
			f->c = f->d;
			f->d = 0;
			f->next = new_f;
			obj->f_amount++;
		}
		f = f->next;
	}
	if (obj->next)
		triangularize(obj->next);
}
