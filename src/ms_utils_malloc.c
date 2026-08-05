/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 17:54:18 by fkruger           #+#    #+#             */
/*   Updated: 2026/07/26 17:54:27 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_utils.h"
#include <libft_io.h>
#include <libft_mem.h>
#include <unistd.h>

void	*ms_malloc(size_t size)
{
	void	*result;

	result = ft_malloc(size);
	if (result)
		return (result);
	ft_putendl_fd("\nOUT OF MEMORY\n", STDERR_FILENO);
	ms_exit(EXIT_FAILURE);
	return (NULL);
}


