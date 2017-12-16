#include <scop.h>

t_xpm	*init_xpm(void)
{
	static int	id = 0;
	t_xpm		*xpm;

	xpm = (t_xpm*)safe_malloc(sizeof(t_xpm));
	ft_bzero((void*)xpm, sizeof(t_xpm));
	xpm->next = NULL;
	xpm->name = NULL;
	xpm->path = NULL;
	xpm->data = NULL;
	xpm->id = id;
	id++;
	return (xpm);
}

void error_callback(int error, const char* description)
{
	(void)error;
	fputs(description, stderr);
}

void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)mods;
	(void)scancode;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

t_glfw	*init_glfw(void)
{
	printf("__ init_glfw\n");
	t_glfw	*glfw;

	glfw = (t_glfw*)safe_malloc(sizeof(t_glfw));
	ft_bzero((void*)glfw, sizeof(t_glfw));
	glfw->size[0] = DEF_WIN_X;
	glfw->size[1] = DEF_WIN_Y;
	glfw->mid[0] = glfw->size[0] / 2;
	glfw->mid[1] = glfw->size[1] / 2;
	glfw->title = ft_strdup(DEF_WIN_TITLE);
	glfw->win = NULL;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed initialize GLFW.");
		exit(EXIT_FAILURE);
	}
	glfwSetErrorCallback(error_callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfw->win = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (glfw->win == NULL)
	{
		fprintf(stderr, "Failed to create GLFW window.");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(glfw->win);
	glfwSetKeyCallback(glfw->win, key_callback);
	glewExperimental = GL_TRUE;
	glewInit();
	printf("GL version: %s\n", glGetString(GL_VERSION));// sleep(5);exit(0);

	static const char * vs_source[] =
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
	// printf("%s\n", *vs_source);

	// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
	static const char * fs_source[] =
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

	GLuint program;
	GLuint vao;
	program = glCreateProgram();
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, fs_source, NULL);
	glCompileShader(fs);
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, vs_source, NULL);
	glCompileShader(vs);
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
	exit(0);
	return (glfw);
}

t_env	*init_env(void)
{
	t_env	*e;

	e = (t_env*)safe_malloc(sizeof(t_env));
	e->objfile = NULL;
	e->mtlfile = NULL;
	e->xpmfile = NULL;
	e->dir = NULL;
	e->glfw = NULL;
	e->chart = init_rgb();
	return (e);
}

t_obj	*init_obj(void)
{
	static int	id = 0;
	t_obj		*object;

	object = (t_obj*)safe_malloc(sizeof(t_obj));
	object->id = id;
	object->id_char = ft_itoa(id);
	object->name = ft_strjoin("Object #", object->id_char);
	object->mtllib = NULL;
	object->mtlfile = NULL;
	object->mat_name = NULL;
	object->mat = NULL;
	object->smooth = 0;
	object->v = NULL;
	object->f = NULL;
	object->v_amount = 0;
	object->f_amount = 0;
	object->next = NULL;
	id++;
	return (object);
}

t_mat	*init_mat(void)
{
	static int	id = 0;
	t_mat		*material;

	material = (t_mat*)safe_malloc(sizeof(t_mat));
	material->id = id;
	material->id_char = ft_itoa(id);
	material->name = ft_strjoin("Material #", material->id_char);
	material->ns = 0.0f;
	material->ka[0] = 0.0f;
	material->ka[1] = 0.0f;
	material->ka[2] = 0.0f;
	material->kd[0] = 0.0f;
	material->kd[1] = 0.0f;
	material->kd[2] = 0.0f;
	material->ks[0] = 0.0f;
	material->ks[1] = 0.0f;
	material->ks[2] = 0.0f;
	material->ni = 0.0f;
	material->d = 0.0f;
	material->illum = 0;
	material->next = NULL;
	id++;
	return (material);
}
