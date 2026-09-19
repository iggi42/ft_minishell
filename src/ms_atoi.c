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

#include <libft_str.h>
#include <libft_byte_t.h>

static int	atoi_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	ms_atoi_prugel(char *digits, int neg)
{
	char	*max;
	size_t	len;

	len = 0;
	max = "9223372036854775807";
	while (*digits == '0')
		digits++;
	while (digits[len] >= '0' && digits[len] <= '9')
		len++;
	if (neg)
		max = "9223372036854775808";
	if (len > 19)
		return (1);
	if (len == 19 && ft_strncmp(digits, max, 19) > 0)
		return (1);
	return (0);
}

int	invalid(char *str)
{
	char	*digits;
	int		neg;

	if (!str || !*str)
		return (1);
	while (atoi_is_space(*str))
		str++;
	neg = (*str == '-');
	if (*str == '-' || *str == '+')
		str++;
	if (*str < '0' || *str > '9')
		return (1);
	digits = str;
	while (*str >= '0' && *str <= '9')
		str++;
	while (atoi_is_space(*str))
		str++;
	if (*str != '\0')
		return (1);
	return (ms_atoi_prugel(digits, neg));
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
	while (atoi_is_space(*str))
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
