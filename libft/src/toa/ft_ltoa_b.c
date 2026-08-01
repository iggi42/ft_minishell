/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:07 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_toa.h"
#include "libft_str.h"
#include <limits.h>

char	*ft_ltoa_b(long nb, const char *alphabet)
{
	char	*result;
	size_t	len;

	len = ft_ltoa_bl(nb, NULL, 0, alphabet);
	result = ft_str_alloc(len);
	ft_ltoa_bl(nb, result, len, alphabet);
	return (result);
}
