#include <scop.h>

int		is_empty(t_void *ptr)
{
	t_str	*s;

	s = (t_str*)ptr;
	if (ft_strlen(s->str) == 0)
		return (1);
	return (0);
}

t_void	*del(t_void *ptr)
{
	t_str	*s;

	s = (t_str*)ptr;
	ft_strclr(s->str);
	return (ptr->next);
}

t_void	*remove_list(t_void *ptr, int (condition)(t_void*), t_void* (del)(t_void*))
{
	t_void	*before;
	t_void	*current;

	before = NULL;
	current = ptr;
	while (current)
		if (condition(current) && before == NULL)
		{
				ptr = del(current);
				free(current);
				current = ptr;
		}
		else
		{
			if (condition(current))
			{
					before->next = del(current);
					free(current);
			}
			else
				before = current;
			current = before->next;
		}
	return (ptr);
}
