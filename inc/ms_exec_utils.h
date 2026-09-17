/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 11:58:49 by fkruger           #+#    #+#             */
/*   Updated: 2026/08/05 11:58:50 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXEC_UTILS_H
# define MS_EXEC_UTILS_H
# include "ms_cmd_t.h"

# define EXIT_CMD_NOT_FOUND 127
# define EXIT_NO_EXEC_PERM 126

enum	e_pipe_end
{
	R = 0,
	W = 1
};

void	ms_stdenv_apply(int stdenv[2]);

void	ms_stdenv_close(void);

// applys the fds in stdenv and then execs into the cmd
// or a builtin, or errors out with the appropate exit code
void	ms_exec_child(t_ms_cmd *cmd, int stdenv[2]);

char	*ms_find_exec_file(char *cmd0);

int		ms_fill_here_doc(char *delimiter, pid_t *writer);

// file utils for redis
int		ms_open_infile(char *infile_path);
int		ms_open_outfile(char *outfile_path);
int		ms_open_outappfile(char *outfile_path);

#endif
