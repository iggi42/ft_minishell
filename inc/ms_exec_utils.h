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
# include <stddef.h>
# include <unistd.h>

# define EXIT_CMD_NOT_FOUND 127
# define EXIT_NO_EXEC_PERM 126

enum	e_pipe_end
{
	R = 0,
	W = 1
};

pid_t	ms_fork(void);
void	ms_close(int fd);
void	ms_dup2(int from, int to);

int		*ms_pipe(int *new_pipe);

char	*ms_find_exec_file(char *cmd0);

int		fill_here_doc(char *delimiter, pid_t *writer);


// file utils for redis
int		open_infile(char *infile_path);

int		open_outfile(char *outfile_path);
int		open_outappfile(char *outfile_path);

#endif
