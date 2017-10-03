#include <scop.h>

void		*for_list(void *list, void* (*func)(void*))
{
	t_void	*ptr;
	void	*ret;

	ptr = (t_void*)list;
	while (ptr)
	{
		if ((ret = func((void*)ptr)) != 0)
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
