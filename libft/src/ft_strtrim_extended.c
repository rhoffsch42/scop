#include <libft.h>

char	*ft_strtrim_extended(const char *s, char *spaces)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = (char*)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	while (ft_strchr(spaces, s[i]) != NULL)
		i++;
	while (s[i])
		dest[j++] = s[i++];
	dest[j] = 0;
	if (j != 0)
	{
		i = ft_strlen(dest) - 1;
		while (ft_strchr(spaces, dest[i]) != NULL)
			i--;
		dest[i + 1] = '\0';
	}
	return (dest);
}
