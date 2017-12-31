#include <scop.h>

const char* GL_type_to_string(GLenum type)
{
	switch(type)
	{
		case GL_BOOL: return "bool";
		case GL_INT: return "int";
		case GL_FLOAT: return "float";
		case GL_FLOAT_VEC2: return "vec2";
		case GL_FLOAT_VEC3: return "vec3";
		case GL_FLOAT_VEC4: return "vec4";
		case GL_FLOAT_MAT2: return "mat2";
		case GL_FLOAT_MAT3: return "mat3";
		case GL_FLOAT_MAT4: return "mat4";
		case GL_SAMPLER_2D: return "sampler2D";
		case GL_SAMPLER_3D: return "sampler3D";
		case GL_SAMPLER_CUBE: return "samplerCube";
		case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
		default: break;
	}
	return "other";
}

void _print_programme_info_log(GLuint programme)
{
	int		max_len = 2048;
	int		len = 0;
	char	program_log[2048];
	glGetProgramInfoLog(programme, max_len, &len, program_log);
	printf("program info log for GL index %u:\n%s", programme, program_log);
}

void print_all(GLuint programme)
{
	printf("--------------------\nshader programme %i info:\n", programme);
	int params = -1;
	glGetProgramiv(programme, GL_LINK_STATUS, &params);
	printf("GL_LINK_STATUS = %i\n", params);

	glGetProgramiv(programme, GL_ATTACHED_SHADERS, &params);
	printf("GL_ATTACHED_SHADERS = %i\n", params);

	glGetProgramiv(programme, GL_ACTIVE_ATTRIBUTES, &params);
	printf("GL_ACTIVE_ATTRIBUTES = %i\n", params);
	for (int i = 0; i < params; i++)
	{
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveAttrib(programme, i, max_length, &actual_length, &size, \
							&type, name);
		if (size > 1)
			for (int j = 0; j < size; j++)
			{
				char long_name[64];
				sprintf(long_name, "%s[%i]", name, j);
				int location = glGetAttribLocation(programme, long_name);
				printf(" %i) type:%s name:%s location:%i\n",
				i, GL_type_to_string(type), long_name, location);
			}
		else
		{
			int location = glGetAttribLocation(programme, name);
			printf(" %i) type:%s name:%s location:%i\n",
			i, GL_type_to_string(type), name, location);
		}
	}

	glGetProgramiv(programme, GL_ACTIVE_UNIFORMS, &params);
	printf("GL_ACTIVE_UNIFORMS = %i\n", params);
	for (int i = 0; i < params; i++)
	{
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveUniform(programme, i, max_length, &actual_length, &size, \
							&type, name);
		if (size > 1)
			for (int j = 0; j < size; j++)
			{
				char long_name[64];
				sprintf(long_name, "%s[%i]", name, j);
				int location = glGetUniformLocation(programme, long_name);
				printf(" %i) type:%s name:%s location:%i\n",
				i, GL_type_to_string(type), long_name, location);
			}
		else
		{
			int location = glGetUniformLocation(programme, name);
			printf(" %i) type:%s name:%s location:%i\n",
			i, GL_type_to_string(type), name, location);
		}
	}
 	_print_programme_info_log(programme);
}

void		vertix_to_vector3(t_vertix *vertix, t_vector3 *vector)
{
	vector->x = vertix->x;
	vector->y = vertix->y;
	vector->z = vertix->z;
}

void		fill_color_array(float *arr, t_face *face)
{
	int		i;
	float	color;

	srand(1);
	i = 0;
	while (face)
	{
		color = (float)(rand() % 200) / 200.0f;
		arr[i + 0] = color;
		arr[i + 1] = color;
		arr[i + 2] = color;
		arr[i + 3] = color;
		arr[i + 4] = color;
		arr[i + 5] = color;
		arr[i + 6] = color;
		arr[i + 7] = color;
		arr[i + 8] = color;
		i += 9;
		face = face->next;
	}
}

void		fill_tex_array(float *arr, t_face *face)
{
	int			i;

	i = 0;
	while (face)
	{
		arr[i + 0] = face->v1->x;
		arr[i + 1] = face->v1->y;
		arr[i + 2] = face->v2->x;
		arr[i + 3] = face->v2->y;
		arr[i + 4] = face->v3->x;
		arr[i + 5] = face->v3->y;
		i += 6;
		face = face->next;
	}
}

