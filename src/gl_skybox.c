/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_skybox.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 13:36:19 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/03/08 14:43:41 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_obj			*get_skybox_obj(char *cwd)
{
	t_obj		*obj;
	char		*path;

	obj = NULL;
	path = ft_strjoin(cwd, SKYBOX_FILE);
	if (is_readable(path))
		obj = build_objects(path);
	else
		ft_errexit(CUBEMAP_MISS_OBJ, RED, GL_ERROR);
	free(path);
	return (obj);
}

static void		build_cubemap(t_prog *prog, t_xpm **xpm)
{
	int			i;

	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &prog->blueprints[0].skybox.tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, prog->blueprints[0].skybox.tex);
	i = 0;
	while (i < 6)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, \
			xpm[i]->width, xpm[i]->height, \
			0, GL_RGB, GL_UNSIGNED_BYTE, xpm[i]->data);
		printf("cubemap %s %dx%d\n", \
			xpm[i]->name, xpm[i]->width, xpm[i]->height);
		i++;
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glUniform1i(prog->slots.skybox.cubemap, 0);
}

static void		get_slots_skybox(t_prog *prog)
{
	int				(*fun)(unsigned int, const char *);
	t_skybox_slots	*slots;

	slots = &prog->slots.skybox;
	fun = glGetUniformLocation;
	slots->mat4_v = get_slot(prog->program, "V", fun);
	slots->mat4_p = get_slot(prog->program, "P", fun);
	slots->cubemap = get_slot(prog->program, "cubemap", fun);
	fun = glGetAttribLocation;
	slots->vertex_position = get_slot(prog->program, "vertex_position", fun);
}

static void		create_blueprints_skybox(t_prog *prog, t_obj *cube)
{
	t_blueprint_skybox	*skybox;

	prog->blueprints = (t_blueprint*)safe_malloc(sizeof(t_blueprint));
	skybox = &prog->blueprints[0].skybox;
	glGenVertexArrays(1, &skybox->vao);
	glBindVertexArray(skybox->vao);
	glEnableVertexAttribArray(0);
	skybox->v_skybox.slot = prog->slots.skybox.vertex_position;
	create_buffer(&skybox->v_skybox, 3, GL_FLOAT);
	fill_buffer(skybox->v_skybox.vbo, cube, fill_points_array, 3);
}

void			create_program_skybox(t_prog *program, char *cwd, t_xpm **xpm, \
										int xpm_len)
{
	t_obj		*obj;
	t_xpm		*xpm_cube[6];
	int			i;
	char		*shaders[2];

	xpm_cube[0] = get_xpm(xpm, xpm_len, CUBEMAP_PX_TEX);
	xpm_cube[1] = get_xpm(xpm, xpm_len, CUBEMAP_NX_TEX);
	xpm_cube[2] = get_xpm(xpm, xpm_len, CUBEMAP_PY_TEX);
	xpm_cube[3] = get_xpm(xpm, xpm_len, CUBEMAP_NY_TEX);
	xpm_cube[4] = get_xpm(xpm, xpm_len, CUBEMAP_PZ_TEX);
	xpm_cube[5] = get_xpm(xpm, xpm_len, CUBEMAP_NZ_TEX);
	i = 0;
	while (i < 6)
		ft_chkptr(xpm_cube[i++], CUBEMAP_MISS_TEX, GL_ERROR);
	shaders[0] = ft_strjoin(cwd, VSHADER_FILE_CUBE);
	shaders[1] = ft_strjoin(cwd, FSHADER_FILE_CUBE);
	create_program(program, shaders[0], shaders[1], get_slots_skybox);
	free(shaders[0]);
	free(shaders[1]);
	obj = get_skybox_obj(cwd);
	create_blueprints_skybox(program, obj);
	free_t_obj((t_void*)obj);
	build_cubemap(program, xpm_cube);
}
