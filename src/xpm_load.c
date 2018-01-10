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

void			error_xpm(char *s1, char *s2)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putchar_fd(10, STDERR_FILENO);
	ft_errexit(s2, RED, XPM_BAD_FORMAT);
}

char			*chk_separator(char *str)
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

t_str			*build_tokens(t_rgb **rgb_ptr, int tok_amount, t_str *ptr, \
								int tok_size)
{
	int		id;
	char	*s;

	startf("build_tokens");
	id = 0;
	while (tok_amount > 0)
	{
		s = chk_separator(ptr->str);
		rgb_ptr[0]->next = NULL;
		rgb_ptr[0]->id = id++;
		rgb_ptr[0]->name = strndup(s, tok_size);
		if (s[3 + tok_size] == '#')
			hex_to_rgb((unsigned char*)&(rgb_ptr[0]->r), s + 4 + tok_size);
		else if ((rgb_ptr[2] = get_color(rgb_ptr[1], s + 3 + tok_size)) != NULL)
			memcpy((void*)&(rgb_ptr[0]->r), (void*)&(rgb_ptr[2]->r), 3);
		else
			error_xpm(s, XPM_ERROR);
		if (--tok_amount)
		{
			rgb_ptr[0]->next = (t_rgb*)safe_malloc(sizeof(t_rgb));
			rgb_ptr[0] = rgb_ptr[0]->next;
		}
		ptr = ptr->next;
	}
	return (ptr);
}

static void		build_xpm(t_xpm *x, t_str *ptr, t_rgb *chart)
{
	int		tok_amount;
	int		tok_size;
	t_rgb	*rgb_tokens[4];
	t_str	*line;

	startf("build_xpm");
	if (strncmp("static", ptr->str, ft_strlen("static")) != 0)
		error_xpm(ptr->str, XPM_ERROR);
	if (sscanf(chk_separator(ptr->next->str), "%d %d %d %d", \
		&(x->width), &(x->height), &tok_amount, &tok_size) != 4)
		error_xpm(ptr->next->str, XPM_ERROR);
	if (tok_amount <= 0 || tok_size <= 0 || x->width <= 0 || x->height <= 0)
		error_xpm(ptr->next->str, XPM_ERROR);
	rgb_tokens[3] = (t_rgb*)safe_malloc(sizeof(t_rgb));
	rgb_tokens[0] = rgb_tokens[3];
	rgb_tokens[1] = chart;
	rgb_tokens[2] = NULL;
	line = build_tokens(rgb_tokens, tok_amount, ptr->next->next, tok_size);
	line = build_pixels(x, rgb_tokens[3], tok_size, line);
	ft_free_list(rgb_tokens[3], free_t_rgb);
}

t_xpm			*load_xpm(char *path, t_rgb *chart)
{
	t_str	*str;
	t_str	*lst;
	char	*all;
	t_xpm	*xpm;

	startf("load_xpm");
	if (!is_typefile(path, ".xpm"))
		ft_errexit(ft_strjoin(path, " is not a valid xpm file"), RED, BAD_ARGS);
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
	return (xpm);
}
