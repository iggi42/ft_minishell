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
#include "ms_exec_builtins.h"
#include "ms_exec_utils.h"
#include "ms_redi.h"
#include "ms_safe.h"
#include "ms_utils.h"
#include <errno.h>
#include <libft_arr.h>
#include <libft_ll.h>

// this _never_ returns
static void	exec_cmd(t_ms_cmd *cmd, int stdenv[2])
{
	char		*path;
	ms_builtin	built_in;

	ms_apply_stdenv(stdenv);
	ft_arr_each((t_arr)(cmd->reds), (void (*)(t_arr_el))apply_redi);
	if (cmd->argv[0] == NULL)
		ms_exit(EXIT_SUCCESS);
	built_in = ms_get_builtin(cmd->argv[0]);
	// TODO get buitltin here if argv[0] matches
	path = ms_find_exec_file(cmd->argv[0]);
	ft_bw_cleanup();
	if (built_in != NULL)
		ms_exit(built_in(cmd->argv));
	else
		execve(path, cmd->argv, __environ);
	ms_error_out(EXIT_NO_EXEC_PERM, path, errno);
}

// returns a list of pids to wait on
static pid_t	spawn_cmd(t_ms_cmd *cmds)
{
	pid_t	fr;
	int		stdenv[2];

	stdenv[R] = STDIN_FILENO;
	stdenv[W] = STDOUT_FILENO;
	// FIXME: this needs to surive empty cmds
	fr = ms_fork();
	if (fr == 0)
		exec_cmd(cmds, stdenv);
	return (fr);
}

t_byte	ms_exec_cmd(t_ms_cmd *cmd)
{
	pid_t		pid;
	ms_builtin	builtin;

	builtin = ms_get_builtin_nofrk(cmd->argv[0]);
	if (builtin)
		return (builtin(cmd->argv));
	pid = spawn_cmd(cmd);
	ft_bw_cleanup();
	return (ms_wait(pid));
}
