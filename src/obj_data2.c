/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_data2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:08:52 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:08:55 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_str			*add_objname(t_obj *obj, t_str *ptr)
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

static void		translate_obj(t_vertix *vertix, float x, float y, float z)
{
	startf("translate_obj");
	while (vertix)
	{
		vertix->x += x;
		vertix->y += y;
		vertix->z += z;
		vertix = vertix->next;
	}
}

static t_void	*center_obj(t_void *objptr)
{
	t_vertix	*vertix;
	float		vmin[3];
	float		vmax[3];

	startf("center_obj");
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
				-(vmin[1] + vmax[1]) / 2, -(vmin[2] + vmax[2]) / 2);
	return (NULL);
}

t_void			*rewrite_objects(t_void *objfile)
{
	t_objfile	*objf;
	t_obj		*obj;

	startf("rewrite_objects");
	objf = (t_objfile*)objfile;
	obj = (t_obj*)objf->obj;
	return (for_list((t_void*)obj, center_obj));
}
