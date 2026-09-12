/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtins_cd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 22:29:36 by fkruger           #+#    #+#             */
/*   Updated: 2026/08/05 22:29:37 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_exit.h"
#include <errno.h>
#include <libft_byte_t.h>
#include <libft_io.h>
#include <libft_mem.h>
#include <libft_str.h>
#include <unistd.h>
#include <limits.h>

static t_byte	ms_chdir(char *s)
{
	char	*err_msg;

	if (s == NULL)
		return (1);
	errno = 0;
	if (chdir(s) == 0)
		return (0);
	err_msg = ms_protect(ft_strf("minishell: cd: %s", s));
	ms_complain(err_msg, errno);
	ft_free(err_msg);
	return (1);
}

t_byte	ms_exec_builtin_cd(char **argv)
{
	char	*target;
	char	cwd[PATH_MAX];

	if (argv[1] != NULL)
		target = argv[1];
	else
		target = ms_env_get("HOME", NULL);
	ms_exit_if(target, "cd: HOME not set");
	if(ms_chdir(target) == 0)
	{
		// TODO check how to handle errors correctly
		ms_exit_if(getcwd(cwd, PATH_MAX), "getpwd failed");
		ms_env_set("OLDPWD", ms_env_get("PWD", ""));
		ms_env_set("PWD", (char *) &cwd);
		return 0;
	}
	return 1;
}
