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

t_void	*draw_face(t_void *f, t_arg args)
{
	// ft_putendl("- - - draw_face");
	t_face	*face;
	t_mat	*mat;

	face = (t_face*)f;
	mat = ((t_obj*)(args.ptr[1]))->mat;
	// if (face->v4 == NULL)
	// 	return (NULL);
	glBegin((face->v4) ? GL_QUADS : GL_TRIANGLES);
	if (mat)
		glColor3f(mat->ka[0], mat->ka[1], mat->ka[2]);
	else
	{
		// unsigned char color = rand() % 255 + 0;
		// glColor3ub(color, color, color);

		// glColor3ub(rand() % 150 + 105, rand() % 150 + 105, rand() % 150 + 105);

		float	*c = (float*)(args.ptr[2]); (*c)++;
		unsigned char	base = 50;
		float			basef = (float)base;
		unsigned char	color;
		color = (unsigned char)((255.0f - basef) * (float)((*c)/47.0f)) + base;
		glColor3ub(color, color, color);
	}

	// printf("vertix %d:\t%f\t%f\t%f\n", face->v1->id, face->v1->x, face->v1->y, face->v1->z);
	// printf("vertix %d:\t%f\t%f\t%f\n", face->v2->id, face->v2->x, face->v2->y, face->v2->z);
	// printf("vertix %d:\t%f\t%f\t%f\n", face->v3->id, face->v3->x, face->v3->y, face->v3->z);
	// if (face->v4)
	// 	printf("vertix %d:\t%f\t%f\t%f\n", face->v4->id, face->v4->x, face->v4->y, face->v4->z);
	float coef = 1;
	glVertex3d(face->v1->x / coef, face->v1->y / coef, face->v1->z / coef);
	glVertex3d(face->v2->x / coef, face->v2->y / coef, face->v2->z / coef);
	glVertex3d(face->v3->x / coef, face->v3->y / coef, face->v3->z / coef);
	if (face->v4)
		glVertex3d(face->v4->x / coef, face->v4->y / coef, face->v4->z / coef);
	glEnd();
	return (NULL);
}

void		draw_obj(t_sdl *sdl, t_obj *obj, int *rot, float *trans)
{
	float c = 0.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

	glTranslatef(trans[0], trans[1], trans[2]);
	glRotated(rot[0], 1, 0, 0);
	glRotated(rot[1], 0, 1, 0);
	glRotated(rot[2], 0, 0, 1);
	printf("%.1f\t%.1f\t%.1f\n", trans[0], trans[1], trans[2]);
	printf("%d\t%d\t%d\n------------------\n", rot[0], rot[1], rot[2]);
	float scale = 0.20;
	glScalef(scale, scale, scale);

	glDepthFunc(GL_LEQUAL);
	for_list_args((t_void*)(obj->f), init_args(sdl, obj, &c, NULL), draw_face);
	// glDepthFunc(GL_ALWAYS);
	// for_list_args(obj->f, init_args(sdl, obj, &c, NULL), draw_face2);

	glFlush();
	SDL_GL_SwapWindow(sdl->win);
}

void		display_object(t_sdl *sdl, t_objfile *objf)
{
	int			quit;
	SDL_Event	event;
	int			rot[3];
	float		trans[3];

	ft_bzero(rot, sizeof(int) * 3);
	ft_bzero(trans, sizeof(float) * 3);
	// draw_test_sdl(sdl);
	// draw_test_gl(sdl);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, sdl->size[0] / sdl->size[1], 0.1f, 1000);
	glEnable(GL_DEPTH_TEST);
	draw_obj(sdl, objf->obj, rot, trans);

	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);

	int		t = 0;
	int		frame = 0;
	int		tick = FRAME_TICK;
	int		start_time;
	int		current_time;
	int		ellapsed_time;
	int		last_time = (int)SDL_GetTicks();
	int		angle = 5;
	float	vec = 0.05f;
	quit = 0;
	while (!quit)
	{
		frame++;
		start_time = SDL_GetTicks();
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
				else if (event.key.keysym.scancode == 36)
					rot[0] += angle;
				else if (event.key.keysym.scancode == 33)
					rot[0] += -angle;
				else if (event.key.keysym.scancode == 37)
					rot[1] += angle;
				else if (event.key.keysym.scancode == 34)
					rot[1] += -angle;
				else if (event.key.keysym.scancode == 38)
					rot[2] += angle;
				else if (event.key.keysym.scancode == 35)
					rot[2] += -angle;
				else if (event.key.keysym.scancode == 82)
					trans[1] += vec;
				else if (event.key.keysym.scancode == 81)
					trans[1] += -vec;
				else if (event.key.keysym.scancode == 80)
					trans[0] += -vec;
				else if (event.key.keysym.scancode == 79)
					trans[0] += vec;
				else if (event.key.keysym.scancode == 30)
					trans[2] += -vec;
				else if (event.key.keysym.scancode == 39)
					trans[2] += vec;
				draw_obj(sdl, objf->obj, rot, trans);
			}
		}
		current_time = SDL_GetTicks();
		ft_putnbrendl(current_time);
		ellapsed_time = current_time - last_time;
		last_time = current_time;

		rot[1] += ellapsed_time / 20;
		draw_obj(sdl, objf->obj, rot, trans);

		if (frame == FPS)
		{
			frame = 0;
			t++;
		}
		ft_putnbrendl(frame);
		ft_putnbrendl(t);

		ellapsed_time = SDL_GetTicks() - start_time;
		if (ellapsed_time < tick)
			SDL_Delay(tick - ellapsed_time);
	}
}

// translate_obj(objf->obj->v, 0, 0.1f, 0);
//
// translate_obj(objf->obj->v, 0, -0.1f, 0);
//
// translate_obj(objf->obj->v, -0.1f, 0, 0);
//
// translate_obj(objf->obj->v, 0.1f, 0, 0);
//
// translate_obj(objf->obj->v, 0, 0, 0.1f);
//
// translate_obj(objf->obj->v, 0, 0, -0.1f);
