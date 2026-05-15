/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 23:40:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/03/15 23:40:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

size_t	ft_str2d(const char *input, double *result)
{
	size_t	i[2];
	long	frac[2];

	i[0] = ft_str2l(input, &frac[0]);
	if (i[0] == 0 || *(input + i[0]) != '/')
		return (0);
	i[1] = ft_str2l(input + i[0] + 1, &frac[1]);
	if (i[1] == 0)
		return (0);
	*result = (double)frac[0] / frac[1];
	return (i[0] + i[1] + 1);
}
