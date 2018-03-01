/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:36 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/01 13:13:43 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_xpm	*init_xpm(void)
{
	static int	id = 0;
	t_xpm		*xpm;

	xpm = (t_xpm*)safe_malloc(sizeof(t_xpm));
	ft_bzero((void*)xpm, sizeof(t_xpm));
	xpm->next = NULL;
	xpm->name = NULL;
	xpm->path = NULL;
	xpm->data = NULL;
	xpm->id = id;
	id++;
	return (xpm);
}

t_env	*init_env(void)
{
	t_env	*e;

	e = (t_env*)safe_malloc(sizeof(t_env));
	e->objfile = NULL;
	e->mtlfile = NULL;
	e->xpmfile = NULL;
	e->dir = NULL;
	e->glfw = NULL;
	e->chart = init_rgb();
	e->cwd = get_current_directory();
	return (e);
}

t_obj	*init_obj(void)
{
	static int	id = 0;
	t_obj		*object;

	object = (t_obj*)safe_malloc(sizeof(t_obj));
	ft_bzero((void*)object, sizeof(t_obj));
	object->id = id;
	object->id_char = ft_itoa(id);
	object->name = ft_strjoin("Object #", object->id_char);
	object->mtllib = NULL;
	object->mtlfile = NULL;
	object->mat_name = NULL;
	object->mat = NULL;
	object->v = NULL;
	object->f = NULL;
	object->next = NULL;
	id++;
	return (object);
}

t_mat	*init_mat(void)
{
	static int	id = 0;
	t_mat		*material;

	material = (t_mat*)safe_malloc(sizeof(t_mat));
	ft_bzero((void*)material, sizeof(t_mat));
	material->id = id;
	material->id_char = ft_itoa(id);
	material->name = ft_strjoin("Material #", material->id_char);
	material->next = NULL;
	id++;
	return (material);
}
