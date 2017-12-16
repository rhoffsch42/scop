#include <scop.h>

void		draw_test_gl(t_sdl *sdl)
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70,(double)800/800,1,1000);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	// glDepthFunc(GL_GREATER);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

	gluLookAt(3,4,2,0,0,0,0,0,1);

	glBegin(GL_QUADS);
		glColor3ub(255,0,0); //face rouge
		glVertex3d(1,1,1);
		glVertex3d(1,1,-1);
		glVertex3d(-1,1,-1);
		glVertex3d(-1,1,1);
	glEnd();

	glBegin(GL_QUADS);
		glColor3ub(0,255,0); //face verte
		glVertex3d(1,-1,1);
		glVertex3d(1,-1,-1);
		glVertex3d(1,1,-1);
		glVertex3d(1,1,1);
	glEnd();

	glBegin(GL_QUADS);
		glColor3ub(0,0,255); //face bleue
		glVertex3d(-1,-1,1);
		glVertex3d(-1,-1,-1);
		glVertex3d(1,-1,-1);
		glVertex3d(1,-1,1);
	glEnd();

	glFlush();
	SDL_GL_SwapWindow(sdl->win);

	SDL_Event	event;
	int			quit = 0;
	while (!quit)
		while (SDL_PollEvent(&event) == 1)
		{
			if (event.type == SDL_KEYDOWN)
			{
				ft_putnbrendl(event.key.keysym.scancode);
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					quit = 1;
					SDL_GL_DeleteContext(sdl->glcontext);
					break ;
				}
			}
		}
	exit (0);
}
void		draw_test_sdl(t_sdl *sdl)
{
	int	y = sdl->mid[1] - 30;
	while (y <= sdl->mid[1] + 30)
	{
		int	x = sdl->mid[0] - 30;
		while (x <= sdl->mid[1] + 30)
		{
			sdl_putpixel(sdl->surface, x, y, RGB(255, 0, 0));
			x++;
		}
		y++;
	}
	SDL_UpdateWindowSurface(sdl->win);
}

void	*draw_face2(void *f, t_arg args)
{
	// ft_putendl("- - - draw_face2");
	t_face	*face;
	t_mat	*mat;

	face = (t_face*)f;
	mat = ((t_obj*)(args.ptr[1]))->mat;
	glBegin(DRAW_MODE);
	if (mat)
		glColor3f(mat->ka[0], mat->ka[1], mat->ka[2]);
	else
		glColor3ub(255, 0, 0);
	float coef = 1;
	glVertex3d(face->v1->x / coef, face->v1->y / coef, face->v1->z / coef);
	glVertex3d(face->v2->x / coef, face->v2->y / coef, face->v2->z / coef);
	glVertex3d(face->v3->x / coef, face->v3->y / coef, face->v3->z / coef);
	if (face->v4)
		glVertex3d(face->v4->x / coef, face->v4->y / coef, face->v4->z / coef);
	glEnd();
	return (NULL);
}

void	print_obj_stats(t_obj *obj, t_gl_env *gl_e)
{
	if (gl_e->tex == 1)
		printf("tex_Color\n");
	else if (gl_e->tex == 2 && obj->mat)
		printf("%s\n", obj->mat->name);
	else
		printf("custom_color\n");
	printf("%.1f\t%.1f\t%.1f\n", \
		gl_e->pos[0], gl_e->pos[1], gl_e->pos[2]);
	printf("%d\t%d\t%d\n------------------\n", \
		gl_e->rot[0], gl_e->rot[1], gl_e->rot[2]);
}

t_void	*draw_face_texture(t_void *f, float cf)
{
	t_face	*face;

	face = (t_face*)f;
	glBegin(GL_TRIANGLES);
	glColor3ub(255, 255, 255);
	glTexCoord2d(face->v1->x, face->v1->y);
	glVertex3d(face->v1->x / cf, face->v1->y / cf, face->v1->z / cf);
	glTexCoord2d(face->v2->x, face->v2->y);
	glVertex3d(face->v2->x / cf, face->v2->y / cf, face->v2->z / cf);
	glTexCoord2d(face->v3->x, face->v3->y);
	glVertex3d(face->v3->x / cf, face->v3->y / cf, face->v3->z / cf);
	glEnd();
	return (NULL);
}

t_void	*draw_face(t_void *f, t_arg args)
{
	t_face			*face;
	t_mat			*mat;
	unsigned char	color;
	float			cf;

	cf = 1.0f;
	face = (t_face*)f;
	mat = ((t_obj*)(args.ptr[1]))->mat;
	color = rand() % 200;
	if (*(int*)(args.ptr[3]) == 1)
		draw_face_texture(f, cf);
	else
	{
		glBegin(GL_TRIANGLES);
		if (mat && *(int*)(args.ptr[3]) == 2)
			glColor3f(mat->kd[0], mat->kd[1], mat->kd[2]);
		else
			glColor3ub(color, color, color);
		glVertex3d(face->v1->x / cf, face->v1->y / cf, face->v1->z / cf);
		glVertex3d(face->v2->x / cf, face->v2->y / cf, face->v2->z / cf);
		glVertex3d(face->v3->x / cf, face->v3->y / cf, face->v3->z / cf);
		glEnd();
	}
	return (NULL);
}

void		draw_obj(t_sdl *sdl, t_obj *obj, t_gl_env *gl_e)
{
	float	c;
	float	scale;

	c = 0.0f;
	scale = 0.20f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
	glTranslatef(gl_e->pos[0], gl_e->pos[1], gl_e->pos[2]);
	glRotated(gl_e->rot[0], 1, 0, 0);
	glRotated(gl_e->rot[1], 0, 1, 0);
	glRotated(gl_e->rot[2], 0, 0, 1);
	print_obj_stats(obj, gl_e);
	glScalef(scale, scale, scale);
	glDepthFunc(GL_LEQUAL);
	srand(1);
	for_list_args((t_void*)(obj->f), \
		init_args(sdl, obj, &c, &gl_e->tex), draw_face);
	glFlush();
	SDL_GL_SwapWindow(sdl->win);
}

void		display_object(t_sdl *sdl, t_objfile **objf, t_xpm **xpm, int *len)
{
	t_sdl_env	*s_e;
	t_gl_env	*gl_e;

	s_e = init_sdl_env();
	gl_e = init_gl_env(objf, xpm, len);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, sdl->size[0] / sdl->size[1], 0.1f, 1000);
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, gl_e->tex_id[0]);
	while (!s_e->quit)
	{
		s_e->start_time = SDL_GetTicks();
		while (SDL_PollEvent(&s_e->event) && !s_e->quit)
			if (s_e->event.type == SDL_KEYDOWN && !s_e->event.key.repeat)
				events(s_e->event.key.keysym.scancode, sdl, s_e, gl_e);
		s_e->current_time = SDL_GetTicks();
		s_e->ellapsed_time = s_e->current_time - s_e->last_time;
		s_e->last_time = s_e->current_time;
		gl_e->rot[1] += (gl_e->rotate) ? s_e->ellapsed_time / 20 : 0;
		draw_obj(sdl, gl_e->objf[gl_e->obj_i]->obj, gl_e);
		s_e->ellapsed_time = SDL_GetTicks() - s_e->start_time;
		if (s_e->ellapsed_time < s_e->tick)
			SDL_Delay(s_e->tick - s_e->ellapsed_time);
	}
}
