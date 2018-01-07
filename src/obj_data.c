/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:08:49 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:08:51 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_str	*add_mtlfile_name(t_obj *obj, t_str *ptr)
{
	char	token[100];
	char	path[500];

	ft_bzero(token, 100);
	ft_bzero(path, 500);
	sscanf(ptr->str, "%s %s", token, path);
	if (ft_strlen(path) > 0)
		obj->mtllib = ft_strdup(path);
	return (ptr->next);
}

t_str	*add_material_name(t_obj *obj, t_str *ptr)
{
	char	token[100];
	char	path[500];

	ft_bzero(token, 100);
	ft_bzero(path, 500);
	sscanf(ptr->str, "%s %s", token, path);
	if (ft_strlen(path) > 0)
		obj->mat_name = ft_strdup(path);
	return (ptr->next);
}

t_str	*add_smooth(t_obj *obj, t_str *ptr)
{
	char	token[20];
	char	token2[10];

	ft_bzero(token, 20);
	ft_bzero(token2, 10);
	sscanf(ptr->str, "%s %s", token, token2);
	if (strcmp(token2, "on") == 0)
		obj->smooth = 1;
	else if (strcmp(token2, "off") == 0)
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

	startf("add_vertix");
	v = (t_vertix*)safe_malloc(sizeof(t_vertix));
	id = 1;
	obj->v = v;
	while (ptr)
	{
		sscanf(ptr->str, "%s", token);
		if (strcmp(token, OBJ_VERTIX) != 0)
			break ;
		if (id != 1)
		{
			v->next = (t_vertix*)safe_malloc(sizeof(t_vertix));
			v = v->next;
		}
		ft_bzero(v, sizeof(t_vertix));
		v->id = id;
		sscanf(ptr->str, "%s %f %f %f", token, &(v->x), &(v->y), &(v->z));
		v->next = NULL;
		ptr = ptr->next;
		obj->v_amount++;
		id++;
	}
	deep--;
	return (ptr);
}

t_vertix	*init_vertix(int id, float x, float y, float z)
{
	t_vertix	*vertix;

	vertix = (t_vertix*)safe_malloc(sizeof(t_vertix));
	ft_bzero(vertix, sizeof(t_vertix));
	vertix->next = NULL;
	vertix->x = x;
	vertix->y = y;
	vertix->z = z;
	vertix->id = id;
	return (vertix);
}
t_str	*add_vertix2(t_obj *obj, t_str *ptr)
{
	char		token[250];
	t_vertix	*v;
	t_vertix	*last;
	int			id;
	float		x, y, z;

	startf("add_vertix");
	id = 1;
	while (ptr)
	{
		sscanf(ptr->str, "%s", token);
		if (strcmp(token, OBJ_VERTIX) != 0)
			break ;
		sscanf(ptr->str, "%s %f %f %f", token, &(x), &(y), &(z));
		v = init_vertix(id, x, y, z);
		if (id == 1)
			obj->v = v;
		else
			last->next = v;
		last = v;
		//////////////
		obj->v_amount++;
		id++;
		ptr = ptr->next;
	}
	deep--;
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
		if (strcmp(token, OBJ_FACE) != 0)
			break ;
		if (++id != 1 && (f->next = (t_face*)safe_malloc(sizeof(t_face))))
			f = f->next;
		ft_bzero(f, sizeof(t_face));
		f->id = id;
		f->next = NULL;
		sscanf(ptr->str, "%s %d %d %d %d", token, \
			&(f->a), &(f->b), &(f->c), &(f->d));
		if (f->a == 0 || f->b == 0 || f->c == 0)
			error_obj(ptr->str, OBJ_ERROR);
		ptr = ptr->next;
		obj->f_amount++;
	}
	return (ptr);
}
