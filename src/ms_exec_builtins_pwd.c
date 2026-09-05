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
#include <libft_byte_t.h>
#include <linux/limits.h>
#include <unistd.h>
#include <limits.h>

t_byte			ms_exec_builtin_pwd(char **argv)
{
	(void) argv;
	char s[PATH_MAX];
	getcwd(s, PATH_MAX);
	ft_putendl_fd(s, STDOUT_FILENO);
	return -1;
}

