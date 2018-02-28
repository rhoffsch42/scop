/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:45:04 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/28 14:01:31 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static t_cam		init_cam(t_vector3 pos, t_vector3 rot)
{
	t_cam	cam;

	cam.pos = pos;
	cam.rot = rot;
	cam.right.x = 1;
	cam.right.y = 0;
	cam.right.z = 0;
	cam.up.x = 0;
	cam.up.y = 1;
	cam.up.z = 0;
	update_cam_vector(&cam);
	return (cam);
}

t_matrix4	model_matrix2(t_vector3 pos, t_vector3 rot, t_matrix4 model)
{
	float		val[8];

	val[0] = cosf(rot.x);
	val[1] = sinf(rot.x);
	val[2] = cosf(rot.y);
	val[3] = sinf(rot.y);
	val[4] = cosf(rot.z);
	val[5] = sinf(rot.z);
	val[6] = COS_A * SIN_B;
	val[7] = SIN_A * SIN_B;
	val[6] = COS_A * SIN_B;
	val[7] = SIN_A * SIN_B;
	model.m.tab[0][0] = COS_B * COS_C;
	model.m.tab[1][0] = val[7] * COS_C + COS_A * SIN_C;
	model.m.tab[2][0] = -val[6] * COS_C + SIN_A * SIN_C;
	model.m.tab[0][1] = -COS_B * SIN_C;
	model.m.tab[1][1] = -val[7] * SIN_C + COS_A * COS_C;
	model.m.tab[2][1] = val[6] * SIN_C + SIN_A * COS_C;
	model.m.tab[0][2] = SIN_B;
	model.m.tab[1][2] = -SIN_A * COS_B;
	model.m.tab[2][2] = COS_A * COS_B;
	model.m.tab[0][3] = pos.x;
	model.m.tab[1][3] = pos.y;
	model.m.tab[2][3] = pos.z;
	model.m.tab[3][3] = 1;
	model = matrix4_set_order(model, !model.order);
	return (model);
}

static t_matrix4	pro_matrix(float rad, float far, float near)
{
	t_matrix4	promatrix;
	float		ratio;

	ratio = 1.0f / tanf(rad / 2.0f);
	promatrix = matrix4(0, MATRIX_ROW_MAJOR);
	promatrix.m.tab[0][0] = ratio / (DEF_WIN_X / DEF_WIN_Y);
	promatrix.m.tab[1][1] = ratio;
	promatrix.m.tab[2][2] = -(far + near) / (far - near);
	promatrix.m.tab[2][3] = -2.0f * far * near / (far - near);
	promatrix.m.tab[3][2] = -1.0f;
	promatrix = matrix4_set_order(promatrix, !promatrix.order);
	return (promatrix);
}

static void			init_shader_attributes_obj3d(t_prog *prog, t_gl_env *gl_e)
{
	gl_e->cam = init_cam((t_vector3){0.0f, 0.0f, 5.0f}, \
						(t_vector3){DTOR(0), DTOR(0), DTOR(0)});
	gl_e->matrix_zero = matrix4(0, MATRIX_ROW_MAJOR);
	gl_e->view = view_matrix(&gl_e->cam, gl_e->matrix_zero);
	gl_e->projection = pro_matrix(DTOR(gl_e->fov), FAR, NEAR);
	if (DATA && DATA_MATRIX)
	{
		printf("View Matrix:\n");
		matrix4_print(gl_e->view);
		printf("Projection Matrix:\n");
		matrix4_print(gl_e->projection);
	}
	glUniformMatrix4fv(prog->slots.obj3d.mat4_v , 1, GL_FALSE, gl_e->view.m.e);
	glUniformMatrix4fv(prog->slots.obj3d.mat4_p, 1, GL_FALSE, gl_e->projection.m.e);
	glUniform1i(prog->slots.obj3d.dismod, gl_e->dismod);
	//prog->slots.obj3d.mat4_m 		attribution lors du chargement de chaque object
	//prog->slots.obj3d.plain_color	attribution lors du chargement de chaque object
}

static GLint		get_slot(GLuint program, const GLchar *varname, \
							GLint (func)(GLuint, const GLchar*))
{
	GLint	slot;

	slot = func(program, varname);
	printf("slot %d:\t%s\n", slot, varname);
	if (slot == -1)
	{
		glGetError();
		ft_errexit("Failed to get slot", RED, GL_ERROR);
	}
	return (slot);
}

// static void		fill_buffer(GLuint vbo, t_obj *obj, void (fill_func)(float*, t_face*), int size)
// {
// 	float	points[obj->f_amount * size];
	
