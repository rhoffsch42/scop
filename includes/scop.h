/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/10 13:44:41 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

/*
**	do not change include order
*/
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "libft.h"
# include "libmath3d.h"
# include "scop_struct.h"
# include "scop_opengl.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <stddef.h>
# include <math.h>

/*
**	BONUS
**	<sys/stat.h>	lstat	string.c
*/
# include <sys/stat.h>

/*
**	0	GL_POINTS
**	1	GL_LINES
**	2	GL_LINE_STRIP
**	3	GL_LINE_LOOP
**	4	GL_TRIANGLES
**	5	GL_TRIANGLE_STRIP
**	6	GL_TRIANGLE_FAN
**	7	GL_QUADS
**	8	GL_QUAD_STRIP
**	9	GL_POLYGON
*/

# define DATA			1
# define DATA_RESOURCES	0
# define DATA_MATRIX	0
# define DATA_SKYBOX	1

# define RAD			0.017453f
# define RAD_DELTA		1.0f
# define POS_DELTA		2.5f
# define ROT_WAY		1
# define MOD_LINE		10
# define MAX_FACE		999999999

# define FPS			60
# define MAX_FPS		120
# define SENSIBILITY	2000.0f
# define ROT_X			1

# define COLOR_RGB_1		"/etc/X11/rgb.txt"
# define COLOR_RGB_2		"/usr/share/emacs/26.0.50/etc/rgb.txt"
# define COLOR_RGB_3		"/usr/share/X11/rgb.txt"
# define VSHADER_FILE		"/shaders/vertex_shader.glsl"
# define FSHADER_FILE		"/shaders/fragment_shader.glsl"
# define VSHADER_FILE_CUBE	"/shaders/vertex_shader_cubemap.glsl"
# define FSHADER_FILE_CUBE	"/shaders/fragment_shader_cubemap.glsl"
# define CUBEMAP_NZ_TEX		"back.xpm"
# define CUBEMAP_PZ_TEX		"front.xpm"
# define CUBEMAP_NY_TEX		"bottom.xpm"
# define CUBEMAP_PY_TEX		"top.xpm"
# define CUBEMAP_PX_TEX		"right.xpm"
# define CUBEMAP_NX_TEX		"left.xpm"
# define PONY_FILE			"textures/pony.xpm"
# define SKYBOX_FILE		"/resources/skybox/skybox.obj"
# define DEF_WIN_TITLE		"Default title"

/*
**	mac res: 2560x1440
*/
# define DEF_WIN_X			1400
# define DEF_WIN_Y			1400
# define MAX_WIN_X			1920
# define MAX_WIN_Y			1080
# define MIN_WIN_X			800
# define MIN_WIN_Y			800
# define BYTE				3
# define FLOAT_MAX_LEN		7
# define COLOR_MAX			255
# define TITLE_MAX_LEN		50
# define TITLE_TRUNC		"[...]"
# define FAR				0.01f
# define NEAR				3000.0f
# define FOV				60.0f
# define FOVX				90.0f
# define FOVY				90.0f
# define MAX_FOV			120.0f

