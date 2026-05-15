/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_m3_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 05:12:26 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/07 05:12:30 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_merle.h"
#include <stdlib.h>

void	*ft_m3_malloc(size_t n)
{
	void	*ptr;

	ptr = malloc(n);
	if (ft_m3_add(ptr))
		return (ptr);
	free(ptr);
	return (NULL);
}
