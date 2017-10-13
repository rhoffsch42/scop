#include <scop.h>

t_void		*get_link(t_void* list, int index)
{
	int		i;

	if (index < 0)
		return (NULL);
	i = 0;
	while (list)
	{
		if (i == index)
			return (list);
		i++;
		list = list->next;
	}
	return (NULL);
}


t_arg		init_args(void *a1, void *a2, void *a3, void *a4)
{
	t_arg	s;
	s.next = NULL;
	s.ptr[0] = a1;
	s.ptr[1] = a2;
	s.ptr[2] = a3;
	s.ptr[3] = a4;
	s.ptr[4] = NULL;
	s.ptr[5] = NULL;
	s.ptr[6] = NULL;
	s.ptr[7] = NULL;
	s.ptr[8] = NULL;
	s.ptr[9] = NULL;
	return (s);
}

t_void		*for_list_args(t_void *ptr, t_arg args, \
							t_void* (*func)(t_void*, t_arg args))
{
	void	*ret;

	while (ptr)
	{
		if ((ret = func(ptr, args)) != NULL)
			return (ret);
		ptr = ptr->next;
	}
	return (NULL);
}

t_void		*for_list(t_void *ptr, t_void* (*func)(t_void*))
{
	t_void	*ret;

	while (ptr)
	{
		if ((ret = func(ptr)) != NULL)
			return (ret);
		ptr = ptr->next;
	}
	return (NULL);
}
/*
	en faisant un for_list dans un for_list, on peut return un pointeur
	du deuxieme  for_list (profondeur 2), comment connaitre le type ?

	- dans for_list donner une valeur a une globale pour identifier le type
	- metre un 'int type;' dans chaque liste, et se referer a une table,
		le 'int type;' doit se trouver au meme endroit dans la structure
		par ex: juste apres le next
		=> header commun a toute liste
*/
