/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:58 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/08 13:09:44 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_xpm	*get_xpm(t_xpm **textures, int len, const char *name)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (strcmp(name, textures[i]->name) == 0)
			return (textures[i]);
		i++;
	}
	return (NULL);
}

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

int		main(int ac, char **av)
{
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
