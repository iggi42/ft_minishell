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
#include "ms_exec_utils.h"
#include "ms_safe.h"
#include <libft_mem.h>

static void	add_pid(t_list **pids, pid_t pid)
{
	t_list	*new_el;
	pid_t	*new_content;

	new_content = ms_malloc(sizeof(pid_t));
	*new_content = pid;
	new_el = ft_lstnew(new_content);
	ft_lstadd_back(pids, new_el);
}

static void	ms_close_unless(int fd, int unless)
{
	if (fd != unless)
		ms_close(fd);
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
		ms_close_unless(stdenv[R], STDIN_FILENO);
		stdenv[R] = out_pipe[R];
		if (cmds[1] != NULL)
			stdenv[W] = ms_pipe((int *)out_pipe)[W];
		else
			stdenv[W] = STDOUT_FILENO;
		fr = ms_fork();
		if (fr == 0)
			ms_exec_child(cmds[0], stdenv);
		add_pid(&result, fr);
		ms_close_unless(out_pipe[W], STDOUT_FILENO);
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
