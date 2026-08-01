/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_set_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 23:50:34 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_iol.h"
#include "libft_mem.h"

void	ft_fmt_set_c(t_iol_el *el, char c)
{
	el->buffer = ft_malloc(sizeof(char));
	if (el->buffer)
	{
		*(el->buffer) = c;
		el->size = sizeof(char);
		el->free = ft_iol_free_always;
	}
}
