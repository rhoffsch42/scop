#include <scop.h>

void		fill_color_array(float *arr, t_face *face)
{
	int		i;
	float	color;

	srand(1);
	i = 0;
	while (face)
	{
		color = (float)(rand() % 200) / 200.0f;
		arr[i + 0] = color;
		arr[i + 1] = color;
		arr[i + 2] = color;
		arr[i + 3] = color;
		arr[i + 4] = color;
		arr[i + 5] = color;
		arr[i + 6] = color;
		arr[i + 7] = color;
		arr[i + 8] = color;
		i += 9;
		face = face->next;
	}
}

void		fill_tex_array(float *arr, t_face *face)
{
	int			i;
	float 		scale;
	float 		offset_y;

	scale = 0.75f;
	offset_y = -0.5f;
	i = 0;
	while (face)
	{
		arr[i + 0] = (face->v1->z) * scale;
		arr[i + 1] = (1 - face->v1->y) * scale + offset_y;
		arr[i + 2] = (face->v2->z) * scale;
		arr[i + 3] = (1 - face->v2->y) * scale + offset_y;
		arr[i + 4] = (face->v3->z) * scale;
		arr[i + 5] = (1 - face->v3->y) * scale + offset_y;
		i += 6;
		face = face->next;
	}
}

void		fill_points_array(float *arr, t_face *face, t_gl_env *gl_e)
{
	int			i;
	t_vector3	tmp;

	i = 0;
	while (face)
	{
		vertix_to_vector3(face->v1, &tmp);
		tmp = vector3_rot(tmp, gl_e->rot, ROT_WAY);
		arr[i + 0] = tmp.x * gl_e->scale + gl_e->pos.x;
		arr[i + 1] = tmp.y * gl_e->scale + gl_e->pos.y;
		arr[i + 2] = tmp.z * gl_e->scale + gl_e->pos.z;
		vertix_to_vector3(face->v2, &tmp);
		tmp = vector3_rot(tmp, gl_e->rot, ROT_WAY);
		arr[i + 3] = tmp.x * gl_e->scale + gl_e->pos.x;
		arr[i + 4] = tmp.y * gl_e->scale + gl_e->pos.y;
		arr[i + 5] = tmp.z * gl_e->scale + gl_e->pos.z;
		vertix_to_vector3(face->v3, &tmp);
		tmp = vector3_rot(tmp, gl_e->rot, ROT_WAY);
		arr[i + 6] = tmp.x * gl_e->scale + gl_e->pos.x;
		arr[i + 7] = tmp.y * gl_e->scale + gl_e->pos.y;
		arr[i + 8] = tmp.z * gl_e->scale + gl_e->pos.z;
		i += 9;
		face = face->next;
	}
}
