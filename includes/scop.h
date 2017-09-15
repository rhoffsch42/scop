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
# include <string.h>
# include <errno.h>
# include <stdbool.h>

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

# define SCOP_DIR		"-d"
# define OBJ_BAD_FORMAT	100
# define OBJ_ERROR		"Error : bad obj format"
# define SCOP_DIR_ERR	"option -d : missing argument\nUsage: scop file.obj [file.mtl] [-d path]"
# define SCOP_BAD_ARG	" : invalid argument\nUsage: scop file.obj [file.mtl] [-d path]"

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
	char				*mtllib;// changer aussi
	char				*material;//changer en struct material
	int					smooth;
	t_vertix			*v;
	t_face				*f;
	struct s_obj		*next;
}						t_obj;

//un object d'un fichier peut avoir le meme nom qu un autre dans un fichier different ?
typedef struct			s_objfile
{
	int					id;
	char				*path;
	char				*name;
	t_obj				*obj;
	struct s_objfile	*next;
}						t_objfile;

typedef struct			s_mat
{
	int					id;
	char				*name;
	float				ns;
	float				c1[3];
	float				c2[3];
	float				c3[3];
	float				ni;
	float				d;
	int					illum;
	struct s_mat		*next;
}						t_mat;

//un materiaux d'un fichier peut avoir le meme nom qu un autre dans un fichier different
typedef struct			s_mtlfile
{
	int					id;
	char				*path;
	char				*name;
	t_mat				*mat;
	struct s_mtlfile	*next;
}						t_mtlfile;

typedef struct			s_env
{
	t_obj				*obj;// faire pareil que .mtl? ie. struct .obj
	t_objfile			*objfile;
	t_mtlfile			*mtlfile;
}						t_env;

////debug, a delete apres

//
int			is_empty(T_LIST ptr);
T_LIST		del(T_LIST ptr);
T_LIST		remove_list(T_LIST ptr, int (condition)(T_LIST), T_LIST (del)(T_LIST));
char		*basename(char *path);
int			is_dir(void);
int			is_readable(char *path);
int			is_typefile(char *file, char *type);

t_env		*init_env(void);
void		load_file(t_env *e, int ac, char **av);
int			is_typefile(char *file, char *type);
void		add_objfile(t_objfile **addr, char *file);
void		add_mtlfile(t_mtlfile **addr, char *file);
t_objfile	*get_objfile(t_objfile *ptr, char *file);
t_mtlfile	*get_mtlfile(t_mtlfile *ptr, char *file);
int			chk_objfile(t_objfile *objfile, char *path);
int			chk_mtlfile(t_mtlfile *mtlfile, char *path);

t_obj		*build_object(char *path);
void		error_obj(char *s1, char *s2);
t_str		*add_vertix(t_obj *obj, t_str *ptr);
t_str		*add_face(t_obj *obj, t_str *ptr);
t_str		*link_mtlfile(t_obj *obj, t_str *ptr);
t_str		*link_material(t_obj *obj, t_str *ptr);
t_str		*add_smooth(t_obj *obj, t_str *ptr);
t_str		*add_name(t_obj *obj, t_str *ptr);

#endif
