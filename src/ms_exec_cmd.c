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
#include "ms_env.h"
#include "ms_exec_builtins.h"
#include "ms_exec_utils.h"
#include "ms_redi.h"
#include "ms_safe.h"
#include <libft_arr.h>
#include <libft_io.h>
#include <libft_str.h>

// this returns true for builtins which can not be done in a fork
// if such a builtin for cmd->argv[0] is found it is run
// and its exit_code stored
static bool	ms_exec_maybe_run_builtin(t_ms_cmd *cmd)
{
	t_ms_builtin	builtin;
	int				stdenv[2];

	builtin = ms_builtin_get_nofrk(cmd->argv[0]);
	stdenv[STDIN_FILENO] = ms_dup(STDIN_FILENO);
	stdenv[STDOUT_FILENO] = ms_dup(STDOUT_FILENO);
	if (cmd->argv[0] == NULL)
		return (false);
	if (builtin == NULL)
		return (false);
	ft_arr_each((t_arr)(cmd->reds), (void (*)(t_arr_el))ms_redi_apply_parent);
	if (ms_env_get_status() == 0)
		ms_env_set_status(builtin(cmd->argv));
	ms_stdenv_apply(stdenv);
	ms_close(stdenv[0]);
	ms_close(stdenv[1]);
	ft_bw_cleanup();
	return (true);
}

// TODO apply and unapply redis,
// even on non-forking builtins this might be funky, ngl.
//  returns a list of pids to wait on
t_byte	ms_exec_cmd(t_ms_cmd *cmd)
{
	pid_t	pid;
	int		stdenv[2];

	stdenv[R] = STDIN_FILENO;
	stdenv[W] = STDOUT_FILENO;
	if (ms_exec_maybe_run_builtin(cmd))
		return (ms_env_get_status());
	pid = ms_fork();
	if (pid == 0)
		ms_exec_child(cmd, stdenv);
	ft_bw_cleanup();
	return (ms_wait(pid));
}
