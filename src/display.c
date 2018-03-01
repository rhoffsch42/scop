/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:45:04 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/01 12:46:24 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		load_shader_attributes(t_prog *p, t_gl *gle)
{
	glUniformMatrix4fv(p->slots.obj3d.mat4_v , 1, GL_FALSE, gle->view.m.e);
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

static void		draw_obj3d(t_prog *prog, t_blueprint_obj3d *obj3d_bp)
{
	t_vbo	*vertex;
	GLenum	mod[2];

	load_obj3d_attributes(prog, obj3d_bp);
	glBindTexture(GL_TEXTURE_2D, obj3d_bp->tex);
	glBindVertexArray(obj3d_bp->vao);
	if (obj3d_bp->cyl_mapping)
		vertex = &obj3d_bp->v_tex_cylinder;
	else
		vertex = &obj3d_bp->v_texture;
	glBindBuffer(GL_ARRAY_BUFFER, vertex->vbo);
	glVertexAttribPointer(vertex->slot, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	mod[0] = (obj3d_bp->draw_mod == MOD_LINE) ? GL_LINE : GL_FILL;				//ameliorer ce truc
	mod[1] = obj3d_bp->draw_mod == MOD_LINE ? GL_TRIANGLES : obj3d_bp->draw_mod;//ameliorer ce truc
	glPolygonMode(GL_FRONT_AND_BACK, mod[0]);
	glDrawArrays(mod[1], 0, obj3d_bp->current_faces * 3);
	glBindVertexArray(0);
}

static void	launch_program_obj3d(t_prog *prog, t_gl *gle, int n)
{
	glUseProgram(prog->program);
	load_shader_attributes(prog, gle);
	while (--n >= 0)
		draw_obj3d(prog, &prog->blueprints[n].obj3d);
}

static int		wait_for_next_frame(t_fps *fps)
{
	fps->ellapsed_time = glfwGetTime() - fps->last_time;
	if (fps->ellapsed_time >= fps->tick)
	{
		fps->last_time += fps->ellapsed_time;
		fps->ellapsed_time = 0.0;
		return (1);
	}
	else
		return (0);
}

void			display_object(t_glfw *glfw, t_objfile **objf, t_xpm **xpm, int *len)
{
	t_gl		gle;
	t_prog		progs[2];

	init_t_gl(&gle, xpm, len);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(-1.0f);
	glDepthFunc(GL_GREATER);
	progs[OBJ3D] = create_program_obj3d(objf, len[0], glfw->cwd);
	glfwGetCursorPos(glfw->win, &gle.mouse_origin_x, &gle.mouse_origin_y);
	printf("Origin mouse:\t%.2f:%.2f\n", gle.mouse_origin_y, gle.mouse_origin_x);
	
	// creer une liste des object crees via les blueprints ?
	// ie: liste de nouvelles instances t_blueprint_obj3d via copy, puis les afficher
	while (!glfwWindowShouldClose(glfw->win))
	{
		if (wait_for_next_frame(&gle.fps))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.2f, 0.4f, 1.0f);

			launch_program_obj3d(&progs[OBJ3D], &gle, len[0]);
			
			glfwSwapBuffers(glfw->win);
			glfwPollEvents();
			events(glfw, &gle, &progs[OBJ3D]);
		}
	}
}

/*
	object mouse picking
	dessiner une image en plus avec une color par object, regarder la color au pixel x:y
*/
