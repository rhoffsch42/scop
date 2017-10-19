#include <scop.h>

static int	linelen(char *s)
{
	int		i;

	i = 0;
	while (s[i] != 10 && s[i] != '\0')
		i++;
	return (i);
}

char	*t_str_to_char(t_str *ptr)
{
	t_str	*ptr1;
	char	*all;
	int		len;

	ptr1 = ptr;
	len = 0;
	while (ptr1)
	{
		len += ft_strlen(ptr1->str);
		len++;
		ptr1 = ptr1->next;
	}
	all = (char*)safe_malloc(sizeof(char) * (len + 1));
	ft_bzero(all, len + 1);
	ptr1 = ptr;
	while (ptr1)
	{
		ft_strcat(all, ptr1->str);
		ft_strcat(all, "\n");
		ptr1 = ptr1->next;
	}
	return (all);
}

t_str	*char_to_t_str(char *str)
{
	t_str	*lst;
	t_str	*ptr;
	int		i;
	int		j;

	ptr = (t_str*)safe_malloc(sizeof(t_str));
	lst = ptr;
	ptr->str = (char*)safe_malloc(sizeof(char) * (linelen(str) + 1));
	i = 0;
	j = 0;
	while (str[i++])
		if (str[i] == '\n')
		{
			ptr->str[j] = '\0';
			ptr->next = (t_str*)safe_malloc(sizeof(t_str));
			ptr = ptr->next;
			ptr->str = \
				(char*)safe_malloc(sizeof(char) * (linelen(str + i + 1) + 1));
			j = 0;
		}
		else
			ptr->str[j++] = str[i];
	(ptr->str)[j] = '\0';
	ptr->next = NULL;
	return (lst);
}

static int		init(char *start, char *end, char *front, int *len)
{
	if (ft_strchr(front, DOUBLE_QUOTE))
		ft_errexit(ft_strjoin(XPM_TOKEN_ERR, front), RED, DATA_CORRUPT);
	if (ft_strchr(start, DOUBLE_QUOTE))
		ft_errexit(ft_strjoin(XPM_TOKEN_ERR, start), RED, DATA_CORRUPT);
	if (ft_strchr(end, DOUBLE_QUOTE))
		ft_errexit(ft_strjoin(XPM_TOKEN_ERR, end), RED, DATA_CORRUPT);
	len[0] = ft_strlen(start);
	len[1] = ft_strlen(end);
	len[2] = ft_strlen(front);
	return (0);
}

void	remove_comments_vl(char *str, char *start, char *end, char *front)
{
	int		i;
	int		dq[2];
	int		len[3];

	i = init(start, end, front, len);
	dq[0] = -1;
	while (str[i])
	{
		if (dq[0] == -1)
		{
			if (strncmp(str + i, start, len[0]) == 0)
			{
				ft_memset(str + i, ' ', len[0]);
				while (str[i] && strncmp(str + i, end, len[1]) != 0)
					str[i++] = ' ';
				if (str[i])
					ft_memset(str + i, ' ', len[1]);
			}
			if (strncmp(str + i, front, len[2]) == 0)
				while (str[i] != '\0' && str[i] != '\n')
					str[i++] = ' ';
		}
		dq[0] *= (str[i] == DOUBLE_QUOTE && dq[1] == 1) ? -1 : 1;
		dq[1] = (str[i++] == '\\') ? 0 : 1;
	}
}
