#include <scop.h>

void	free_t_str(void	*list)
{
	t_str	*ptr;

	ptr = (t_str*)list;
	ft_strclr(ptr->str);
	free(ptr->str);
	ptr->str = NULL;
	ptr->next = NULL;
	free(ptr);
}

void	ft_free_list(void *list, void (custom_free)(void*))
{
	t_void	*ptr;
	t_void	*f;

	ptr = (t_void*)list;
	while (ptr)
	{
		f = ptr;
		ptr = ptr->next;
		custom_free(f);
	}
}
