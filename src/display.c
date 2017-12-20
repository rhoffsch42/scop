#include <scop.h>

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

const char* GL_type_to_string(GLenum type) {
  switch(type) {
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

void print_all(GLuint programme) {
  printf("--------------------\nshader programme %i info:\n", programme);
  int params = -1;
  glGetProgramiv(programme, GL_LINK_STATUS, &params);
  printf("GL_LINK_STATUS = %i\n", params);

  glGetProgramiv(programme, GL_ATTACHED_SHADERS, &params);
  printf("GL_ATTACHED_SHADERS = %i\n", params);

  glGetProgramiv(programme, GL_ACTIVE_ATTRIBUTES, &params);
  printf("GL_ACTIVE_ATTRIBUTES = %i\n", params);
  for (int i = 0; i < params; i++) {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveAttrib (
      programme,
      i,
      max_length,
      &actual_length,
      &size,
      &type,
      name
    );
    if (size > 1) {
      for(int j = 0; j < size; j++) {
        char long_name[64];
        sprintf(long_name, "%s[%i]", name, j);
        int location = glGetAttribLocation(programme, long_name);
        printf("  %i) type:%s name:%s location:%i\n",
          i, GL_type_to_string(type), long_name, location);
      }
    } else {
      int location = glGetAttribLocation(programme, name);
      printf("  %i) type:%s name:%s location:%i\n",
        i, GL_type_to_string(type), name, location);
    }
  }

  glGetProgramiv(programme, GL_ACTIVE_UNIFORMS, &params);
  printf("GL_ACTIVE_UNIFORMS = %i\n", params);
  for(int i = 0; i < params; i++) {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveUniform(
      programme,
      i,
      max_length,
      &actual_length,
      &size,
      &type,
      name
    );
    if(size > 1) {
      for(int j = 0; j < size; j++) {
        char long_name[64];
        sprintf(long_name, "%s[%i]", name, j);
        int location = glGetUniformLocation(programme, long_name);
        printf("  %i) type:%s name:%s location:%i\n",
          i, GL_type_to_string(type), long_name, location);
      }
    } else {
      int location = glGetUniformLocation(programme, name);
      printf("  %i) type:%s name:%s location:%i\n",
        i, GL_type_to_string(type), name, location);
    }
  }

  _print_programme_info_log(programme);
  // exit(0);
}

void		vertix_to_vector3(t_vertix *vertix, t_vector3 *vector)
{
	vector->x = vertix->x;
	vector->y = vertix->y;
	vector->z = vertix->z;
}

void		fill_color_array(float *arr, t_face *face, t_gl_env *gl_e)
{
	int			i;

	(void)gl_e;
	i = 0;
	while (face)
	{
		arr[i + 0] = 1.0f;
		arr[i + 1] = 0.0f;
		arr[i + 2] = 0.0f;
		arr[i + 3] = 0.0f;
		arr[i + 4] = 1.0f;
		arr[i + 5] = 0.0f;
		arr[i + 6] = 0.0f;
		arr[i + 7] = 0.0f;
		arr[i + 8] = 1.0f;
		i += 9;
		face = face->next;
	}
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
// float colours[] = {
//   1.0f, 0.0f,  0.0f,
//   0.0f, 1.0f,  0.0f,
//   0.0f, 0.0f,  1.0f
// };
void		show_why(GLuint shader)
{
	GLsizei	maxl = 1000;
	GLsizei	l;
	GLchar	*info = malloc(1000);

	glGetShaderInfoLog(shader, maxl, &l, info);
	printf("%s\n", info);
	// void glGetShaderInfoLog(	GLuint shader,
 	// GLsizei maxLength,
 	// GLsizei *length,
 	// GLchar *infoLog);
	exit(0);
}

void		draw_glfour(t_glfw* glfw, t_obj *obj, t_xpm *xpm, t_gl_env *gl_e)
{
	printf("__ draw_glfour\n");
	(void)xpm;
	(void)glfw;
	int		len = obj->f_amount * 9;
	float	points[len];
	float	colours[len];
	fill_points_array(points, obj->f, gl_e);
	printf("___ data points generated\n");
	fill_color_array(colours, obj->f, gl_e);
	printf("___ data colours generated\n");
	// int i = 0;
	// while (i < obj->f_amount)
	// {
	// 	printf("%f\t%f\t%f\n", points[i + 0], points[i + 1], points[i + 2]);
	// 	printf("%f\t%f\t%f\n", points[i + 3], points[i + 4], points[i + 5]);
	// 	printf("%f\t%f\t%f\n\n", points[i + 6], points[i + 7], points[i + 8]);
	// 	i++;
	// }
	// printf("i: %d\n", i);
	// printf("points amount: %d\n", obj->f_amount);

	glGenBuffers(1, &gl_e->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->vbo);
	glBufferData(GL_ARRAY_BUFFER, len * sizeof(float), points, GL_STATIC_DRAW);

	GLuint colours_vbo = 0;
	glGenBuffers(1, &colours_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
	glBufferData(GL_ARRAY_BUFFER, len * sizeof(float), colours, GL_STATIC_DRAW);

	glGenVertexArrays(1, &gl_e->vao);
	glBindVertexArray(gl_e->vao);
	// glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, gl_e->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);// = glVertexAttribPointer(0, ...) <- this number
	glEnableVertexAttribArray(1);// = glVertexAttribPointer(1, ...) <- this number

	/*
	"#version 410\n"
	*/
	const char *vertex_shader[] =
	{
		"#version 410\n"
		"layout(location = 0) in vec3 vertex_position;"
		"layout(location = 1) in vec3 vertex_colour;"

		"out vec3 colour;"

		"void main() {"
		"  colour = vertex_colour;"
		"  gl_Position = vec4(vertex_position, 1.0);"
		"}"
	};
	const char *vertex_shader_old[] =
	{
		"#version 410\n"
		"in vec3 vp;"
		"void main() {"
		"  gl_Position = vec4(vp, 1.0);"
		"}"
	};(void)vertex_shader_old;

	const char *fragment_shader[] =
	{
		"#version 410\n"
		"in vec3 colour;"
		"out vec4 frag_colour;"

		"void main() {"
		"  frag_colour = vec4(colour, 1.0);"
		"}"
	};
	const char *fragment_shader_old[] =
	{
		"#version 410\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
		"}"
	};(void)fragment_shader_old;

	GLint	rep;
	gl_e->vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(gl_e->vs, 1, vertex_shader, NULL);
	glCompileShader(gl_e->vs);
	glGetShaderiv(gl_e->vs, GL_COMPILE_STATUS, &rep);
	if (rep == GL_FALSE)
	{
		printf("vertex_shader compilation error:\n");
		show_why(gl_e->vs);
	}

	gl_e->fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(gl_e->fs, 1, fragment_shader, NULL);
	glCompileShader(gl_e->fs);
	glGetShaderiv(gl_e->fs, GL_COMPILE_STATUS, &rep);
	if (rep == GL_FALSE)
	{
		printf("fragment_shader compilation error:\n");
		show_why(gl_e->fs);
	}

	gl_e->shader_programme = glCreateProgram();
	glAttachShader(gl_e->shader_programme, gl_e->fs);
	glAttachShader(gl_e->shader_programme, gl_e->vs);
	// glBindAttribLocation(gl_e->shader_programme, 0, "vertex_position");//mac version for layout keyword (gl 3.2)
	// glBindAttribLocation(gl_e->shader_programme, 1, "vertex_colour");//mac version for layout keyword (gl 3.2)
	glLinkProgram(gl_e->shader_programme);

	int params = -1;
	glGetProgramiv(gl_e->shader_programme, GL_LINK_STATUS, &params);
	if (GL_TRUE != params)
	{
		fprintf(stderr,
		"ERROR: could not link shader programme GL index %u\n",
		gl_e->shader_programme);
		_print_programme_info_log(gl_e->shader_programme);
		print_all(gl_e->shader_programme);
		exit(0);
	}
	else
		printf("PG LINK OK\n");
	print_all(gl_e->shader_programme);

	// glDeleteVertexArrays(1, &gl_e->vao);
	// glDeleteProgram(gl_e->shader_programme);
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
	while(!glfwWindowShouldClose(glfw->win)) {
		draw_glfour(glfw, objf[gl_e->obj_i]->obj, xpm[gl_e->tex_i], gl_e);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(gl_e->shader_programme);
		glBindVertexArray(gl_e->vao);
		glDrawArrays(GL_TRIANGLES, 0, objf[gl_e->obj_i]->obj->f_amount * 3);
		glfwSwapBuffers(glfw->win);
		glfwPollEvents();

		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_ESCAPE))
			printf("press escape: %d\n", 666);
		if ((val = glfwGetKey(glfw->win, GLFW_KEY_ENTER)) == GLFW_PRESS \
			&& !boolens[GLFW_KEY_ENTER])
		{
			boolens[GLFW_KEY_ENTER] = 1;
			printf("Changing material/texture/color.\n");
		}
		else if (val == GLFW_RELEASE)
			boolens[GLFW_KEY_ENTER] = 0;
		if ((val = glfwGetKey(glfw->win, GLFW_KEY_SPACE)) == GLFW_PRESS \
			&& !boolens[GLFW_KEY_SPACE])
		{
			boolens[GLFW_KEY_SPACE] = 1;
			gl_e->rotate = !gl_e->rotate;
			printf("Rotation on/off\n");
		}
		else if (val == GLFW_RELEASE)
			boolens[GLFW_KEY_SPACE] = 0;
		if ((val = glfwGetKey(glfw->win, GLFW_KEY_PAGE_DOWN)) == GLFW_PRESS \
			&& !boolens[GLFW_KEY_PAGE_DOWN])
		{
			boolens[GLFW_KEY_PAGE_DOWN] = 1;
			gl_e->obj_i = (gl_e->obj_i < gl_e->obj_len - 1) ? gl_e->obj_i + 1 : 0;
			printf("object ind up\n");
		}
		else if (val == GLFW_RELEASE)
			boolens[GLFW_KEY_PAGE_DOWN] = 0;
		if ((val = glfwGetKey(glfw->win, GLFW_KEY_PAGE_UP)) == GLFW_PRESS \
			&& !boolens[GLFW_KEY_PAGE_UP])
		{
			boolens[GLFW_KEY_PAGE_UP] = 1;
			gl_e->obj_i = (gl_e->obj_i > 0) ? gl_e->obj_i - 1 : gl_e->obj_len - 1;
			printf("object ind down\n");
		}
		else if (val == GLFW_RELEASE)
			boolens[GLFW_KEY_PAGE_UP] = 0;
		if ((val = glfwGetKey(glfw->win, GLFW_KEY_HOME)) == GLFW_PRESS \
			&& !boolens[GLFW_KEY_HOME])
		{
			boolens[GLFW_KEY_HOME] = 1;
			gl_e->tex_i = (gl_e->tex_i < gl_e->xpm_len - 1) ? gl_e->tex_i + 1 : 0;
			printf("texture up\n");
		}
		else if (val == GLFW_RELEASE)
			boolens[GLFW_KEY_HOME] = 0;
		if ((val = glfwGetKey(glfw->win, GLFW_KEY_END)) == GLFW_PRESS \
			&& !boolens[GLFW_KEY_END])
		{
			boolens[GLFW_KEY_END] = 1;
			gl_e->tex_i = (gl_e->tex_i != 0) ? gl_e->tex_i - 1 : gl_e->xpm_len - 1;
			printf("texture down\n");
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
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_1))//pav1
			gl_e->pos.z += 0.01f;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_0))//pav0
			gl_e->pos.z -= 0.01f;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_7))//pav7
			gl_e->rot.x -= RAD;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_4))//pav4
			gl_e->rot.x += RAD;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_8))//pav8
			gl_e->rot.y -= RAD;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_5))//pav5
			gl_e->rot.y += RAD;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_9))//pav9
			gl_e->rot.z -= RAD;
		if (GLFW_PRESS == glfwGetKey(glfw->win, GLFW_KEY_KP_6))//pav6
			gl_e->rot.z += RAD;

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
