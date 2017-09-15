#include <libft.h>

void	ft_chkptr(void *ptr, char *message, int code)
{
	if (ptr == NULL)
		ft_errexit(message, RED, code);
}

void	*safe_malloc(int size)
{
	void	*ptr;

	ptr = malloc(size);
	ft_chkptr(ptr, "Error : malloc failed\n", MALLOC_FAIL);
	return (ptr);
}
