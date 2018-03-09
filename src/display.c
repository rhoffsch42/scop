/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:45:04 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/09 21:09:36 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		load_shader_attributes_obj(t_prog *p, t_gl *gle)
{
	glUniformMatrix4fv(p->slots.obj3d.mat4_v, 1, GL_FALSE, gle->view.m.e);
	glUniformMatrix4fv(p->slots.obj3d.mat4_p, 1, GL_FALSE, gle->projection.m.e);
}

static void		load_obj3d_attributes(t_prog *prog, t_blueprint_obj3d *obj3d_bp)
{
	t_obj3d_slots	*s;

	s = &prog->slots.obj3d;
	glUniform1i(s->dismod, obj3d_bp->display_mod);
	glUniformMatrix4fv(s->mat4_m, 1, GL_FALSE, obj3d_bp->model_matrix.m.e);
	glUniform3f(s->plain_color, obj3d_bp->plain_color.x, \
								obj3d_bp->plain_color.y, \
								obj3d_bp->plain_color.z);
}

static void		launch_program_obj3d(t_prog *prog, t_gl *gle, int n)
{
	t_vbo				*vertex;
	GLenum				mod[2];
	t_blueprint_obj3d	*obj3d_bp;

	glUseProgram(prog->program);
	load_shader_attributes_obj(prog, gle);
	while (--n >= 0)
	{
		obj3d_bp = &prog->blueprints[n].obj3d;
		load_obj3d_attributes(prog, obj3d_bp);
		glBindTexture(GL_TEXTURE_2D, obj3d_bp->tex);
		glBindVertexArray(obj3d_bp->vao);
		if (obj3d_bp->cyl_mapping)
			vertex = &obj3d_bp->v_tex_cylinder;
		else
			vertex = &obj3d_bp->v_texture;
		glBindBuffer(GL_ARRAY_BUFFER, vertex->vbo);
		glVertexAttribPointer(vertex->slot, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		mod[0] = (obj3d_bp->draw_mod == MOD_LINE) ? GL_LINE : GL_FILL;
		mod[1] = (obj3d_bp->draw_mod == MOD_LINE) ? \
					GL_TRIANGLES : obj3d_bp->draw_mod;
		glPolygonMode(GL_FRONT_AND_BACK, mod[0]);
		glDrawArrays(mod[1], 0, obj3d_bp->current_faces * 3);
		glBindVertexArray(0);
	}
}

static void		launch_program_skybox(t_prog *prog, t_gl *gle)
{
	t_blueprint_skybox	*skybox;

	skybox = &prog->blueprints[0].skybox;
	glUseProgram(prog->program);
	glUniformMatrix4fv(prog->slots.skybox.mat4_v, 1, GL_FALSE, gle->view.m.e);
	glUniformMatrix4fv(prog->slots.skybox.mat4_p, 1, GL_FALSE, \
						gle->projection.m.e);
	glUniform1i(prog->slots.skybox.cubemap, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->tex);
	glBindVertexArray(skybox->vao);
	glBindBuffer(GL_ARRAY_BUFFER, skybox->v_skybox.vbo);
	glVertexAttribPointer(skybox->v_skybox.slot, 3, GL_FLOAT, GL_FALSE, 0, \
							NULL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glBindVertexArray(0);
}

void			display_object(t_glfw *glfw, t_objfile **objf, t_xpm **xpm, \
								int *len)
{
	t_gl		gle;
	t_prog		progs[2];

	init_t_gl(&gle, xpm, len);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(-1.0f);
	glDepthFunc(GL_GREATER);
	create_program_skybox(&progs[SKYBOX], glfw->cwd, xpm, len[1]);
	create_program_obj3d(&progs[OBJ3D], objf, len[0], glfw->cwd);
	glfwGetCursorPos(glfw->win, &gle.mouse_origin_x, &gle.mouse_origin_y);
	while (!glfwWindowShouldClose(glfw->win))
	{
		if (wait_for_next_frame(&gle.fps))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
			if (progs[SKYBOX].blueprints)
				launch_program_skybox(&progs[SKYBOX], &gle);
			launch_program_obj3d(&progs[OBJ3D], &gle, len[0]);
			glfwSwapBuffers(glfw->win);
			glfwPollEvents();
			events(glfw, &gle, &progs[OBJ3D]);
		}
	}
}
