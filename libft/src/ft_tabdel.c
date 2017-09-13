#include <libft.h>

void	ft_tabdel(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i] != NULL)
	{
		ft_strdel(&(*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}
