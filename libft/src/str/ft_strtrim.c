/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:28:48 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:07 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_str.h"

char	*ft_strtrim(char const *src, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	length;

	i = 0;
	while (*(src + i) != '\0' && ft_strchr(set, *(src + i)) != NULL)
		i++;
	start = i;
	i = 0;
	length = ft_strlen(src) - start;
	while (i < length && ft_strchr(set, *(src + start + length - i)) != NULL)
		i++;
	length -= i;
	return (ft_substr(src, start, length + 1));
}
