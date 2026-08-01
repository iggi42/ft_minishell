/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:15:39 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"
#include "libft_str.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*result;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	result = ft_str_alloc(size);
	if (result != NULL)
		ft_strlcpy(result, s, size + 1);
	return (result);
}
