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

t_byte			ms_exec(t_ms_cmd **run_me);
// run an array of cmds in a pipe. don't use for 1 cmd.
t_byte			ms_exec_pipe(t_ms_cmd **full_pipe);

// runs a single and doesn't fork for all of them
t_byte			ms_exec_cmd(t_ms_cmd *run_me);

#endif
