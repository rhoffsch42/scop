#include <scop.h>

void		error_obj(char *s1, char *s2)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putchar_fd(10, STDERR_FILENO);
	ft_errexit(s2, RED, OBJ_BAD_FORMAT);
}

static t_void		*link_vertix(t_void *f, t_arg args)
{
	t_face		*face;
	t_vertix	*vertix;

	face = (t_face*)f;
	vertix = (t_vertix*)(args.ptr[0]);
	face->v1 = (t_vertix*)get_link((t_void*)vertix, face->a - 1);
	face->v2 = (t_vertix*)get_link((t_void*)vertix, face->b - 1);
	face->v3 = (t_vertix*)get_link((t_void*)vertix, face->c - 1);
	face->v4 = (t_vertix*)get_link((t_void*)vertix, face->d - 1);
	if ((!(face->v1) && face->a != 0) || (!(face->v2) && face->b != 0) \
		|| (!(face->v3) && face->c != 0) || (!(face->v4) && face->d != 0))
	{
		ft_putstr("f ");
		ft_putnbr(face->a);
		ft_putchar(32);
		ft_putnbr(face->b);
		ft_putchar(32);
		ft_putnbr(face->c);
		ft_putchar(32);
		ft_putnbrendl(face->d);
		error_obj(OBJ_FACE_ERROR, OBJ_ERROR);
	}
	return (NULL);
}

static void		build_data(t_obj *obj, t_str *ptr)
{
	char	keyword[100];

	printf("__ build_data (obj)\n");
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

t_obj		*build_objects(char *path)
{
	t_str	*lst;
	t_obj	*new_obj;

	lst = ft_getfile(path);
	remove_comments(lst, COMMENT_CHAR);
	remove_white_spaces(lst);
	lst = (t_str*)remove_list((t_void*)lst, is_empty, free_t_str);
	// pour l instant un seul objet est cree, il faudra faire une boucle (ou autre)
	// pour avoir plusieurs objects dans un objfile
	new_obj = init_obj();
	build_data(new_obj, lst);
	triangularize(new_obj);
	if (ft_listlen(new_obj->v) != new_obj->v_amount || \
		ft_listlen(new_obj->f) != new_obj->f_amount)
		ft_errexit(DATA_CORRUPT_MSG, RED, DATA_CORRUPT);
	ft_free_list(lst, free_t_str);
	lst = NULL;
	for_list_args((t_void*)(new_obj->f), \
		init_args(new_obj->v, NULL, NULL, NULL), link_vertix);
	return (new_obj);
}
