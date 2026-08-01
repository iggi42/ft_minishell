/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:31:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:07 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_str.h"
#include "libft_mem.h"

// returns the size of the substring
static size_t	ft_substr_len(const char *s, size_t start, size_t len)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start > s_len)
		return (0);
	if ((start + len) > s_len)
		return (s_len - start);
	return (len);
}

char	*ft_substr(const char *s, size_t start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	output_len;

	i = 0;
	output_len = ft_substr_len(s, start, len);
	if (output_len == 0)
		return (ft_calloc(1, sizeof(char)));
	result = ft_calloc(output_len + 1, sizeof(char));
	while (result != NULL && *(s + start + i) && i < len)
	{
		*(result + i) = *(s + start + i);
		i++;
	}
	return (result);
}
