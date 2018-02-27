/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_opengl.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:25:11 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/27 21:30:20 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_OPENGL_H
# define SCOP_OPENGL_H

typedef struct			s_vbo
{
	GLuint				vbo;
	GLint				slot;
}						t_vbo;

typedef struct			s_blueprint_skybox
{
	GLuint				vao;
	t_vbo				vertex;
	GLuint				texture_id;
}						t_blueprint_skybox;

typedef struct			s_blueprint_obj3d
{
	GLuint				vao;
	t_vbo				vertex_obj;
	t_vbo				blackwhite;//black and white 42
	t_vbo				vertex_texture;
	t_vbo				vertex_texture_cylinder;
	t_matrix4			model_matrix;
	GLuint				tex;
	uint8_t				rotate;
	t_vector3			pos;
	t_vector3			rot;
	int					current_faces;
	int					max_faces;
	t_vector3			plain_color;
	uint8_t				display_mod;
	uint8_t				draw_mod;
	uint8_t				cyl_mapping;
}						t_blueprint_obj3d;

typedef union			u_blueprint
{
	t_blueprint_skybox	skybox;
	t_blueprint_obj3d	obj3d;
}						t_blueprint;

typedef struct			s_skybox_slots
{
	GLint				mat4_v;
	GLint				mat4_p;
}						t_skybox_slots;

typedef struct			s_obj3d_slots
{
	GLint				mat4_m;
	GLint				mat4_v;
	GLint				mat4_p;
	GLint				dismod;
	GLint				plain_color;
}						t_obj3d_slots;

typedef union			u_slots
{
	t_skybox_slots		skybox;
	t_obj3d_slots		obj3d;
}						t_slots;

typedef struct			s_prog
{
	GLuint				program;
	GLuint				vshader;
	GLuint				fshader;
	t_slots				slots;
	t_blueprint			*blueprints;//a malloc, pour X blueprint(s)
	int					blueprints_amount;
}						t_prog;

typedef struct			s_gl
{
	t_cam				cam;
	t_fps				fps;
	t_matrix4			matrix_zero;
	t_matrix4			view;
	t_matrix4			projection;
	GLuint				*textures_id;
	GLuint				tex_max;
	int					obj_i;
	int					obj_max;
	float				fov;
	uint8_t				boolens[348];
}						t_gl;

#endif
