/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iol_elcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_iol.h"
#include "libft_str.h"

int	ft_iol_elcmp(const t_iol_el *el1, const t_iol_el *el2)
{
	int	buffer;

	if (el1 == el2)
		return (0);
	buffer = el1->size - el2->size;
	if (buffer == 0)
		return (ft_strncmp(el1->buffer, el2->buffer, el1->size));
	return (buffer);
}
