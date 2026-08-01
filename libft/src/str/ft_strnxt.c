/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnxt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 23:40:23 by fkruger           #+#    #+#             */
/*   Updated: 2026/03/15 23:40:24 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnxt(const char *s, int (*check)(int c))
{
	size_t	i;

	i = 0;
	while (*(s + i))
	{
		if (check((int)*(s + i)))
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