// 	fill_func(points, obj->f);
// 	glBindBuffer(GL_ARRAY_BUFFER, vbo);
// 	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * size * sizeof(float), points, GL_STATIC_DRAW);
// }// si tout fonctionne, check avec cette fonction, remplacer le pave en dessous

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
	blueprint->model_matrix = model_matrix2(blueprint->pos, blueprint->rot, matrix4(0, MATRIX_ROW_MAJOR));
	// = identity, charger direct IDENTITY ?
	blueprint->current_faces = obj->f_amount;
	blueprint->max_faces = obj->f_amount;
	if (obj->mat)
		blueprint->plain_color = (t_vector3){obj->mat->kd[0], obj->mat->kd[1], obj->mat->kd[2]};
	blueprint->display_mod = DISPLAY_TEXTURE;
	blueprint->draw_mod = GL_TRIANGLES;
	blueprint->cyl_mapping = 0;
	blueprint->tex = 1;
}

static void		create_buffer(t_vbo *vertex_buffer, int size, GLenum type)
{
	glGenBuffers(1, &vertex_buffer->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->vbo);
	glVertexAttribPointer(vertex_buffer->slot, size, type, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vertex_buffer->slot);
}

static void		create_blueprints_obj3d(t_prog *prog, t_objfile **objf, int n)
{
	int		i;

	prog->blueprints = (t_blueprint*)safe_malloc(sizeof(t_blueprint) * (n + 1));
	prog->blueprints_amount = n;
	i = 0;
	while (i < n)
	{
		glGenVertexArrays(1, &prog->blueprints[i].obj3d.vao);
		glBindVertexArray(prog->blueprints[i].obj3d.vao);
		glEnableVertexAttribArray(0);//utile ?
		prog->blueprints[i].obj3d.vertex_obj.slot = get_slot(prog->program, "vertex_position", glGetAttribLocation);
		prog->blueprints[i].obj3d.blackwhite.slot = get_slot(prog->program, "vertex_colour", glGetAttribLocation);
		prog->blueprints[i].obj3d.vertex_texture.slot = get_slot(prog->program, "vertexUV", glGetAttribLocation);
		prog->blueprints[i].obj3d.vertex_texture_cylinder.slot = get_slot(prog->program, "vertexUV", glGetAttribLocation);
		create_buffer(&prog->blueprints[i].obj3d.vertex_obj, 3, GL_FLOAT);
		create_buffer(&prog->blueprints[i].obj3d.blackwhite, 3, GL_FLOAT);
		glEnable(GL_TEXTURE_2D);// a bouger autre part ?
		create_buffer(&prog->blueprints[i].obj3d.vertex_texture, 2, GL_FLOAT);
		create_buffer(&prog->blueprints[i].obj3d.vertex_texture_cylinder, 2, GL_FLOAT);
		load_data_obj3d(&prog->blueprints[i].obj3d, objf[i]->obj);
		i++;
	}
}

static void		get_slots_obj3d(t_prog *prog)
{
	prog->slots.obj3d.mat4_m = get_slot(prog->program, "M", glGetUniformLocation);
	prog->slots.obj3d.mat4_v = get_slot(prog->program, "V", glGetUniformLocation);
	prog->slots.obj3d.mat4_p = get_slot(prog->program, "P", glGetUniformLocation);
	prog->slots.obj3d.dismod = get_slot(prog->program, "dismod", glGetUniformLocation);
	prog->slots.obj3d.plain_color = get_slot(prog->program, "plain_color", glGetUniformLocation);
}

static GLuint	init_shader(char *filename, int type)
{
	GLint			ret;
	GLuint			shader;
	t_str			*content;
	const GLchar	*gl_content;

	content = ft_getfile(filename);
	gl_content = t_str_to_char(content);
	ft_free_list(content, free_t_str);
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &gl_content, NULL);
	free((void*)gl_content);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE)
		gl_compile_error(shader, "shader compilation error:");
	return (shader);
}

static t_prog		create_program2(char *cwd, char *vshader_file, char *fshader_file, \
									void (get_slot_uniform)(t_prog*))
{
	t_prog		program;
	int			p;

	vshader_file = ft_strjoin(cwd, vshader_file);
	fshader_file = ft_strjoin(cwd, fshader_file);
	program.vshader = init_shader(vshader_file, GL_VERTEX_SHADER);
	program.fshader = init_shader(fshader_file, GL_FRAGMENT_SHADER);
	free(vshader_file);
	free(fshader_file);

	program.program = glCreateProgram();
	glAttachShader(program.program, program.vshader);
	glAttachShader(program.program, program.fshader);
	glLinkProgram(program.program);
	get_slot_uniform(&program);

	p = -1;
	glValidateProgram(program.program);
	glGetProgramiv(program.program, GL_LINK_STATUS, &p);
	if (p != GL_TRUE)
		print_programme_info_log(program.program);
	glUseProgram(program.program);
	return (program);
}