void	perpective_vector3(t_vector3 *src, t_vector3 *dst, t_vector3 rad, float rot_direction)
{
	float		v[8];
	float		mat[16];
	t_vector3	tmp;

	rad.x *= rot_direction;
	rad.y *= rot_direction;
	rad.z *= rot_direction;
	v[0] = cosf(rad.x);
	v[1] = sinf(rad.x);
	v[2] = cosf(rad.y);
	v[3] = sinf(rad.y);
	v[4] = cosf(rad.z);
	v[5] = sinf(rad.z);
	v[6] = v[0] * v[3];
	v[7] = v[1] * v[3];
	ft_bzero(mat, sizeof(float) * 16);
	mat[0] = v[2] * v[4];
	mat[1] = -v[2] * v[5];
	mat[2] = v[3];
	mat[4] = v[7] * v[4] + v[0] * v[5];
	mat[5] = -v[7] * v[5] + v[0] * v[4];
	mat[6] = -v[1] * v[2];
	mat[8] = -v[6] * v[4] + v[1] * v[5];
	mat[9] = v[6] * v[5] + v[1] * v[4];
	mat[10] = v[0] * v[2];
	mat[15] =  1;
	tmp.x = src->x;
	tmp.y = src->y;
	tmp.z = src->z;
	dst->x = tmp.x * mat[0] + tmp.y * mat[1] + tmp.z * mat[2];
	dst->y = tmp.x * mat[4] + tmp.y * mat[5] + tmp.z * mat[6];
	dst->z = tmp.x * mat[8] + tmp.y * mat[9] + tmp.z * mat[10];
}


void		fill_points_array(float *arr, t_face *face, t_gl_env *gl_e)
{
	int			i;
	t_vector3	tmp;

	i = 0;
	while (face)
	{
		vertix_to_vector3(face->v1, &tmp);
		rot_vector3_bis(&tmp, &tmp, gl_e->rot, ROT_WAY);
		arr[i + 0] = tmp.x * gl_e->scale + gl_e->pos.x;
		arr[i + 1] = tmp.y * gl_e->scale + gl_e->pos.y;
		arr[i + 2] = tmp.z * gl_e->scale + gl_e->pos.z;
		vertix_to_vector3(face->v2, &tmp);
		rot_vector3_bis(&tmp, &tmp, gl_e->rot, ROT_WAY);
		arr[i + 3] = tmp.x * gl_e->scale + gl_e->pos.x;
		arr[i + 4] = tmp.y * gl_e->scale + gl_e->pos.y;
		arr[i + 5] = tmp.z * gl_e->scale + gl_e->pos.z;
		vertix_to_vector3(face->v3, &tmp);
		rot_vector3_bis(&tmp, &tmp, gl_e->rot, ROT_WAY);
		arr[i + 6] = tmp.x * gl_e->scale + gl_e->pos.x;
		arr[i + 7] = tmp.y * gl_e->scale + gl_e->pos.y;
		arr[i + 8] = tmp.z * gl_e->scale + gl_e->pos.z;
		i += 9;
		face = face->next;
	}
}

void		gl_compile_error(GLuint shader, char *intro)
{
	GLsizei	maxl = 1000;
	GLsizei	l;
	GLchar	*info = safe_malloc(1000);

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

void	mat_identity(float *m)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		m[i] = 0;
		if (i % 5 == 0)
			m[i] = 1;
		i++;
	}
}

void	mat_mul(float *a, float *b)
{
	int		h;
	int		w;
	int		z;
	float	m[16];

	h = -1;
	while (++h < 4)
	{
		w = -1;
		while (++w < 4)
		{
			z = -1;
			m[h * 4 + w] = 0;
			while (++z < 4)
				m[h * 4 + w] += a[h * 4 + z] * b[z * 4 + w];
		}
	}
	h = 0;
	while (h < 16)
	{
		a[h] = m[h];
		h++;
	}
}

void	set_projection_matrix(float *m, float fov)
{
	float	s;
	float	far;
	float	near;

	far = 0.001f;
	near = 100.0f;
	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	ft_bzero(m, 16);
	m[0] = s / (DEF_WIN_X / DEF_WIN_Y);
	m[5] = s;
	m[10] = -(far + near) / (far - near);
	m[11] = -1;
	m[14] = -2 * far * near / (far - near);
}

