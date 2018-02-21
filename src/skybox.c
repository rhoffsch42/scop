/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 17:50:42 by rhoffsch          #+#    #+#             */
/*   Updated: 2018/02/20 19:22:20 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
**  id: 6 -> 11
*/
int    skybox(t_gl_env *gl_e)
{
    char    *extensions;
    int     i;
    int     ind;

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
    GLenum  cubemap[6] = {
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
    };

    GLuint  cubemap_id;
    glGenTextures(1, &cubemap_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cubemap_id);
    i = 0;
    ind = 6;
    while (i < 6)
    {
        glTexImage2D(cubemap[i], 0, 3, gl_e->xpm[ind]->width, gl_e->xpm[ind]->height,
            0, GL_RGB, GL_UNSIGNED_BYTE, gl_e->xpm[ind]->data);
        i++;
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);

    float points[] = {
  -10.0f,  10.0f, -10.0f,
  -10.0f, -10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
   10.0f,  10.0f, -10.0f,
  -10.0f,  10.0f, -10.0f,
  
  -10.0f, -10.0f,  10.0f,
  -10.0f, -10.0f, -10.0f,
  -10.0f,  10.0f, -10.0f,
  -10.0f,  10.0f, -10.0f,
  -10.0f,  10.0f,  10.0f,
  -10.0f, -10.0f,  10.0f,
  
   10.0f, -10.0f, -10.0f,
   10.0f, -10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
   
  -10.0f, -10.0f,  10.0f,
  -10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f, -10.0f,  10.0f,
  -10.0f, -10.0f,  10.0f,
  
  -10.0f,  10.0f, -10.0f,
   10.0f,  10.0f, -10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
  -10.0f,  10.0f,  10.0f,
  -10.0f,  10.0f, -10.0f,
  
  -10.0f, -10.0f, -10.0f,
  -10.0f, -10.0f,  10.0f,
   10.0f, -10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
  -10.0f, -10.0f,  10.0f,
   10.0f, -10.0f,  10.0f
};
GLuint vbo;
glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);

GLuint vao;
glGenVertexArrays(1, &vao);
glBindVertexArray(vao);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    return (cubemap_id);
}

// void create_cube_map(
//   const char* front,
//   const char* back,
//   const char* top,
//   const char* bottom,
//   const char* left,
//   const char* right,
//   GLuint* tex_cube) {
//   // generate a cube-map texture to hold all the sides
//   glActiveTexture(GL_TEXTURE0);
//   glGenTextures(1, tex_cube);
  
//   // load each image and copy into a side of the cube-map texture
//   load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
//   load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
//   load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
//   load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
//   load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
//   load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
//   // format cube map texture
//   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// }

// bool load_cube_map_side(
//   GLuint texture, GLenum side_target, const char* file_name) {
//   glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

//   int x, y, n;
//   int force_channels = 4;
//   unsigned char*  image_data = stbi_load(
//     file_name, &x, &y, &n, force_channels);
//   if (!image_data) {
//     fprintf(stderr, "ERROR: could not load %s\n", file_name);
//     return false;
//   }
//   // non-power-of-2 dimensions check
//   if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
//     fprintf(stderr,
//     	"WARNING: image %s is not power-of-2 dimensions\n",
//     	file_name);
//   }
  
//   // copy image data into 'target' side of cube map
//   glTexImage2D(
//     side_target,
//     0,
//     GL_RGBA,
//     x,
//     y,
//     0,
//     GL_RGBA,
//     GL_UNSIGNED_BYTE,
//     image_data);
//   free(image_data);
//   return true;
// }