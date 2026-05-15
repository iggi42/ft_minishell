/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa_bl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:35:38 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:07 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_toa.h"
#include "libft_mem.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

size_t	ft_ptoa_bl(void *ptr, char *target, size_t max_len,
		const char *alphabet)
{
	size_t	addr;
	size_t	len;

	addr = (uintptr_t)ptr;
	len = ft_ultoa_bl(addr, NULL, 0, alphabet);
	if (len + 2 > max_len || target == NULL)
		return (len + 2);
	if (target != NULL)
	{
		ft_memcpy(target, "0x", 2);
		ft_ultoa_bl(addr, target + 2, len, alphabet);
	}
	return (len + 2);
}
