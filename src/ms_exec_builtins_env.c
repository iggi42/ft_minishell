/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtins_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 22:29:52 by fkruger           #+#    #+#             */
/*   Updated: 2026/08/05 22:29:59 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_arr.h"
#include "libft_io.h"
#include "libft_mem.h"
#include "ms_env.h"
#include <unistd.h>

// env is not a bash builtin normaly, but a posix utility

static void	print_line(void *line)
{
	ft_putendl_fd(line, STDOUT_FILENO);
}

t_byte	ms_exec_builtin_env(char **argv)
{
	char	**my_environ;

	(void)argv;
	my_environ = ms_env_environ_export();
	ft_arr_each((t_arr)my_environ, print_line);
	ft_arr_each((t_arr)my_environ, ft_free);
	ft_free(my_environ);
	return (0);
}
