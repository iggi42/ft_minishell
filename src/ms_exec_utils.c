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

#include "ms_safe.h"
#include "ms_env.h"
#include "ms_exit.h"
#include "unistd.h"
#include "ms_exec_utils.h"
#include <libft_str.h>
#include <libft_arr.h>
#include <libft_mem.h>

void ms_apply_stdenv(int stdenv[2])
{
	ms_dup2(stdenv[R], STDIN_FILENO);
	ms_dup2(stdenv[W], STDOUT_FILENO);
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
	//TODO handle getting PATH='::' (basically any amount of just ':')
	paths = ms_protect(ft_split(ms_get_env("PATH", "."), ':'));
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
		path = ms_strdup(cmd0);
	if (access(path, F_OK))
	{
		path = ft_strf("%s: command not found", cmd0);
		ms_error_out(EXIT_CMD_NOT_FOUND, path, 0);
	}
	return (path);
}