# define SCOP_DIR			"-d"
# define OBJ_BAD_FORMAT		100
# define DATA_CORRUPT		101
# define MTL_BAD_FORMAT		102
# define GLEW_FAIL			103
# define GLFW_FAIL			104
# define XPM_BAD_FORMAT		105
# define RGB_FILE_ERR		106
# define GL_ERROR			107
# define UNKNOW_ERROR		108
# define USAGE			"Usage: scop file.obj [file.mtl] [file.xpm] [-d path]"
# define RGB_FILE_OPEN		"Error : can't open rgb.txt"
# define RGB_FILE_EMPTY		"Error : rgb.txt is empty"
# define OBJ_ERROR			"Error : bad obj format"
# define GLEW_WIN_FAIL		"Failed initialize GLEW"
# define GLFW_INIT_FAIL		"Failed initialize GLFW."
# define GLFW_WIN_FAIL		"Failed to create GLFW window."
# define ARB_CUBEMAP_MISS	"Extension missing: GL_ARB_texture_cube_map_array"
# define GL_COMPILE_SHADER	"OpenGL shader error"
# define OBJ_FACE_ERROR		"Incorrect vertix number"
# define OBJF_NO_OBJ		"Error : This file has no valid object"
# define MTLF_NO_MAT		"Error : This file has no valid material"
# define MTL_ERROR			"Error : bad mtl format"
# define MTL_NO_NAME		"Error : bad mtl format (missing material name)"
# define MTL_USED			"Error : name already in use"
# define DATA_CORRUPT_MSG	"Error : data corrupt"
# define SCOP_DIR_ERR		"Option -d : missing argument\n"
# define SCOP_BAD_ARG		" : invalid argument\n"
# define SCOP_NO_OBJ		"No object file found\n"
# define XPM_ERROR			"Error : bad xpm format"
# define XPM_COLOR_TOKEN	"Error : bad xpm format (unknow color token)"
# define XPM_TOKEN_ERR		"Bad token for remove_comments_vl : "
# define CUBEMAP_MISS_TEX	"Missing texture for the CUBEMAP"
# define CUBEMAP_MISS_OBJ	"Missing object for the CUBEMAP"

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

# define COS_A	val[0]
# define SIN_A	val[1]
# define COS_B	val[2]
# define SIN_B	val[3]
# define COS_C	val[4]
# define SIN_C	val[5]

# define MODS				2
# define DISPLAY_COLOR		0
# define DISPLAY_MATERIAL	1

# define SKYBOX				0
# define OBJ3D				1

/*
**	libft
*/
void		ft_free_list(void *list, t_void *(custom_free)(t_void*));
t_void		*free_t_str(t_void *list);
int			safe_open(char *path);
void		hex_to_rgb(unsigned char *rgb, char *s);
t_void		**list_to_tab(t_void *list);
int			is_directory(const char *path);
char		*get_current_directory(void);

/*
**	misc
*/
double		scale_d(double val, double min, double max);
void		vertix_to_vector3(t_vertix *vertix, t_vector3 *vector);
void		dump_datafile(t_objfile *objfile, t_mtlfile *mtlfile, t_str *dir, \
							t_xpm *xpm);
void		dump_data_obj(t_obj *obj);

/*
**	free structure
*/
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

/*
**	color
*/
t_rgb		*init_rgb(void);
t_rgb		*get_color(t_rgb *rgb, char *name);

/*
**	file manipulation
*/
t_void		*del(t_void *ptr);
int			is_empty(t_void *ptr);
t_void		*remove_list(t_void *ptr, int (condition)(t_void*), \
						t_void *(del)(t_void*));
char		*basename(char *path);
int			is_dir(void);
int			is_readable(char *path);
int			is_typefile(char *file, char *type);
char		*remove_trailing_slach(char *str);
t_void		*for_list(t_void *list, t_void *(*func)(t_void*));
t_void		*for_list_args(t_void *list, t_arg args, \
							t_void *(*func)(t_void*, t_arg args));
t_arg		init_args(void *a1, void *a2, void *a3, void *a4);
t_void		*get_link(t_void *list, int index);

/*
** parsing char* / t_str
*/
void		remove_comments_l(t_str *ptr, char *comment_str);
void		remove_comments_vl(char *str, char *start, char *end, char *front);
char		*t_str_to_char(t_str *ptr);
t_str		*char_to_t_str(char *str);
void		remove_comments_str(char *str, char *comm);

/*
** inits
*/
t_env		*init_env(void);
t_obj		*init_obj(void);
t_mat		*init_mat(void);
t_xpm		*init_xpm(void);
t_glfw		*init_glfw(t_glfw *glfw);
void		init_t_fps(t_fps *fps);

