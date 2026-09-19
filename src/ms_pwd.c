/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:25:57 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:26:00 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include <errno.h>
#include <libft_mem.h>
#include <limits.h>
#include <unistd.h>

char	*ms_pwd(void)
{
	static char	cwd[PATH_MAX];

	ft_bzero(cwd, sizeof(cwd));
	errno = 0;
	(void) getcwd(cwd, PATH_MAX);
	if (errno != 0)
	{
		ms_env_set_status(1);
		cwd[0] = '\0';
	}
	return ((char *)cwd);
}
