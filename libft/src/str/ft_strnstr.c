/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:19:58 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:07 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_str.h"

static const char	*ft_strnstr_s(const char *big, size_t blen,
		const char *little, const size_t llen)
{
	char	*begin;
	size_t	dis;

	begin = ft_strchr(big, *little);
	if (begin == NULL)
		return (NULL);
	dis = begin - big;
	if (dis > blen)
		return (NULL);
	blen -= dis;
	if (llen > blen)
		return (NULL);
	if (ft_strncmp(begin, little, llen) == 0)
		return (begin);
	else
		return (ft_strnstr_s(begin + 1, blen - 1, little, llen));
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	llen;

	llen = ft_strlen(little);
	if (llen == 0)
		return ((char *)big);
	return ((char *)ft_strnstr_s(big, len, little, llen));
}
