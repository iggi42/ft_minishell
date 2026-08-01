/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:35:38 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_merle.h"
#include <stdlib.h>

#ifdef M3_ENABLED

void	*ft_malloc(size_t size)
{
	return (ft_m3_malloc(size));
}
#else

void	*ft_malloc(size_t size)
{
	return (malloc(size));
}
#endif
