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
# include <GL/glew.h>
# include <GLFW/glfw3.h>

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <stddef.h>
# include <math.h>

//memory
#include <sys/resource.h>
#include <errno.h>

/*
0	GL_POINTS
1	GL_LINES
2	GL_LINE_STRIP
3	GL_LINE_LOOP
4	GL_TRIANGLES
5	GL_TRIANGLE_STRIP
6	GL_TRIANGLE_FAN
7	GL_QUADS
8	GL_QUAD_STRIP
9	GL_POLYGON
*/

# define DATA			0
# define ENDL			ft_putchar(10);
# define SPACE			ft_putchar(32);
# define TAB			ft_putchar('\t');

# define RGB(r, g, b)	(65536 * (int)(r) + 256 * (int)(g) + (int)(b))
# define RTOD(x)		(x * (180.0f / M_PI))
# define DTOR(x)		(x * M_PI / 180.0f)
# define RAD			0.017453f
# define ROT_WAY		1
# define ROT_RIGHT		-1
# define ROT_LEFT		1

# define DRAW_MODE		GL_POINTS
// # define DRAW_MODE		GL_LINE_STRIP
# define FPS			40
# define FRAME_TICK		(1000 / FPS)


# define COLOR_RGB_1	"/etc/X11/rgb.txt"
// # define COLOR_RGB_2	"/usr/share/X11/rgb.txt"
# define COLOR_RGB_2	"/usr/share/emacs/26.0.50/etc/rgb.txt" //MAC 42
# define VSHADER_FILE	"./shaders/vertex_shader.glsl"
# define FSHADER_FILE	"./shaders/fragment_shader.glsl"
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
# define GLEW_FAIL			103
# define GLFW_FAIL			104
# define XPM_BAD_FORMAT		105
# define RGB_FILE_ERR		106
# define GL_ERROR			107
# define RGB_FILE_OPEN		"Error : can't open rgb.txt"
# define RGB_FILE_EMPTY		"Error : rgb.txt is empty"
# define OBJ_ERROR			"Error : bad obj format"
# define GLEW_WIN_FAIL		"Failed initialize GLEW"
# define GLFW_INIT_FAIL		"Failed initialize GLFW."
# define GLFW_WIN_FAIL		"Failed to create GLFW window."
# define GL_COMPILE_SHADER	"OpenGL shader error"
# define OBJ_FACE_ERROR		"Incorrect vertix number"
# define OBJF_NO_OBJ		"Error : This file has no valid object"
# define MTLF_NO_MAT		"Error : This file has no valid material"
# define MTL_ERROR			"Error : bad mtl format"
# define MTL_USED			"Error : name already in use"
# define DATA_CORRUPT_MSG	"Error : data corrupt"
# define SCOP_DIR_ERR		"option -d : missing argument\nUsage: scop file.obj [file.mtl] [-d path]"
# define SCOP_BAD_ARG		" : invalid argument\nUsage: scop file.obj [file.mtl] [file.xpm] [-d path]"
# define XPM_ERROR			"Error : bad xpm format"
# define XPM_TOKEN_ERR		"Bad token for remove_comments_vl : "

# define COMMENT_CHAR		"#"
# define DOUBLE_QUOTE		'"'

# define OBJ_MTLFILE		"mtllib"
# define OBJ_NEW			"o"
# define OBJ_MTLUSE			"usemtl"
# define OBJ_VERTIX			"v"
# define OBJ_TEXTURE		"vt"
# define OBJ_NORMAL			"vn"
# define OBJ_FACE			"f"
# define OBJ_SMOOTH			"s"

# define MTL_MAT			"newmtl"
# define MTL_AMBIANT		"Ka"
# define MTL_DIFFUSE		"Kd"
# define MTL_SPECULAR		"Ks"
# define MTL_SPEC_EXP		"Ns"
# define MTL_DENSITY		"Ni"
# define MTL_OPACITY		"d"
# define MTL_ILLUM			"illum"

