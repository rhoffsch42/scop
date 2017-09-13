#include <libft.h>

void	ft_chkmalloc(void *ptr)
{
	if (ptr == NULL)
		ft_errexit("Error: malloc failed\n", RED, MALLOC_FAIL);
}
