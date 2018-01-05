/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:05:10 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:06:00 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_rgb			*get_color(t_rgb *rgb, char *name)
{
	while (rgb)
	{
		if (strcmp(name, rgb->name) == 0)
			return (rgb);
		rgb = rgb->next;
	}
	return (NULL);
}

static void		build_rgb(t_rgb *rgb, t_str *ptr)
{
	static int	id = 0;
	char		color[100];

	ft_bzero(color, sizeof(char) * 100);
	rgb->next = NULL;
	rgb->id = id;
	id++;
	sscanf(ptr->str, "%hhu %hhu %hhu %100[0-9a-zA-Z ]", \
		&(rgb->r), &(rgb->g), &(rgb->b), color);
	rgb->name = ft_strdup(color);
	if (ptr->next)
	{
		rgb->next = (t_rgb*)safe_malloc(sizeof(t_rgb));
		build_rgb(rgb->next, ptr->next);
	}
}

t_rgb			*init_rgb(void)
{
	char	*file;
	t_str	*lst;
	t_rgb	*rgb;

	file = (is_readable(COLOR_RGB_1)) ? COLOR_RGB_1 : COLOR_RGB_2;
	if (!is_readable(file))
		ft_errexit(RGB_FILE_OPEN, RED, RGB_FILE_ERR);
	lst = ft_getfile(file);
	remove_comments(lst, "!");
	remove_white_spaces(lst);
	lst = (t_str*)remove_list((t_void*)lst, is_empty, free_t_str);
	if (!lst)
		ft_errexit(RGB_FILE_EMPTY, RED, RGB_FILE_ERR);
	rgb = (t_rgb*)safe_malloc(sizeof(t_rgb));
	build_rgb(rgb, lst);
	ft_free_list(lst, free_t_str);
	return (rgb);
}
