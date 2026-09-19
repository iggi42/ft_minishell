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

#include "ms_env.h"
#include "ms_exec.h"
#include "ms_signal.h"
#include <libft_arr.h>
#include <signal.h>

void	ms_exec(t_ms_cmd **run_me)
{
	t_byte	result;

	ms_env_set_status(0);
	if (*run_me == NULL)
		return ;
	ft_arr_each((t_arr)run_me, (void (*)(t_arr_el))ms_heredocs_prepare);
	if (ms_signal_last() == SIGINT)
		result = 128 + SIGINT;
	else if (*(run_me + 1) == NULL)
		result = ms_exec_cmd(*run_me);
	else
		result = ms_exec_pipe(run_me);
	ft_arr_each((t_arr)run_me, (void (*)(t_arr_el))ms_heredoc_cleanup);
	ms_env_set_status(result);
}
