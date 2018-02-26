/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_opengl.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:25:11 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/26 19:30:26 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_OPENGL_H
# define SCOP_OPENGL_H

typedef struct			s_vbo
{
	GLuint				vertex;
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
	uint8_t				rotate;
	t_vector3			pos;
	t_vector3			rot;
	int					current_faces;
	int					max_faces;
	t_vector3			plain_color;
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

#endif
