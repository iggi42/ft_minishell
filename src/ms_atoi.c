/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:27:40 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:27:53 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_byte_t.h>
#include <stdbool.h>

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	invalid(char *str)
{
	if (!str || !*str)
		return (1);
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (*str < '0' || *str > '9')
		return (1);
	while (*str >= '0' && *str <= '9')
		str++;
	while (is_space(*str))
		str++;
	return (*str != '\0');
}

bool	ms_atoi_valid(char *str)
{
	return (!invalid(str));
}

t_byte	ms_atoi(char *str)
{
	int		sign;
	t_byte	result;

	sign = 1;
	result = 0;
	if (invalid(str))
		return (2);
	while (is_space(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}
