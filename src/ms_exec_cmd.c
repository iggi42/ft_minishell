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
#include "libft_byte_t.h"
#include "ms_cmd_t.h"
// #include "ms_dbg.h"
#include "ms_env.h"
#include "ms_exec_builtins.h"
#include "ms_exec_utils.h"
#include "ms_exit.h"
#include "ms_redi.h"
#include "ms_safe.h"
#include <errno.h>
#include <libft_arr.h>
#include <libft_ll.h>

// this _never_ returns
static void	exec_1_cmd(t_ms_cmd *cmd, int stdenv[2])
{
	char		*path;
	ms_builtin	built_in;
	char		**my_environ;

	ms_apply_stdenv(stdenv);
	ft_arr_each((t_arr)(cmd->reds), (void (*)(t_arr_el))ms_redi_apply);
	if (cmd->argv[0] == NULL)
		ms_exit(EXIT_SUCCESS);
	built_in = ms_get_builtin(cmd->argv[0]);
	path = ms_find_exec_file(cmd->argv[0]);
	ft_bw_cleanup();
	if (built_in != NULL)
		ms_exit(built_in(cmd->argv));
	my_environ = ms_protect(ms_env_environ_export());
	errno = 0;
	execve(path, cmd->argv, my_environ);
	ms_error_out(EXIT_NO_EXEC_PERM, path, errno);
}

static pid_t	spawn_cmd(t_ms_cmd *cmd)
{
	pid_t	fr;
	int		stdenv[2];

	stdenv[R] = STDIN_FILENO;
	stdenv[W] = STDOUT_FILENO;
	// FIXME: this needs to surive empty cmds
	fr = ms_fork();
	if (fr == 0)
		exec_1_cmd(cmd, stdenv);
	return (fr);
}

// #include <ms_dbg.h>

// this returns true for builtins which can not be done in a fork
// if such a builtin for cmd->argv[0] is found it is run and its exit_code stored
static bool	ms_exec_maybe_run_builtin(t_ms_cmd *cmd, t_byte *exit_code)
{
	ms_builtin	builtin;

	if (cmd->argv[0] == NULL)
		return (false);
	builtin = ms_get_builtin_nofrk(cmd->argv[0]);
	if (builtin == NULL)
		return (false);
	*exit_code = builtin(cmd->argv);
	return (true);
}

// TODO apply and unapply redis,
// even on non-forking builtins this might be funky, ngl.
//  returns a list of pids to wait on
t_byte	ms_exec_cmd(t_ms_cmd *cmd)
{
	pid_t	pid;
	t_byte	result;

	// ms_print_cmd("single cmd", cmd);
	if (ms_exec_maybe_run_builtin(cmd, &result))
		return (result);
	pid = spawn_cmd(cmd);
	ft_bw_cleanup();
	return (ms_wait(pid));
}