/*
** parsing args
*/
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

/*
** parsing .xpm
*/
void		error_xpm(char *s1, char *s2);
t_xpm		*load_xpm(char *path, t_rgb *chart);
t_str		*build_pixels(t_xpm *xpm, t_rgb *rgb_tokens, int t_size, \
							t_str *ptr);
char		*chk_separator(char *str);
GLuint		xpm_to_glid(t_xpm *xpm);

/*
** parsing .obj
*/
t_obj		*build_objects(char *path);
void		error_obj(char *s1, char *s2);
t_str		*add_vertix(t_obj *obj, t_str *ptr);
t_str		*add_face(t_obj *obj, t_str *ptr);
void		triangularize(t_obj *obj);
t_str		*add_mtlfile_name(t_obj *obj, t_str *ptr);
t_str		*add_material_name(t_obj *obj, t_str *ptr);
t_str		*add_smooth(t_obj *obj, t_str *ptr);
t_str		*add_objname(t_obj *obj, t_str *ptr);
void		obj_checks(t_objfile *objfile);
t_void		*rewrite_objects(t_void *objfile);
void		triangularize(t_obj *obj);

/*
** parsing .mtl
*/
t_mat		*build_material(char *path);
t_str		*add_mtlname(t_mat **mat, t_str *ptr);
t_str		*add_color(t_str *ptr, float *color);
t_str		*add_value(t_str *ptr, int *var);
t_str		*add_value_f(t_str *ptr, float *var);
void		error_mtl(char *s1, char *s2);
void		mtl_checks(t_mtlfile *mtlfile);

/*
** glfw & OpenGL
*/
int			wait_for_next_frame(t_fps *fps);
void		init_t_gl(t_gl *gle, t_xpm **xpm, int *len);
void		display_object(t_glfw *glfw, t_objfile **objf, t_xpm **xpm, \
							int *len);
t_matrix4	model_matrix(t_vector3 pos, t_vector3 rot, t_matrix4 model);
t_matrix4	view_matrix(t_cam *cam, t_matrix4 viewmatrix);
t_matrix4	pro_matrix(float rad, float far, float near);
t_cam		init_cam(t_vector3 pos, t_vector3 rot);
void		update_cam_vector(t_cam *cam);
void		create_program(t_prog *program, char *vshader_file, \
				char *fshader_file, void (get_slot_uniform)(t_prog*));
void		create_buffer(t_vbo *vertex_buffer, int size, GLenum type);
void		fill_buffer(GLuint vbo, t_obj *obj, \
							void (fill_func)(float*, t_face*), int summit);
void		fill_color_array(float *arr, t_face *face);
void		fill_tex_array(float *arr, t_face *face);
void		fill_tex_cylinder_array(float *arr, t_face *face);
void		fill_points_array(float *arr, t_face *face);
GLint		get_slot(GLuint program, const GLchar *varname, \
							GLint (func)(GLuint, const GLchar*));
void		create_program_obj3d(t_prog *program, t_objfile **objf, \
								int n, char *cwd);
void		create_program_skybox(t_prog *program, char *cwd, t_xpm **xpm, \
								int xpm_len);
t_xpm		*get_xpm(t_xpm **textures, int len, const char *name);

void		print_mvp_matrix(t_gl *gle, t_blueprint_obj3d *obj);
void		print_pixel(float x, float y);
void		print_cam_properties(t_gl *gle);

/*
**	OpenGL error
*/
void		print_programme_info_log(GLuint programme);
void		gl_compile_error(GLuint shader, char *intro);

/*
** events
*/
int			is_first_press(t_glfw *glfw, int key, t_gl *gle);
void		events(t_glfw *glfw, t_gl *gle, t_prog *prog);
void		update_matrices(t_gl *gle, t_blueprint *blueprints);
void		update_texture(t_glfw *glfw, t_gl *gle, t_blueprint *blueprints);

#endif
