#include <libft.h>

int		is_empty(t_void *ptr)
{
	t_str	*s;

	s = (t_str*)ptr;
	if (s->str[0] == '\0')
		return (1);
	return (0);
}

t_void	*remove_list(t_void *ptr, int (condition)(t_void*), t_void* (delf)(t_void*))
{
	t_void	*before;
	t_void	*current;

	before = NULL;
	current = ptr;
	while (current)
		if (condition(current) && before == NULL)
		{
				ptr = delf(current);
				current = ptr;
		}
		else
		{
			if (condition(current))
				before->next = delf(current);
			else
				before = current;
			current = before->next;
		}
	return (ptr);
}
