/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:58 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:09:41 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_str		*ft_getfile(char *filename)
{
	t_str	*ptr[3];
	char	*buf;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_errexit("Error: open failed", RED, OPEN_FAIL);
	ptr[2] = NULL;
	while (get_next_line(fd, &buf) > 0)
	{
		ptr[0] = (t_str*)safe_malloc(sizeof(t_str));
		ptr[0]->str = ft_strdup(buf);
		ptr[0]->next = NULL;
		if (ptr[2] == NULL)
		{
			ptr[1] = ptr[0];
			ptr[2] = ptr[0];
		}
		else
		{
			ptr[1]->next = ptr[0];
			ptr[1] = ptr[1]->next;
		}
	}
	close(fd);
	return (ptr[2]);
}

void		remove_comments(t_str *ptr, char *comment_str)
{
	char	*ptr1;

	while (ptr)
	{
		ptr1 = ft_strstr(ptr->str, comment_str);
		if (ptr1)
			ptr1[0] = 0;
		ptr = ptr->next;
	}
}

void		remove_white_spaces(t_str *ptr)
{
	char	*str;

	while (ptr)
	{
		str = ptr->str;
		ptr->str = ft_strtrim_extended(ptr->str, WHITESPACES);
		free(str);
		ptr = ptr->next;
	}
}
