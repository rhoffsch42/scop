#include <libft.h>

int	ft_listlen(void *list)
{
	int		i;
	t_void	*ptr;

	ptr = (t_void*)list;
	i = 0;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}
