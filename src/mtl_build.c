#include <scop.h>

void		error_mtl(char *s1, char *s2)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putchar_fd(10, STDERR_FILENO);
	ft_errexit(s2, RED, MTL_BAD_FORMAT);
}

static void		build_data(t_mat **mat, t_str *ptr)
{
	char	keyword[100];

	while (ptr)
	{
		sscanf(ptr->str, "%s", keyword);
		if (ft_strcmp(keyword, MTL_MAT) == 0)
			ptr = add_mtlname(mat, ptr);
		else if (ft_strcmp(keyword, MTL_AMBIANT) == 0)
			ptr = add_color(ptr, (*mat)->ka);
		else if (ft_strcmp(keyword, MTL_DIFFUSE) == 0)
			ptr = add_color(ptr, (*mat)->kd);
		else if (ft_strcmp(keyword, MTL_SPECULAR) == 0)
			ptr = add_color(ptr, (*mat)->ks);
		else if (ft_strcmp(keyword, MTL_SPEC_EXP) == 0)
			ptr = add_value_f(ptr, &((*mat)->ns));
		else if (ft_strcmp(keyword, MTL_DENSITY) == 0)
			ptr = add_value_f(ptr, &((*mat)->ni));
		else if (ft_strcmp(keyword, MTL_OPACITY) == 0)
			ptr = add_value_f(ptr, &((*mat)->d));
		else if (ft_strcmp(keyword, MTL_ILLUM) == 0)
			ptr = add_value(ptr, &((*mat)->illum));
		else
			error_mtl(ptr->str, MTL_ERROR);
	}
}

t_mat			*build_material(char *path)
{
	t_str	*lst;
	t_mat	*new_mat;

	lst = ft_getfile(path);
	remove_comments(lst, COMMENT_CHAR);
	remove_white_spaces(lst);
	lst = remove_list(lst, is_empty, del);
	new_mat = NULL;
	build_data(&new_mat, lst);

	ft_free_list(lst, free_t_str);
	lst = NULL;
	return (new_mat);
}