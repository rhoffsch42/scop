/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_obj3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:43:32 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/28 22:41:14 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			get_slots_obj3d(t_prog *prog)
{
	int			(*fun)(unsigned int, const char *);

	fun = glGetUniformLocation;
	prog->slots.obj3d.mat4_m = get_slot(prog->program, "M", fun);
	prog->slots.obj3d.mat4_v = get_slot(prog->program, "V", fun);
	prog->slots.obj3d.mat4_p = get_slot(prog->program, "P", fun);
	prog->slots.obj3d.dismod = get_slot(prog->program, "dismod", fun);
	prog->slots.obj3d.plain_color = get_slot(prog->program, "plain_color", fun);
}

static void		load_data_obj3d(t_blueprint_obj3d *blueprint, t_obj *obj)
{
	float	points[obj->f_amount * 9];
	float	colors[obj->f_amount * 9];
	float	tex[obj->f_amount * 6];
	float	tex_cylinder[obj->f_amount * 6];

	fill_points_array(points, obj->f);
	fill_color_array(colors, obj->f);
	fill_tex_array(tex, obj->f);
	fill_tex_cylinder_array(tex_cylinder, obj->f);
	glBindBuffer(GL_ARRAY_BUFFER, blueprint->vertex_obj.vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float), points, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, blueprint->blackwhite.vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float), colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, blueprint->vertex_texture.vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 6 * sizeof(float), tex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, blueprint->vertex_texture_cylinder.vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 6 * sizeof(float), tex_cylinder, GL_STATIC_DRAW);
	blueprint->rotate = 1;
	blueprint->pos = vector3(0.0f, 0.0f, 0.0f);
	blueprint->rot = vector3(0.0f, 0.0f, 0.0f);
	blueprint->model_matrix = matrix4(IDENTITY, MATRIX_ROW_MAJOR);
	blueprint->current_faces = obj->f_amount;
	blueprint->max_faces = obj->f_amount;
	if (obj->mat)
		blueprint->plain_color = (t_vector3){obj->mat->kd[0], obj->mat->kd[1], \
											obj->mat->kd[2]};
	blueprint->display_mod = DISPLAY_TEXTURE;
	blueprint->draw_mod = GL_TRIANGLES;
	blueprint->cyl_mapping = 0;
	blueprint->tex = 1;
}

void			create_blueprints_obj3d(t_prog *prog, t_objfile **objf, int n)
{
	t_blueprint_obj3d	*obj;

	prog->blueprints = (t_blueprint*)safe_malloc(sizeof(t_blueprint) * (n + 1));
	prog->blueprints_amount = n;
	while (--n >= 0)
	{
		obj = &prog->blueprints[n].obj3d;
		glGenVertexArrays(1, &obj->vao);
		glBindVertexArray(obj->vao);
		glEnableVertexAttribArray(0);//utile ?
		// tous ces slots en bas peuvent s'obtenir une seule fois apres avoir creer le program
		// les mettre avec les autres slots t_prog::slots::obj3d, et les copier dans les t_vbo::slot ?
		obj->vertex_obj.slot = \
			get_slot(prog->program, "vertex_position", glGetAttribLocation);
		obj->blackwhite.slot = \
			get_slot(prog->program, "vertex_colour", glGetAttribLocation);
		obj->vertex_texture.slot = \
			get_slot(prog->program, "vertexUV", glGetAttribLocation);
		obj->vertex_texture_cylinder.slot = \
			get_slot(prog->program, "vertexUV", glGetAttribLocation);
		////////////////////////////////
		create_buffer(&obj->vertex_obj, 3, GL_FLOAT);
		create_buffer(&obj->blackwhite, 3, GL_FLOAT);
		create_buffer(&obj->vertex_texture, 2, GL_FLOAT);
		create_buffer(&obj->vertex_texture_cylinder, 2, GL_FLOAT);
		load_data_obj3d(obj, objf[n]->obj);
	}
}
