/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_crud.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:23:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 12:23:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_kv.h"
#include "libft_lst_kv.h"
#include "ms_env_core.h"
#include "ms_safe.h"
#include <stdbool.h>

void	ms_env_set(char *key, char *value)
{
	void		*my_val;
	void		*my_key;
	t_kv_pair	*prev;

	my_val = ms_strdup(value);
	my_key = ms_strdup(key);
	prev = ft_kv_put(ms_env_core_get(), my_key, my_val);
	ft_kv_free_entry(prev);
}

void	ms_env_touch(char *key)
{
	if (ft_kv_get(ms_env_core_get(), (void *)key) != NULL)
		return ;
	ms_env_set(key, "");
}

char	*ms_env_get(char *key, char *fallback)
{
	char	*result;

	result = ft_kv_get(ms_env_core_get(), (void *)key);
	if (result == NULL)
		return (fallback);
	return (result);
}

bool	ms_env_unset(char *name)
{
	t_kv_pair	*prev_pair;

	prev_pair = ft_kv_pop(ms_env_core_get(), name);
	if (prev_pair == NULL)
		return (false);
	return (ft_kv_free_entry(prev_pair), true);
}
