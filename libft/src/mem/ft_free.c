/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/07 03:53:44 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_merle.h"
#include <stdlib.h>

#ifdef M3_ENABLED

void	ft_free(void *ptr)
{
	ft_m3_free(ptr);
}
#else

void	ft_free(void *ptr)
{
	free(ptr);
}
#endif
