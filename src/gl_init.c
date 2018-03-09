/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:54:15 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/09 18:32:45 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	gl_compile_error(GLuint shader, char *intro)
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

/*
**  xy 0:0 => bas gauche fenetre
*/

void	print_pixel(float x, float y)
{
	uint8_t	pix[3];

	glReadPixels(x, y, 1, 1, GL_RGB, GL_BYTE, &pix);
	printf("%d\t%d\t%d\n", pix[0], pix[1], pix[2]);
}

void	init_t_gl(t_gl *gle, t_xpm **xpm, int *len)
{
	int	i;

	if (len[1] > 0)
		gle->textures_id = (GLuint*)safe_malloc(sizeof(GLuint) * len[1]);
	i = -1;
	while (++i < len[1])
		gle->textures_id[i] = xpm_to_glid(xpm[i]);
	gle->fov = FOV;
	gle->cam = init_cam((t_vector3){0.0f, 0.0f, 5.0f}, \
						(t_vector3){DTOR(0), DTOR(0), DTOR(0)});
	gle->matrix_zero = matrix4(0, MATRIX_ROW_MAJOR);
	gle->identity = matrix4(IDENTITY, MATRIX_ROW_MAJOR);
	gle->view = view_matrix(&gle->cam, gle->identity);
	gle->projection = pro_matrix(DTOR(gle->fov), FAR, NEAR);
	if (DATA && DATA_MATRIX)
	{
		printf("View Matrix:\n");
		matrix4_print(gle->view);
		printf("Projection Matrix:\n");
		matrix4_print(gle->projection);
	}
	init_t_fps(&gle->fps);
	gle->obj_i = 0;
	gle->obj_max = len[0];
	gle->tex_max = len[1];
}

GLint	get_slot(GLuint program, const GLchar *varname, \
							GLint (func)(GLuint, const GLchar*))
{
	GLint	slot;

	slot = func(program, varname);
	printf("slot %d :\t%s\n", slot, varname);
	if (slot == -1)
	{
		glGetError();
		ft_errexit("Failed to get slot", RED, GL_ERROR);
	}
	return (slot);
}

t_cam	init_cam(t_vector3 pos, t_vector3 rot)
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
