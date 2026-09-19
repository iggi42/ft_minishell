/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_environ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:10:47 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 12:10:54 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_env_core.h"
#include "ms_exit.h"
#include "ms_safe.h"
#include <libft_arr.h>
#include <libft_mem.h>
#include <libft_str.h>
#include <libft_toa.h>

// this code is for interactions of our variable store with __environ

static void	*ms_env_fold(void *acc, void *el)
{
	t_kv_pair	*pair;

	pair = el;
	if (ft_str_eq("?", pair->key))
		return (acc);
	*(void **)acc = ms_protect(ft_strf("%s=%s", pair->key, pair->val));
	return (((void **)acc) + 1);
}

char	**ms_env_environ_export(void)
{
	char	**result;
	t_kv	*store;

	store = ms_env_core_get();
	result = ms_protect(ft_arr_new(ft_lstsize(store->_store)));
	ft_lstfold(store->_store, result, ms_env_fold);
	return ((char **)result);
}

static bool	parse_env(char *input, char **output)
{
	char	*split;

	split = ft_strchr(input, '=');
	if (split == NULL)
		return (false);
	output[0] = ms_substr(input, 0, split - input);
	output[1] = ms_substr(input, 1 + split - input, ft_strlen(input));
	return (true);
}

void	ms_env_environ_import(char **environ)
{
	char	*kv[2];

	if (environ == NULL || *environ == NULL)
		return ;
	if (parse_env(*environ, kv))
	{
		ms_env_set(kv[0], kv[1]);
		ft_free(kv[0]);
		ft_free(kv[1]);
	}
	ms_env_environ_import(environ + 1);
}
