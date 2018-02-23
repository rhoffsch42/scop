/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 17:50:42 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/23 20:02:00 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
**  index textures: 6 -> 11
*/

static int		wait_for_next_frame(t_fps *fps)
{
	fps->ellapsed_time = glfwGetTime() - fps->last_time;
	if (fps->ellapsed_time >= fps->tick)
	{
		fps->last_time += fps->ellapsed_time;
		fps->ellapsed_time = 0.0;
		return (1);
	}
	else
		return (0);
}

static t_cam		init_cam(float x, float y, float z)
{
	t_cam	cam;

	cam.pos.x = x;
	cam.pos.y = y;
	cam.pos.z = z;
	cam.right.x = 1;
	cam.right.y = 0;
	cam.right.z = 0;
	cam.up.x = 0;
	cam.up.y = 1;
	cam.up.z = 0;
	cam.forward.x = 0;
	cam.forward.y = 0;
	cam.forward.z = 1;
	cam.front = vector3_cross(cam.up, cam.right);
	return (cam);
}

static t_matrix4	view_matrix(void)
{
	t_cam		cam;
	t_matrix4	viewmatrix;

	cam = init_cam(0, 0, 0);
	viewmatrix = matrix4(0, MATRIX_ROW_MAJOR);
	viewmatrix.m.tab[0][0] = cam.right.x;
	viewmatrix.m.tab[1][0] = cam.right.y;
	viewmatrix.m.tab[2][0] = cam.right.z;
	viewmatrix.m.tab[0][1] = cam.up.x;
	viewmatrix.m.tab[1][1] = cam.up.y;
	viewmatrix.m.tab[2][1] = cam.up.z;
	viewmatrix.m.tab[0][2] = cam.forward.x;
	viewmatrix.m.tab[1][2] = cam.forward.y;
	viewmatrix.m.tab[2][2] = cam.forward.z;
	viewmatrix.m.tab[0][3] = cam.pos.x;
	viewmatrix.m.tab[1][3] = cam.pos.y;
	viewmatrix.m.tab[2][3] = cam.pos.z;
	viewmatrix.m.tab[3][3] = 1;
	viewmatrix = matrix4_set_order(viewmatrix, !viewmatrix.order);
	return (viewmatrix);
}

static t_matrix4	pro_matrix(float rad, float far, float near)
{
	t_matrix4	promatrix;
	float		ratio;

	ratio = 1.0f / tanf(rad / 2.0f);
	promatrix = matrix4(0, MATRIX_ROW_MAJOR);
	promatrix.m.tab[0][0] = ratio / (DEF_WIN_X / DEF_WIN_Y);
	promatrix.m.tab[1][1] = ratio;
	promatrix.m.tab[2][2] = -(far + near) / (far - near);
	promatrix.m.tab[2][3] = -2.0f * far * near / (far - near);
	promatrix.m.tab[3][2] = -1.0f;
	promatrix = matrix4_set_order(promatrix, !promatrix.order);
	return (promatrix);
}

static void     check_gl_extensions(void)
{
    char    *extensions;
    int     i;

    i = 0;
    while ((extensions = (char*)glGetStringi(GL_EXTENSIONS, i)) != NULL)
    {
        if (strcmp(ARB_CUBEMAP, extensions) == 0)
		{
            printf("%s\tOK\n", extensions);
            break ;
        }
		i++;
    }
    if (!extensions)
        ft_errexit(ARB_CUBEMAP_MISS, RED, GL_ERROR);
}
static t_xpm    *get_xpm(t_xpm **textures, int len, const char *name)
{
    int i;

    i = 0;
    while (i < len)
    {
        if (strcmp(name, textures[i]->name) == 0)
            return (textures[i]);
        i++;
    }
    return (NULL);
}

static GLuint	init_shader(char *filename, int type)
{
	GLint			ret;
	GLuint			shader;
	t_str			*content;
	const GLchar	*gl_content;

	content = ft_getfile(filename);
	gl_content = t_str_to_char(content);
	ft_free_list(content, free_t_str);
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &gl_content, NULL);
	free((void*)gl_content);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE)
		gl_compile_error(shader, "shader compilation error:");
	return (shader);
}

