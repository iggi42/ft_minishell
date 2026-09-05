/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtins_export.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 22:29:43 by fkruger           #+#    #+#             */
/*   Updated: 2026/08/05 22:29:48 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_byte_t.h>
#include "ms_env.h"

// TODO: without arguments: print env sorted alphabetical
// TODO: parsing variable names, check for valid var names
// valid var names start with a _ or a-z / A-Z .
// the rest of the name may also contain 0-9

t_byte			ms_exec_builtin_export(char **argv)
{
	(void) argv;
	// ms_set_env(char *name, const char *value)
	return -1;
}
