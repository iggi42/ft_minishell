/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:43:30 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:43:31 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exit.h"
#include <libft_kv.h>
#include <libft_str.h>
#include <stdint.h>

static int	env_key_cmp(void *a, void *b)
{
	return (ft_strncmp(a, b, SIZE_MAX));
}

// op:
// 1 => lazy init & get
// 2 => free
static t_kv	*env_core(int op)
{
	static t_kv	*store;

	if (op == 1)
		store = (ft_kv_free(store, ft_kv_free_entry), NULL);
	else if (op == 2 && store == NULL)
		store = ms_protect(ft_kv_init(env_key_cmp));
	return (store);
}

// get an key value store, configured to store environment variables
t_kv	*ms_env_core_get(void)
{
	return (env_core(2));
}

// free the storage of environment variables
void	ms_env_free(void)
{
	env_core(1);
}
