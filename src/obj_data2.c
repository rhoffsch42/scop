#include <scop.h>

t_str	*add_objname(t_obj *obj, t_str *ptr)
{
	char	token[100];
	char	name[500];

	ft_bzero(token, 100);
	ft_bzero(name, 500);
	sscanf(ptr->str, "%s %s", token, name);
	if (ft_strlen(name) > 0)
		obj->name = ft_strdup(name);
	return (ptr->next);
}
