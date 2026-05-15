/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iszero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_mem.h"
#include <stdbool.h>

bool	ft_iszero(const void *start, const size_t size)
{
	t_byte	rele;

	if (size == 0)
		return (true);
	rele = *(t_byte *)start;
	if (rele != 0)
		return (false);
	return (ft_iszero(start + 1, size - 1));
}
