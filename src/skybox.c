/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 17:50:42 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/26 00:05:54 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#define COS_A	val[0]
#define SIN_A	val[1]
#define COS_B	val[2]
#define SIN_B	val[3]
#define COS_C	val[4]
#define SIN_C	val[5]

/*
**  index textures: 6 -> 11
*/

t_matrix4	view_matrix_sky(t_gl_env *gl_e, t_matrix4 viewmatrix)
{
	t_vector3	res;
	float		val[8];

	COS_A = cosf(gl_e->cam.rot.x);
	SIN_A = sinf(gl_e->cam.rot.x);
	COS_B = cosf(gl_e->cam.rot.y);
	SIN_B = sinf(gl_e->cam.rot.y);
	COS_C = cosf(gl_e->cam.rot.z);
	SIN_C = sinf(gl_e->cam.rot.z);
	val[6] = COS_A * SIN_B;
	val[7] = SIN_A * SIN_B;
	viewmatrix.m.tab[0][0] = COS_B * COS_C;
	viewmatrix.m.tab[1][0] = val[7] * COS_C + COS_A * SIN_C;
	viewmatrix.m.tab[2][0] = -val[6] * COS_C + SIN_A * SIN_C;
	viewmatrix.m.tab[0][1] = -COS_B * SIN_C;
	viewmatrix.m.tab[1][1] = -val[7] * SIN_C + COS_A * COS_C;
	viewmatrix.m.tab[2][1] = val[6] * SIN_C + SIN_A * COS_C;
	viewmatrix.m.tab[0][2] = SIN_B;
	viewmatrix.m.tab[1][2] = -SIN_A * COS_B;
	viewmatrix.m.tab[2][2] = COS_A * COS_B;
	res = vector3_rot(gl_e->cam.pos, gl_e->cam.rot, ROT_WAY);
	viewmatrix.m.tab[0][3] = -res.x;
	viewmatrix.m.tab[1][3] = -res.y;
	viewmatrix.m.tab[2][3] = -res.z;
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

static void     check_sky_extensions(void)
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

void    skybox(t_gl_env *gl_e, t_obj *obj)
{
    int     i;

    check_sky_extensions();
    glEnable(GL_TEXTURE_CUBE_MAP_ARB);
    glActiveTexture(GL_TEXTURE0);
    GLenum  cubemap[6] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
    };
    t_xpm   *xpm_ptr[6];
    ft_chkptr(xpm_ptr[0] = get_xpm(gl_e->xpm, gl_e->xpm_len, CUBEMAP_NX_TEX), CUBEMAP_MISS_TEX, GL_ERROR);
    ft_chkptr(xpm_ptr[1] = get_xpm(gl_e->xpm, gl_e->xpm_len, CUBEMAP_PX_TEX), CUBEMAP_MISS_TEX, GL_ERROR);
    ft_chkptr(xpm_ptr[2] = get_xpm(gl_e->xpm, gl_e->xpm_len, CUBEMAP_NY_TEX), CUBEMAP_MISS_TEX, GL_ERROR);
    ft_chkptr(xpm_ptr[3] = get_xpm(gl_e->xpm, gl_e->xpm_len, CUBEMAP_PY_TEX), CUBEMAP_MISS_TEX, GL_ERROR);
    ft_chkptr(xpm_ptr[4] = get_xpm(gl_e->xpm, gl_e->xpm_len, CUBEMAP_NZ_TEX), CUBEMAP_MISS_TEX, GL_ERROR);
    ft_chkptr(xpm_ptr[5] = get_xpm(gl_e->xpm, gl_e->xpm_len, CUBEMAP_PZ_TEX), CUBEMAP_MISS_TEX, GL_ERROR);
    printf("Searching CUBEMAP textures\tOK\n");

    glGenTextures(1, &gl_e->sky_tex_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, gl_e->sky_tex_id);
    i = 0;
    while (i < 6)
    {
        printf("cubemap build:\t%s - %dx%d\n", xpm_ptr[i]->name, xpm_ptr[i]->width, xpm_ptr[i]->height);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        
        glTexImage2D(cubemap[i], 0, GL_RGB, xpm_ptr[i]->width, xpm_ptr[i]->height,
            0, GL_RGB, GL_UNSIGNED_BYTE, xpm_ptr[i]->data);
        i++;
    }
    printf("Building OpenGL textures\tOK\n");

    ////////////    program et shaders
    char    *shaders[2];

    shaders[0] = ft_strjoin(gl_e->cwd, VSHADER_FILE_CUBE);
    // -> /Users/rhoffsch/projects/scop_github/shaders/vertex_shader_cubemap.glsl
    shaders[1] = ft_strjoin(gl_e->cwd, FSHADER_FILE_CUBE);
    // -> /Users/rhoffsch/projects/scop_github/shaders/fragment_shader_cubemap.glsl

    gl_e->sky_vshader = init_shader(shaders[0], GL_VERTEX_SHADER);
    /*
        gl_e->sky_vshader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(gl_e->sky_vshader, 1, &file_content, NULL);
        glCompileShader(gl_e->sky_vshader);

        GLint	ret;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	    if (ret == GL_FALSE)
		    gl_compile_error(shader, "shader compilation error:");
    */
	gl_e->sky_fshader = init_shader(shaders[1], GL_FRAGMENT_SHADER);
    /*
        gl_e->sky_vshader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(gl_e->sky_vshader, 1, &file_content, NULL);
        glCompileShader(gl_e->sky_vshader);

        GLint	ret;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	    if (ret == GL_FALSE)
		    gl_compile_error(shader, "shader compilation error:");
    */
    free(shaders[0]);
    free(shaders[1]);

	gl_e->sky_programme = glCreateProgram();
	glAttachShader(gl_e->sky_programme, gl_e->sky_vshader);
	glAttachShader(gl_e->sky_programme, gl_e->sky_fshader);
	glLinkProgram(gl_e->sky_programme);

    int p = -1;
	glValidateProgram(gl_e->sky_programme);
	glGetProgramiv(gl_e->sky_programme, GL_LINK_STATUS, &p);
	(p != GL_TRUE) ? print_programme_info_log(gl_e->sky_programme) : (void)p;
	glUseProgram(gl_e->sky_programme);

    ////////////    vao
    glGenVertexArrays(1, &gl_e->sky_vao);
    glBindVertexArray(gl_e->vao); 

    ////////////    vbo
    float   points[obj->f_amount * 9];
    fill_points_array(points, obj->f);

    glGenBuffers(1, &gl_e->sky_tex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, gl_e->sky_tex_vbo);
    glBufferData(GL_ARRAY_BUFFER, obj->f_amount * 9 * sizeof(float), points, GL_STATIC_DRAW);

	if ((gl_e->sky_vbo_slot = glGetAttribLocation(gl_e->sky_programme, "vertex")) == -1)
	{
		glGetError();
		ft_errexit("glGetAttribLocation failed (-1)", RED, GL_ERROR);
	}
	printf("slot %d:\t%s\n", gl_e->sky_vbo_slot, "vertex");
    glVertexAttribPointer(gl_e->sky_vbo_slot, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0);//utile ?
	glBindVertexArray(0);
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
	viewmatrix = view_matrix_sky(gl_e, matrix4(0, MATRIX_ROW_MAJOR));
    if (DATA && DATA_SKYBOX)
	{
		printf("View Matrix:\n");
		matrix4_print(viewmatrix);
		printf("Projection Matrix:\n");
		matrix4_print(promatrix);
	}

    GLint projection = glGetUniformLocation(gl_e->sky_programme, "P");
    GLint view = glGetUniformLocation(gl_e->sky_programme, "V");
    glUniformMatrix4fv(projection, 1, GL_FALSE, promatrix.m.e);
    glUniformMatrix4fv(view, 1, GL_FALSE, viewmatrix.m.e);
}
