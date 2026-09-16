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
#include "ms_safe.h"
#include <libft_arr.h>
#include <libft_byte_t.h>

void ms_exec(t_ms_cmd **run_me, t_byte *status_code)
{
	if (*run_me == NULL)
		return ;
	if(*status_code != 0)
		return;
	ft_arr_each((t_arr)run_me, (void (*)(t_arr_el))ms_heredocs_prepare);
	if(*status_code == 0)
	{
		if (*(run_me + 1) == NULL)
			ms_exec_cmd(*run_me, status_code);
		else
			 ms_exec_pipe(run_me, status_code);
	}
	ft_arr_each((t_arr)run_me, (void (*)(t_arr_el))ms_heredoc_cleanup);
	ms_env_set_status(*status_code);
}
