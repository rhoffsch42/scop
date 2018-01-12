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
	display_object(e->glfw, object_tab, texture_tab, \
		(int[2]){ft_listlen(e->objfile), ft_listlen(e->xpmfile)});
	printf("________________END________________\n");
	return (0);
}
