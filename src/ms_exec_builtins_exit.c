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

#include <libft_byte_t.h>
#include <stdlib.h>
#include "libft_str.h"
#include "ms_env.h"
#include "ms_exit.h"
#include <libft_io.h>
#include <libft_arr.h>

t_byte			ms_exec_builtin_exit(char **argv)
{
	t_byte exit_code;
	size_t argc;

	argc = ft_arr_len((t_arr)argv);
	if(argc > 2)
		return (2);
	if(argv[0] == NULL)
		ms_exit(EXIT_FAILURE);
	if(argv[1] == NULL)
		exit_code = ms_env_get_status();
	else
		exit_code = ft_atoi(argv[1]);
	ms_exit(exit_code);
	return -1;
}

