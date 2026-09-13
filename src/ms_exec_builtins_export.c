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

#include "ms_env.h"
#include "ms_exit.h"
#include "ms_parsing_getlen.h"
#include "ms_safe.h"
#include <libft_arr.h>
#include <libft_io.h>
#include <libft_mem.h>
#include <libft_str.h>

// TODO: without arguments: print env sorted alphabetical
// TODO: parsing variable names, check for valid var names
// valid var names start with a _ or a-z / A-Z .
// the rest of the name may also contain 0-9

t_byte	import_var(char *arg)
{
	size_t	var_name_len;
	char	*var_name;

	var_name_len = ms_parsing_varname(arg);
	if (var_name_len == 0)
	{
		var_name = ms_protect(ft_strf("export: `%s': not a valid identifier",
					arg));
		ms_complain(var_name, 0);
		ft_free(var_name);
		return (1);
	}
	if(arg[var_name_len] == '=')
		var_name = ms_substr(arg, 0, var_name_len);
	else
		var_name = ms_strdup("");
	if(arg[var_name_len] == '\0')
		ms_env_set(var_name, "");
	else
		ms_env_set(var_name, &arg[var_name_len + 1]);
	ft_free(var_name);
	return (0);
}

// return true if importing worked
t_byte	import_vars(char **arg)
{
	if (*arg == NULL)
		return (0);
	return (import_var(*arg) | import_vars(arg + 1));
}

t_byte	print_declares(void)
{
	return (0);
}

t_byte	ms_exec_builtin_export(char **argv)
{
	if (ft_arr_len((t_arr)argv) < 2)
		return (print_declares());
	return (import_vars(argv + 1));
}
