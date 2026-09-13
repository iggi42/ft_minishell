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
#include "libft_arr_t.h"
#include "ms_cmd_t.h"
#include "ms_env.h"
#include "ms_dbg.h"
#include "ms_exec.h"
#include "ms_safe.h"
#include <libft_arr.h>
#include <libft_byte_t.h>

t_byte	ms_exec(t_ms_cmd **run_me)
{
	t_byte	result;

	if (*run_me == NULL)
		return (0);
	ft_arr_each((t_arr)run_me, (void (*)(t_arr_el)) ms_heredocs_prepare);
	if (ft_arr_len((t_arr)run_me) > 1)
		result = ms_exec_pipe(run_me);
	else
		result = ms_exec_cmd(*run_me);
	ms_env_set_status(result);
	return (result);
}
