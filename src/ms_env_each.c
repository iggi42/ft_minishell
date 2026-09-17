#include "ms_env_core.h"
#include <stddef.h>

static void	ms_env_folder(t_kv_pair *pair, void *folder)
{
	((void (*)(t_kv_pair *, void *))folder)(pair->key, pair->val);
}

void	ms_env_each(void (*each)(char *name, char *value))
{
	if (each == NULL)
		return ;
	ft_kv_fold(ms_env_core_get(), ms_env_folder, each);
}
