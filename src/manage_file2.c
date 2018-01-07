/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:08:08 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:08:11 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

int		chk_objfile(t_objfile *objfile, char *path)
{
	t_objfile	*ptr;

	ptr = get_objfile(objfile, path);
	if (ptr)
	{
		COLOR(YELLOW, STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(" : name already in use (", STDERR_FILENO);
		ft_putstr_fd(ptr->path, STDERR_FILENO);
		ft_putstr_fd(")\nEntry ignored\n\n", STDERR_FILENO);
		COLOR(NOCOLOR, STDERR_FILENO);
		return (0);
	}
	return (1);
}

int		chk_mtlfile(t_mtlfile *mtlfile, char *path)
{
	t_mtlfile	*ptr;

	ptr = get_mtlfile(mtlfile, path);
	if (ptr)
	{
		COLOR(YELLOW, STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(" : name already in use (", STDERR_FILENO);
		ft_putstr_fd(ptr->path, STDERR_FILENO);
		ft_putstr_fd(")\nEntry ignored\n\n", STDERR_FILENO);
		COLOR(NOCOLOR, STDERR_FILENO);
		return (0);
	}
	return (1);
}

t_xpm	*get_xpmfile(t_xpm *ptr, char *path)
{
	startf("get_xpmfile");
	while (ptr)
	{
		if (strcmp(path, ptr->path) == 0)
		{
			ft_putendl("Found!");
			return (ptr);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

int		chk_xpmfile(t_xpm *xpmfile, char *path)
{
	t_xpm	*ptr;

	startf("chk_xpmfile");
	ptr = get_xpmfile(xpmfile, path);
	if (ptr)
	{
		COLOR(YELLOW, STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(" : name already in use (", STDERR_FILENO);
		ft_putstr_fd(ptr->path, STDERR_FILENO);
		ft_putstr_fd(")\nEntry ignored\n\n", STDERR_FILENO);
		COLOR(NOCOLOR, STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	add_xpmfile(t_xpm **addr, char *file, t_rgb *chart)
{
	static int	id = 0;
	t_xpm		*new_xpmfile;

	startf("add_xpmfile");
	if (!chk_xpmfile(*addr, file))
		return ;
	new_xpmfile = load_xpm(file, chart);
	new_xpmfile->id = id;
	id++;
	new_xpmfile->next = *addr;
	*addr = new_xpmfile;
}
