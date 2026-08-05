/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 16:26:51 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/19 16:26:51 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "bw.h"
#include "ms_exec_utils.h"
#include "ms_redi.h"
#include "ms_env.h"
#include "ms_utils.h"
#include <errno.h>
#include <fcntl.h>
#include <libft_io.h>
#include <libft_arr.h>
#include <libft_mem.h>
#include <libft_merle.h>
#include <libft_str.h>
#include <string.h>
#include <unistd.h>

int	*ms_pipe(int *new_pipe)
{
	if (pipe(new_pipe) == 0)
	{
		ft_bw_add(new_pipe[R]);
		ft_bw_add(new_pipe[W]);
		return (new_pipe);
	}
	ms_error_out(EXIT_FAILURE, "pipe failure", errno);
	return (NULL);
}

pid_t	ms_fork(void)
{
	pid_t	result;

	errno = 0;
	result = fork();
	if (result < 0)
		ms_error_out(EXIT_FAILURE, "fork failure", errno);
	return (result);
}

void	ms_close(int fd)
{
	ft_bw_rm(fd);
	close(fd);
}

void	ms_dup2(int from, int to)
{
	int		result;
	char	*err_msg;

	result = dup2(from, to);
	if (result == to)
		return (ft_bw_add(to));
	err_msg = ft_strf("ft_dup failure [%d => %d]: %s", from, to,
			strerror(errno));
	ft_putendl_fd(err_msg, STDERR_FILENO);
	ft_free(err_msg);
	ms_exit(EXIT_FAILURE);
}

bool	is_path(char *cmd)
{
	while (cmd != NULL)
	{
		if (*cmd == '/')
			return (true);
		if (*cmd == '\0')
			return (false);
		cmd++;
	}
	return (false);
}

static char	*default_str(char *normal, char *fallback)
{
	if (*normal == '\0')
		return (fallback);
	return (normal);
}

static char	*ms_search_path(char *cmd0)
{
	char	**paths;
	size_t	i;
	char	*full_path;
	char	*sub_optimal;

	if (cmd0 == NULL || *cmd0 == '\0')
		return (NULL);
	paths = ft_split(ms_get_env("PATH", "."), ':');
	i = 0;
	sub_optimal = NULL;
	while (paths != NULL && paths[i])
	{
		full_path = ft_strf("%s/%s", default_str(paths[i], "."), cmd0);
		if (full_path == NULL || access(full_path, X_OK) == 0)
			return (ft_arr_each((t_arr)paths, ft_free), ft_free(paths),
				ft_free(sub_optimal), full_path);
		if (sub_optimal == NULL && access(full_path, F_OK) == 0)
			sub_optimal = (ft_free(sub_optimal), full_path);
		else
			ft_free(full_path);
		i++;
	}
	if (paths)
		ft_arr_each((t_arr)paths, ft_free);
	return (ft_free(paths), sub_optimal);
}

char	*ms_find_exec_file(char *cmd0)
{
	char	*path;

	if (!is_path(cmd0))
		path = ms_search_path(cmd0);
	else
		path = ft_strdup(cmd0);
	if (path == NULL || access(path, F_OK))
	{
		path = ft_strf("%s: command not found", cmd0);
		ms_error_out(EXIT_CMD_NOT_FOUND, path, 0);
	}
	return (path);
}

int	open_infile(char *infile_path)
{
	int	fd;

	errno = 0;
	fd = open(infile_path, O_RDONLY | O_CLOEXEC);
	if (fd >= 0)
		return (fd);
	ms_error_out(EXIT_FAILURE, infile_path, errno);
	return (-1);
}

int	open_outfile(char *outfile_path)
{
	int	fd;

	errno = 0;
	fd = open(outfile_path, O_CREAT | O_TRUNC | O_WRONLY | O_CLOEXEC, 0644);
	if (fd >= 0)
		return (fd);
	ms_error_out(EXIT_FAILURE, outfile_path, errno);
	return (-1);
}

int	open_outappfile(char *outfile_path)
{
	int	fd;

	errno = 0;
	fd = open(outfile_path, O_CREAT | O_WRONLY | O_APPEND | O_CLOEXEC, 0644);
	if (fd >= 0)
		return (fd);
	ms_error_out(EXIT_FAILURE, outfile_path, errno);
	return (-1);
}
