/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:14:55 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_byte_t.h"
#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	t_byte	*ptr;

	i = 0;
	ptr = (t_byte *)s;
	while (s != NULL && i < n)
	{
		ptr[i] = (t_byte)c;
		i++;
	}
	return (s);
}
