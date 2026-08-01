/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:35:38 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:07 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_toa.h"
#include "libft_str.h"
#include "libft_mem.h"

char	*ft_ptoa_b(void *ptr, const char *alphabet)
{
	size_t	size;
	char	*result;

	size = ft_ptoa_bl(ptr, NULL, 0, alphabet);
	result = ft_str_alloc(size);
	if (size == ft_ptoa_bl(ptr, result, size, alphabet))
		return (result);
	ft_free(result);
	return (NULL);
}
