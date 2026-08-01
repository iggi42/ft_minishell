/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:10:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_char.h"
#include "libft_str.h"
#include <stdbool.h>

static bool	ft_isspace(const char c)
{
	return (ft_strchr(" \f\n\r\t\v", c) != NULL);
}

int	ft_atoi(const char *nptr)
{
	char	*runner;
	int		sign;
	long	result;

	runner = (char *)nptr;
	while (ft_isspace(*runner))
		runner++;
	sign = 1;
	if (*runner == '-')
	{
		sign *= -1;
		runner++;
	}
	else if (*runner == '+')
		runner++;
	result = 0;
	while (ft_isdigit(*runner))
	{
		result = result * 10 + (*runner - 48);
		runner++;
	}
	return ((int)sign * result);
}
