/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:17:42 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_mem.h"

static void	*ft_memcpy_r(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		*((t_byte *)dest + (i - 1)) = *((t_byte *)src + (i - 1));
		i--;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else if (dest > src)
		return (ft_memcpy_r(dest, src, n));
	else
		return (dest);
}
