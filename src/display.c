#include <scop.h>

void	*draw_face2(void *f, t_arg args)
{
	// printf("__ draw_face2\n");
	t_face	*face;
	t_mat	*mat;

	face = (t_face*)f;
	mat = ((t_obj*)(args.ptr[1]))->mat;
	glBegin(DRAW_MODE);
	if (mat)
		glColor3f(mat->ka[0], mat->ka[1], mat->ka[2]);
	else
		glColor3ub(255, 0, 0);
	float coef = 1;
	glVertex3d(face->v1->x / coef, face->v1->y / coef, face->v1->z / coef);
	glVertex3d(face->v2->x / coef, face->v2->y / coef, face->v2->z / coef);
	glVertex3d(face->v3->x / coef, face->v3->y / coef, face->v3->z / coef);
	if (face->v4)
		glVertex3d(face->v4->x / coef, face->v4->y / coef, face->v4->z / coef);
	glEnd();
	return (NULL);
}

void	print_obj_stats(t_obj *obj, t_gl_env *gl_e)
{
	if (gl_e->tex == 1)
		printf("tex_Color\n");
	else if (gl_e->tex == 2 && obj->mat)
		printf("%s\n", obj->mat->name);
	else
		printf("custom_color\n");
	printf("%.1f\t%.1f\t%.1f\n", \
		gl_e->pos[0], gl_e->pos[1], gl_e->pos[2]);
	printf("%d\t%d\t%d\n------------------\n", \
		gl_e->rot[0], gl_e->rot[1], gl_e->rot[2]);
}

t_void	*draw_face_texture(t_void *f, float cf)
{
	t_face	*face;

	face = (t_face*)f;
	glBegin(GL_TRIANGLES);
	glColor3ub(255, 255, 255);
	glTexCoord2d(face->v1->x, face->v1->y);
	glVertex3d(face->v1->x / cf, face->v1->y / cf, face->v1->z / cf);
	glTexCoord2d(face->v2->x, face->v2->y);
	glVertex3d(face->v2->x / cf, face->v2->y / cf, face->v2->z / cf);
	glTexCoord2d(face->v3->x, face->v3->y);
	glVertex3d(face->v3->x / cf, face->v3->y / cf, face->v3->z / cf);
	glEnd();
	return (NULL);
}

t_void	*draw_face(t_void *f, t_arg args)
{
	t_face			*face;
	t_mat			*mat;
	unsigned char	color;
	float			cf;

	cf = 1.0f;
	face = (t_face*)f;
	mat = ((t_obj*)(args.ptr[1]))->mat;
	color = rand() % 200;
	if (*(int*)(args.ptr[3]) == 1)
		draw_face_texture(f, cf);
	else
	{
		glBegin(GL_TRIANGLES);
		if (mat && *(int*)(args.ptr[3]) == 2)
			glColor3f(mat->kd[0], mat->kd[1], mat->kd[2]);
		else
			glColor3ub(color, color, color);
		glVertex3d(face->v1->x / cf, face->v1->y / cf, face->v1->z / cf);
		glVertex3d(face->v2->x / cf, face->v2->y / cf, face->v2->z / cf);
		glVertex3d(face->v3->x / cf, face->v3->y / cf, face->v3->z / cf);
		glEnd();
	}
	return (NULL);
}

void		draw_obj(t_glfw *glfw, t_obj *obj, t_gl_env *gl_e)
{
	float	c;
	float	scale;

	c = 0.0f;
	scale = 0.20f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
	glTranslatef(gl_e->pos[0], gl_e->pos[1], gl_e->pos[2]);
	glRotated(gl_e->rot[0], 1, 0, 0);
	glRotated(gl_e->rot[1], 0, 1, 0);
	glRotated(gl_e->rot[2], 0, 0, 1);
	print_obj_stats(obj, gl_e);
	glScalef(scale, scale, scale);
	glDepthFunc(GL_LEQUAL);
	srand(1);
	for_list_args((t_void*)(obj->f), \
		init_args(glfw, obj, &c, &gl_e->tex), draw_face);
	glFlush();
	// SDL_GL_SwapWindow(glfw->win);
}

void		old_draw_glfour(t_glfw *glfw)
{
	const char *vs_source[] =
	{
		"#version 410 core                                                 \n"
		"                                                                  \n"
		"void main(void)                                                   \n"
		"{                                                                 \n"
		"    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
		"                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
		"                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
		"                                                                  \n"
		"    gl_Position = vertices[gl_VertexID];                          \n"
		"}                                                                 \n"
	};
	printf("%s\n", *vs_source);
	const char *fs_source[] =
	{
		"#version 410 core                                                 \n"
		"                                                                  \n"
		"out vec4 color;                                                   \n"
		"                                                                  \n"
		"void main(void)                                                   \n"
		"{                                                                 \n"
		"    color = vec4(0.0, 0.8, 1.0, 1.0);                             \n"
		"}                                                                 \n"
	};
	// printf("%s\n", *fs_source);

	GLuint	program;
	GLuint	vao;
	GLuint	fs;
	GLuint	vs;
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, fs_source, NULL);
	glCompileShader(fs);
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, vs_source, NULL);
	glCompileShader(vs);
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glUseProgram(program);
	while (!glfwWindowShouldClose(glfw->win))
	{
		static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, green);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(glfw->win);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(program);
}

void		vertix_to_vector3(t_vertix *vertix, t_vector3 *vector)
{
	vector->x = vertix->x;
	vector->y = vertix->y;
	vector->z = vertix->z;
}

