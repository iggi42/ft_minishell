/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:04:07 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 19:04:08 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXEC_H
# define MS_EXEC_H
# include "ms_cmd_t.h"

void	ms_exec(t_ms_cmd **run_me, t_byte *exit_code);
// run an array of cmds in a pipe. don't use for 1 cmd.
void	ms_exec_pipe(t_ms_cmd **full_pipe, t_byte *exit_code);

// runs a single and doesn't fork for all of them
void	ms_exec_cmd(t_ms_cmd *run_me, t_byte *exit_code);

void	ms_heredocs_prepare(t_ms_cmd *cmd);
void	ms_heredoc_cleanup(t_ms_cmd *cmd);

#endif
