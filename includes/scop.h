/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2017/05/24 14:02:47 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <libft.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define ENDL			ft_putchar(10);
# define SPACE			ft_putchar(32);
# define T_LIST			t_str*

# define RGB(r, g, b)	(65536 * (int)(r) + 256 * (int)(g) + (int)(b))
# define RTOD(x)		(x * (180.0f / M_PI))
# define DTOR(x)		(x * M_PI / 180.0f)
# define ROT_WAY		1
# define ROT_RIGHT		-1
# define ROT_LEFT		1

# define DEF_WIN_TITLE	"Default title"
# define DEF_WIN_X		800
# define DEF_WIN_Y		800
# define MAX_WIN_X		1920
# define MAX_WIN_Y		1080
# define MIN_WIN_X		800
# define MIN_WIN_Y		800
# define FLOAT_MAX_LEN	7
# define COLOR_MAX		255
# define TITLE_MAX_LEN	50
# define TITLE_TRUNC	"[...]"
# define SCREEN_DIST	1.0f
# define FOV			90.0f

# define OBJ_BAD_FORMAT	100
# define OBJ_ERROR		"Error : bad obj format"

# define COMMENT_CHAR	'#'

# define OBJ_MTLFILE	"mtllib"
# define OBJ_NEW		"o"
# define OBJ_MTLUSE		"usemtl"
# define OBJ_VERTIX		"v"
# define OBJ_TEXTURE	"vt"
# define OBJ_NORMAL		"vn"
# define OBJ_FACE		"f"
# define OBJ_SMOOTH		"s"

# define MTL_MAT		"newmtl"
# define MTL_COLOR		"Kd"
# define MTL_xxxx1		"Ka"
# define MTL_xxxx2		"Ks"
# define MTL_xxxx3		"Ns"
# define MTL_xxxx4		"Ni"
# define MTL_TRANSP		"d"
# define MTL_xxxx5		"illum"

typedef struct			s_vertix
{
	int					id;
	float				x;
	float				y;
	float				z;
	struct s_vertix		*next;
}						t_vertix;

typedef struct			s_face
{
	int					id;
	int					a;
	int					b;
	int					c;
	int					d;
	struct s_face		*next;
}						t_face;

typedef struct			s_obj
{
	int					id;
	char				*name;
	char				*mtllib;//changer en struct mtllib
	char				*material;//changer en struct material
	int					smooth;
	t_vertix			*v;
	t_face				*f;

}						t_obj;

typedef struct			s_env
{
	int					a;
}						t_env;

////debug, a delete apres

//
int			is_empty(T_LIST ptr);
T_LIST		del(T_LIST ptr);
T_LIST		remove_list(T_LIST ptr, int (condition)(T_LIST), T_LIST (del)(T_LIST));

t_obj		*build_object(char *path);
void		error_obj(char *s1, char *s2);
t_str		*add_vertix(t_obj *obj, t_str *ptr);
t_str		*add_face(t_obj *obj, t_str *ptr);
t_str		*add_mtlfile(t_obj *obj, t_str *ptr);
t_str		*add_material(t_obj *obj, t_str *ptr);

#endif
