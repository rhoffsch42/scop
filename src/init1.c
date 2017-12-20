#include <scop.h>

t_xpm	*init_xpm(void)
{
	static int	id = 0;
	t_xpm		*xpm;

	printf("__ init_xpm\n");
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

t_env	*init_env(void)
{
	t_env	*e;

	printf("__ init_env\n");
	e = (t_env*)safe_malloc(sizeof(t_env));
	e->objfile = NULL;
	e->mtlfile = NULL;
	e->xpmfile = NULL;
	e->dir = NULL;
	e->glfw = NULL;
	e->chart = init_rgb();
	return (e);
}

t_obj	*init_obj(void)
{
	static int	id = 0;
	t_obj		*object;

	printf("__ init_obj\n");
	object = (t_obj*)safe_malloc(sizeof(t_obj));
	ft_bzero((void*)object, sizeof(t_obj));
	object->id = id;
	object->id_char = ft_itoa(id);
	object->name = ft_strjoin("Object #", object->id_char);
	object->mtllib = NULL;
	object->mtlfile = NULL;
	object->mat_name = NULL;
	object->mat = NULL;
	object->v = NULL;
	object->f = NULL;
	object->next = NULL;
	id++;
	return (object);
}

t_mat	*init_mat(void)
{
	static int	id = 0;
	t_mat		*material;

	printf("__ init_mat\n");
	material = (t_mat*)safe_malloc(sizeof(t_mat));
	ft_bzero((void*)material, sizeof(t_mat));
	material->id = id;
	material->id_char = ft_itoa(id);
	material->name = ft_strjoin("Material #", material->id_char);
	material->next = NULL;
	id++;
	return (material);
}
