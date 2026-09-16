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
#include <libft_str.h>

// this returns true for builtins which can not be done in a fork
// if such a builtin for cmd->argv[0] is found it is run and its exit_code stored
static bool	ms_exec_maybe_run_builtin(t_ms_cmd *cmd, t_byte *exit_code)
{
	ms_builtin	builtin;

	if (cmd->argv[0] == NULL)
		return (false);
	builtin = ms_builtin_get_nofrk(cmd->argv[0]);
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
	int		stdenv[2];

	if (ms_exec_maybe_run_builtin(cmd, &result))
		return (result);
	stdenv[R] = STDIN_FILENO;
	stdenv[W] = STDOUT_FILENO;
	pid = ms_fork();
	if (pid == 0)
		ms_exec_child(cmd, stdenv);
	ft_bw_cleanup();
	return (ms_wait(pid));
}
