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
#include "ms_exit.h"
#include <libft_io.h>

t_byte			ms_exec_builtin_exit(char **argv)
{
	ms_exit(EXIT_SUCCESS);
	(void) argv;
	return -1;
}

