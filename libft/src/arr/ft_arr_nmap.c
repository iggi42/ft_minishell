/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:05:34 by fkruger           #+#    #+#             */
/*   Updated: 2026/03/09 17:05:36 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_arr.h"

t_arr	*ft_arr_nmap(t_arr input, size_t n, t_arr_el (*map)(t_arr_el el))
{
	t_arr	*result;
	size_t	i;

	if (input == NULL)
		return (NULL);
	result = ft_arr_new(n);
	i = 0;
	while (result != NULL && i < n)
	{
		result[i] = map(input[i]);
		i++;
	}
	return (result);
}
