#include <scop.h>

int		is_empty(T_LIST ptr)
{
	if (ft_strlen(ptr->str) == 0)
		return (1);
	return (0);
}

T_LIST	del(T_LIST ptr)
{
	ft_strclr(ptr->str);
	return (ptr->next);
}

T_LIST	remove_list(T_LIST ptr, int (condition)(T_LIST), T_LIST (del)(T_LIST))
{
	T_LIST	before;
	T_LIST	current;

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
