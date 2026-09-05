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
# include <libft_byte_t.h>

typedef t_byte	(*ms_builtin)(char **argv);

ms_builtin		ms_get_builtin(char *name);
ms_builtin		ms_get_builtin_frk(char *name);
ms_builtin		ms_get_builtin_nofrk(char *name);

// run an array of cmds in a pipe. don't use for 1 cmd.
t_byte			ms_run_pipe(t_ms_cmd **full_pipe);

#endif
