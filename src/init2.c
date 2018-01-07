/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:41 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/01/05 17:07:44 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_sdl_env	*init_sdl_env(void)
{
	t_sdl_env	*sdl_e;

	startf("init_sdl_env");
	sdl_e = (t_sdl_env*)safe_malloc(sizeof(t_sdl_env));
	ft_bzero(sdl_e, sizeof(t_sdl_env));
	sdl_e->tick = FRAME_TICK;
	sdl_e->last_time = 0;
	deep--;
	return (sdl_e);
}

t_gl_env	*init_gl_env(t_objfile **objf, t_xpm **xpm, int *len)
{
	t_gl_env	*gl_e;
	int			i;

	startf("init_gl_env");
	gl_e = (t_gl_env*)safe_malloc(sizeof(t_gl_env));
	ft_bzero(gl_e, sizeof(t_gl_env));
	gl_e->objf = objf;
	gl_e->xpm = xpm;
	gl_e->tex_id = NULL;
	if (len[1] > 0)
		gl_e->tex_id = (GLuint*)safe_malloc(sizeof(GLuint) * len[1]);
	i = 0;
	while (i < len[1])
	{
		gl_e->tex_id[i] = xpm_to_glid(xpm[i]);
		i++;
	}
	gl_e->obj_len = len[0];
	gl_e->xpm_len = len[1];
	gl_e->pos.z = -1.0f;
	gl_e->rotate = 1;
	gl_e->angle = 10;
	gl_e->vector = 0.1f;
	gl_e->scale = 0.20f;
	deep--;
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
	deep--;
	return (glfw);
}
