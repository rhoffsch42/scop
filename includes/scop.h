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

# define SCOP_DIR			"-d"
# define OBJ_BAD_FORMAT		100
# define DATA_CORRUPT		101
# define MTL_BAD_FORMAT		102
# define OBJ_ERROR			"Error : bad obj format"
# define MTL_ERROR			"Error : bad mtl format"
# define MTL_USED			"Error : name already in use"
# define DATA_CORRUPT_MSG	"Error : data corrupt"
# define SCOP_DIR_ERR		"option -d : missing argument\nUsage: scop file.obj [file.mtl] [-d path]"
# define SCOP_BAD_ARG		" : invalid argument\nUsage: scop file.obj [file.mtl] [-d path]"

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
# define MTL_AMBIANT	"Ka"
# define MTL_DIFFUSE	"Kd"
# define MTL_SPECULAR	"Ks"
# define MTL_SPEC_EXP	"Ns"
# define MTL_DENSITY	"Ni"
# define MTL_OPACITY	"d"
# define MTL_ILLUM		"illum"

typedef struct			s_vertix
{
	struct s_vertix		*next;
	int					id;
	float				x;
	float				y;
	float				z;
}						t_vertix;

typedef struct			s_face
{
	struct s_face		*next;
	int					id;
	int					a;
	int					b;
	int					c;
	int					d;
}						t_face;

typedef struct			s_mat
{
	struct s_mat		*next;
	int					id;
	char				*name;
	float				ka[3];// color ambiant (0.0 - 1.0) x3
	float				kd[3];// color diffuse (0.0 - 1.0) x3
	float				ks[3];// color specular (0.0 - 1.0) x3
	float				ns;// specular exponent (0 - 100)
	float				ni;// densite optique
	float				d;// opacite (0.0 - 1.0)
	int					illum;// lumiere param
}						t_mat;

//un materiaux d'un fichier peut avoir le meme nom qu un autre dans un fichier different
typedef struct			s_mtlfile
{
	struct s_mtlfile	*next;
	int					id;
	char				*path;
	char				*name;
	t_mat				*mat;
}						t_mtlfile;

typedef struct			s_obj
{
	struct s_obj		*next;
	int					id;
	char				*name;
	char				*mtllib;
	t_mtlfile			*mtlfile;
	char				*mat_name;
	t_mat				*mat;
	int					smooth;
	t_vertix			*v;
	t_face				*f;
	int					v_amount;
	int					f_amount;
}						t_obj;

//un object d'un fichier peut avoir le meme nom qu un autre dans un fichier different ?
typedef struct			s_objfile
{
	struct s_objfile	*next;
	int					id;
	char				*path;
	char				*name;
	t_obj				*obj;
}						t_objfile;

typedef struct			s_env
{
	t_obj				*obj;// faire pareil que .mtl? ie. struct .obj
	t_objfile			*objfile;
	t_mtlfile			*mtlfile;
	t_str				*dir;
}						t_env;

////debug, a delete apres

// libft
void		ft_free_list(void *list, void (custom_free)(void*));
void		free_t_str(void	*list);


// file manipulation
int			is_empty(T_LIST ptr);
T_LIST		del(T_LIST ptr);
T_LIST		remove_list(T_LIST ptr, int (condition)(T_LIST), T_LIST (del)(T_LIST));
char		*basename(char *path);
int			is_dir(void);
int			is_readable(char *path);
int			is_typefile(char *file, char *type);
char		*remove_trailing_slach(char *str);

t_env		*init_env(void);
t_obj		*init_obj(void);
t_mat		*init_mat(void);

//parsing args
void		load_file(t_env *e, int ac, char **av);
int			is_typefile(char *file, char *type);
void		add_objfile(t_objfile **addr, char *file);
void		add_mtlfile(t_mtlfile **addr, char *file);
t_objfile	*get_objfile(t_objfile *ptr, char *file);
t_mtlfile	*get_mtlfile(t_mtlfile *ptr, char *file);
int			chk_objfile(t_objfile *objfile, char *path);
int			chk_mtlfile(t_mtlfile *mtlfile, char *path);
void		link_file(t_env *e);

//parsing .obj
t_obj		*build_object(char *path);
void		error_obj(char *s1, char *s2);
t_str		*add_vertix(t_obj *obj, t_str *ptr);
t_str		*add_face(t_obj *obj, t_str *ptr);
t_str		*add_mtlfile_name(t_obj *obj, t_str *ptr);
t_str		*add_material_name(t_obj *obj, t_str *ptr);
t_str		*add_smooth(t_obj *obj, t_str *ptr);
t_str		*add_objname(t_obj *obj, t_str *ptr);

//parsing .mtl
t_mat		*build_material(char *path);
t_str		*add_mtlname(t_mat **mat, t_str *ptr);
t_str		*add_color(t_str *ptr, float *color);
t_str		*add_value(t_str *ptr, int *var);
t_str		*add_value_f(t_str *ptr, float *var);
void		error_mtl(char *s1, char *s2);

#endif
