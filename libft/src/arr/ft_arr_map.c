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

t_arr	*ft_arr_map(t_arr input, t_arr_el (*map)(t_arr_el el))
{
	t_arr	*result;
	size_t	size;
	size_t	i;

	size = ft_arr_len(input);
	result = ft_arr_new(size);
	i = 0;
	while (input[i])
	{
		result[i] = map(input[i]);
		i++;
	}
	return (result);
}
