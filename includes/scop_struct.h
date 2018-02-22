/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/22 20:07:25 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_STRUCT_H
# define SCOP_STRUCT_H

/*
**	s_rgb: ne pas modifier la structure (padding, comportement aleatoire ?)
**	voir fonction build_tokens(...) (xpm_load.c)
*/
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

/*
**	s_face: ne pas modifier la structure (padding, comportement aleatoire ?)
**	voir fonction triangularize(...) (obj_data2.c)
*/
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

/*
**	s_mat :
**	float				ka[3];// color ambiant (0.0 - 1.0) x3
**	float				kd[3];// color diffuse (0.0 - 1.0) x3
**	float				ks[3];// color specular (0.0 - 1.0) x3
**	float				ns;// specular exponent (0 - 100)
**	float				ni;// densite optique
**	float				d;// opacite (0.0 - 1.0)
**	int					illum;// lumiere param
*/
typedef struct			s_mat
{
	struct s_mat		*next;
	int					id;
	char				*id_char;
	char				*name;
	float				ka[3];
	float				kd[3];
	float				ks[3];
	float				ns;
	float				ni;
	float				d;
	int					illum;
}						t_mat;

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
	char				*title;
	GLFWwindow			*win;
	char				*cwd;
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
	char				*cwd;
}						t_env;

typedef struct			s_fps
{
	double				fps;
	double				tick;
	double				ellapsed_time;
	double				last_time;
}						t_fps;

typedef struct			s_gl_env
{
	////// temporaire struct programm
	GLuint				vbo;
	GLuint				colors_vbo;
	GLuint				tex_vbo;
	GLuint				tex_cylinder_vbo;
	int					vbo_slot;
	int					colors_slot;
	int					tex_slot;
	int					tex_cylinder_slot;
	GLuint				vao;
	GLuint				vshader;
	GLuint				fshader;
	GLuint				shader_programme;
	int					obj_face_amount;
	t_vector3			plain_color;
	////// struct program end ?
	GLint				gl_display_mod;
	int					dismod;
	GLint				gl_plain_color;
	GLint				gl_projection;
	////// struct program end
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
	float				fov;
	int					draw_mod;
	int					texture_mod;
	int					face_drawed;
	char				boolens[348];
	char				*cwd;
	char				*shaders[2];
}						t_gl_env;

typedef struct			s_cam
{
	t_vector3			pos;
	t_vector3			right;
	t_vector3			up;
	t_vector3			forward;
	t_vector3			front;
}						t_cam;

typedef struct			s_logs
{
	int					params;
	char				name[64];
	char				long_name[64];
	int					length;
	int					actual_length;
	int					size;
	int					location;
	GLenum				type;
	int					i;
	int					j;
}						t_logs;

#endif
