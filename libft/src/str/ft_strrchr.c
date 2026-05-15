/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:30:47 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:07 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <limits.h>
#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*found;
	char	*runner;

	found = NULL;
	runner = (char *)s;
	while (*runner != '\0')
	{
		if (*runner == ((char)c))
			found = runner;
		runner++;
	}
	if (c == '\0')
		return (runner);
	else
		return (found);
}
