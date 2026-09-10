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
#include "ms_exec.h"
#include "libft_arr_t.h"
#include <libft_arr.h>

t_byte			ms_exec(t_ms_cmd **run_me)
{
	if(ft_arr_len((t_arr) *run_me) > 1)
		return ms_exec_pipe(run_me);
	return ms_exec_cmd(*run_me);
}