void		fill_points_array(float *arr, t_face *face, float scale, float *offset, t_vector3 rot)
{
	int			i;
	t_vector3	tmp;

	i = 0;
	while (face)
	{
		vertix_to_vector3(face->v1, &tmp);
		rot_vector3_bis(&tmp, &tmp, rot, ROT_WAY);
		arr[i + 0] = tmp.x * scale + offset[0];
		arr[i + 1] = tmp.y * scale + offset[1];
		arr[i + 2] = tmp.z * scale + offset[2];
		vertix_to_vector3(face->v2, &tmp);
		rot_vector3_bis(&tmp, &tmp, rot, ROT_WAY);
		arr[i + 3] = tmp.x * scale + offset[0];
		arr[i + 4] = tmp.y * scale + offset[1];
		arr[i + 5] = tmp.z * scale + offset[2];
		vertix_to_vector3(face->v3, &tmp);
		rot_vector3_bis(&tmp, &tmp, rot, ROT_WAY);
		arr[i + 6] = tmp.x * scale + offset[0];
		arr[i + 7] = tmp.y * scale + offset[1];
		arr[i + 8] = tmp.z * scale + offset[2];
		i += 9;
		face = face->next;
	}
}

void		new_draw_glfour(t_glfw *glfw, t_obj *obj)
{
	float		scale = 0.20f;
	float		offset[3] = {0, 0, 0};
	t_vector3	rot = {DTOR(90), DTOR(10), DTOR(45)};

	int		len = obj->f_amount * 9;
	float	points[len];
	fill_points_array(points, obj->f, scale, offset, rot);
	int i = 0;
	while (i < obj->f_amount)
	{
		printf("%f\t%f\t%f\n", points[i + 0], points[i + 1], points[i + 2]);
		printf("%f\t%f\t%f\n", points[i + 3], points[i + 4], points[i + 5]);
		printf("%f\t%f\t%f\n\n", points[i + 6], points[i + 7], points[i + 8]);
		i++;
	}
	printf("i: %d\n", i);
	printf("points amount: %d\n", obj->f_amount);
	// exit(0);

	GLuint vbo = 0;
	GLuint vao = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, len * sizeof(float), points, GL_STATIC_DRAW);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	const char *vertex_shader[] =
	{
		"#version 410\n"
		"in vec3 vp;"
		"void main() {"
		"  gl_Position = vec4(vp, 1.0);"
		"}"
	};
	const char* fragment_shader[] =
	{
		"#version 410\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
		"}"
	};
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, fragment_shader, NULL);
	glCompileShader(fs);
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	while(!glfwWindowShouldClose(glfw->win)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, obj->f_amount * 3);
		glfwSwapBuffers(glfw->win);
		glfwPollEvents();
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_ESCAPE))
			printf("press escape: %d\n", 666);
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_ENTER))//ENTER
			printf("Changing material/texture/color.\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_SPACE))//SPACE
			printf("Rotatio on/off\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_LEFT))//gauche
			printf("going left\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_RIGHT))//droite
			printf("going right\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_DOWN))//bas
			printf("going bot\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_UP))//haut
			printf("going top\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_1))//pav1
			printf("going far\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_0))//pav0
			printf("going close\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_7))//pav7
			printf("rot X up\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_4))//pav4
			printf("rot X down\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_8))//pav8
			printf("rot Y up\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_5))//pav5
			printf("rot Y down\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_9))//pav9
			printf("rot Z up\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_6))//pav6
			printf("rot Z down\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_PAGE_UP))//pageUp
			printf("object ind up\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_PAGE_DOWN))//pageDown
			printf("object ind down\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_HOME))//home
			printf("texture up\n");
		else if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_END))//end
			printf("texture down\n");
	}
	/*
	36	ENTER
	49	SPACE
	12	gauche
	12	droite
	12	bas
	12	haut
	83	pav1
	82	pav0
	89	pav7
	86	pav4
	91	pav8
	87	pav5
	92	pav9
	88	pav6
	*/
	exit(0);
}

void		display_object(t_glfw *glfw, t_objfile **objf, t_xpm **xpm, int *len)
{
	printf("__ display_object\n");

	// old_draw_glfour(glfw);
	new_draw_glfour(glfw, objf[0]->obj);

	t_sdl_env	*s_e;
	t_gl_env	*gl_e;

	s_e = init_sdl_env();
	gl_e = init_gl_env(objf, xpm, len);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// gluPerspective(90, glfw->size[0] / glfw->size[1], 0.1f, 1000);
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, gl_e->tex_id[0]);
	while (!s_e->quit)
	{
		// s_e->start_time = SDL_GetTicks();
		// while (SDL_PollEvent(&s_e->event) && !s_e->quit)
		// 	if (s_e->event.type == SDL_KEYDOWN && !s_e->event.key.repeat)
		// 		events(s_e->event.key.keysym.scancode, glfw, s_e, gl_e);
		// s_e->current_time = SDL_GetTicks();
		// s_e->ellapsed_time = s_e->current_time - s_e->last_time;
		// s_e->last_time = s_e->current_time;
		// gl_e->rot[1] += (gl_e->rotate) ? s_e->ellapsed_time / 20 : 0;
		draw_obj(glfw, gl_e->objf[gl_e->obj_i]->obj, gl_e);
		// s_e->ellapsed_time = SDL_GetTicks() - s_e->start_time;
		// if (s_e->ellapsed_time < s_e->tick)
		// 	SDL_Delay(s_e->tick - s_e->ellapsed_time);
	}
}
