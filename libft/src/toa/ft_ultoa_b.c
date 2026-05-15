/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:07 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_toa.h"
#include "libft_str.h"

char	*ft_ultoa_b(unsigned long nb, const char *alphabet)
{
	size_t	size;
	char	*result;

	size = ft_ultoa_bl(nb, NULL, 0, alphabet);
	result = ft_str_alloc(size);
	ft_ultoa_bl(nb, result, size, alphabet);
	return (result);
}
