/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:02:18 by rhoffsch          #+#    #+#             */
/*   Updated: 2015/09/25 07:41:26 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

# define WHITESPACES "\v\r\f \n\t\0"
# define BUFF_SIZE 65
# define COLOR(X, FD) ft_strcolor("\033[", X, "m", FD)
# define BLACK "30"
# define RED "31"
# define GREEN "32"
# define YELLOW "33"
# define BLUE "34"
# define MAGENTA "35"
# define CYAN "36"
# define WHITE "37"
# define NOCOLOR "0"

# define OK				0
# define BAD_ARGS		1
# define OPEN_FAIL		2
# define MALLOC_FAIL	3

typedef struct		s_void
{
	struct s_void	*next;
}					t_void;

typedef struct		s_istr
{
	struct s_istr	*next;
	int				*istr;
	int				size;
}					t_istr;

typedef struct		s_list
{
	struct s_list	*next;
	void			*content;
	size_t			content_size;
}					t_list;

typedef struct		s_str
{
	struct s_str	*next;
	char			*str;
}					t_str;

t_str				*ft_getfile(char *filename);
void				remove_comments(t_str *ptr, char *comment_str);
void				remove_white_spaces(t_str *ptr);
t_void				*remove_list(t_void *ptr, int (condition)(t_void*), \
								t_void *(del)(t_void*));
t_void				*del(t_void *ptr);
int					is_empty(t_void *ptr);
int					ft_listlen(void *list);
void				ft_chkptr(void *ptr, char *message, int code);
void				*safe_malloc(int size);
void				ft_errexit(const char *message, char *color, int code);
void				ft_free_tab(char **tab);
int					get_next_line(int const fd, char **line);
void				ft_putchar(char c);
void				ft_nputchar(char c, int n);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putnbrendl(int n);
void				ft_bigputnbr(long long n);
void				ft_puttab(char **tab);
int					ft_strlen(const char *s);
int					ft_tablen(char **tab);
char				*ft_strdup(const char *s1);
char				*ft_strndup(char *src, int start, int end);
void				ft_strswap(char **s1, char **s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strjoin_free(char *s1, char *s2, int n);
char				**ft_tabjoin(char *s, char **tab);
void				ft_clear_tab(char ***tab);
char				*ft_strtrim(const char *s);
char				*ft_strtrim_extended(const char *s, char *spaces);
char				**ft_strsplit(const char *s, char c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_int_strchr(int *istr, int size, int n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isdigit_str(char *str);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_atoi(const char *str);
t_istr				ft_atoi_str(char **tab);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_tabdel(char ***tab);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_itoa(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_putstr_color(char *str, char *color, int fd);
void				ft_putchar_color(char c, char *color);
void				ft_strcolor(char *c1, char *color, char *c2, int fd);
t_istr				*ft_int_strdup(int *str, int size);
double				ft_fabs(double n);
int					ft_abs(int n);

#endif
