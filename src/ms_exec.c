/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 18:52:00 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 18:52:01 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_byte_t.h"
#include "ms_env.h"
#include "ms_exec.h"
#include <libft_arr.h>

t_byte	ms_exec(t_ms_cmd **run_me)
{
	t_byte	result;

	if (ft_arr_len((t_arr)run_me) > 1)
		result = ms_exec_pipe(run_me);
	else
		result = ms_exec_cmd(*run_me);
	ms_env_set_status(result);
	return (result);
}
