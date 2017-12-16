#include <scop.h>

void	rot_vector2(t_vector2 *src, t_vector2 *dst, float rad, float rot_direction)
{
	float	x;
	float	y;

	rad *= rot_direction;
	x = src->x;
	y = src->y;
	dst->x = x * cosf(rad) - y * sinf(rad);
	dst->y = x * sinf(rad) + y * cosf(rad);
}

void	rot_vector3_bis(t_vector3 *src, t_vector3 *dst, t_vector3 rad, float rot_direction)
{
	float		v[8];
	float		mat[16];
	t_vector3	tmp;

	rad.x *= rot_direction;
	rad.y *= rot_direction;
	rad.z *= rot_direction;
	v[0] = cosf(rad.x);
	v[1] = sinf(rad.x);
	v[2] = cosf(rad.y);
	v[3] = sinf(rad.y);
	v[4] = cosf(rad.z);
	v[5] = sinf(rad.z);
	v[6] = v[0] * v[3];
	v[7] = v[1] * v[3];
	ft_bzero(mat, sizeof(float) * 16);
	mat[0] = v[2] * v[4];
	mat[1] = -v[2] * v[5];
	mat[2] = v[3];
	mat[4] = v[7] * v[4] + v[0] * v[5];
	mat[5] = -v[7] * v[5] + v[0] * v[4];
	mat[6] = -v[1] * v[2];
	mat[8] = -v[6] * v[4] + v[1] * v[5];
	mat[9] = v[6] * v[5] + v[1] * v[4];
	mat[10] = v[0] * v[2];
	mat[15] =  1;
	tmp.x = src->x;
	tmp.y = src->y;
	tmp.z = src->z;
	dst->x = tmp.x * mat[0] + tmp.y * mat[1] + tmp.z * mat[2];
	dst->y = tmp.x * mat[4] + tmp.y * mat[5] + tmp.z * mat[6];
	dst->z = tmp.x * mat[8] + tmp.y * mat[9] + tmp.z * mat[10];
}

void	rot_vector3(t_vector3 *src, t_vector3 *dst, t_vector3 rad, float rot_direction)
{
	float		v[8];
	float		mat[16];
	t_vector3	tmp;

	rad.x *= rot_direction;
	rad.y *= rot_direction;
	rad.z *= rot_direction;
	v[0] = cosf(rad.x);
	v[1] = sinf(rad.x);
	v[2] = cosf(rad.y);
	v[3] = sinf(rad.y);
	v[4] = cosf(rad.z);
	v[5] = sinf(rad.z);
	v[6] = v[0] * v[3];
	v[7] = v[1] * v[3];
	ft_bzero(mat, sizeof(float) * 16);
	mat[0] = v[2] * v[4];
	mat[1] = v[2] * v[5];
	mat[2] = -v[3];
	mat[4] = v[7] * v[4] - v[0] * v[5];
	mat[5] = v[7] * v[5] + v[0] * v[4];
	mat[6] = v[1] * v[2];
	mat[8] = v[6] * v[4] - v[1] * v[5];
	mat[9] = v[6] * v[5] + v[1] * v[4];
	mat[10] = v[0] * v[2];
	mat[15] =  1;
	tmp.x = src->x;
	tmp.y = src->y;
	tmp.z = src->z;
	dst->x = tmp.x * mat[0] + tmp.y * mat[1] + tmp.z * mat[2];
	dst->y = tmp.x * mat[4] + tmp.y * mat[5] + tmp.z * mat[6];
	dst->z = tmp.x * mat[8] + tmp.y * mat[9] + tmp.z * mat[10];
}

void	revrot_vector3(t_vector3 *src, t_vector3 *dst, t_vector3 rad, float rot_direction)
{
	float		v[8];
	float		mat[16];
	t_vector3	tmp;

	rad.x *= rot_direction;
	rad.y *= rot_direction;
	rad.z *= rot_direction;
	v[0] = cosf(rad.z);
	v[1] = sinf(rad.z);
	v[2] = cosf(rad.y);
	v[3] = sinf(rad.y);
	v[4] = cosf(rad.x);
	v[5] = sinf(rad.x);
	v[6] = v[0] * v[3];
	v[7] = v[1] * v[3];
	ft_bzero(mat, sizeof(float) * 16);
	mat[0] = v[2] * v[4];
	mat[1] = v[2] * v[5];
	mat[2] = -v[3];
	mat[4] = v[7] * v[4] - v[0] * v[5];
	mat[5] = v[7] * v[5] + v[0] * v[4];
	mat[6] = v[1] * v[2];
	mat[8] = v[6] * v[4] - v[1] * v[5];
	mat[9] = v[6] * v[5] + v[1] * v[4];
	mat[10] = v[0] * v[2];
	mat[15] =  1;
	tmp.x = src->x;// ces valeurs doivent etre en degres? probablement pas
	tmp.y = src->y;
	tmp.z = src->z;
	dst->x = tmp.x * mat[0] + tmp.y * mat[1] + tmp.z * mat[2];
	dst->y = tmp.x * mat[4] + tmp.y * mat[5] + tmp.z * mat[6];
	dst->z = tmp.x * mat[8] + tmp.y * mat[9] + tmp.z * mat[10];
}
