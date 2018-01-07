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
		printf("<=============>\n");
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
		mtlfile = mtlfile->next;
		printf("- - - - - - - - - - - - - - - - - - - -\n");
	}
	printf("*******************************************\n");
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

void	startf(char *func_name)
{
	char	str[500];

	ft_bzero(str, 500);
	str[0] = '_';
	str[1] = ' ';
	strcpy(str + strlen(str), func_name);
	strcpy(str + strlen(str), "\t\t\t\t.\n");
	printf("%s", str);
}

int		main(int ac, char **av)
{
	// exit(0);
	ft_puttab(av);
	printf("________________BEGIN________________\n");
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
		printf("%d\n", rgb->r);
		printf("%d\n", rgb->g);
		printf("%d\n", rgb->b);
	}
	object_tab = (t_objfile**)list_to_tab((t_void*)(e->objfile));
	texture_tab = (t_xpm**)list_to_tab((t_void*)(e->xpmfile));
	e->glfw = init_glfw(NULL);
	(void)texture_tab;
	display_object(e->glfw, object_tab, texture_tab, \
		(int[2]){ft_listlen(e->objfile), ft_listlen(e->xpmfile)});
	// free_t_env((t_void*)e);
	printf("________________END________________\n");
	return (0);
}
