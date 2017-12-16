#include <scop.h>

t_sdl_env	*init_sdl_env(void)
{
	t_sdl_env	*sdl_e;

	sdl_e = (t_sdl_env*)safe_malloc(sizeof(t_sdl_env));
	ft_bzero(sdl_e, sizeof(t_sdl_env));
	sdl_e->tick = FRAME_TICK;
	sdl_e->last_time = (int)SDL_GetTicks();
	return (sdl_e);
}

t_gl_env	*init_gl_env(t_objfile **objf, t_xpm **xpm, int *len)
{
	t_gl_env	*gl_e;
	int			i;

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
	gl_e->rotate = 1;
	gl_e->angle = 10;
	gl_e->vector = 0.1f;
	return (gl_e);
}
