/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:53:37 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:53:39 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

bool	ms_is_path(char *cmd)
{
	while (cmd != NULL)
	{
		if (*cmd == '/')
			return (true);
		if (*cmd == '\0')
			return (false);
		cmd++;
	}
	return (false);
}
