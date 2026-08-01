/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:17:10 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:07 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_str.h"
#include "libft_mem.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	size;
	char	*result;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = ft_calloc(size, sizeof(char));
	if (result != NULL)
	{
		ft_strlcpy(result, s1, size);
		ft_strlcat(result, s2, size);
	}
	return (result);
}
