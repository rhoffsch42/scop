/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:09:16 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:09:18 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	error_xpm(char *s1, char *s2)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putchar_fd(10, STDERR_FILENO);
	ft_errexit(s2, RED, XPM_BAD_FORMAT);
}

char	*chk_separator(char *str)
{
	int	len;
	int	i;

	i = 1;
	len = ft_strlen(str);
	if (str[len - i] == ',')
		i++;
	if (str[0] != '"' || str[len - i] != '"')
		error_xpm(str, XPM_ERROR);
	str[len - i] = '\0';
	return (str + 1);
}

/*
**	possible char for tokens?
**	"%1[].+@#$\%&*=-;:>,<!~`^/()_'|{} a-zA-Z0-9[] %s %s\0"
*/

t_str	*build_tokens(t_rgb **rgb_ptr, int token_amount, t_str *ptr, int t_size)
{
	int		id;
	char	*s;

	startf("build_tokens");
	id = 0;
	while (token_amount > 0)
	{
		s = chk_separator(ptr->str);
		rgb_ptr[0]->next = NULL;
		rgb_ptr[0]->id = id++;
		rgb_ptr[0]->name = ft_strdup(s);
		rgb_ptr[0]->name[t_size] = '\0';
		if (s[3 + t_size] == '#')
			hex_to_rgb((unsigned char*)&(rgb_ptr[0]->r), s + 4 + t_size);
		// hex_to_rgb: attention au padding dans la structure, comportement aleatoire ?
		else if ((rgb_ptr[2] = get_color(rgb_ptr[1], s + 3 + t_size)) != NULL)
		{
			rgb_ptr[0]->r = rgb_ptr[2]->r;
			rgb_ptr[0]->g = rgb_ptr[2]->g;
			rgb_ptr[0]->b = rgb_ptr[2]->b;
		}
		else
			error_xpm(s, XPM_ERROR);
		// ft_putstr(rgb_ptr[0]->name);SPACE
		// ft_putstr(s + 3 + t_size);SPACE
		// ft_putnbr(rgb_ptr[0]->r);SPACE
		// ft_putnbr(rgb_ptr[0]->g);SPACE
		// ft_putnbr(rgb_ptr[0]->b);ENDL
		rgb_ptr[0]->next = (t_rgb*)safe_malloc(sizeof(t_rgb));
		rgb_ptr[0] = rgb_ptr[0]->next;
		token_amount--;
		ptr = ptr->next;
	}
	deep--;
	return (ptr);
}

static void		build_xpm(t_xpm *x, t_str *ptr, t_rgb *chart)
{
	int		token_amount;
	int		t_size;
	t_rgb	*rgb_tokens[4];
	t_str	*line;

	startf("build_xpm");
	if (strncmp("static", ptr->str, ft_strlen("static")) != 0)
		error_xpm(ptr->str, XPM_ERROR);
	if (sscanf(chk_separator(ptr->next->str), "%d %d %d %d", \
		&(x->width), &(x->height), &token_amount, &t_size) != 4)
		error_xpm(ptr->next->str, XPM_ERROR);
	if (token_amount <= 0 || t_size <= 0 || x->width <= 0 || x->height <= 0)
		error_xpm(ptr->next->str, XPM_ERROR);
	rgb_tokens[3] = (t_rgb*)safe_malloc(sizeof(t_rgb));
	rgb_tokens[0] = rgb_tokens[3];
	rgb_tokens[1] = chart;
	rgb_tokens[2] = NULL;
	line = build_tokens(rgb_tokens, token_amount, ptr->next->next, t_size);
	line = build_pixels(x, rgb_tokens[3], t_size, line);
	ft_free_list(rgb_tokens[3], free_t_rgb);
	deep--;
}

t_xpm		*load_xpm(char *path, t_rgb *chart)
{
	t_str	*str;
	t_str	*lst;
	char	*all;
	t_xpm	*xpm;

	startf("load_xpm");
	if (!is_typefile(path, ".xpm"))
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_errexit(" is not a valid xpm file", RED, BAD_ARGS);
	}
	str = ft_getfile(path);
	all = t_str_to_char(str);
	remove_comments_vl(all, "/*", "*/", "//");
	lst = char_to_t_str(all);
	remove_white_spaces(lst);
	lst = (t_str*)remove_list((t_void*)lst, is_empty, free_t_str);
	xpm = init_xpm();
	xpm->path = ft_strdup(path);
	xpm->name = ft_strdup(basename(path));
	xpm->next = NULL;
	build_xpm(xpm, lst, chart);
	ft_free_list(lst, free_t_str);
	ft_free_list(str, free_t_str);
	free(all);
	deep--;
	return (xpm);
}
