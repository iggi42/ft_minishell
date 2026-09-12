/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtins_pwd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 22:29:40 by fkruger           #+#    #+#             */
/*   Updated: 2026/08/05 22:29:41 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"
#include "ms_exit.h"
#include <libft_byte_t.h>
#include <limits.h>
#include <unistd.h>

t_byte	ms_exec_builtin_pwd(char **argv)
{
	char	cwd[PATH_MAX];

	(void)argv;
	// TODO check how to handle errors correctly
	ms_exit_if(getcwd(cwd, PATH_MAX), "getpwd failed");
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}
