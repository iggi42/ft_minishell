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
#include <libft_arr.h>
#include <libft_byte_t.h>
#include <libft_io.h>
#include <libft_mem.h>
#include <libft_str.h>
#include <limits.h>
#include <unistd.h>

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

static void	update_pwd(void)
{
	char	cwd[PATH_MAX];

	ms_exit_if(getcwd(cwd, PATH_MAX), "getpwd failed");
	ms_env_set("OLDPWD", ms_env_get("PWD", ""));
	ms_env_set("PWD", (char *) &cwd);
}

t_byte	ms_exec_builtin_cd(char **argv)
{
	char	*target;
	size_t	argc;

	argc = ft_arr_len((t_arr)argv);
	if (argc > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments",
				STDERR_FILENO), 1);
	if (argc < 2)
	{
		target = ms_env_get("HOME", NULL);
		if (target == NULL)
			return (ms_complain("cd: HOME not set", 0), 1);
	}
	else if (ft_str_eq("-", argv[1]))
	{
		target = ms_env_get("OLDPWD", NULL);
		ft_printf("%s\n", target);
	}
	else
		target = argv[1];
	if (ms_chdir(target) == 0)
		return (update_pwd(), 0);
	return (1);
}
