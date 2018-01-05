#include <scop.h>

// vec2	cylinder_mapping()
// {
// 	float	u;
// 	float	v;
//
// 	u = 0.5 + atan(position.z, position.x) / PI * 0.5;
// 	v = position.y / 10.0;
// 	return (vec2(u, v) * 15);
// }

void		gl_compile_error(GLuint shader, char *intro)
{
	GLsizei		maxl;
	GLsizei		l;
	GLchar		*info;

	maxl = 1000;
	info = safe_malloc(1000);
	glGetShaderInfoLog(shader, maxl, &l, info);
	printf("%s\n%s\n", intro, info);
	ft_errexit(GL_COMPILE_SHADER, RED, GL_ERROR);
}

GLuint		init_shader(char *filename, int type)
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

void		create_program(t_gl_env *gl_e)
{
	glGenVertexArrays(1, &gl_e->vao);
	glBindVertexArray(gl_e->vao);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &gl_e->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &gl_e->colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	glEnable(GL_TEXTURE_2D);
	glGenBuffers(1, &gl_e->tex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->tex_vbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);

	gl_e->vshader = init_shader(VSHADER_FILE, GL_VERTEX_SHADER);
	gl_e->fshader = init_shader(FSHADER_FILE, GL_FRAGMENT_SHADER);
	gl_e->shader_programme = glCreateProgram();
	glAttachShader(gl_e->shader_programme, gl_e->vshader);
	glAttachShader(gl_e->shader_programme, gl_e->fshader);
	glLinkProgram(gl_e->shader_programme);

	gl_e->display_mod = glGetUniformLocation(gl_e->shader_programme, "dismod");
	gl_e->projection = glGetUniformLocation(gl_e->shader_programme, "pro");

	int params = -1;
	glGetProgramiv(gl_e->shader_programme, GL_LINK_STATUS, &params);
	if (GL_TRUE != params)
		print_programme_info_log(gl_e->shader_programme);

	// glDeleteVertexArrays(1, &gl_e->vao);
	// glDeleteProgram(gl_e->shader_programme);
}

void		draw_glfour(t_obj *obj, t_gl_env *gl_e)
{
	// printf("__ draw_glfour\n");
	float	points[obj->f_amount * 9];
	float	colors[obj->f_amount * 9];
	float	tex[obj->f_amount * 6];

	fill_points_array(points, obj->f, gl_e);
	fill_color_array(colors, obj->f);
	fill_tex_array(tex, obj->f);

	glBindBuffer(GL_ARRAY_BUFFER, gl_e->vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float), points, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, gl_e->colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float), colors, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, gl_e->tex_vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 6 * sizeof(float), tex, GL_STATIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, gl_e->tex_id[gl_e->tex_i]);
}

void		display_object(t_glfw *glfw, t_objfile **objf, t_xpm **xpm, int *len)
{
	printf("__ display_object\n");
	t_gl_env	*gl_e;
	char		*boolens;
	t_matrix4	promatrix;

	boolens = (char*)safe_malloc(sizeof(char) * 348);
	ft_bzero(boolens, sizeof(char) * 348);
	gl_e = init_gl_env(objf, xpm, len);

	glEnable(GL_DEPTH_TEST);
	glClearDepth(-1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	// glDepthFunc(GL_LESS);
	glDepthFunc(GL_GREATER);

	create_program(gl_e);
	glUseProgram(gl_e->shader_programme);

	promatrix = pro_matrix(DTOR(FOVX), DTOR(FOVY), FAR, NEAR);
	promatrix = matrix4_mult(promatrix, view_matrix());
	printf("Projection * View Matrix:\n");
	matrix4_print(promatrix);
	glUniformMatrix4fv(gl_e->projection, 1, GL_FALSE, promatrix.m.e);

	while(!glfwWindowShouldClose(glfw->win))
	{
		draw_glfour(objf[gl_e->obj_i]->obj, gl_e);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(gl_e->vao);
		glDrawArrays(GL_TRIANGLES, 0, objf[gl_e->obj_i]->obj->f_amount * 3);
		glBindVertexArray(0);
		glfwSwapBuffers(glfw->win);
		glfwPollEvents();
		events(glfw, gl_e, &boolens);
	}
}
