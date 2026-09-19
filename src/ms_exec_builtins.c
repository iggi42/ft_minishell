/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 17:36:23 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/05 17:36:24 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec_builtins.h"
#include <libft_str.h>

t_ms_builtin	ms_builtin_get_frk(char *name)
{
	if (ft_str_eq("echo", name))
		return (ms_exec_builtin_echo);
	if (ft_str_eq("pwd", name))
		return (ms_exec_builtin_pwd);
	if (ft_str_eq("env", name))
		return (ms_exec_builtin_env);
	return (NULL);
}

t_ms_builtin	ms_builtin_get_nofrk(char *name)
{
	if (ft_str_eq("cd", name))
		return (ms_exec_builtin_cd);
	if (ft_str_eq("exit", name))
		return (ms_exec_builtin_exit);
	if (ft_str_eq("export", name))
		return (ms_exec_builtin_export);
	if (ft_str_eq("unset", name))
		return (ms_exec_builtin_unset);
	return (NULL);
}

t_ms_builtin	ms_builtin_get(char *name)
{
	t_ms_builtin	res;

	res = ms_builtin_get_nofrk(name);
	if (res != NULL)
		return (res);
	return (ms_builtin_get_frk(name));
}
