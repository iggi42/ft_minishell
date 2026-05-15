/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:12:32 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_byte_t.h"
#include <stddef.h>

void	*ft_memchr(const void *s, const t_byte c, size_t n)
{
	if (n == 0)
		return (NULL);
	if (*(t_byte *)s == c)
		return ((void *)s);
	return (ft_memchr(s + 1, c, n - 1));
}
