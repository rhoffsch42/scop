/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_obj3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:43:32 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/01 18:06:39 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		get_slots_obj3d(t_prog *prog)
{
	int				(*fun)(unsigned int, const char *);
	t_obj3d_slots	*slots;

	slots = &prog->slots.obj3d;
	fun = glGetUniformLocation;
	slots->mat4_m = get_slot(prog->program, "M", fun);
	slots->mat4_v = get_slot(prog->program, "V", fun);
	slots->mat4_p = get_slot(prog->program, "P", fun);
	slots->dismod = get_slot(prog->program, "dismod", fun);
	slots->plain_color = get_slot(prog->program, "plain_color", fun);
	fun = glGetAttribLocation;
	slots->vertex_position = get_slot(prog->program, "vertex_position", fun);
	slots->vertex_colour = get_slot(prog->program, "vertex_colour", fun);
	slots->vertexUV = get_slot(prog->program, "vertexUV", fun);
}

static void		load_data_obj3d(t_blueprint_obj3d *blueprint, t_obj *obj)
{
	fill_buffer(blueprint->v_obj.vbo, obj, fill_points_array, 3);
	fill_buffer(blueprint->v_blackwhite.vbo, obj, fill_color_array, 3);
	fill_buffer(blueprint->v_texture.vbo, obj, fill_tex_array, 2);
	fill_buffer(blueprint->v_tex_cylinder.vbo, obj, fill_tex_cylinder_array, 2);
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

static void		create_blueprints_obj3d(t_prog *prog, t_objfile **objf, int n)
{
	t_blueprint_obj3d	*obj;

	prog->blueprints = (t_blueprint*)safe_malloc(sizeof(t_blueprint) * (n + 1));
	prog->blueprints_amount = n;
	while (--n >= 0)
	{
		obj = &prog->blueprints[n].obj3d;
		glGenVertexArrays(1, &obj->vao);
		glBindVertexArray(obj->vao);
		glEnableVertexAttribArray(0);//usefull ?
		obj->v_obj.slot = prog->slots.obj3d.vertex_position;
		obj->v_blackwhite.slot = prog->slots.obj3d.vertex_colour;
		obj->v_texture.slot = prog->slots.obj3d.vertexUV;
		obj->v_tex_cylinder.slot = prog->slots.obj3d.vertexUV;
		create_buffer(&obj->v_obj, 3, GL_FLOAT);
		create_buffer(&obj->v_blackwhite, 3, GL_FLOAT);
		create_buffer(&obj->v_texture, 2, GL_FLOAT);
		create_buffer(&obj->v_tex_cylinder, 2, GL_FLOAT);
		load_data_obj3d(obj, objf[n]->obj);
	}
}

t_prog			create_program_obj3d(t_objfile **objf, int n, char *cwd)
{
	t_prog		prog;

	prog = create_program(cwd, VSHADER_FILE, FSHADER_FILE, get_slots_obj3d);
	create_blueprints_obj3d(&prog, objf, n);
	return (prog);
}
