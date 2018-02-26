/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:45:04 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/26 19:33:57 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
	glBindBuffer(GL_ARRAY_BUFFER, blueprint->vertex_obj.vertex);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float), points, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, blueprint->blackwhite.vertex);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float), colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, blueprint->vertex_texture.vertex);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 6 * sizeof(float), tex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, blueprint->vertex_texture_cylinder.vertex);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 6 * sizeof(float), tex_cylinder, GL_STATIC_DRAW);
	blueprint->rotate = 1;
	blueprint->pos = (t_vector3){0.0f, 0.0f, 0.0f};
	blueprint->rot = (t_vector3){0.0f, 0.0f, 0.0f};
	blueprint->current_faces = obj->f_amount;
	blueprint->max_faces = obj->f_amount;
	if (obj->mat)
		blueprint->plain_color = (t_vector3){obj->mat->kd[0], obj->mat->kd[1], obj->mat->kd[2]};
}

static void		create_buffer(t_vbo *vbo, int size, GLenum type)
{
	glGenBuffers(1, &vbo->vertex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo->vertex);
	glVertexAttribPointer(vbo->slot, size, type, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vbo->slot);
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

void	display_object2(t_glfw *glfw, t_objfile **objf, t_xpm **xpm, int *len)
{
	t_gl_env	*gl_e;
	t_fps		*fps;
	t_prog		prog[2];(void)prog;

	gl_e = init_gl_env(objf, xpm, len, glfw->cwd);
	fps = init_t_fps();

	prog[OBJ3D].blueprints = NULL;
	prog[OBJ3D] = create_program2(glfw->cwd, VSHADER_FILE, FSHADER_FILE, get_slots_obj3d);
	create_blueprints_obj3d(&prog[OBJ3D], objf, len[0]);

	exit(0);
}