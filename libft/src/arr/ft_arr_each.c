/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_each.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:20:49 by fkruger           #+#    #+#             */
/*   Updated: 2026/03/01 17:22:13 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_arr_t.h"
#include <stddef.h>

void	ft_arr_each(t_arr arr, void *(*apply)(void *))
{
	size_t	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (*((t_arr_el *)arr + i))
		(apply(*(arr + i)), i++);
}
