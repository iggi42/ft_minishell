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
#include "ms_exit.h"
#include "ms_env.h"
#include "ms_utils.h"
#include <unistd.h>
#include <libft_mem.h>
#include <libft_arr.h>
#include <libft_str.h>
#include <sys/stat.h>

static char	*default_str(char *normal, char *fallback)
{
	if (*normal == '\0')
		return (fallback);
	return (normal);
}

// splits a PATH like string on ':' but keeps the empty entries,
// so ":/bin" stays two entries and the current dir keeps its position
static char	**ms_split_path(char *path)
{
	char	**result;
	size_t	count;
	size_t	i;
	char	*sep;

	count = 1;
	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] == ':')
			count++;
		i++;
	}
	result = (char **)ms_protect(ft_arr_new(count));
	i = 0;
	while (i < count)
	{
		sep = ft_strchr(path, ':');
		if (sep == NULL)
			sep = path + ft_strlen(path);
		result[i] = ms_substr(path, 0, sep - path);
		path = sep + 1;
		i++;
	}
	return (result);
}

static char	*ms_search_path(char *cmd0)
{
	char	**paths;
	size_t	i;
	char	*full_path;
	char	*sub_optimal;

	if (cmd0 == NULL || *cmd0 == '\0')
		return (NULL);
	paths = ms_split_path(ms_env_get("PATH", "."));
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

// a directory is X_OK for access(), but it is not a command:
// dropping it here lets the caller report 127, like bash does
static char	*drop_dir(char *path)
{
	struct stat	info;

	if (path == NULL || stat(path, &info) != 0)
		return (path);
	if (!S_ISDIR(info.st_mode))
		return (path);
	return (ft_free(path), NULL);
}

char	*ms_find_exec_file(char *cmd0)
{
	char	*path;

	if (!ms_is_path(cmd0))
		path = drop_dir(ms_search_path(cmd0));
	else
		path = ms_strdup(cmd0);
	return (path);
}
