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

t_sdl	*init_sdl(void)
{
	t_sdl	*sdl;

	sdl = (t_sdl*)safe_malloc(sizeof(t_sdl));
	ft_bzero((void*)sdl, sizeof(t_sdl));
	sdl->size[0] = DEF_WIN_X;
	sdl->size[1] = DEF_WIN_Y;
	sdl->mid[0] = sdl->size[0] / 2;
	sdl->mid[1] = sdl->size[1] / 2;
	sdl->title = ft_strdup(DEF_WIN_TITLE);
	sdl->surface = NULL;
	sdl->win = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_errexit(SDL_GetError(), RED, SDL_FAIL);
	sdl->win = SDL_CreateWindow(sdl->title, SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, sdl->size[0], sdl->size[1], \
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if ((sdl->glcontext = SDL_GL_CreateContext(sdl->win)) == NULL)
		ft_errexit(SDL_GetError(), RED, SDL_FAIL);
	printf("GL version: %s\n", glGetString(GL_VERSION));
	SDL_ShowWindow(sdl->win);
	SDL_RaiseWindow(sdl->win);
	sdl->surface = SDL_GetWindowSurface(sdl->win);
	SDL_FillRect(sdl->surface, NULL, 0x000000);
	SDL_UpdateWindowSurface(sdl->win);
	return (sdl);
}

t_env	*init_env(void)
{
	t_env	*e;

	e = (t_env*)safe_malloc(sizeof(t_env));
	e->objfile = NULL;
	e->mtlfile = NULL;
	e->dir = NULL;
	e->sdl = NULL;
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
