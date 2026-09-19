/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtins_unset.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 22:29:49 by fkruger           #+#    #+#             */
/*   Updated: 2026/08/05 22:29:50 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include <libft_arr.h>

// bash reports success even when the name was never set
static void	*folding_unset(void *acc, t_arr_el el)
{
	ms_env_unset((char *)el);
	return (acc);
}

t_byte	ms_exec_builtin_unset(char **argv)
{
	t_byte	result;

	if (argv[0] == NULL)
		return (-1);
	result = 0;
	ft_arr_fold((t_arr)(argv + 1), folding_unset, &result);
	return (result);
}
