#include <scop.h>

void		event_properties(int scancode, t_gl_env *gl_e)
{
	if (scancode == 44)//space
		gl_e->rotate = (gl_e->rotate) ? 0 : 1;
	else if (scancode == 40)//enter (center)
	{
		gl_e->tex = (gl_e->tex == 2) ? 0 : gl_e->tex + 1;
		(gl_e->tex == 1) ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);
	}
}

void		event_assets(int scancode, t_gl_env *gl_e)
{
	if (scancode == 75)//up obj
		gl_e->obj_i = (gl_e->obj_i < gl_e->obj_len - 1) ? gl_e->obj_i + 1 : 0;
	else if (scancode == 78)//down obj
		gl_e->obj_i = (gl_e->obj_i != 0) ? gl_e->obj_i - 1 : gl_e->obj_len - 1;
	else if (scancode == 74)//up texture
	{
		gl_e->tex_i = (gl_e->tex_i < gl_e->xpm_len - 1) ? gl_e->tex_i + 1 : 0;
		glBindTexture(GL_TEXTURE_2D, gl_e->tex_id[gl_e->tex_i]);
	}
	else if (scancode == 77)//down texture
	{
		gl_e->tex_i = (gl_e->tex_i != 0) ? gl_e->tex_i - 1 : gl_e->xpm_len - 1;
		glBindTexture(GL_TEXTURE_2D, gl_e->tex_id[gl_e->tex_i]);
	}
	else
		event_properties(scancode, gl_e);
}

void		event_obj_translate(int scancode, t_gl_env *gl_e)
{
	if (scancode == 82)
		gl_e->pos[1] += gl_e->vector;
	else if (scancode == 81)
		gl_e->pos[1] += -gl_e->vector;
	else if (scancode == 80)
		gl_e->pos[0] += -gl_e->vector;
	else if (scancode == 79)
		gl_e->pos[0] += gl_e->vector;
	else if (scancode == 30)
		gl_e->pos[2] += -gl_e->vector;
	else if (scancode == 39)
		gl_e->pos[2] += gl_e->vector;
	else
		event_assets(scancode, gl_e);
}

void		event_obj_rotate(int scancode, t_gl_env *gl_e)
{
	if (scancode == 36)
		gl_e->rot[0] += gl_e->angle;
	else if (scancode == 33)
		gl_e->rot[0] += -gl_e->angle;
	else if (scancode == 37)
		gl_e->rot[1] += gl_e->angle;
	else if (scancode == 34)
		gl_e->rot[1] += -gl_e->angle;
	else if (scancode == 38)
		gl_e->rot[2] += gl_e->angle;
	else if (scancode == 35)
		gl_e->rot[2] += -gl_e->angle;
	else
		event_obj_translate(scancode, gl_e);
}

void		events(int scancode, t_sdl *sdl, t_sdl_env *sdl_e, t_gl_env *gl_e)
{
	if (scancode == SDL_SCANCODE_ESCAPE)
	{
		sdl_e->quit = 1;
		SDL_GL_DeleteContext(sdl->glcontext);
		// break ;
	}
	else
		event_obj_rotate(scancode, gl_e);
}


// 21/10
// 1200	0
// 0		4
// 1232	0
// 0		4.2
// 1297	0
// 0		4.6
// 1399	0
// 0		4.8
// 1568	0
// 0		5.2
// 1663	0
// 0		5.5
// 1723	0
// 13/11
// 23 jours <=> 523
// = 31 jours <=> 704 pour 1200
// taxe 0%
