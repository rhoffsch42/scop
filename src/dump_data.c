/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:04:35 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/24 16:12:47 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	dump_data_mtl(t_mat *mat)
{
	printf("\tDATAS :\n");
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
		printf("<=============>\n");
	}
}

void	dump_data_obj(t_obj *obj)
{
	t_vertix	*v;
	t_face		*f;

	printf("\tDATAS :\n");
	printf("ID:      \t%d\n", obj->id);
	printf("Name:    \t%s\n", obj->name);
	printf("Mtl library:\t%s\n", obj->mtllib ? obj->mtllib : "\'N/D\'");
	if (obj->mat_name)
		printf("Material:\t%s (id: %d)\n", \
			obj->mat_name, obj->mat ? obj->mat->id : -1);
	else
		printf("Material:\t%s\n", "\'N/D\'");
	printf("Smooth: \t%s\n", obj->smooth == 0 ? "off" : "on");
	printf("Vertix amount:\t%d\n", obj->v_amount);
	printf("Faces amount:\t%d\n", obj->f_amount);
	if (DATA == 0 || DATA_RESOURCES == 0)
		return ;
	v = obj->v;
	printf("vertix %d:\t%f\t%f\t%f\n", v->id, v->x, v->y, v->z);
	while ((v = v->next))
		printf("vertix %d:\t%f\t%f\t%f\n", v->id, v->x, v->y, v->z);
	f = obj->f;
	printf("face   %d:\t%d\t%d\t%d\t%d\n", f->id, f->a, f->b, f->c, f->d);
	while ((f = f->next))
		printf("face   %d:\t%d\t%d\t%d\t%d\n", f->id, f->a, f->b, f->c, f->d);
}

void	dump_datafile2(t_str *dir, t_xpm *xpm)
{
	while (dir)
	{
		printf("-d %s\n", dir->str);
		dir = dir->next;
	}
	while (xpm)
	{
		printf("%s\n", xpm->path);
		xpm = xpm->next;
	}
	printf("*******************************************\n");
}

void	dump_datafile(t_objfile *objfile, t_mtlfile *mtlfile, t_str *dir, \
						t_xpm *xpm)
{
	printf("*******************************************\n");
	while (objfile)
	{
		printf("type:   \tobjfile\n");
		printf("id:     \t%d\n", objfile->id);
		printf("path:   \t%s\n", objfile->path);
		printf("name:   \t%s\n", objfile->name);
		dump_data_obj(objfile->obj);
		objfile = objfile->next;
		printf("- - - - - - - - - - - - - - - - - - - -\n");
	}
	printf("*******************************************\n");
	while (mtlfile)
	{
		printf("type:   \tmtlfile\n");
		printf("id:     \t%d\n", mtlfile->id);
		printf("path:   \t%s\n", mtlfile->path);
		printf("name:   \t%s\n", mtlfile->name);
		dump_data_mtl(mtlfile->mat);
		printf("- - - - - - - - - - - - - - - - - - - -\n");
		mtlfile = mtlfile->next;
	}
	printf("*******************************************\n");
	dump_datafile2(dir, xpm);
}