#define MODS				3
#define DISPLAY_TEXTURE		0
#define DISPLAY_COLOR		1
#define DISPLAY_MATERIAL	2

typedef struct			s_vector2
{
	float				x;
	float				y;
}						t_vector2;

typedef struct			s_vector3
{
	float				x;
	float				y;
	float				z;
}						t_vector3;

typedef struct			s_rgb
{
	struct s_rgb		*next;
	int					id;
	char				*name;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_rgb;

typedef struct			s_arg
{
	struct s_arg		*next;
	void				*ptr[10];
}						t_arg;

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
	t_vertix			*v1;
	t_vertix			*v2;
	t_vertix			*v3;
	t_vertix			*v4;
}						t_face;

typedef struct			s_mat
{
	struct s_mat		*next;
	int					id;
	char				*id_char;
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
	char				*id_char;
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

typedef struct			s_glfw
{
	int					size[2];
	int					mid[2];
	char				*title;
	GLFWwindow			*win;
}						t_glfw;

typedef struct			s_xpm
{
	struct s_xpm		*next;
	int					id;
	char				*name;
	char				*path;
	int					width;
	int					height;
	unsigned char		*data;
}						t_xpm;

typedef struct			s_env
{
	t_objfile			*objfile;
	t_mtlfile			*mtlfile;
	t_xpm				*xpmfile;
	t_str				*dir;
	t_glfw				*glfw;
	t_rgb				*chart;
}						t_env;

typedef struct			s_sdl_env
{
	// SDL_Event			event;
	int					quit;
	int					virtual_time;
	int					frame;
	int					tick;
	int					start_time;
	int					current_time;
	int					ellapsed_time;
	int					last_time;
}						t_sdl_env;

typedef struct			s_gl_env
{
	GLuint				tex_vbo;
	GLuint				colors_vbo;
	GLuint				vbo;
	GLuint				vao;
	GLuint				vshader;
	GLuint				fshader;
	GLuint				shader_programme;
	GLint				display_mod;
	int					dismod;
	GLint				projection;
	t_objfile			**objf;
	t_xpm				**xpm;
	GLuint				*tex_id;
	int					obj_len;
	int					xpm_len;
	int					obj_i;
	int					tex_i;
	int					tex;
	int					rotate;
	t_vector3			rot;
	t_vector3			pos;
	int					angle;
	float				vector;
	float				scale;
}						t_gl_env;
////debug, a delete apres
void	print_memory(void);

// libft
void		ft_free_list(void *list, t_void* (custom_free)(t_void*));
t_void		*free_t_str(t_void *list);
int			safe_open(char *path);
void		hex_to_rgb(unsigned char *rgb, char *s);
t_void		**list_to_tab(t_void *list);

// free structure
t_void		*free_t_env(t_void *list);
t_void		*free_t_xpm(t_void	*list);
t_void		*free_t_rgb(t_void *list);
t_void		*free_t_vertix(t_void *list);
t_void		*free_t_face(t_void *list);
t_void		*free_t_mat(t_void *list);
t_void		*free_t_mtlfile(t_void *list);
t_void		*free_t_obj(t_void *list);
t_void		*free_t_objfile(t_void *list);
t_void		*free_t_glfw(t_void *list);

// color
t_rgb		*init_rgb(void);
t_rgb		*get_color(t_rgb *rgb, char *name);

// file manipulation
t_void		*del(t_void *ptr);
int			is_empty(t_void *ptr);
t_void		*remove_list(t_void *ptr, int (condition)(t_void*), t_void* (del)(t_void*));
char		*basename(char *path);
int			is_dir(void);
int			is_readable(char *path);
int			is_typefile(char *file, char *type);
char		*remove_trailing_slach(char *str);
t_void		*for_list(t_void *list, t_void* (*func)(t_void*));
t_void		*for_list_args(t_void *list, t_arg args, t_void* (*func)(t_void*, t_arg args));
t_arg		init_args(void *a1, void *a2, void *a3, void *a4);
t_void		*get_link(t_void* list, int index);


//parsing char* / t_str
void		remove_comments_l(t_str *ptr, char *comment_str);
void		remove_comments_vl(char *str, char *start, char *end, char *front);
char		*t_str_to_char(t_str *ptr);
t_str		*char_to_t_str(char *str);
void		remove_comments_str(char *str, char *comm);

// inits
t_env		*init_env(void);
t_obj		*init_obj(void);
t_mat		*init_mat(void);
t_xpm		*init_xpm(void);
t_glfw		*init_glfw(void);
t_sdl_env	*init_sdl_env(void);
t_gl_env	*init_gl_env(t_objfile **objf, t_xpm **xpm, int *len);

//parsing args
void		load_file(t_env *e, int ac, char **av);
int			is_typefile(char *file, char *type);
void		add_objfile(t_objfile **addr, char *file);
void		add_mtlfile(t_mtlfile **addr, char *file);
void		add_xpmfile(t_xpm **addr, char *file, t_rgb *chart);
t_objfile	*get_objfile(t_objfile *ptr, char *file);
t_mtlfile	*get_mtlfile(t_mtlfile *ptr, char *file);
int			chk_objfile(t_objfile *objfile, char *path);
int			chk_mtlfile(t_mtlfile *mtlfile, char *path);
int			chk_xpmfile(t_xpm *xpmfile, char *path);
void		link_file(t_env *e);

// parsing .xpm
void		error_xpm(char *s1, char *s2);
t_xpm		*load_xpm(char *path, t_rgb *chart);
t_str		*build_pixels(t_xpm *xpm, t_rgb *rgb_tokens, int t_size, t_str *ptr);
char		*chk_separator(char *str);
GLuint		xpm_to_glid(t_xpm *xpm);

//parsing .obj
t_obj		*build_objects(char *path);
void		error_obj(char *s1, char *s2);
t_str		*add_vertix(t_obj *obj, t_str *ptr);
t_str		*add_face(t_obj *obj, t_str *ptr);
t_str		*add_mtlfile_name(t_obj *obj, t_str *ptr);
t_str		*add_material_name(t_obj *obj, t_str *ptr);
t_str		*add_smooth(t_obj *obj, t_str *ptr);
t_str		*add_objname(t_obj *obj, t_str *ptr);
void		obj_checks(t_objfile *objfile);
t_void		*rewrite_objects(t_void *objfile);
void		triangularize(t_obj* obj);

//parsing .mtl
t_mat		*build_material(char *path);
t_str		*add_mtlname(t_mat **mat, t_str *ptr);
t_str		*add_color(t_str *ptr, float *color);
t_str		*add_value(t_str *ptr, int *var);
t_str		*add_value_f(t_str *ptr, float *var);
void		error_mtl(char *s1, char *s2);
void		mtl_checks(t_mtlfile *mtlfile);

//sdl/glfw
void		display_object(t_glfw *glfw, t_objfile **objf, t_xpm **xpm, int *len);
void		translate_obj(t_vertix *vertix, float x, float y, float z);

// sdl events
// void		events(int scancode, t_sdl *sdl, t_sdl_env *sdl_e, t_gl_env *gl_e);
// int			event_obj_rotate(int scancode, int *rot, int angle);
// int			event_obj_translate(int scancode, float *pos, float vector);
// int			event_assets(int scancode, t_objfile **objf, GLuint *texture_id, t_arg args);
// int			event_properties(int scancode, int *rotate, int *tex);

//rotations matricielles
void	rot_vector2(t_vector2 *src, t_vector2 *dst, float rad, float rot_direction);
void	rot_vector3_bis(t_vector3 *src, t_vector3 *dst, t_vector3 rad, float rot_direction);
void	rot_vector3(t_vector3 *src, t_vector3 *dst, t_vector3 rad, float rot_direction);
void	revrot_vector3(t_vector3 *src, t_vector3 *dst, t_vector3 rad, float rot_direction);

#endif
