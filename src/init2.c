/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:07:41 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/07 06:49:42 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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

void		error_callback(int error, const char *description)
{
	(void)error;
	fputs(description, stderr);
}

t_glfw		*init_glfw(t_glfw *glfw)
{
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
	glfwSetInputMode(glfw->win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(glfw->win, GLFW_STICKY_KEYS, 1);
	glfwSetInputMode(glfw->win, GLFW_STICKY_MOUSE_BUTTONS, 1);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		ft_errexit(GLEW_WIN_FAIL, RED, GLEW_FAIL);
	printf("GL version: %s\n", glGetString(GL_VERSION));
	return (glfw);
}
