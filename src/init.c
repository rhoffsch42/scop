#include <scop.h>

t_env	*init_env(void)
{
	t_env	*e;

	e = (t_env*)safe_malloc(sizeof(t_env));
	e->obj = NULL;
	e->objfile = NULL;
	e->mtlfile = NULL;
	e->dir = NULL;
	return (e);
}

t_obj	*init_obj(void)
{
	static int	id = 0;
	t_obj	*object;

	object = (t_obj*)safe_malloc(sizeof(t_obj));
	object->id = id;
	object->name = ft_strdup("\'N/D\'");
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
	t_mat	*material;

	material = (t_mat*)safe_malloc(sizeof(t_mat));
	material->id = id;
	material->name = ft_strdup("\'N/D\'");
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
