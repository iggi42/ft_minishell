/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:06:28 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/19 15:06:29 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bw.h"
#include "ms_cmd_t.h"
#include "ms_exec_utils.h"
#include "ms_redi.h"
#include "ms_utils.h"
#include <errno.h>
#include <fcntl.h>
#include <libft_arr.h>
#include <libft_io.h>
#include <libft_ll.h>
#include <libft_mem.h>
#include <libft_merle.h>
#include <libft_os.h>
#include <libft_str.h>
#include <string.h>
#include <unistd.h>

void	apply_stdenv(int stdenv[2])
{
	ms_dup2(stdenv[R], STDIN_FILENO);
	ms_dup2(stdenv[W], STDOUT_FILENO);
}

// this _never_ returns
static void	exec_cmd(t_ms_cmd *cmd, int stdenv[2])
{
	char	*path;

	apply_stdenv(stdenv);
	ft_arr_each((t_arr)(cmd->reds), (void (*)(t_arr_el))apply_redi);
	path = ms_find_exec_file(cmd->argv[0]);
	ft_bw_cleanup();
	execve(path, cmd->argv, __environ);
	ms_error_out(EXIT_NO_EXEC_PERM, path, errno);
}

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
	while (cmds[0] != NULL)
	{
		stdenv[R] = out_pipe[R];
		if (cmds[1] != NULL)
			stdenv[W] = ms_pipe((int *)out_pipe)[W];
		else
			stdenv[W] = STDOUT_FILENO;
		fr = ms_fork();
		if (fr == 0)
			exec_cmd(cmds[0], stdenv);
		add_pid(&result, fr);
		cmds++;
	}
	return (result);
}

// not defined for an empty pipe, needs at least 1 element!
t_byte	ms_run_pipe(t_ms_cmd **full_pipe)
{
	t_list	*pids;
	t_byte	result;

	pids = spawn_pipe(full_pipe);
	ft_bw_cleanup();
	result = 0;
	while (pids)
	{
		result = ft_wait(*(int *)pids->content);
		pids = pids->next;
	}
	return (result);
}
