/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtins_echo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 22:29:30 by fkruger           #+#    #+#             */
/*   Updated: 2026/08/05 22:29:34 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"
#include <unistd.h>
#include <libft_byte_t.h>
#include <stdbool.h>
#include <stddef.h>

// flags have to be at the start
// -nnnn is valid -n flag (may only contain n)
//
bool static	is_n_arg(char *may_ne)
{
	if (may_ne == NULL || *may_ne == '\0' || *may_ne != '-')
		return (false);
	while (*(++may_ne) == 'n')
	{
		if (!*(may_ne + 1))
			return (true);
	}
	return (false);
}

t_byte	ms_exec_builtin_echo(char **argv)
{
	size_t	n;
	size_t	i;

	n = 1;
	i = 0;
	while (argv[n] && is_n_arg(argv[n]))
		n++;
	while (argv[n + i])
	{
		ft_putstr_fd(argv[n + i], STDOUT_FILENO);
		if (argv[n + (++i)])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (n == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
