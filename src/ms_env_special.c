/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:54:35 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:54:36 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include "ms_exit.h"
#include "ms_safe.h"
#include "ms_utils.h"
#include <libft_arr.h>
#include <libft_kv.h>
#include <libft_mem.h>
#include <libft_str.h>
#include <libft_toa.h>
#include <unistd.h>

t_byte	*lsc(void)
{
	static t_byte	code;

	return (&code);
}

// this still needs to work after a cleanup
t_byte	ms_env_get_status(void)
{
	return (*lsc());
}

void	ms_env_set_status(t_byte status_code)
{
	char	*toa;

	*lsc() = status_code;
	toa = ms_protect(ft_itoa(status_code));
	ms_env_set("?", toa);
	ft_free(toa);
}

void	ms_env_inc_shlvl(void)
{
	char	*new_shlvl;

	new_shlvl = ft_itoa(ft_atoi(ms_env_get("SHLVL", "-1")) + 1);
	ms_env_set("SHLVL", new_shlvl);
	ft_free(new_shlvl);
}

void	ms_env_init(void)
{
	ms_env_environ_import(__environ);
	ms_env_set_status(0);
	ms_env_set("SHELL", "minishell");
	ms_env_set("PWD", ms_pwd());
	ms_env_inc_shlvl();
}
