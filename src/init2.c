/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:41 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/22 18:27:48 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_fps		*init_t_fps(void)
{
	t_fps	*fps;

	fps = (t_fps*)ft_strnew(sizeof(t_fps));
	fps->fps = FPS;
	fps->tick = 1.0 / fps->fps;
	fps->last_time = glfwGetTime();
	fps->ellapsed_time = 0.0;
	return (fps);
}

t_gl_env	*init_gl_env(t_objfile **objf, t_xpm **xpm, int *len, char *cwd)
{
	t_gl_env	*gl_e;
	int			i;

	startf("init_gl_env");
	gl_e = (t_gl_env*)ft_strnew(sizeof(t_gl_env));
	gl_e->objf = objf;
	gl_e->xpm = xpm;
	gl_e->tex_id = NULL;
	if (len[1] > 0)
		gl_e->tex_id = (GLuint*)safe_malloc(sizeof(GLuint) * len[1]);
	i = -1;
	while (++i < len[1])
		gl_e->tex_id[i] = xpm_to_glid(xpm[i]);
	gl_e->obj_len = len[0];
	gl_e->xpm_len = len[1];
	gl_e->pos.z = -5.0f;
	gl_e->rotate = 1;
	gl_e->angle = 10;
	gl_e->vector = 0.1f;
	gl_e->scale = 0.20f;
	gl_e->fov = FOV;
	gl_e->draw_mod = GL_TRIANGLES;
	gl_e->face_drawed = MAX_FACE;
	gl_e->cwd = cwd;
	gl_e->shaders[0] = ft_strjoin(gl_e->cwd, VSHADER_FILE);
	gl_e->shaders[1] = ft_strjoin(gl_e->cwd, FSHADER_FILE);
	gl_e->texture_mod = 1;
	return (gl_e);
}

void		error_callback(int error, const char *description)
{
	(void)error;
	fputs(description, stderr);
}

void		key_callback(GLFWwindow *window, int key, int scancode, \
						int action, int mods)
{
	(void)mods;
	(void)scancode;
	if (action == GLFW_PRESS)
		printf("press: %d\n", scancode);
	else if (action == GLFW_RELEASE)
		printf("release: %d\n", scancode);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

t_glfw		*init_glfw(t_glfw *glfw)
{
	startf("init_glfw");
	glfw = (t_glfw*)safe_malloc(sizeof(t_glfw));
	ft_bzero((void*)glfw, sizeof(t_glfw));
	glfw->size[0] = DEF_WIN_X;
	glfw->size[1] = DEF_WIN_Y;
	glfw->title = ft_strdup(DEF_WIN_TITLE);
	if (!glfwInit())
		ft_errexit(GLFW_INIT_FAIL, RED, GLFW_FAIL);
	glfwSetErrorCallback(error_callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if ((glfw->win = glfwCreateWindow(glfw->size[0], glfw->size[1], \
			DEF_WIN_TITLE, NULL, NULL)) == NULL)
		ft_errexit(GLFW_WIN_FAIL, RED, GLFW_FAIL);
	glfwMakeContextCurrent(glfw->win);
	glfwSetKeyCallback(glfw->win, key_callback);
	glfwSetInputMode(glfw->win, GLFW_STICKY_KEYS, 1);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		ft_errexit(GLEW_WIN_FAIL, RED, GLEW_FAIL);
	printf("GL version: %s\n", glGetString(GL_VERSION));
	return (glfw);
}
