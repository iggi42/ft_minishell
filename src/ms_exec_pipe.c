/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:06:28 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/19 15:06:29 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bw.h"
#include "ms_env.h"
#include "ms_exec_builtins.h"
#include "ms_exec_utils.h"
#include "ms_exit.h"
#include "ms_redi.h"
#include "ms_safe.h"
#include <errno.h>
#include <libft_arr.h>
#include <libft_ll.h>
#include <libft_io.h>
#include <libft_mem.h>
#include <stdio.h>
#include <unistd.h>

static void	add_pid(t_list **pids, pid_t pid)
{
	t_list	*new_el;
	pid_t	*new_content;

	new_content = ms_malloc(sizeof(pid_t));
	*new_content = pid;
	new_el = ft_lstnew(new_content);
	ft_lstadd_back(pids, new_el);
}

// returns a list of pids to wait on
static t_list	*spawn_pipe(t_ms_cmd **cmds)
{
	pid_t	fr;
	int		out_pipe[2];
	int		stdenv[2];
	t_list	*result;

	result = NULL;
	out_pipe[R] = STDIN_FILENO;
	stdenv[R] = STDIN_FILENO;
	while (cmds[0] != NULL)
	{
		if(stdenv[R] != STDIN_FILENO)
			ms_close(stdenv[R]);
		stdenv[R] = out_pipe[R];
		if (cmds[1] != NULL)
			stdenv[W] = ms_pipe((int *)out_pipe)[W];
		else
			stdenv[W] = STDOUT_FILENO;
		// ft_printf_fd(STDERR_FILENO, "stdenv [%d, %d], pipe [R:%d, W:%d] \n", stdenv[0], stdenv[1], out_pipe[R], out_pipe[W]);
		fr = ms_fork();
		if (fr == 0)
			ms_exec_child(cmds[0], stdenv);
		add_pid(&result, fr);
		if(stdenv[W] != STDOUT_FILENO)
			ms_close(out_pipe[W]);
		cmds++;
	}
	return (result);
}

// not defined for an empty pipe, needs at least 1 element!
t_byte	ms_exec_pipe(t_ms_cmd **full_pipe)
{
	t_list	*current_pids;
	t_list	*start_pids;
	t_byte	result;

	start_pids = spawn_pipe(full_pipe);
	current_pids = start_pids;
	ft_bw_cleanup();
	result = 0;
	while (current_pids)
	{
		result = ms_wait(*(int *)current_pids->content);
		current_pids = current_pids->next;
	}
	ft_lstclear(&start_pids, ft_free);
	return (result);
}
