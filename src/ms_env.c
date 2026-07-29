#include "libft_arr.h"
#include "libft_arr_t.h"
#include "libft_ll.h"
#include "libft_lst_kv.h"
#include "ms_utils.h"
#include <libft_kv.h>
#include <libft_mem.h>
#include <libft_str.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

static int	env_key_cmp(void *a, void *b)
{
	return (ft_strncmp(a, b, SIZE_MAX));
}

// op:
// 1 => lazy init & get
// 2 => free
#define MSC_INIT 1
#define MSC_FREE 2

static t_kv	*env_core(int op)
{
	static t_kv	*store;

	if (op == MSC_FREE)
		store = (ft_kv_free(store, ft_kv_free_entry), NULL);
	else if (op == MSC_INIT && store == NULL)
		store = ms_protect(ft_kv_init(env_key_cmp));
	return (store);
}

void	ms_set_env(char *key, const char *value)
{
	t_kv		*store;
	void		*my_val;
	void		*my_key;
	t_kv_pair	*prev;

	my_val = ms_protect(ft_strdup(value));
	my_key = ms_protect(ft_strdup(key));
	store = env_core(MSC_INIT);
	prev = ft_kv_put(store, my_key, my_val);
	ft_kv_free_entry(prev);
}

char	*ms_get_env(char *key, char *fallback)
{
	t_kv	*store;
	char	*result;

	store = env_core(MSC_INIT);
	result = ft_kv_get(store, (void *)key);
	if (result == NULL)
		return (fallback);
	return (result);
}

void		ms_unset_env(char *name)
{
	t_kv	*store;

	store = env_core(MSC_INIT);
	ft_kv_free_entry(ft_kv_pop(store, name));
}

#include <unistd.h>
static void *ms_env_envstr(void *pair)
{
	if(pair == NULL)
		return NULL;
	// return ft_strf("%s=%s", pair->key, pair->val);
	return ft_strdup("lol");
}

char	**ms_get_environ(void)
{
	t_arr *keypairs = ft_lst2arr(env_core(MSC_INIT)->_store);
	return (char **) ft_arr_map(*keypairs, ms_env_envstr);
}
 
// array of t_kv_pair*
t_arr	*ms_env_arr(void)
{
	t_kv	*store;

	store = env_core(MSC_INIT);
	return ms_protect(ft_lst2arr(store->_store));
}

void	ms_env_free(void)
{
	env_core(MSC_FREE);
}
