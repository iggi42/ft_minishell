/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 23:41:32 by fkruger           #+#    #+#             */
/*   Updated: 2026/03/15 23:41:34 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"
#include <stdbool.h>
#include <stddef.h>

size_t	ft_str2l(const char *input, long *result)
{
	size_t	size;
	bool	sign;

	size = 0;
	sign = false;
	*result = 0;
	if (*input == '-')
	{
		size++;
		sign = !sign;
	}
	while (ft_isdigit(input[size]))
	{
		if (size >= (19 + sign))
			return (0);
		if ((*result * 10 - (input[size] - 48)) > *result)
			return (0);
		*result = *result * 10 - (input[size++] - 48);
	}
	if (!sign)
		*result *= -1;
	return (size);
}
