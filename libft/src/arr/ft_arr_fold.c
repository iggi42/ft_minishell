/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_fold.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:09:41 by fkruger           #+#    #+#             */
/*   Updated: 2026/03/09 17:10:54 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_arr_t.h"
#include <stddef.h>

void	*ft_arr_fold(t_arr arr, void *(*fold)(void *, t_arr_el *), void *acc)
{
	size_t	i;

	i = 0;
	while (*(arr + i))
		acc = fold(acc, *(arr + i++));
	return (acc);
}
