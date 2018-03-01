/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangularize_face.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:08:52 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/01 12:54:25 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		divide_square(int id, t_face *f)
{
	t_face	*new_f;

	new_f = (t_face*)safe_malloc(sizeof(t_face));
	new_f->next = f->next;
	f->next = new_f;
	new_f->id = id;
	new_f->a = f->b;
	new_f->b = f->c;
	new_f->c = f->d;
	new_f->d = 0;
	new_f->v1 = NULL;
	new_f->v2 = NULL;
	new_f->v3 = NULL;
	new_f->v4 = NULL;
	f->c = f->d;
	f->d = 0;
}

void			triangularize(t_obj *obj)
{
	t_face	*f;
	int		id;

	while (obj)
	{
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
				divide_square(id, f);
				obj->f_amount++;
			}
			f = f->next;
		}
		obj = obj->next;
	}
}