static void		draw_obj3d(t_prog *prog, t_blueprint_obj3d *obj3d_bp)
{
	glBindTexture(GL_TEXTURE_2D, obj3d_bp->tex);
	glBindVertexArray(obj3d_bp->vao);
	//	update vbo + slots
	if (obj3d_bp->cyl_mapping)
	{
		glBindBuffer(GL_ARRAY_BUFFER, obj3d_bp->vertex_texture_cylinder.vbo);
		glVertexAttribPointer(obj3d_bp->vertex_texture_cylinder.slot, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, obj3d_bp->vertex_texture.vbo);
		glVertexAttribPointer(obj3d_bp->vertex_texture.slot, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	glUniform1i(prog->slots.obj3d.dismod, obj3d_bp->display_mod);
	glUniformMatrix4fv(prog->slots.obj3d.mat4_m, 1, GL_FALSE, obj3d_bp->model_matrix.m.e);
	//////////////////
	if (obj3d_bp->draw_mod == MOD_LINE)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, obj3d_bp->current_faces * 3);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(obj3d_bp->draw_mod, 0, obj3d_bp->current_faces * 3);
	}
	glBindVertexArray(0);
}

static void	load_obj3d_attributes(t_gl_env *gl_e, t_obj3d_slots *slots, t_blueprint_obj3d *obj3d_bp)
{
	gl_e->face_drawed = obj3d_bp->max_faces;
	glUniformMatrix4fv(slots->mat4_m , 1, GL_FALSE, obj3d_bp->model_matrix.m.e);
	glUniform3f(slots->plain_color, obj3d_bp->plain_color.x, \
									obj3d_bp->plain_color.y, \
									obj3d_bp->plain_color.z);
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

void	print_pixel(float x, float y)
{
	uint8_t	pix[3] = {0, 0, 0};

	glReadPixels(x, y, 1, 1, GL_RGB, GL_BYTE, &pix);
	printf("%d\t%d\t%d\n", pix[0], pix[1], pix[2]);
}

void	init_t_gl(t_gl *gle, t_xpm **xpm, int *len)
{
	int	i;

	if (len[1] > 0)
		gle->textures_id = (GLuint*)safe_malloc(sizeof(GLuint) * len[1]);
	// rajouter +1 au texture_id et le terminer par '0' car opengl renvoie 1 pour la 1ere tex generee
	// -> plus de variable xpm_len necessaire
	i = -1;
	while (++i < len[1])
		gle->textures_id[i] = xpm_to_glid(xpm[i]);
	gle->fov = FOV;
	gle->cam = init_cam((t_vector3){0.0f, 0.0f, 5.0f}, \
						(t_vector3){DTOR(0), DTOR(0), DTOR(0)});
	gle->matrix_zero = matrix4(0, MATRIX_ROW_MAJOR);
	gle->view = view_matrix(&gle->cam, gle->matrix_zero);
	gle->projection = pro_matrix(DTOR(gle->fov), FAR, NEAR);
	if (DATA && DATA_MATRIX)
	{
		printf("View Matrix:\n");
		matrix4_print(gle->view);
		printf("Projection Matrix:\n");
		matrix4_print(gle->projection);
	}
	gle->fps = *init_t_fps();
	gle->obj_i = 0;
	gle->obj_max = len[0];
	gle->tex_max = len[1];
}

void	display_object2(t_glfw *glfw, t_objfile **objf, t_xpm **xpm, int *len)
{
	t_gl		gle;
	t_gl_env	*gl_e;
	t_prog		progs[2];
	int			i;

	init_t_gl(&gle, xpm, len);
	gl_e = init_gl_env(objf, xpm, len, glfw->cwd);

	progs[OBJ3D].blueprints = NULL;
	progs[OBJ3D] = create_program2(glfw->cwd, VSHADER_FILE, FSHADER_FILE, get_slots_obj3d);
	create_blueprints_obj3d(&progs[OBJ3D], objf, len[0]);
	init_shader_attributes_obj3d(&progs[OBJ3D], gl_e);
	//render
	glfwGetCursorPos(glfw->win, &gle.mouse_origin_x, &gle.mouse_origin_y);
	printf("Origin mouse:\t%.2f:%.2f\n", gle.mouse_origin_y, gle.mouse_origin_x);
	// creer une liste des object crees via les blueprints ?
	// ie: liste de nouvelles instances t_blueprint_obj3d via copy, puis les afficher

	glEnable(GL_DEPTH_TEST);
	glClearDepth(-1.0f);
	glDepthFunc(GL_GREATER);
	while (!glfwWindowShouldClose(glfw->win))
	{
		if (wait_for_next_frame(&gle.fps))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.2f, 0.4f, 1.0f);

			glUseProgram(progs[OBJ3D].program);
			i = 0;
			while (i < len[0])
			{
				load_obj3d_attributes(gl_e, &progs[OBJ3D].slots.obj3d, &progs[OBJ3D].blueprints[i].obj3d);
				draw_obj3d(&progs[OBJ3D], &progs[OBJ3D].blueprints[i].obj3d);
				i++;
			}
			glfwSwapBuffers(glfw->win);
			glfwPollEvents();
			events(glfw, &gle, &progs[OBJ3D]);
		}
	}
	exit(0);
}

/*
	object mouse picking
	dessiner une image en plus avec une color par object, regarder la color au pixel x:y
*/
