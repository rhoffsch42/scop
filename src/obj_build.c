#include <scop.h>

void		error_obj(char *s1, char *s2)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putchar_fd(10, STDERR_FILENO);
	ft_errexit(s2, RED, OBJ_BAD_FORMAT);
}

static void		build_data(t_obj *obj, t_str *ptr)
{
	char	keyword[100];

	while (ptr)
	{
		sscanf(ptr->str, "%s", keyword);
		if (ft_strcmp(keyword, OBJ_MTLFILE) == 0)
			ptr = add_mtlfile_name(obj, ptr);
		else if (ft_strcmp(keyword, OBJ_NEW) == 0)
			ptr = add_objname(obj, ptr);
		else if (ft_strcmp(keyword, OBJ_VERTIX) == 0)
			ptr = add_vertix(obj, ptr);
		else if (ft_strcmp(keyword, OBJ_FACE) == 0)
			ptr = add_face(obj, ptr);
		else if (ft_strcmp(keyword, OBJ_MTLUSE) == 0)
			ptr = add_material_name(obj, ptr);
		else if (ft_strcmp(keyword, OBJ_SMOOTH) == 0)
			ptr = add_smooth(obj, ptr);
		else
			error_obj(ptr->str, OBJ_ERROR);
	}
}

t_obj		*build_object(char *path)
{
	t_str	*lst;
	t_obj	*new_obj;

	lst = ft_getfile(path);
	remove_comments(lst, COMMENT_CHAR);
	remove_white_spaces(lst);
	lst = remove_list(lst, is_empty, del);
	// pour l instant un seul objet est cree, il faudra faire une boucle (ou autre)
	// pour avoir plusieurs objects dans un objfile
	new_obj = init_obj();
	build_data(new_obj, lst);
	if (ft_listlen(new_obj->v) != new_obj->v_amount || \
		ft_listlen(new_obj->f) != new_obj->f_amount)
		ft_errexit(DATA_CORRUPT_MSG, RED, DATA_CORRUPT);
	// free(lst);// faire ca correctement : free tout les str
	ft_free_list(lst, free_t_str);
	lst = NULL;
	return (new_obj);
}
