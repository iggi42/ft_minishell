/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtins_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 22:30:01 by fkruger           #+#    #+#             */
/*   Updated: 2026/08/05 22:30:01 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_exit.h"
#include "ms_utils.h"
#include <libft_arr.h>
#include <libft_io.h>
#include <libft_mem.h>
#include <libft_str.h>
#include <unistd.h>

t_byte	ms_exec_builtin_exit(char **argv)
{
	t_byte	exit_code;
	size_t	argc;
	char	*msg;

	argc = ft_arr_len((t_arr)argv);
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (argv[1] != NULL && !ms_atoi_valid(argv[1]))
	{
		msg = ms_protect(ft_strf("minishell: exit: %s: "
					"numeric argument required", argv[1]));
		ms_complain(msg, 0);
		ft_free(msg);
		ms_exit(2);
	}
	if (argc > 2)
		return (ms_complain("minishell: exit: too many arguments", 0), 1);
	if (argv[0] == NULL)
		ms_exit(EXIT_FAILURE);
	if (argv[1] == NULL)
		exit_code = ms_env_get_status();
	else
		exit_code = ms_atoi(argv[1]);
	ms_exit(exit_code);
	return (-1);
}
