/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:37:53 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_byte_t.h"
#include <stddef.h>

int	ft_memcmp(const void *m1, const void *m2, size_t n)
{
	int		buffer;
	t_byte	*b1;
	t_byte	*b2;

	if (n == 0 || m1 == m2)
		return (0);
	b1 = (t_byte *)m1;
	b2 = (t_byte *)m2;
	buffer = *b1 - *b2;
	if (buffer == 0)
		return (ft_memcmp(b1 + 1, b2 + 1, n - 1));
	return (buffer);
}
