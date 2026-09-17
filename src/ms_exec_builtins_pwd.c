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
#include "ms_env.h"
#include "ms_utils.h"
#include <libft_byte_t.h>
#include <unistd.h>

t_byte	ms_exec_builtin_pwd(char **argv)
{
	(void)argv;
	ft_putendl_fd(ms_pwd(), STDOUT_FILENO);
	return (ms_env_get_status());
}