float	matrix[16];

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
	set_projection_matrix(matrix, 90);
	if (matrix[11] != -1)
	{
		printf("%s\n", "FUCK");
		exit(0);
	}

	int params = -1;
	glGetProgramiv(gl_e->shader_programme, GL_LINK_STATUS, &params);
	if (GL_TRUE != params)
	{
		fprintf(stderr,
		"ERROR: could not link shader programme GL index %u\n",
		gl_e->shader_programme);
		_print_programme_info_log(gl_e->shader_programme);
		print_all(gl_e->shader_programme);
		exit(GL_ERROR);
	}

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

	// old_draw_glfour(glfw);
	t_gl_env	*gl_e;
	int			val;
	char		boolens[348];

	ft_bzero(boolens, sizeof(char) * 348);
	gl_e = init_gl_env(objf, xpm, len);

	// glEnable(GL_CULL_FACE); // cull face
	// glCullFace(GL_BACK); // cull back face
	// glFrontFace(GL_CW); // GL_CCW for counter clock-wise
	glEnable(GL_DEPTH_TEST);
	glClearDepth(0.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	// glDepthFunc(GL_LESS);
	glDepthFunc(GL_GREATER);

	create_program(gl_e);
	glUseProgram(gl_e->shader_programme);
	glUniformMatrix4fv(gl_e->projection, 1, GL_FALSE, matrix);
	while(!glfwWindowShouldClose(glfw->win))
	{
		draw_glfour(objf[gl_e->obj_i]->obj, gl_e);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(gl_e->vao);
		glDrawArrays(GL_TRIANGLES, 0, objf[gl_e->obj_i]->obj->f_amount * 3);
		glBindVertexArray(0);
		glfwSwapBuffers(glfw->win);
		glfwPollEvents();


		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_ESCAPE))
			printf("press escape: %d\n", 666);
		if ((val = glfwGetKey(glfw->win, GLFW_KEY_ENTER)) == GLFW_PRESS \
			&& !boolens[GLFW_KEY_ENTER])
		{
			boolens[GLFW_KEY_ENTER] = 1;
			gl_e->dismod = (gl_e->dismod < MODS - 1) ? gl_e->dismod + 1 : 0;
			glUniform1i(gl_e->display_mod, gl_e->dismod);
		}
		else if (val == GLFW_RELEASE)
			boolens[GLFW_KEY_ENTER] = 0;
		if ((val = glfwGetKey(glfw->win, GLFW_KEY_SPACE)) == GLFW_PRESS \
			&& !boolens[GLFW_KEY_SPACE])
		{
			boolens[GLFW_KEY_SPACE] = 1;
			gl_e->rotate = !gl_e->rotate;
		}
		else if (val == GLFW_RELEASE)
			boolens[GLFW_KEY_SPACE] = 0;
		if ((val = glfwGetKey(glfw->win, GLFW_KEY_PAGE_DOWN)) == GLFW_PRESS \
			&& !boolens[GLFW_KEY_PAGE_DOWN])
		{
			boolens[GLFW_KEY_PAGE_DOWN] = 1;
			gl_e->obj_i = (gl_e->obj_i < gl_e->obj_len - 1) ? gl_e->obj_i + 1 : 0;
		}
		else if (val == GLFW_RELEASE)
			boolens[GLFW_KEY_PAGE_DOWN] = 0;
		if ((val = glfwGetKey(glfw->win, GLFW_KEY_PAGE_UP)) == GLFW_PRESS \
			&& !boolens[GLFW_KEY_PAGE_UP])
		{
			boolens[GLFW_KEY_PAGE_UP] = 1;
			gl_e->obj_i = (gl_e->obj_i > 0) ? gl_e->obj_i - 1 : gl_e->obj_len - 1;
		}
		else if (val == GLFW_RELEASE)
			boolens[GLFW_KEY_PAGE_UP] = 0;
		if ((val = glfwGetKey(glfw->win, GLFW_KEY_HOME)) == GLFW_PRESS \
			&& !boolens[GLFW_KEY_HOME])
		{
			boolens[GLFW_KEY_HOME] = 1;
			gl_e->tex_i = (gl_e->tex_i < gl_e->xpm_len - 1) ? gl_e->tex_i + 1 : 0;
		}
		else if (val == GLFW_RELEASE)
			boolens[GLFW_KEY_HOME] = 0;
		if ((val = glfwGetKey(glfw->win, GLFW_KEY_END)) == GLFW_PRESS \
			&& !boolens[GLFW_KEY_END])
		{
			boolens[GLFW_KEY_END] = 1;
			gl_e->tex_i = (gl_e->tex_i != 0) ? gl_e->tex_i - 1 : gl_e->xpm_len - 1;
		}
		else if (val == GLFW_RELEASE)
			boolens[GLFW_KEY_END] = 0;

		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_LEFT))//gauche
			gl_e->pos.x -= 0.01f;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_RIGHT))//droite
			gl_e->pos.x += 0.01f;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_DOWN))//bas
			gl_e->pos.y -= 0.01f;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_UP))//haut
			gl_e->pos.y += 0.01f;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_0))//pav1
			gl_e->pos.z -= 0.01f;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_1))//pav0
			gl_e->pos.z += 0.01f;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_7))//pav7
			gl_e->rot.x += RAD;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_4))//pav4
			gl_e->rot.x -= RAD;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_8))//pav8
			gl_e->rot.y += RAD;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_5))//pav5
			gl_e->rot.y -= RAD;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_9))//pav9
			gl_e->rot.z += RAD;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_6))//pav6
			gl_e->rot.z -= RAD;

		if (gl_e->rotate)
			gl_e->rot.y += RAD;
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
}
