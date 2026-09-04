#include "libft_arr.h"
#include "libft_arr_t.h"
#include "libft_ll.h"
#include "libft_lst_kv.h"
#include "ms_redi_t.h"
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

void	ms_unset_env(char *name)
{
	t_kv	*store;

	store = env_core(MSC_INIT);
	ft_kv_free_entry(ft_kv_pop(store, name));
}

#include <unistd.h>

static void	*ms_env_fold(void *acc, void *el)
{
	t_kv_pair *pair;

	pair = el;
	*(void **) acc = ms_protect(ft_strf("%s=%s", pair->key, pair->val));
	return ((void **) acc) + 1;
}

char	**ms_get_environ(void)
{
	char **result;
	t_kv *store;

	store = env_core(MSC_INIT);
	result = ms_protect(ft_arr_new(ft_lstsize(store->_store)));
	ft_lstfold(store->_store, result, ms_env_fold);
	return (char **) result;
}

static bool	parse_env(char *input, char **output)
{
	char	*split;

	split = ft_strchr(input, '=');
	if (split == NULL)
		return (false);
	output[0] = ft_substr(input, 0, split - input);
	output[1] = ft_substr(input, 1 + split - input, ft_strlen(input));
	return (true);
}

// TODO: add SHLVL incr
// TODO: $?
void	ms_load_env(char **environ)
{
	char	*kv[2];

	if (environ == NULL || *environ == NULL)
		return ;
	if (parse_env(*environ, kv))
		ms_set_env(kv[0], kv[1]);
	ms_load_env(environ + 1);
}

// array of t_kv_pair*
t_arr	*ms_env_arr(void)
{
	t_kv	*store;

	store = env_core(MSC_INIT);
	return (ms_protect(ft_lst2arr(store->_store)));
}

void	ms_env_free(void)
{
	env_core(MSC_FREE);
}
