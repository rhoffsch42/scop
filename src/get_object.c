#include <scop.h>

void		error_obj(char *s1, char *s2)
{
	ft_putstr_fd("________ERROR OBJ________\n", STDERR_FILENO);
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putchar_fd(10, STDERR_FILENO);
	// ft_errexit(s2, YELLOW, OBJ_BAD_FORMAT);
}

t_obj	*init_obj(void)
{
	static int	id = 0;
	t_obj	*object;

	ft_chkmalloc(object = (t_obj*)malloc(sizeof(t_obj)));
	object->id = id;
	object->name = ft_strdup("Default name");
	object->mtllib = NULL;
	object->material = NULL;
	object->smooth = 0;
	object->v = NULL;
	object->f = NULL;
	id++;
	return (object);
}

static void		build_data(t_obj *obj, t_str *ptr)
{
	char	keyword[100];

	while (ptr)
	{
		ft_putendl(ptr->str);
		sscanf(ptr->str, "%s", keyword);
		if (ft_strcmp(keyword, OBJ_MTLFILE) == 0)
			ptr = add_mtlfile(obj, ptr);
		else if (ft_strcmp(keyword, OBJ_NEW) == 0)
		{
			error_obj(ptr->str, OBJ_ERROR);
			ptr = ptr->next;
		}
		else if (ft_strcmp(keyword, OBJ_VERTIX) == 0)
			ptr = add_vertix(obj, ptr);
		else if (ft_strcmp(keyword, OBJ_FACE) == 0)
			ptr = add_face(obj, ptr);
		else if (ft_strcmp(keyword, OBJ_MTLUSE) == 0)
			ptr = add_material(obj, ptr);
		else if (ft_strcmp(keyword, OBJ_SMOOTH) == 0)
		{
			error_obj(ptr->str, OBJ_ERROR);
			ptr = ptr->next;
		}
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
	new_obj = init_obj();
	build_data(new_obj, lst);
	return (new_obj);
}