GLuint    skybox(t_gl_env *gl_e, t_glfw *glfw)
{
    int     i;

    check_gl_extensions();
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_CUBE_MAP_ARB);
    GLenum  cubemap[6] = {
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
    };
    t_xpm   *xpm_ptr[6];
    ft_chkptr(xpm_ptr[0] = get_xpm(gl_e->xpm, gl_e->xpm_len, CUBEMAP_NX_TEX), CUBEMAP_MISS_TEX, GL_ERROR);
    ft_chkptr(xpm_ptr[1] = get_xpm(gl_e->xpm, gl_e->xpm_len, CUBEMAP_PX_TEX), CUBEMAP_MISS_TEX, GL_ERROR);
    ft_chkptr(xpm_ptr[2] = get_xpm(gl_e->xpm, gl_e->xpm_len, CUBEMAP_NY_TEX), CUBEMAP_MISS_TEX, GL_ERROR);
    ft_chkptr(xpm_ptr[3] = get_xpm(gl_e->xpm, gl_e->xpm_len, CUBEMAP_PY_TEX), CUBEMAP_MISS_TEX, GL_ERROR);
    ft_chkptr(xpm_ptr[4] = get_xpm(gl_e->xpm, gl_e->xpm_len, CUBEMAP_NZ_TEX), CUBEMAP_MISS_TEX, GL_ERROR);
    ft_chkptr(xpm_ptr[5] = get_xpm(gl_e->xpm, gl_e->xpm_len, CUBEMAP_PZ_TEX), CUBEMAP_MISS_TEX, GL_ERROR);
    printf("Searching CUBEMAP textures\tOK\n");

    GLuint  cubemap_id;
    glGenTextures(1, &cubemap_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cubemap_id);
    i = 0;
    while (i < 6)
    {
        printf("cubemap build:\t%s\n", xpm_ptr[i]->name);
        glTexImage2D(cubemap[i], 0, GL_RGB, xpm_ptr[i]->width, xpm_ptr[i]->height,
            0, GL_RGB, GL_UNSIGNED_BYTE, xpm_ptr[i]->data);
        i++;
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    printf("Building OpenGL textures\tOK\n");

    float   l = 1.0f;
    float   points[] = {
        -l,  l, -l,
        -l, -l, -l,
        l, -l, -l,
        l, -l, -l,
        l,  l, -l,
        -l,  l, -l,
        
        -l, -l,  l,
        -l, -l, -l,
        -l,  l, -l,
        -l,  l, -l,
        -l,  l,  l,
        -l, -l,  l,
        
        l, -l, -l,
        l, -l,  l,
        l,  l,  l,
        l,  l,  l,
        l,  l, -l,
        l, -l, -l,
        
        -l, -l,  l,
        -l,  l,  l,
        l,  l,  l,
        l,  l,  l,
        l, -l,  l,
        -l, -l,  l,
        
        -l,  l, -l,
        l,  l, -l,
        l,  l,  l,
        l,  l,  l,
        -l,  l,  l,
        -l,  l, -l,
        
        -l, -l, -l,
        -l, -l,  l,
        l, -l, -l,
        l, -l, -l,
        -l, -l,  l,
        l, -l,  l
    };
    ////////////    program et shaders
    char    *shaders[2];

    shaders[0] = ft_strjoin(gl_e->cwd, VSHADER_FILE_CUBE);
    // -> /Users/rhoffsch/projects/scop_github/shaders/vertex_shader_cubemap.glsl
    shaders[1] = ft_strjoin(gl_e->cwd, FSHADER_FILE_CUBE);
    // -> /Users/rhoffsch/projects/scop_github/shaders/fragment_shader_cubemap.glsl

    gl_e->vshader = init_shader(shaders[0], GL_VERTEX_SHADER);
    /*
        gl_e->vshader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(gl_e->vshader, 1, &file_content, NULL);
        glCompileShader(gl_e->vshader);

        GLint	ret;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	    if (ret == GL_FALSE)
		    gl_compile_error(shader, "shader compilation error:");
    */
	gl_e->fshader = init_shader(shaders[1], GL_FRAGMENT_SHADER);
    /*
        gl_e->fshader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(gl_e->fshader, 1, &file_content, NULL);
        glCompileShader(gl_e->fshader);

        GLint	ret;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	    if (ret == GL_FALSE)
		    gl_compile_error(shader, "shader compilation error:");
    */

	gl_e->shader_programme = glCreateProgram();
	glAttachShader(gl_e->shader_programme, gl_e->vshader);
	glAttachShader(gl_e->shader_programme, gl_e->fshader);
	glLinkProgram(gl_e->shader_programme);

    int p = -1;
	glValidateProgram(gl_e->shader_programme);
	glGetProgramiv(gl_e->shader_programme, GL_LINK_STATUS, &p);
	(p != GL_TRUE) ? print_programme_info_log(gl_e->shader_programme) : (void)p;
	glUseProgram(gl_e->shader_programme);

    ////////////    vao
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glEnableVertexAttribArray(0);//utile ?


    ////////////    vbo
	int		slot;
	if ((slot = glGetAttribLocation(gl_e->shader_programme, "vertex")) == -1)
	{
		glGetError();
		ft_errexit("glGetAttribLocation failed (-1)", RED, GL_ERROR);
	}
	printf("slot %d:\t%s\n", slot, "vertex");
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);
    glVertexAttribPointer(slot, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(slot);
    /*  0 : slot
        3 : size (nb de values)
        GL_FLOAT : type
        GL_FALSE : pas de normalisation des values entre 0:1 || -1:1
        0 : offset between vertex attribute
        NULL : offset of first component of the first generic vertex attribute (NULL = 0)
    */

    ////////////    load data
    // glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);
    //3coo(xyz) * (6cotes * (2faces * 3sommets) * float


    ////////////    matrice
	t_matrix4	promatrix;
	t_matrix4	viewmatrix;
	promatrix = pro_matrix(DTOR(gl_e->fov), FAR, NEAR);
	viewmatrix = view_matrix();
    if (1)
	{
		printf("View Matrix:\n");
		matrix4_print(viewmatrix);
		printf("Projection Matrix:\n");
		matrix4_print(promatrix);
	}

    GLint projection = glGetUniformLocation(gl_e->shader_programme, "P");
    GLint view = glGetUniformLocation(gl_e->shader_programme, "V");
    glUniformMatrix4fv(projection, 1, GL_FALSE, promatrix.m.e);
    glUniformMatrix4fv(view, 1, GL_FALSE, viewmatrix.m.e);

    ////////////    render
    t_fps		*fps = init_t_fps();
    glEnable(GL_DEPTH_TEST);
    glClearDepth(-1.0f);
    glDepthFunc(GL_GREATER);
    glUseProgram(gl_e->shader_programme);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);
    glBindVertexArray(vao);
    while (!glfwWindowShouldClose(glfw->win))
    {
        if (wait_for_next_frame(fps))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glDepthMask(GL_FALSE);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            //  draw from 0
            //  to 36: 3coo(xyz) * (6cotes * (2faces * 3sommets) * float
            glDepthMask(GL_TRUE);
            glfwSwapBuffers(glfw->win);
            glfwPollEvents();
        }
    }

    exit(0);
}
