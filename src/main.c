/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:58 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/01 12:52:17 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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

void test_rot(void)
{
	float		x = DTOR(90);
	float		y = DTOR(10);
	float		z = DTOR(-10);
	t_vector3	rot = vector3(x, y, z);
	t_vector3	rotinv = vector3(-x, -y, -z);

	t_vector3	vec1 = vector3(-1, -5, -10);
	t_vector3	vec2 = vector3_rotZYX(vec1, rot, 1);
	t_vector3	vec3 = vector3_rotZYX(vec1, rotinv, 1);

	vector3_print(vec1);
	vector3_print(rot);
	vector3_print(rotinv);
	printf("-----\n");
	vector3_print(vec2);
	vector3_print(vec3);
	exit(0);
}

int		main(int ac, char **av)
{
	// test_rot();
	t_env		*e;
	t_objfile	**object_tab;
	t_xpm		**texture_tab;

	ft_puttab(av);
	printf("________________BEGIN________________\n");
	e = init_env();
	load_file(e, ac, av);
	printf("___ dump_datafile\n");
	dump_datafile(e->objfile, e->mtlfile, e->dir, e->xpmfile);
	if (!e->objfile)
		ft_errexit(ft_strjoin(SCOP_NO_OBJ, USAGE), RED, BAD_ARGS);
	object_tab = (t_objfile**)list_to_tab((t_void*)(e->objfile));
	texture_tab = (t_xpm**)list_to_tab((t_void*)(e->xpmfile));
	e->glfw = init_glfw(NULL);
	e->glfw->cwd = e->cwd;
	display_object(e->glfw, object_tab, texture_tab, \
		(int[2]){ft_listlen(e->objfile), ft_listlen(e->xpmfile)});
	printf("________________END________________\n");
	return (0);
}