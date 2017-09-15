#include <scop.h>

t_env	*init_env(void)
{
	t_env	*e;

	e = (t_env*)safe_malloc(sizeof(t_env));
	e->obj = NULL;
	e->objfile = NULL;
	e->mtlfile = NULL;
	return (e);
}
